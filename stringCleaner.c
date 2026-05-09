#include <string.h>

#include "includeHandler.h"
#include "commentHandler.h"
#include "variableHandler.h"
#include "statsHandler.h"
#include "enumHandler.h"
#include "stringCleaner.h"
#include "variableUtils.h"
#include "structHandler.h"
#include "defineHandler.h"


/*
Legge e interpreta la stringa
rilevando eventuali commenti,
variabili oppure #define.
La variabile flag viene utilizzata per
capire in che stringa ci troviamo, ad
esempio se ci troviamo dentro
ad un commento multilinea
*/

int flag = 0;
/*
 * FLAG VALUES:
 0 : NOTHING
 1 : MULTILINE_COMMENT
 2 : MULTILINE_ENUM
*/

void clearString(char* fin_name, char* line, FILE* fout, int row){
	
	char *subline;
	bool struct_or_enum = false;
	
	/* Flags */
	if (flag == MULTILINE_COMMENT)
		flag = eraseLine(line, "", END_MULTILINE_COMMENT);
	if (flag == MULTILINE_ENUM)
		flag = checkEnum(fin_name, line, row, MULTILINE_ENUM);
	if (flag == MULTILINE_STRUCT)
		flag = checkStruct(fin_name, line, row, MULTILINE_STRUCT);
	/* End flag section */
	
	/* Comment section */
	// Multiline comment
	subline = strstr(line, START_MULTILINE_COMMENT);
	if (subline != NULL) flag = eraseLine(subline, "", END_MULTILINE_COMMENT); 
	
	// Single line comment
	subline = strstr(line, START_COMMENT);
	if (subline != NULL) flag = eraseLine(subline, "", "\n");
	/* End comment section */
	
	/* Include section */
	subline = strstr(line, INCLUDE_STRING);
	if (subline != NULL) import(subline, fout);
	/* End include section */
	
	/* Enum section */
	subline = strstr(line, ENUM_STRING);
	if (subline != NULL) {
		flag = checkEnum(fin_name, subline, row, NOTHING); 
		struct_or_enum = true;
	}
	/* End enum section */
	/* Struct section */
	subline = strstr(line, STRUCT_STRING);
	if (subline != NULL) {
		flag = checkStruct(fin_name, subline, row, NOTHING); 
		struct_or_enum = true;
	}
	/* End struct section */
	
	/* Variables section */
	// N.B. Viene saltato se è stata già rilevata una struct
	// Rileva la definizione di una variabile
	subline = strstr(line, DEFINE);
	if(subline != NULL) checkDefine(fin_name, subline, row); 
	
	// Rilevata una definizione di un nuovo tipo
	// !DEVO RILEVARE CORRETTAMENTE LE TYPEDEF ENUM
	subline = strstr(line, TYPEDEF);
	if (subline != NULL && !struct_or_enum) {
		addDataType(fin_name, subline, row);
		// Non controllo una variabile
		// già controllata in addDataType
		return;
	}
	bool skip_declaration = (flag == 4);

	/* Variables section */
	// Rilevata una variabile standard in C e
	// rileva una variabile creata dall'utente
	if(!skip_declaration) findDeclarations(fin_name, line, row);
	/* End variables section */
}




void jumpSpaces(char** line) {
	while(**line == ' ' || **line == '\t' || **line == '\r') (*line)++;
}



void freeStringCleaner() {
	freeVariableHandler();
	freeStatsHandler();
}
