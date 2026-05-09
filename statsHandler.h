#ifndef STATSHANDLER_H
#define STATSHANDLER_H

/* Structs */
// Definisce la struttura di un
// errore delle variabili
typedef struct {
	char *filename; 	
	int riga;
} var_err;


// Definisce le statistiche
// di un file
typedef struct {
	char* filename;
	int dim;
	int rows;
} file_stats;


/* Variables */
extern int n_var;
extern int n_err_var;
extern int row_deleted_comment;
extern int included_files;
extern int row;
extern int fout_dim;
extern int fout_rows;

extern var_err **ve_list;
extern file_stats **fs_list;


/* Functions */
var_err *createVarErr(char*, int); 		// Crea e ritorna un oggetto var_err
file_stats *createFileStats(int, int, char*);   // Crea e ritorna un oggetto file_stats


void increaseVar();			// Numero di variabili controllate
void decreseVar();			// Decresce di 1 le variabili controllate
void addError(char*, int);		// Nome del file e riga di errore
void increaseDeletedComment();		// Numero di righe commentate cancellate
void increaseIncludedFiles();		// Numero di file inclusi
void addInputFileStats(int, int, char*);// Dimensione e numero di righe dei file input/include
void addOutputFileStats(int, int);	// Dimensione e numero di righe del file output

void freeStatsHandler(); 		// Removing all allocated memories
#endif
