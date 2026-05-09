#include "variableHandler.h"
#include "variableUtils.h"
#include "structHandler.h"

#include <stdio.h>
#include <string.h>


// Global flags
const int ENDED_STRUCT = 0;
const int MULTILINE_STRUCT = 3;
const int ENDED_SINGLE_LINE_STRUCT = 4;

// Global struct name
const char* STRUCT_STRING = "struct";

/*
 * La funzione cerca il nome della struct
 * e ne verifica la correttezza.
 * Le variabili al suo interno vengono normalmente
 * rilevate dallo stringCleaner.
 */
int checkStruct(char *fin_name, char *line, int row, int flag) {
	
	// Const variables
	const char *STRUCT_START = "{";
	const char *STRUCT_END = "}";
	
	// Local variables
	// char **custom_data_types = get_custom_data_types();
	char *cpy = strdup(line);
	cpy = removeSpaces(cpy);
	int name_size = strlen(STRUCT_STRING);


	// Caso 1. Nome all'inizio 
	char *start = strstr(cpy, STRUCT_START);
	if (start) {
		char *name = strdup(cpy+name_size);
		int start_index = strcspn(name, STRUCT_START);
		name[start_index] = '\0';
		if (strlen(name) > 0 ) handleVar(fin_name, name, row);
	}
	
	// Caso 2. Nome alla fine
	char *end = strstr(cpy, STRUCT_END);
	int end_index = 0;
	if (end) {
		end = removeSpaces(end);
		char *name = end+1;
		end_index = strcspn(name, ";");
		name[end_index] = '\0';
		if (strlen(name) > 0 ) handleVar(fin_name, name, row);	
		if (!start) return ENDED_STRUCT;
	}
	
	if (start && end) return singleLineStruct(fin_name, line, row, STRUCT_START, STRUCT_END);
	
	// La struct non è termianta
	// finchè non troviamo una fine "}"
	return MULTILINE_STRUCT;
}

int singleLineStruct(char *fin_name, char *line, int row, const char *STRUCT_START, const char *STRUCT_END) {
	
	char *cpy = strdup(line);
	
	char *start = strstr(cpy, STRUCT_START);
	start++;
	
	int end_index = strcspn(start, STRUCT_END);
	
	start[end_index] = '\0';
	
	// printf("[StructHandler] start: %s\n", start);
	
	handleDeclarations(fin_name, start, row, false);
	
	return ENDED_SINGLE_LINE_STRUCT;
}


