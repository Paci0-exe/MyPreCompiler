#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>

// Definisce la struttura di un handler
typedef struct {
	bool wantInput;
	bool wantOutput;
	bool wantVerbose;
		
	char *finName;
	char *foutName;
	
	FILE *fin;
	FILE *fout;
} handler;


// Ritorna un nuovo handler
handler *newHandler(int argc, char *argv[]);


// Gestisce i vari parametri passati
// dallo stdin
void handleParams(int, char**, handler*);

// Ritorna l'input e l'output
// presenti in h
FILE *getInput(handler *);
FILE *getOutput(handler *);
void closeInput();
void closeOutput();
void closeFile(FILE*);

#endif
