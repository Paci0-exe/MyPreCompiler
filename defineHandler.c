#include "defineHandler.h"
#include "statsHandler.h"
#include "variableHandler.h"
#include "variableUtils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *DEFINE = "define";

void checkDefine(char *fin_name, char *line, int row) {

	// Aumento il contatore di variabili
	increaseVar();
	
	//printf("checking define: %s\n", line);
	
	// Duplica la stringa passata
	char *cpy = strdup(line);
	
	// Ignora il token "define"
	strtok(cpy, " ");
	
	// Ottieni la variabile
	char *token = strtok(NULL, " ");
	if(!checkVariableSyntax(custom_data_types, token))
		addError(fin_name, row);
		
}
/*
 * Aggiunge alla lista dei tipi custom
 * il tipo passato alla funzione.
 * Inoltre ne controlla la sintassi
 */
void addDataType(char *fin_name, char *newDataType, int row) {

	int size = 0;
	
	increaseVar();
	
	char *dataType = getDataType(newDataType);
	if (!checkVariableSyntax(custom_data_types, dataType)) {
		addError(fin_name, row);
		return;
	}
	
	// Se non è mai stato inizializzato, inizializzalo
	if(custom_data_types == NULL) custom_data_types = malloc(0);
	

	// Calcola la grandezza dell'array
	while (	custom_data_types[size] != NULL )
		size++;

	// Rialloca la memoria aggiungendo due spazi
	custom_data_types = realloc(custom_data_types, (size+2) * sizeof(char*));
	if (custom_data_types == NULL) {
		fprintf(stderr, "Errore durante la reallocazione di memoria \n");
		exit(1);
	}

	// Aggiungi il nuovo tipo di dato
	custom_data_types[size] = strdup(dataType);
	// Aggiungi NULL
	custom_data_types[size+1] = NULL;

}

/*
 * Ritorna l'ultima variabile scritta
 * prima del ';'.
*/
char *getDataType(char *line){


	char *cp = NULL;
	char *last = NULL;
	char *tmp = NULL;
	
	// Copying
	cp = strdup(line);
	if (cp == NULL) {
		fprintf(stderr, "Errore durante la copia di una stringa \n");
		exit(1);
	}
	
	// Tokenize
	char *token = strtok(cp, " ");
	do 
	{
		tmp = token;
		token = strtok(NULL, " ");
	} while(token != NULL && *token != '\n');
	
	// Salvo il penultimo valore
	last = strdup(tmp);
	
	// Removing ';'
	int last_char = strchr(last, ';') - last;
	if (last[last_char] == ';') last[last_char] = '\0';
	
	
	return last;
} 

