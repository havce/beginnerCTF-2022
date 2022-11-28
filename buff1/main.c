#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define buffsize 40

void win(){
	puts("good job");
	char flag[buffsize];
	FILE *f = fopen("flag.txt","r");
	fgets(flag,buffsize,f);
	printf(flag);
}

int main(void){
	setbuf(stdout, NULL);
  	setbuf(stdin, NULL);
  	setbuf(stderr, NULL);

	puts("can i know hour name to say hello?");
	char name[buffsize];
	gets(name);
	printf("hi %s !!\n"  , name );
	//win();
}