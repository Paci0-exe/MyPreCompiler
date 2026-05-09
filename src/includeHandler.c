#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "includeHandler.h"
#include "inputHandler.h"
#include "stringCleaner.h"
#include "processor.h"
#include "statsHandler.h"


const char *INCLUDE_STRING = "#include";
const char *INCLUDE_TYPES[] = {"<>", "\"\""};


/*
 * Importa nel file "fout" il file
 * cui nome è scritto nella stringa
 * "line".
*/
void import(char *line, FILE *fout) {
	
	char *filename = getImportName(line);
	FILE *fin = fopen(filename, "r");
	if (fin == NULL) {
		fprintf(stderr, "Errore durante la lettura del file %s \n", filename);
		exit(1);
	}

	increaseIncludedFiles();
	core(filename, fin, fout);
}


/*
 * Estrae il nome del file dalla 
 * stringa passata in input
*/
char *getImportName(char *line) {
	// Mi calcolo la lunghezza dell'array
	// che contiene i vari simboli di inclusione
	int size = sizeof(INCLUDE_TYPES) / sizeof(char*);
	
	int const FIRST = 0;
	int const LAST = 1;
	
	// Li itero uno alla volta
	for (int i = 0; i < size; i++){
		// Prendo il simbolo di inclusione i-esimo
		char *include = strdup(INCLUDE_TYPES[i]);
		// Controllo se fa parte della stringa
		char *first_include = strchr(line, include[FIRST]);
		// Se non ne fa parte continua il ciclo
		if (first_include == NULL) continue;
		
		// Se ne fa parte allora incrementa
		// di uno il puntatore affinchè escluda
		// il simbolo di inclusione trovato
		first_include++;
		
		// Cerca il secondo simbolo di inclusione
		char *second_include = strchr(first_include, include[LAST]);
		// Se non lo trova interrompi il ciclo:
		// dichiarazione non valida
		if (second_include == NULL) break;
		
		// Calcolo la lunghezza tra i due simboli
		int size = second_include - first_include;
		// Estraggo il nome del file
		char *filename = strndup(first_include, size);
		// Salto l'include nella riga
		// passata alla funzione
		strcpy(line, second_include+1);
		return filename;
			
	}
	perror("Errore nella dichiarazione dell'include \n");
	exit(1); 
}
