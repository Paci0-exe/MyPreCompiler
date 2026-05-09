#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "statsHandler.h"

/* Struct functions */
/* Crea e ritorna un oggetto di tipo var_err */
var_err *createVarErr(char *filename, int riga) {
	var_err *v_err = malloc(sizeof(var_err));
	v_err -> filename = strdup(filename);
	v_err -> riga = riga;
	return v_err;
}


/* Crea e ritorna un oggetto di tipo file_stats */
file_stats *createFileStats(int dim, int rows, char* filename) {
	file_stats *fs = malloc(sizeof(file_stats));
	fs -> filename = strdup(filename);
	fs -> dim = dim;
	fs -> rows = rows;
	return fs;
}


/* Variables declarations */
int n_var = 0;
int n_err_var = 0;
int row_deleted_comment = 0;
int included_files = 0;
int row = 0;

int fout_dim = 0;
int fout_rows = 0;

var_err **ve_list = NULL;
file_stats **fs_list = NULL;



/* Function implementation */
void increaseVar() {
	n_var++;
}

void decreseVar() {
	n_var--;
}

void increaseDeletedComment() {
	row_deleted_comment++;
}

void increaseIncludedFiles() {
	included_files++;
}

void addOutputFileStats(int dim, int rows) {
	if (dim != -1)
		fout_dim = dim;
	if (rows != -1) 
		fout_rows += rows;
}


void addInputFileStats(int dim, int rows, char* filename) {

	file_stats *fs = createFileStats(dim, rows, filename);
	
	if (fs_list == NULL) fs_list = malloc(0);
	
	int size = 0;
	while(fs_list[size] != NULL) size++;
	
	fs_list = realloc(fs_list, (size+2) * sizeof(file_stats*));
	
	fs_list[size] = fs;
	fs_list[size+1] = NULL;
}


void addError(char *filename, int riga) {
	
	printf("[StatsHandler] Errore rilevato\n");
	
	char *dupFilename = strdup(filename);
	var_err *v_err = createVarErr(dupFilename, riga);
	
	//printf("created: %s %d\n", v_err -> filename, v_err -> riga);

	if (n_err_var == 0) ve_list = malloc(0);
	
	ve_list = realloc(ve_list, (n_err_var+1) * sizeof(var_err*));
	
	ve_list[n_err_var] = v_err;
	
	n_err_var++;
}


void freeStatsHandler() {
	// Controllo che sia stato inizializzato
	if(n_err_var == 0) return;
	
	// Libero tutti i suoi elementi
	int i;
	for(i = 0; i < n_err_var; i++)
		free(ve_list[i]);

	// Libero l'ultimo elemento ed
	// il puntatore stesso
	free(fs_list);
}
