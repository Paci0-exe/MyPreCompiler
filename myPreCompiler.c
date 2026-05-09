#include "inputHandler.h"
#include "processor.h"
#include "statsHandler.h"

void printStats();
void freeMyPreCompiler();

int main(int argc, char *argv[]) {
	

	// Pre-processing
	handler *h = newHandler(argc, argv); // Creo e gestisco l'input dalla shell
	
	// Processing
	start(h);
	
	// Post-processing
	printStats(h);
	
	// Removing allocated memories
	freeMyPreCompiler();
	
	
	return 0;
}

void printStats(handler *h) {
	if (!h -> wantVerbose) return;
	
	fprintf(stderr, "-------------------\n");
	fprintf(stderr, "Statistiche: \n");
	fprintf(stderr, "Variabili controllate: %d\n", n_var);
	fprintf(stderr, "Numero di errori rilevati: %d\n", n_err_var);
	fprintf(stderr, "Numero di righe commentate eliminate: %d\n", row_deleted_comment);
	fprintf(stderr, "Numero di file inclusi: %d\n", included_files);
	fprintf(stderr, "Numero di righe del file di output: %d\nDimensione del file di output: %dbytes\n", fout_rows, fout_dim);
	
	int i = 0;
	file_stats *fs;
	while(fs_list[i] != NULL){
		fs = fs_list[i];
		fprintf(stderr, "Dimensione input/include del file %s: %dbytes, numero di righe: %d\n", fs->filename, fs->dim, fs->rows);
		i++;
	}
	
	var_err *ve;
	for (i = 0; i < n_err_var; i++)
	{
		ve = ve_list[i];
		fprintf(stderr, "Errore nel file: %s in riga %d\n", ve -> filename, ve -> riga);	
	}
	
	fprintf(stderr, "-------------------\n");
} 

void freeMyPreCompiler() {
	freeProcessor();
}
