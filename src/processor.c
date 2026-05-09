#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "inputHandler.h"
#include "includeHandler.h"
#include "processor.h"
#include "stringCleaner.h"
#include "statsHandler.h"

/*
 * Inizializza le variabili per il
 * pre-processamento del file
*/
void start(handler *h) {
	
	// Input - Output
	FILE *fin = getInput(h);
	FILE *fout = getOutput(h);
	char *fin_name = h -> finName;
	
	// Core
	core(fin_name, fin, fout);
	
	// Post-processing
	fseek(fout, 0, SEEK_END);
	int out_dim = ftell(fout);
	addOutputFileStats(out_dim, -1);
	
	// Closing input - output
	closeInput(h);
	closeOutput(h);
}

/*
 * Funzione principale: iterna
 * sul file di input e, tramite la
 * funzione clearString, decide cosa
 * applicare alla stringa ottenuta.
*/
void core(char *fin_name, FILE* fin, FILE* fout) {

	const int MAX_LINE = 100;
	char line[MAX_LINE+2];
	
	int rows = 0;
	int out_rows = 0;
	
	// Cycling
	while (fgets(line, MAX_LINE, fin) != NULL) {
		rows++;
		out_rows++;
		clearString(fin_name, line, fout, rows);
		if (fputs(line, fout) == EOF) 
			perror("Errore durante la scrittura di un file\n");
	}
	// out_rows++; Non serve
	int dim = ftell(fin);
	
	// printf("[PROCESSOR] rows: %d, file: %s\n", rows, fin_name); 
	
	addInputFileStats(dim, rows, fin_name);
	addOutputFileStats(-1, out_rows);
	
	// Numero di righe sbagliati
	
}


void freeProcessor() {
	freeStringCleaner();
}
