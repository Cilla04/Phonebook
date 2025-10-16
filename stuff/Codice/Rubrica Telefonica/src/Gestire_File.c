#include "Gestire_File.h"

Rubrica importare_rubrica(FILE* file_rubrica, FILE* file_messaggi, FILE* file_errori)
{
	Rubrica rubrica;

	if(esiste_file(file_rubrica) == 0){ // Controlla se il file esiste
		fread(&rubrica, sizeof(Rubrica), 1, file_rubrica); // Se il file esiste, legge il contenuto del file nella rubrica
		stampare_messaggio(MESSAGGIO_RUBRICA_IMPORTATA, file_messaggi, file_errori); // Stampa un messaggio di successo dell'importazione della rubrica
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Se il file non esiste, stampa un messaggio di errore
	}
	return rubrica; // Restituisce la rubrica
}

void esportare_rubrica(Rubrica rubrica, FILE* file_rubrica, FILE* file_messaggi, FILE* file_errori)
{
	if(esiste_file(file_rubrica) == 0){ // Controlla se il file esiste
		fwrite(&rubrica, sizeof(Rubrica), 1, file_rubrica); // Se il file esiste, scrive il contenuto della struttura rubrica nel file
		stampare_messaggio(MESSAGGIO_RUBRICA_ESPORTATA, file_messaggi, file_errori); // Stampa un messaggio di successo dell'esportazione della rubrica
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Se il file non esiste, stampa un messaggio di errore
	}
	return;
}

bool esiste_file(FILE* file)
{
	bool errore;

	errore = 0; // Inizializza la variabile errore a 0, indicando che non ci sono errori inizialmente
	if(file == NULL){ // Se file è NULL, significa che il file non esiste o non può essere aperto
		errore = 1; // Imposta errore a 1 per indicare che c'è stato un problema con il file
	}
	return errore; // Restituisce il valore di errore, che sarà 1 se il file non esiste o 0 altrimenti
}
