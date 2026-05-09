#include "variableUtils.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// All C datatypes
char *TYPES[] = {
"char", "short", "int", "long", "float", "double", "signed", "_Bool", "bool", "void", NULL
};

// All C Keywords
char *KEYWORDS[] = {
"auto","break","case","continue","default","do","else","enum","for","goto","if","return",
"sizeof","struct","switch","union","while","_Alignof","_Generic","_Noreturn", "_Static_assert", NULL
};

// All C Modifiers
char *MODIFIERS[] = {  
    "register", "static", "extern", "_Thread_local", 
    "const", "volatile", "restrict", "_Atomic", "_Alignas", 
    "define", "typedef", "unsigned", "signed", "long", "short", 
    NULL  
};

char END_OF_DECLARATION[] = {'=', ';', ' ', '\n', '\0'};


/* Ritorna true sse la variabile è un modificatore */
bool isAModifier(char *line) {
	return isIn(MODIFIERS, line);
}

/* Ritorna true sse la variabile è una keyword*/
bool isAKeyword(char *line) {
	return isIn(KEYWORDS, line);
}

/* Ritorna true sse la variabile è un tipo standard */
bool isAType(char *line) {
	return isIn(TYPES, line);
}

/* Ritoran true sse la variabile appartiene a c_types */
bool isACustomType(char **c_types, char *line){
	return isIn(c_types, line);
}

/* Ritoran true sse la variabile è contenuta nell'array */
bool isIn(char *array[], char *var) {
	if (array == NULL) return false;
	var = ignoreSpaces(var);
	int i = 0;
	int size;
	char *type;
	do
	{
		type = strdup(array[i]);
		size = strlen(type);
		if (strncmp(var, type, size) == 0) {
			//printf("[VariableUtils] Sono uguali: %s %s\n", type, var); 
			if (isEndOfDeclaration(var[size])) return true;
			}
		i++;
	}while(array[i] != NULL);
	return false;	
}


/*
 * Ritorna true sse, la variabile passata è
 * una variabile, nel senso che:
 * NON è un TIPO di dato in C
 * NON è un MODIFICATORE in C
 * NON è un tipo custom(typedef e #define) in C
 */
bool isAVariable(char**c_types, char *var) {
	if (
	isAType(var)       ||
	isAModifier(var)   ||
	isACustomType(c_types, var) ||
	isAKeyword(var)
	) return false;
	
	return true;
}

bool checkVariableSyntax(char **c_types, char* var) {

	printf("[VariableUtils] checking syntax: %s\n", var);

	var = ignoreSpaces(var);
	if (!isAVariable(c_types, var)) return false;
	
	int i = 0; 
	bool more_pointers = true;
	bool first_char = true;
	
	// Controllo la sintassi finchè non trovo uno
	// di questi simboli che rappresentano
	// la fine di una variabile
	while(!isEndOfDeclaration(var[i])) 
	      {
		// Siamo arrivati alla fine della
		// variabile
		if(var[i] == ',') return true;

		// Pointers '*', '&'
		if (var[i] == '*' || var[i] == '&'){
			if(!more_pointers) return false;
			i++;
			continue;
		}
		// Da adesso non verranno ammessi puntatori
		more_pointers = false;
			
		
		// First char		
		if(first_char) {
			if(!isalpha(var[i]) && var[i] != '_') return false;
			first_char = false;
		}
		
		// Others chars
		if(!isalnum(var[i]) && var[i] != '_') return false;
		
		// Increse i
		i++;
	}
	// Non esiste alcuna variabile, ad esempio
	// int =  oppure int ;
	if ( i <= 0 ) return false;
	
	return true;
}

char* ignoreSpaces(char* var) {
	while(*var == ' ' || *var == '\t') var++;
	
	return var;
}

char *removeSpaces(char* var) {
	int count = 0;
	int size = strlen(var);
	int i;
	for(i = 0; i < size; i++)
		if(var[i] != ' ' && var[i] != '\t') 
			var[count++] = var[i];
	var[count] = '\0';

	return var;
}


bool isEndOfDeclaration(char c) {
	int i = 0;
	do {
		char end_of_decl = END_OF_DECLARATION[i++];
		if (c == end_of_decl) return true;
	}while(END_OF_DECLARATION[i-1] != '\0');
	
	return false;
}
