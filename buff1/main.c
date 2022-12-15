#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 64

void win() {
  puts("Well done! Here's a gift for you ");
  char flag[BUF_SIZE];

  int fd = open("./flag.txt", O_RDONLY);
  read(fd, flag, BUF_SIZE - 1);
  flag[BUF_SIZE - 1] = '\0';

  write(1, flag, BUF_SIZE);
}

int main(void) {
  setbuf(stdout, NULL);
  setbuf(stdin, NULL);
  setbuf(stderr, NULL);

  puts("Hey, what's your name?");
  char name[BUF_SIZE];

  gets(name);
  printf("Hi %s! Hope you're doing well.\n", name);
}