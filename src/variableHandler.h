#ifndef VARIABLEHANDLER_H
#define VARIABLEHANDLER_H

#include <stdbool.h>


extern char **custom_data_types;

extern const char *TYPEDEF;
extern const char *DEFINE;

/*
 * Ho bisogno di tre cose principali:
 * 1. Stesso dato, una o più variabili: int a, b, c;
 * 2. Controllo su sintassi: var; (o meglio assenza di dato)
 * 3. Tanti dati, tante variabili: int a; int b; int c;
*/

/*
 * IDEAS:
 * int a, b, c; float b; c_var asd;
 * 1. Suddivido per ogni ";"
 * 2. Suddiviso per ogni ","
 * 3. Controllo la sintassi.
*/

char *ignoreTypes(char*);
void findDeclarations(char*, char*, int);
void handleDeclarations(char*, char*, int, bool);
void handleVars(char*, char*, int, bool);
void handleVar(char*, char*, int);

char **get_custom_data_types();
bool isAFunction(const char*);

void freeVariableHandler();

#endif
