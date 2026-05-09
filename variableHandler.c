#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "variableUtils.h"
#include "variableHandler.h"
#include "defineHandler.h"
#include "statsHandler.h"


const char *TYPEDEF = "typedef";

char **custom_data_types;

char *ignoreTypes(char *line) {

	char *cpy = strdup(line);
	/* Trovo il [type] */
	const char *SPACE = " ";

	char *token_ptr;
	char *token = strtok_r(cpy, SPACE, &token_ptr);
	while(isAModifier(token)) token = strtok_r(NULL, SPACE, &token_ptr); // Skippa tutti i modificatori
	if (isAType(token) || isACustomType(custom_data_types, token)) return token_ptr;
	return NULL;
	
}

/* 
 * La funzione cerca una dichiarzione di variabili del tipo
 * [modifiers] [type] var1, ..., varn; ...
 * Una volta rilevata la invia alla funzione successiva (v. handleDeclarations)
*/
void findDeclarations(char *fin_name, char *line, int row) {
	
	char *cpy = strdup(line);
	cpy = ignoreSpaces(cpy);
	
	if (isAFunction(line)) return;
	if (isEndOfDeclaration(*cpy)) return;
	
	char *decl = ignoreTypes(cpy);
	if (decl != NULL) handleDeclarations(fin_name, decl, row, true);
	
}

/*
 * Questa funzione viene invocata quando si presenta una dichiarazione
 * di variabili del tipo: [modifiers] [type] var1, ..., varn;
 * anche multiple nella stessa riga.
 * La funzione suddivide la stringa in base ai ';' che trova e la
 * invia alla funzione successiva (v. handleVars)
*/

void handleDeclarations(char *fin_name, char *line, int row, bool type_founded) {


	char *cpy = strdup(line);

	char *decl_pointer;
	const char *DECL_SEPARATOR = ";";
	
	
	

	char *decls = strtok_r(cpy, DECL_SEPARATOR, &decl_pointer);
	do {
		decls = ignoreSpaces(decls);
		if (*decls == '\0') continue;
		//printf("[VariableHandler] dichiarazioni: %s\n", decls);
		handleVars(fin_name, decls, row, type_founded);
		
	} while ((decls = strtok_r(NULL, DECL_SEPARATOR, &decl_pointer))!= NULL);
	
}

/*
 * La funzione ha il compito di, data una dichiarazione del tipo
 * "[modifier] [type] var1, var2, ..., varn;"
 * 1. Rilevare i modificatori
 * 2. Rilevare il tipo (standard o custom)
 * 3. Rilevare le variabili ed inviare a controllo (v. handleVar)
*/
void handleVars(char *fin_name, char *vars, int row, bool type_founded) {

	

	// Variabili locali
	char *var_pointer;
	const char *VAR_SEPARATOR = ",";

	// Se non abbiamo trovato alcun tipo allora
	// dobbiamo ignorarli nella lettura della variabile
	char *cpy = strdup(vars);
	cpy = ignoreSpaces(cpy);
	if (!type_founded) cpy = ignoreTypes(cpy);
	

	// Inizio il ciclo delle variabili
	char *var = strtok_r(cpy, VAR_SEPARATOR, &var_pointer);
	do
	{
		// printf("[VariableHandler]\tvar: %s\n", var);
		if (*var == '\n') continue;
		var = ignoreSpaces(var);
		handleVar(fin_name, var, row);	
	} while((var = strtok_r(NULL, VAR_SEPARATOR, &var_pointer)) != NULL);
}

/*
 * Controlla la variabile passata alla funzione controllandone
 * 1. La sintassi
 * 2. Che non ci siano spazi come "sonoUna Variabile"
 * Inoltre aggiunge eventuali errori
 */
void handleVar(char *fin_name, char *line, int row) {

	// True sse la variabile è corretta
	bool isCorrect = false;
	
	// Copio la riga
	char *cpy = strdup(line);
	
	const char *SPACE_STRING = " ";
	printf("[VariableHandler] ---------------------\n");
	printf("[VariableHandler]variabile da controllare: %s\n", cpy);
	
	// Aumenta il contatore di variabili
	// presenti nella riga
	increaseVar();	
		 
	/* Se nella variabile è presente uno spazio
	 * e la sintassi è ancora corretta allora
	 * ci troviamo in una dichiarazione del tipo
	 * int variabile non valida;
	 * Mentre in casi come: int x = 0;
	 * non si genererà alcun errore.
	 */
	char *space_founded = strstr(cpy, SPACE_STRING);
	if (space_founded != NULL) {
		space_founded = removeSpaces(space_founded);
		char c = *space_founded;
		if (!isEndOfDeclaration(c)) addError(fin_name, row);
		return;
	}
	

	// Controllo la sintassi della variabile,
	// se scorretta allora viene creato un errore
	isCorrect = checkVariableSyntax(custom_data_types, cpy);
	if(!isCorrect){
		addError(fin_name, row);
	}
}


/*
 * Controlla se la riga passata
 * è una funzione, in modo specifico
 * controlla se nella riga ci sono
 * "(" e ")", se ci sono entrambi allora
 * la considera una funzione e torna true,
 * ritorna false altrimenti.
 */
bool isAFunction(const char *line){
	char *open_par, *closed_par;
	open_par = strstr(line, "(");
	closed_par = strstr(line, ")");
	if (open_par != NULL && closed_par != NULL) return true;
	return false;
}

char **get_custom_data_types() {
	return custom_data_types;
}


void freeVariableHandler() {

	// Controllo che sia stato inizializzato
	if (custom_data_types == NULL) return;
	
	// Libero tutti i suoi elementi
	int i = 0;
	while(custom_data_types[i] != NULL){
		free(custom_data_types[i]);
		i++;
	}
	
	// Rimuovo l'ultimo elemento ed
	// il puntatore stesso.
	free(custom_data_types);
}
