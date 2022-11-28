#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char real_psw[16];
typedef struct {
	char user[16];
	char psw[16];
	char cf[16];
	int auth;
}login;
int read_psw(){
	int fd=open("/dev/urandom");
	read(fd,real_psw,15);
	real_psw[15]=0;
}
int check_auth(){
	login a;
	a.auth=1;
	puts("--------LOGIN--------");
	puts("inserisci il tuo username");
	scanf("%s",a.user);
	puts("inserisci la tua password");
	scanf("%s",a.psw);
	a.auth=strcmp(a.psw,real_psw)==0;
	puts("inserisci il tuo codice fiscale");
	scanf("%s",a.cf);
	return a.auth;
}
int main(void){
	read_psw();
	int auth=check_auth();
	if(auth){
		puts("GOOD JOB");
		system("cat flag.txt");
	}

}