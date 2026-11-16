#ifndef GESTIRE_SCHERMO_H_
#define GESTIRE_SCHERMO_H_

#include <windows.h>

#include "Globali.h"
#include "Gestire_Tipi.h"
#include "Gestire_File.h"

// Operazione che gestisce il cursore sullo schermo
void gotoXY(int x, int y);
// Operazione che sovrascrive zone dello schermo con gli spazi
void pulire_schermata(int riga_inizio, int colonna_inizio, int riga_fine, int colonna_fine);
// Operazione che stampa a video da file
void stampare_interfaccia(FILE* file, FILE* file_errori);
void stampare_riga(int riga_desiderata, FILE* file, FILE* file_errori);
// Operazione che stampa a video errori da file
void stampare_errore(int errore, FILE* file_errori);
// Operazione che stampa a video messaggi da file
void stampare_messaggio(int messaggio, FILE* file_messaggi, FILE* file_errori);
// Operazione che pulisce il buffer per evitare errori di input
void pulire_stdin();
void pulire_buffer_input(char* stringa);

#endif /* GESTIRE_SCHERMO_H_ */
