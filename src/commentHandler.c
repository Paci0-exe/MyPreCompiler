 #include <string.h>
 #include <stdio.h>
 
#include "commentHandler.h" 
#include "statsHandler.h"



const int NOTHING = 0;
const int MULTILINE_COMMENT = 1;
const char *END_MULTILINE_COMMENT = "*/";
const char *START_MULTILINE_COMMENT = "/*";
const char *START_COMMENT = "//"; 



/*
 * Passata una stringa 'main', una stringa di 'inzio' 
 * e una stringa di 'file', cancella nella stringa 'main'
 * da 'inizio' a 'fine'.
 * Se la stringa di inzio è vuota ("") allora verrà
 * considerata l'intera stringa.
 * Se la stringa di 'fine' non viene trovata viene
 * semplicemente cancellata la stringa fino a \n (non compreso).
 * 
 * Ritorna:
 * -1: Non è stato cancellato nulla
 * 0: Non è stata trovata la stringa di 'fine'
 * 1: è stata trovata la stringa di 'fine'
 */
int eraseLine(char *line, const char *start, const char *end) {
	// Ottengo la sottostringa che inizia da 'start'
	char *subline = strstr(line, start); 
	
	// Lunghezza della stringa end
	const int endLength = strlen(end);
	
	// Una volta trovata la stringa di 'fine',
	// se esiste, la variabile incomincerà
	// a decrescere. Una volta arrivata a 0 ritorna 1
	// che sta ad indicare che la stringa è stata
	// cancellata fino alla stringa di 'fine'
	int lastWords = endLength;
	
	// Se la stringa di inizio è vuota
	// allora viene presa in considerazione
	// l'intera stringa
	if(strncmp(start, "", 2) == 0) subline = line;
	
	// Se esiste la stringa 'inizio'
	// nella stringa
	if (subline != NULL) {
		// Aumento il contatore di righe
		// di commento eliminate
		increaseDeletedComment();
		// Cicla sulla sotto stringa
		for(int i = 0; i < strlen(subline); i++) { 
			// Se l'elemento che sto per cancellare è uguale
			// alla stringa di 'fine' allora mi dovrò fermare
			// dopo aver cancellato la stringa di 'fine'
			// Se 'fine' = '\n' allora la funzione ritorna 0
			// non appena rileva \n.
			if (strncmp(subline+i, end, endLength) == 0 || lastWords < endLength) {
				lastWords--;
			}
			// Cancella il carattere i-esimo
			// solo se non è \n
			if(subline[i] != '\n') subline[i] = ' ';
			if (lastWords == 0) return 0;
		}
		return 1;
	}
	return -1;
}

