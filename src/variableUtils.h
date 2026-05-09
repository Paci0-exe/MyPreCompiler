#ifndef VARIABLESUTILS_H
#define VARIABLESUTILS_H

#include <stdbool.h>

extern char *TYPES[];			 // Array contenente tutti i tipi STANDARD in C
extern char *KEYWORDS[];		 // Array contenente tutte le parole chiavi STANDARD in C
extern char *MODIFIERS[];		 // Array contenente tutti i modificatori STANDARD in C
extern char END_OF_DECLARATION[];	 // Array contenente tutti i caratteri POTREBBERO rappresentare la fine di una dichiarazione

bool isAType(char*); 		 	 // Controlla se fa parte dei tipi standard di C
bool isACustomType(char**, char*);       // Controlla se fa parte dei tipi 'custom' creati dall'utente tramite typedef
bool isAModifier(char*); 		 // Controlla se è un modificatore
bool isAVariable(char**, char *);        // Controlla se è una variabile
bool isAKeyword(char*); 		 // Controlla se è una keyword
bool isIn(char **, char*);    	         // Controlla se la variabile è presente nell'array

bool isEndOfDeclaration(char);		 // Controlla se il carattere passato POTREBBE rappresentare la fine di una dichiarazione
bool checkVariableSyntax(char**, char*); // Controlla la sintassi della variabile

char* ignoreSpaces(char*);		 // Ignora gli spazi iniziali della stringa
char* removeSpaces(char*);		 // Rimuove qualsiasi spazio nella stringa
#endif
