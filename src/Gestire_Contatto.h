#ifndef GESTIRE_CONTATTO_H_
#define GESTIRE_CONTATTO_H_

#include "Globali.h"
#include "Gestire_Tipi.h"
#include "Gestire_Schermo.h"
#include "Gestire_File.h"
#include "Ricercare_Contatto.h"

// Operazione inserire nuovo contatto
Rubrica inserire_nuovo_contatto(Rubrica rubrica, FILE* interfaccia_nuovo_contatto, FILE* file_messaggi, FILE* file_errori);
Contatto inserire_nuovo_nome(Contatto nuovo_contatto, FILE* interfaccia_nome, FILE* file_errori);
Contatto inserire_nuovo_cognome(Contatto nuovo_contatto, bool ristampa_contatto, FILE* interfaccia_cognome, FILE* file_errori);
Contatto inserire_nuovo_numero_telefono(Contatto nuovo_contatto, bool ristampa_contatto, FILE* interfaccia_numero, FILE* file_errori);
// Operazione cancellare un contatto
Rubrica cancellare_contatto(Rubrica rubrica, FILE* interfaccia_cancellare_contatto, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori);
// Operazione modificare un contatto
Rubrica modificare_contatto(Rubrica rubrica, FILE* interfaccia_modificare_contatto, FILE* interfaccia_modificare_nome, FILE* interfaccia_modificare_cognome, FILE* interfaccia_modificare_numero, FILE* interfaccia_opzioni_modifica, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori);
Rubrica modificare_campi_contatto(Rubrica rubrica, Contatto contatto_da_modificare, int scelta_modifica, int pos, FILE* interfaccia_modificare_nome, FILE* interfaccia_modificare_cognome, FILE* interfaccia_modificare_numero, FILE* file_messaggi, FILE* file_errori);
// Operazione gestire stati di un contatto
Rubrica gestire_stati(Rubrica rubrica, FILE* interfaccia_gestire_stati, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* interfaccia_aggiungere_preferiti, FILE* interfaccia_rimuovere_preferiti, FILE* interfaccia_aggiungere_bloccati, FILE* interfaccia_rimuovere_bloccati, FILE* file_messaggi, FILE* file_errori);
Rubrica aggiungere_preferiti(Rubrica rubrica, FILE* interfaccia_aggiungere_preferiti, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori);
Rubrica aggiungere_bloccati(Rubrica rubrica, FILE* interfaccia_aggiungere_bloccati, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori);
Rubrica rimuovere_preferiti(Rubrica rubrica, FILE* interfaccia_rimuovere_preferiti, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori);
Rubrica rimuovere_bloccati(Rubrica rubrica, FILE* interfaccia_rimuovere_bloccati, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori);

#endif /* GESTIRE_CONTATTO_H_ */
