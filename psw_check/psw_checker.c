#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 20

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
}

void print_flag() {
  char *flag = getenv("FLAG");
  if (flag == NULL) {
    printf("Error! If you see this error, please contact the admin.");
    return;
  }

  printf("Your flag is: %s\n", flag);
}

int main(void) {
  char name[BUF_LEN];
  char psw[BUF_LEN];
  setup();

  do {
    puts("Inserisci il tuo username:");
    fgets(name, BUF_LEN, stdin);

    name[strlen(name) - 1] = '\0';

    puts("Inserisci la tua password:");
    fgets(psw, BUF_LEN, stdin);

    psw[strlen(psw) - 1] = '\0';

    if (strcmp(name, "admin") == 0 && strcmp(psw, "lmE5apcAiF") == 0) {
      puts("LOGIN ESEGUITO ECCO LA TUA FLAG! ");
      print_flag();
      break;
    }

    puts("Credenziali errate ! ");
  } while (1);

  return 0;
}
