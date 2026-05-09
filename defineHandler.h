#ifndef DEFINEHANDLER_H
#define DEFINEHANDLER_H

extern const char *DEFINE;

void addDataType(char*, char*, int);	// Aggiunge un nuovo tipo
void checkDefine(char*, char*, int);	// Controlla #define
char *getDataType(char*);		// Ottiene il nome del typedef

#endif
