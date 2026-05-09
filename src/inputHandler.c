#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inputHandler.h"

/*
La struct rappresenta la versione
"lunga" dei parametri, se hanno bisogno
di argomenti opzionali/obbligatori, e qual è
la loro versione 'ridotta'
*/
struct option long_options[] = {
	{"in", required_argument, NULL, 'i'},
	{"out", required_argument, NULL, 'o'},
	{"verbose", no_argument, NULL, 'v'},
	{0, 0, 0, 0}
};

/*
Rappresenta la versione ridotta dei parametri
dove nome_parametro: significa che il parametro
necessita di un input
*/
const char *short_options = "i:o:v";

/*
Crea e ritorna un nuovo handler in base
ai parametri passati dallo stdin.
*/
handler *newHandler(int argc, char *argv[]) {
	handler *h = malloc(sizeof(handler));
	h -> wantInput = false;
	h -> wantOutput = false;
	h -> wantVerbose = false;
	h -> finName = argv[1];
	h -> foutName = "";
	h -> fin = NULL;
	h -> fout = NULL;
	
	handleParams(argc, argv, h);
	return h;
}


/*
Gestisce i vari parametri passati andando
ad aggiornare l'handler.
*/
void handleParams(int argc, char *argv[], handler *h) {
	// Pre-condition
	if (argc <= 1) {
			printf("Non è stato inserito alcun file da pre-processare \n");
		exit(0);
	}

	int opt;
	while((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {	
		switch (opt) {
			
			case 'i':
				h-> wantInput = true; h -> finName = optarg;
				break;
			case 'o':
				h -> wantOutput = true; h -> foutName = optarg;
				break;
			case 'v':
				h -> wantVerbose = true;
				break; 	
			default:
				exit(1);	
		}
	}
	
}

FILE *getInput(handler *h) {
	FILE *f = fopen(h->finName, "r");
	if (f == NULL) {
		perror("Errore durante l'apertura di uno dei file di input");
		exit(1);
	}
	h -> fin = f;
	return f;
}

FILE *getOutput(handler *h) {
	char *out = h -> foutName;
	if(strcmp(out, "") == 0) {
		return stdout;
	}
	
	FILE *f = fopen(out, "w+");
	if (f == NULL) {
		perror("Errore durante l'apertura del file di output");
		exit(1);
	}
	h -> fout = f;
	return f;
}

void closeInput(handler *h) {
	FILE *fin = h -> fin;
	closeFile(fin);
	h -> fin = NULL;
}

void closeOutput(handler *h) {
	FILE *fout = h -> fout;
	closeFile(fout);
	h -> fout = NULL;
}

void closeFile(FILE *f) {
	if (f != NULL && fclose(f) != 0)
	{
		perror("Errore durante la chiusura di un file");
		exit(1);
	}
}

