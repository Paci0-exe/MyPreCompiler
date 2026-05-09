#include "enumHandler.h"
#include "variableHandler.h"
#include "variableUtils.h"

#include <stdio.h>
#include <string.h>


const char* ENUM_STRING = "enum";

const int ENDED_ENUM = 0;
const int MULTILINE_ENUM = 2;


int checkEnum(char* fin_name, char* line, int row, int flag) {
	
	// Const variables
	const char *ENUM_START = "{";
	const char *ENUM_END = "}";
	
	// Local variables
	// char **custom_data_types = get_custom_data_types();
	char *cpy = strdup(line);
	cpy = removeSpaces(cpy);
	int name_size = strlen(ENUM_STRING);

	char *name = "\0";

	// Caso 1. Nome all'inizio 
	char *start = strstr(cpy, ENUM_START);
	if (start) {
		name = strdup(cpy+name_size);
		int start_index = strcspn(name, ENUM_START);
		name[start_index] = '\0';
		if (strlen(name) > 0 ) handleVar(fin_name, name, row);
		cpy = start+1;	
	}
	
	// Caso 2. Nome alla fine
	char *end = strstr(cpy, ENUM_END);
	if (end) {
		end = removeSpaces(end);
		int end_index = strcspn(end, ";");
		name = end+1;
		name[end_index-1] = '\0';	
		if (strlen(name) > 0 ) handleVar(fin_name, name, row);
		if (start == NULL) return ENDED_ENUM;
	}
	
	
	if (*cpy == '\n') return MULTILINE_ENUM;
	
	if (flag == MULTILINE_ENUM) return multiLineEnum(fin_name, cpy, row);
	
	/* SingleLine: enum Name {VAL1, VAL2, ..., VALN}*/
	if (start && end) singleLineEnum(fin_name, start, row);
	
	/* Multiline Enum */
	else return multiLineEnum(fin_name, cpy, row);
	
	/* Dichiarazione: enum Type var = VALORE */
	/* enum || enum Eum var = VALORE */
	if (!start && !end) {
		if (strstr(cpy, "=") || strstr(cpy, ";")) return 0; // Dichiarazione enum
	}

	
	
	return 0;
}

/*
 * enum { var1, var2, var3 } Giorno;
 */
int singleLineEnum(char *fin_name, char *line, int row) {

	// Start sta puntando a '{'
	// con +1 punto all'inizio della
	// variabile presente (se esiste)
	char *start = ++line;

	// Calcolo la distanza tra '{' e '}'
	// se 0 non esiste alcuna variabile
	int size =  strcspn(start, "}");
	if (size == 0) return 0;
	
	// Estraggo la lista di variabili dall'enum
	char vars[size];
	int i = 0;
	while(i < size) vars[i++] = *start++;
	vars[i] = '\0';
	
	// Invio a controllo
	handleVars(fin_name, vars, row, true);
	
	return 0;
}
/*
 * enum nome {
 *	var1,
 *	var2,
 *	var3
 * }
 * OR
 * enum { var1,
 *	var2,
 *	var3
 * } name;
 */
int multiLineEnum(char* fin_name, char* line, int row) {

	handleVars(fin_name, line, row, true);
	 
	return MULTILINE_ENUM;
}

/* Non funziona */
char *getEnumName(char* line) {

	// Copio la riga
	char *cpy = strdup(line); 
	
	// Salto la parola "enum"
	char *name = strtok(cpy, " ");
	
	// Ottengo la parola dopo "enum"
	name = strtok(NULL, " ");
	
	/*
	 *NB: anche la funzione checkVariables
	 * elimina eventuali spazi MA bisogna
	 * comunque eliminarlo dato che il nome
	 * POTREBBE non essere presente all'inizio
	 * ma alla fine, dunque bisogna verificare che
	 * name != { (caso in cui il nome si trova alla fine
	*/
	name = ignoreSpaces(name);

	name = (*name != '{' && *name != ';') ? name :  "";
	
	return name;
}

