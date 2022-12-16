#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_LEN 256

typedef struct {
  char username[24];
  char password[64];
} User;

// Nothing to see here.
void setup() {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

void print_banner() {
  puts("  _______   _______   ______    ______    ______  ");
  puts(" /       | /       | /      \\  /      \\  /      \\ ");
  puts("/$$$$$$$/ /$$$$$$$/ /$$$$$$  |/$$$$$$  |/$$$$$$  |");
  puts("$$      \\ $$ |      $$ |  $$ |$$ |  $$ |$$    $$ |");
  puts(" $$$$$$  |$$ \\_____ $$ \\__$$ |$$ |__$$ |$$$$$$$$/ ");
  puts("/     $$/ $$       |$$    $$/ $$    $$/ $$       |");
  puts("$$$$$$$/   $$$$$$$/  $$$$$$/  $$$$$$$/   $$$$$$$/ ");
  puts("                              $$ |                ");
  puts("                              $$ |       by havce ");
  puts("                              $$/      v1.0-final ");
  puts("");
  puts("Welcome to the scope service by havce!");
  puts("A SaaS CLI service where you can securely store your oscilloscope");
  puts("measurements in a safe(tm) fashion.");
  puts("");
}

int read_details(User *user) {
  printf("Username: ");
  if (!fgets(user->username, sizeof(user->username), stdin) && ferror(stdin)) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }

  // Remove trailing newlines.
  user->username[strcspn(user->username, "\n")] = '\0';

  // We don't want empty usernames.
  if (strnlen(user->username, sizeof(user->username)) == 0) {
    return 0;
  }

  printf("Password: ");
  if (!fgets(user->password, sizeof(user->password), stdin) && ferror(stdin)) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }

  // Remove trailing newlines.
  user->password[strcspn(user->password, "\n")] = '\0';

  return 1;
}

// No path traversals, please.
void sanitize_name(char *buf, size_t size) {
  for (int i = 0; (i < size) || buf[i] == 0; i++) {
    if ((buf[i] == '.') || (buf[i] == '/')) {
      buf[i] = '-';
    }

    // Even on Windows. Even if this program is non-portable.
    if (buf[i] == '\\') {
      buf[i] = '-';
    }
  }
}

// Given a ptr to User struct, return a path to the
// relative, cleaned up, user file. Needs to be free'd
// after use, by the user.
char *get_user_path(User *user) {
  char *prefix = "./users/";
  size_t len = strlen(prefix) + sizeof(user->username);

  // Since calloc zeroes memory, we (try to) mitigate UAFs, should
  // there be any.
  char *buf = calloc(1, len + 1);
  if (buf == NULL) {
    perror("calloc");
    exit(EXIT_FAILURE);
  }

  // We don't want path traversals.
  sanitize_name(user->username, sizeof(user->username));

  // Hacky hack to avoid buffer overflows.
  // Username pippo gets translated to a path ./users/pippo.
  if (snprintf(buf, len, "%s%s", prefix, user->username) < 0) {
    perror("snprintf");
    exit(EXIT_FAILURE);
  }

  return buf;
}

// Implements user registration.
int regis(User *user) {
  char *path = NULL;
  FILE *file = NULL;
  int res = 0;

  if (!read_details(user)) {
    puts("Invalid details");
    goto cleanup;
  }

  path = get_user_path(user);

  file = fopen(path, "w+x");
  if (file == NULL) {
    switch (errno) {
    case EEXIST:
      printf("User %s already exists.\n", user->username);
      goto cleanup;
    case ENOENT:
      puts("Directory not found. Have you checked if users/ directory exists?");
    }

    perror("fopen");
    exit(EXIT_FAILURE);
  }

  if (!fputs(user->password, file) && ferror(file)) {
    perror("fputs");
    exit(EXIT_FAILURE);
  }
  res = 1;

cleanup:
  if (file != NULL)
    fclose(file);

  if (path != NULL)
    free(path);

  return res;
}

// Implements user login.
int login(User *user) {
  char buf[BUF_LEN];
  char *path = NULL;
  FILE *file = NULL;
  int auth = 0;

  if (!read_details(user)) {
    puts("Invalid details");
    return 0;
  }

  path = get_user_path(user);

  // Open user file read only.
  file = fopen(path, "r");
  if (file == NULL) {
    if (errno == ENOENT) {
      printf("Username %s not found\n", user->username);
      goto cleanup;
    }

    perror("fopen");
    exit(EXIT_FAILURE);
  }

  // Read the password.
  if (!fgets(buf, sizeof(buf), file) && ferror(file)) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }

  // Check if password is correct.
  auth = strncmp(user->password, buf, BUF_LEN) == 0;

