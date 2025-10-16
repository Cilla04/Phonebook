#ifndef RICERCARE_CONTATTO_H_
#define RICERCARE_CONTATTO_H_

#include "Globali.h"
#include "Gestire_Tipi.h"
#include "Gestire_Schermo.h"
#include "Gestire_File.h"

// Operazione ricercare contatto e visualizzarlo con le varie scelte effettuate dall'utente
void ricercare_contatto(Rubrica rubrica, FILE* interfaccia_ricercare_contatto, FILE* interfaccia_ricercare_contatto_stato, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori);
int scegliere_ricerca_stato(FILE* interfaccia_ricercare_contatto_stato, FILE* file_errori);
void stampare_contatto_desiderato(Rubrica rubrica, Vettore contatti_trovati, int contatto_esatto, FILE* file_messaggi, FILE* file_errori);
Vettore selezionare_nome_cognome(Rubrica rubrica, int tipologia_ricerca, int selezione_preferito_bloccato, FILE* interfaccia, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_errori);
Vettore inserire_nome_da_ricercare(Rubrica rubrica, Vettore contatti_trovati, int tipologia_ricerca, int selezione_preferito_bloccato, FILE* interfaccia_inserire_nome, FILE* file_errori);
Vettore inserire_cognome_da_ricercare(Rubrica rubrica, Vettore contatti_trovati, int tipologia_ricerca, int selezione_preferito_bloccato, FILE* interfaccia_inserire_cognome, FILE* file_errori);
Vettore ricercare_per_nome(Rubrica rubrica, Vettore contatti_trovati, int tipologia_ricerca, int selezione_preferito_bloccato, char* nome_da_cercare);
Vettore ricercare_per_cognome(Rubrica rubrica, Vettore contatti_trovati, int tipologia_ricerca, int selezione_preferito_bloccato, char* cognome_da_cercare);
Vettore riempire_vettore(Rubrica rubrica, Vettore contatti_trovati, int y, int pos, int pos_contatti_trovati);
void visualizzare_contatto(Contatto contatto_cercato, int pos_contatti_trovati);
int selezionare_contatto(Vettore contatti_trovati, char* criterio_selezione, FILE* file_messaggi, FILE* file_errori);
bool contiene_stringa(char* stringa_da_paragonare, char* stringa_da_cercare);
// Operazione controllo se esiste un contatto uguale
bool esiste_contatto(Rubrica rubrica, Contatto nuovo_contatto, FILE* file_errori);
// Operazione controllo dello stato se è preferito o bloccato
bool controlla_stato(Rubrica rubrica, int selezione_preferito_bloccato, int pos);

#endif /* RICERCARE_CONTATTO_H_ */
