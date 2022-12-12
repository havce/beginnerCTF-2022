#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define DIM_VARIABLE 20

void stamp_flag(){
	 FILE *file = fopen("flag.txt", "r");
	    if (file == NULL) {
	        printf("Errore nell'apertura del file!\n");
	        return 0;
	    }

	    // leggi il file riga per riga e stampa il contenuto a video
	    char line[100];
	    while (fgets(line, 100, file) != NULL) {
	        printf("%s", line);
	    }

	    // chiudi il file
	    fclose(file);
}
int main(void){

	char name [DIM_VARIABLE];
	char psw[DIM_VARIABLE];
	do{
		puts("inserisci il tuo username:");
		fgets(name, DIM_VARIABLE, stdin);
	    name[strlen(name) - 1] = '\0';
		puts("Inserisci la tua password:");
		fgets(psw, DIM_VARIABLE, stdin);
	    psw[strlen(psw) - 1] = '\0';

	    if(strcmp(name,"admin")==0 && strcmp(psw ,"lmE5apcAiF")==0){
		   puts("LOGIN ESEGUITO ECCO LA TUA FLAG! ");
		   stamp_flag();
		   break;
	    } else{
	    	puts("credenziali errate ! ");
	    }
	}while(1);
return 0;
}