cleanup:
  // Cleanup.
  if (file != NULL)
    fclose(file);

  if (path != NULL)
    free(path);

  return auth;
}

// Implements change password.
int change_pwd(User *user) {
  char old_password[BUF_LEN];
  char buf[BUF_LEN];
  FILE *file = NULL;
  char *path = NULL;
  int res = 0;

  // Clear buffers on the stack.
  memset(old_password, 0, BUF_LEN);
  memset(buf, 0, BUF_LEN);

  printf("Username: ");
  if (!fgets(user->username, sizeof(user->username), stdin) && ferror(stdin)) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }
  user->username[strcspn(user->username, "\n")] = '\0';

  if (strnlen(user->username, sizeof(user->username)) == 0) {
    puts("Invalid username");
    goto cleanup;
  }

  path = get_user_path(user);

  file = fopen(path, "r");
  if (file == NULL) {
    if (errno == ENOENT) {
      printf("User %s does not exist.\n", user->username);
      goto cleanup;
    }

    perror("fopen");
    exit(EXIT_FAILURE);
  }

  if (!fgets(old_password, BUF_LEN, file) && ferror(file)) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }

  printf("Old password: ");
  if (!fgets(buf, BUF_LEN, stdin) && ferror(stdin)) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }

  printf("New password: ");
  if (!fgets(user->password, sizeof(user->password), stdin) && ferror(stdin)) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }

  // Remove trailing newlines.
  buf[strcspn(buf, "\n")] = '\0';
  old_password[strcspn(old_password, "\n")] = '\0';
  user->password[strcspn(user->password, "\n")] = '\0';

  // Check if user knows the old password.
  if (strncmp(old_password, buf, strlen(buf)) != 0) {
    puts("Old password is wrong!");
    goto cleanup;
  }

  // Reuse buf buffer.
  snprintf(buf, BUF_LEN, "echo -n \"%s\" > %s", user->password, path);
  res = system(buf) == 0;

cleanup:
  if (file != NULL)
    fclose(file);

  if (path != NULL)
    free(path);

  return res;
}

void print_menu() {
  puts("1) Login.");
  puts("2) Register.");
  puts("3) Change password.");
  puts("4) Print version.");
  puts("5) Exit.");
  printf("> ");
}

int read_int() {
  char buf[8];

  if (!fgets(buf, sizeof(buf), stdin)) {
    perror("fgets");
    exit(EXIT_FAILURE);
  }

  return atoi(buf);
}

void print_version() { puts("Version v1.0-final."); }

int check_admin(User *user) {
  return strncmp(user->username, "admin", sizeof(user->username)) == 0;
}

void show_list(User* user) {
  printf("Reading 1: recorded on 28-11-22 by %s.\n", user->username);
  puts("Reading 2: made on 1-12-22 by admin.");
}

void user_menu(User *user) {
  char buf[BUF_LEN];
  do {
    if (check_admin(user)) {
      printf("# ");
    } else {
      printf("$ ");
    }

    if (!fgets(buf, BUF_LEN, stdin) && ferror(stdin)) {
      perror("fgets");
      exit(EXIT_FAILURE);
    }
    buf[strcspn(buf, "\n")] = '\0';

    if (strncmp(buf, "exit", BUF_LEN) == 0) {
      printf("Good-bye %s!\n", user->username);
      return;
    } else if (strncmp(buf, "whoami", BUF_LEN) == 0) {
      printf("%s\n", user->username);
      continue;
    } else if (strncmp(buf, "list", 4) == 0) {
      show_list(user);
      continue;
    }

    printf("error: Elon has disabled the %s microservice.\n", buf);

  } while (1);
}

void menu() {
  int choice = 0;
  User *user = calloc(1, sizeof(User));
  if (user == NULL) {
    perror("calloc");
    exit(EXIT_FAILURE);
  }

  do {
    print_menu();
    choice = read_int();
    switch (choice) {
    case 1:
      if (!login(user)) {
        puts("Login failed. Please retry.");
        break;
      }
      puts("Logged in successfully!");
      user_menu(user);
      break;
    case 2:
      if (!regis(user)) {
        puts("Registration failed.");
        break;
      }
      printf("Successfully registered user %s.\n", user->username);
      user_menu(user);
      break;
    case 3:
      if (!change_pwd(user)) {
        puts("Failed to change password. Retry.");
        break;
      }
      puts("You can now login with the new password.");
      break;
    case 4:
      print_version();
      break;
    case 5:
      break;
    default:
      puts("Invalid choice. Try again.");
    }
    puts("");
  } while (choice != 5);
  
  // Free user, even if we're heading to bed.
  free(user);
}

int main() {
  setup();
  print_banner();

  menu();
}
