#include "Gestire_Tipi.h"

// Vettore
int leggere_valore(Vettore vettore, int pos)
{
    int valore;

    valore = *((vettore.valori) + pos); // Legge il valore nella posizione specificata del vettore
    return valore; // Restituisce il valore letto
}

void scrivere_valore(Vettore* vettore, int pos, int nuovo_valore)
{
    *((vettore->valori) + pos) = nuovo_valore; // Scrive il nuovo valore nella posizione specificata del vettore
    return;
}

int leggere_dimensione_vettore(Vettore vettore)
{
    int dimensione;

    dimensione = vettore.dimensione; // Legge la dimensione del vettore
    return dimensione; // Restituisce la dimensione letta
}

void scrivere_dimensione_vettore(Vettore* vettore, int dimensione)
{
    vettore->dimensione = dimensione; // Scrive la nuova dimensione nel campo dimensione di vettore
    return;
}

// Rubrica
Contatto leggere_contatto(Rubrica rubrica, int pos)
{
	Contatto contatto;

	contatto = rubrica.contatti[pos]; // Legge il contatto nella posizione specificata della rubrica
	return contatto; // Restituisce il contatto letto
}

void scrivere_contatto(Rubrica* rubrica, int pos, Contatto nuovo_contatto)
{
	rubrica->contatti[pos] = nuovo_contatto; // Scrive il nuovo contatto nella posizione specificata della rubrica
	return;
}

int leggere_lunghezza(Rubrica rubrica)
{
	int lunghezza;

	lunghezza = rubrica.lunghezza; // Legge la lunghezza della rubrica
	return lunghezza; // Restituisce la lunghezza letta
}

void scrivere_lunghezza(Rubrica* rubrica, int nuova_lunghezza)
{
	rubrica->lunghezza = nuova_lunghezza; // Scrive la nuova lunghezza nel campo lunghezza della rubrica
	return;
}

// Contatto
char* leggere_nome(Contatto contatto)
{
    char* nome = malloc(LUNGHEZZA_MASSIMA_NOME + 2);
    if(nome != NULL){ // Controlla se l'allocazione della memoria è avvenuta correttamente
        strcpy(nome, contatto.nome); // Copia il nome del contatto nella memoria allocata
    }
    return nome; // Restituisce il puntatore al nome
}

void scrivere_nome(Contatto* contatto, char* nuovo_nome)
{
	strcpy(contatto->nome, nuovo_nome); // Copia il nuovo nome nel contatto
	return;
}

char* leggere_cognome(Contatto contatto)
{
    char* cognome = malloc(LUNGHEZZA_MASSIMA_COGNOME + 2);
    if(cognome != NULL){ // Controlla se l'allocazione della memoria è avvenuta correttamente
        strcpy(cognome, contatto.cognome); // Copia il cognome del contatto nella memoria allocata
    }
    return cognome; // Restituisce il puntatore al cognome
}

void scrivere_cognome(Contatto* contatto, char* nuovo_cognome)
{
	strcpy(contatto->cognome, nuovo_cognome); // Copia il nuovo cognome nel contatto
	return;
}

char* leggere_numero_telefono(Contatto contatto)
{
    char* numero_telefono = malloc(LUNGHEZZA_MASSIMA_NUMERO_TELEFONICO + 2);
    if(numero_telefono != NULL){ // Controlla se l'allocazione della memoria è avvenuta correttamente
        strcpy(numero_telefono, contatto.numero_telefono); // Copia il numero di telefono del contatto nella memoria allocata
    }
    return numero_telefono; // Restituisce il puntatore al numero di telefono
}

void scrivere_numero_telefono(Contatto* contatto, char* nuovo_numero_telefono)
{
	strcpy(contatto->numero_telefono, nuovo_numero_telefono); // Copia il nuovo numero di telefono nel contatto
	return;
}

Stato leggere_stato_contatto(Contatto contatto)
{
	Stato stato_contatto;

	stato_contatto = contatto.stato_contatto; // Legge lo stato del contatto
	return stato_contatto; // Restituisce lo stato letto
}

void scrivere_stato_contatto(Contatto* contatto, Stato nuovo_stato)
{
	contatto->stato_contatto = nuovo_stato; // Scrive il nuovo stato nel campo stato del contatto
	return;
}

// Stato
bool leggere_preferito(Stato stato)
{
	bool preferito;

	preferito = stato.preferito; // Legge il valore booleano di preferito di stato
	return preferito; // Restituisce il valore letto
}

void scrivere_preferito(Stato* stato, bool nuovo_preferito)
{
	stato->preferito = nuovo_preferito; // Scrive il nuovo valore booleano nel campo preferito di stato
	return;
}

bool leggere_bloccato(Stato stato)
{
	bool bloccato;

	bloccato = stato.bloccato; // Legge il valore booleano di bloccato di stato
	return bloccato; // Restituisce il valore letto
}

void scrivere_bloccato(Stato* stato, bool nuovo_bloccato)
{
	stato->bloccato = nuovo_bloccato; // Scrive il nuovo valore booleano nel campo bloccato di stato
	return;
}
