#include <stdio.h>
#include <stdlib.h>

void print_banner() {
  puts("  ,,                                                  ");
  puts("`7MM           mm     mm                              ");
  puts("  MM           MM     MM                              ");
  puts("  MM  ,pW\"Wq.mmMMmm mmMMmm .gP\"Ya `7Mb,od8 `7M'   `MF'");
  puts("  MM 6W'   `Wb MM     MM  ,M'   Yb  MM' \"'   VA   ,V  ");
  puts("  MM 8M     M8 MM     MM  8M\"\"\"\"\"\"  MM        VA ,V   ");
  puts("  MM YA.   ,A9 MM     MM  YM.    ,  MM         VVV    ");
  puts(".JMML.`Ybmd9'  `Mbmo  `Mbmo`Mbmmd'.JMML.       ,V     ");
  puts("                                              ,V      ");
  puts("                                           OOb\"       ");
}

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

long long get_random() {
  long long result = 0;

  // One can never be sure with all these
  // hackers hanging around...
  for (int i = 0; i < 1000; i++) {
    result += (long long)rand();
  }

  return result;
}

int main() {
  long long guess = 0;
  FILE* flag = NULL;
  char buf[128];

  setup();
  print_banner();

  puts("Welcome to the havce lottery!");
  puts("Guess the magic number and win a flag.");

  long long extraction = get_random();
  printf("Insert your guess: ");
  scanf("%lld", &guess);

  if (guess != extraction) {
    puts("Your prediction was wrong. Try again another time. Bye!");
    return EXIT_FAILURE;
  }
  
  flag = fopen("flag.txt", "r");
  if (!flag) {
    perror("fopen");
    return EXIT_FAILURE;
  }
  
  char *f = fgets(buf, 128, flag);
  if (!f && ferror(flag)) {
    fprintf(stderr, "Couldn't read file flag.txt. Contact the admins.");
    return EXIT_FAILURE;
  }
  
  printf("Congrats! Here's your flag: %s.", buf);
  return EXIT_SUCCESS;
}
