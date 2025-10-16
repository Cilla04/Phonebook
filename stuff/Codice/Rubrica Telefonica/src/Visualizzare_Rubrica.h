#ifndef VISUALIZZARE_RUBRICA_H_
#define VISUALIZZARE_RUBRICA_H_

#include "Globali.h"
#include "Gestire_Tipi.h"
#include "Gestire_Schermo.h"
#include "Gestire_File.h"

// Operazione ordinare rubrica
Rubrica ordinare_rubrica(Rubrica rubrica, FILE* interfaccia_ordinare_rubrica, FILE* file_messaggi, FILE* file_errori);
int inserire_scelta_ordine(FILE* interfaccia_ordinare_rubrica, FILE* file_messaggi, FILE* file_errori);
void aggiornare_visualizzazione(FILE* file_messaggi, FILE* file_errori);
Rubrica ordinare_nome_crescente(Rubrica rubrica);
Rubrica ordinare_nome_decrescente(Rubrica rubrica);
Rubrica ordinare_cognome_crescente(Rubrica rubrica);
Rubrica ordinare_cognome_decrescente(Rubrica rubrica);
// Operazione visualizzare rubrica
void visualizzare_rubrica(Rubrica rubrica, FILE* interfaccia_visualizzare_rubrica, FILE* interfaccia_tipologia_visualizzazione, FILE* file_messaggi, FILE* file_errori);
void stampare_rubrica(Rubrica rubrica, int tipologia_visualizzazione, FILE* interfaccia_visualizzare_rubrica, FILE* file_errori);
int stampare_contatti(Rubrica rubrica, int pos, int tipologia_visualizzazione);

#endif /* VISUALIZZARE_RUBRICA_H_ */
