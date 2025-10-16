#ifndef GESTIRE_TIPI_H_
#define GESTIRE_TIPI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Globali.h"

typedef struct{
	int* valori;
	int dimensione;
} Vettore;

typedef struct{
	bool preferito;
	bool bloccato;
} Stato;

typedef struct{
	char nome[LUNGHEZZA_MASSIMA_NOME + 1];
	char cognome[LUNGHEZZA_MASSIMA_COGNOME + 1];
	char numero_telefono[LUNGHEZZA_MASSIMA_NUMERO_TELEFONICO + 1];
	Stato stato_contatto;
} Contatto;

typedef struct{
	Contatto contatti[DIMENSIONE_MASSIMA_RUBRICA];
	int lunghezza;
} Rubrica;

// Operazioni Vettore
int leggere_valore(Vettore vettore, int pos);
void scrivere_valore(Vettore* vettore, int pos, int nuovo_valore);
int leggere_dimensione_vettore(Vettore vettore);
void scrivere_dimensione_vettore(Vettore* vettore, int dimensione);
// Operazioni Rubrica
Contatto leggere_contatto(Rubrica rubrica, int pos);
void scrivere_contatto(Rubrica* rubrica, int pos, Contatto nuovo_contatto);
int leggere_lunghezza(Rubrica rubrica);
void scrivere_lunghezza(Rubrica* rubrica, int nuova_lunghezza);
// Operazioni Contatto
char* leggere_nome(Contatto contatto);
void scrivere_nome(Contatto* contatto, char* nuovo_nome);
char* leggere_cognome(Contatto contatto);
void scrivere_cognome(Contatto* contatto, char* nuovo_cognome);
char* leggere_numero_telefono(Contatto contatto);
void scrivere_numero_telefono(Contatto* contatto, char* nuovo_numero_telefono);
Stato leggere_stato_contatto(Contatto contatto);
void scrivere_stato_contatto(Contatto* contatto, Stato nuovo_stato);
// Operazioni Stato
bool leggere_preferito(Stato stato);
void scrivere_preferito(Stato* stato, bool nuovo_preferito);
bool leggere_bloccato(Stato stato);
void scrivere_bloccato(Stato* stato, bool nuovo_bloccato);

#endif /* GESTIRE_TIPI_H_ */
