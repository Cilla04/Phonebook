#include "Visualizzare_Rubrica.h"

Rubrica ordinare_rubrica(Rubrica rubrica, FILE* interfaccia_ordinare_rubrica, FILE* file_messaggi, FILE* file_errori)
{
	int scelta_nome_cognome;
	int scelta_ordine;

	scelta_nome_cognome = -1;
	if(esiste_file(interfaccia_ordinare_rubrica) == 0){ // Controlla se il file di interfaccia esiste
		do{
			// Stampa l'interfaccia per la scelta dell'ordinamento
			system("cls");
			rewind(interfaccia_ordinare_rubrica);
			stampare_interfaccia(interfaccia_ordinare_rubrica, file_errori);
			gotoXY(13, 7);
			scanf("%d", &scelta_nome_cognome); // Legge la scelta dell'utente
			pulire_stdin();
			if(scelta_nome_cognome == 1){ // L'utente sceglie di ordinare per nome
				// ordinare_per_nome
				do{
					scelta_ordine = inserire_scelta_ordine(interfaccia_ordinare_rubrica, file_messaggi, file_errori); // Chiede all'utente l'ordine (crescente o decrescente)
					if(scelta_ordine == 1){ // Ordina per nome crescente
						rubrica = ordinare_nome_crescente(rubrica);
						stampare_messaggio(MESSAGGIO_ORDINATA_NOME_CRESCENTE, file_messaggi, file_errori);
					} else if(scelta_ordine == 2){ // Ordina per nome decrescente
						rubrica = ordinare_nome_decrescente(rubrica);
						stampare_messaggio(MESSAGGIO_ORDINATA_NOME_DECRESCENTE, file_messaggi, file_errori);
					}
					if(scelta_ordine < 0 || scelta_ordine > 2){
						stampare_errore(ERRORE_SCELTA_UTENTE, file_errori); // Se l'utente inserisce una scelta non valida, stampa un errore
					}
				} while(scelta_ordine < 0 || scelta_ordine > 2); // Ripete finché l'ordine non è valido o vuole uscire
			} else if(scelta_nome_cognome == 2){ // Se l'utente sceglie di ordinare per cognome
				// ordinare_per_cognome
				do{
					scelta_ordine = inserire_scelta_ordine(interfaccia_ordinare_rubrica, file_messaggi, file_errori); // Chiede all'utente l'ordine (crescente o decrescente)
					if (scelta_ordine == 1){ // Ordina per cognome crescente
						rubrica = ordinare_cognome_crescente(rubrica);
						stampare_messaggio(MESSAGGIO_ORDINATA_COGNOME_CRESCENTE, file_messaggi, file_errori);
					} else if(scelta_ordine == 2){ // Ordina per cognome decrescente
						rubrica = ordinare_cognome_decrescente(rubrica);
						stampare_messaggio(MESSAGGIO_ORDINATA_COGNOME_DECRESCENTE, file_messaggi, file_errori);
					}
					if(scelta_ordine < 0 || scelta_ordine > 2){ // Se l'utente inserisce una scelta non valida, stampa un errore
						stampare_errore(ERRORE_SCELTA_UTENTE, file_errori);
					}
				} while(scelta_ordine < 0 || scelta_ordine > 2); // Ripete finché l'ordine non è valido
			}
			if(scelta_nome_cognome < 0 || scelta_nome_cognome > 2){ // Se l'utente inserisce una scelta non valida, stampa un errore
				stampare_errore(ERRORE_SCELTA_UTENTE, file_errori);
			}
		} while(scelta_nome_cognome < 0 || scelta_nome_cognome > 2); // Ripete finché la scelta non è valida
		if(scelta_ordine == 0 || scelta_nome_cognome == 0){ // Se l'utente sceglie di non ordinare, stampa un messaggio
			stampare_messaggio(MESSAGGIO_NON_ORDINATA, file_messaggi, file_errori);
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Se il file di interfaccia non esiste, stampa un errore
	}
	return rubrica; // Restituisce la rubrica ordinata
}

int inserire_scelta_ordine(FILE* interfaccia_ordinare_rubrica, FILE* file_messaggi, FILE* file_errori)
{
	int scelta_ordine;

	scelta_ordine = -1;
	// Stampa l'interfaccia per la scelta dell'ordinamento
	system("cls");
	rewind(interfaccia_ordinare_rubrica);
	stampare_interfaccia(interfaccia_ordinare_rubrica, file_errori);
	aggiornare_visualizzazione(file_messaggi, file_errori);
	gotoXY(13, 7);
	scanf("%d", &scelta_ordine); // Legge la scelta dell'utente
	pulire_stdin();
	return scelta_ordine; // Restituisce la scelta dell'utent
}

void aggiornare_visualizzazione(FILE* file_messaggi, FILE* file_errori)
{
	gotoXY(1, 3);
	stampare_riga(MESSAGGIO_CRESCENTE, file_messaggi, file_errori);
	gotoXY(1, 5);
	stampare_riga(MESSAGGIO_DECRESCENTE, file_messaggi, file_errori);
	return;
}

Rubrica ordinare_nome_crescente(Rubrica rubrica)
{
	int pos_rubrica;
	int confronto_stringhe;
	bool ordinato;
	Contatto contatto_1;
	Contatto contatto_2;
	Contatto tmp;

	do{
		ordinato = 1; // Assume che la rubrica sia ordinata
		pos_rubrica = 0;
		while(pos_rubrica < leggere_lunghezza(rubrica) - 1){ // Scorre la rubrica confrontando ogni coppia di contatti
			// Legge il contatto corrente e il successivo
			contatto_1 = leggere_contatto(rubrica, pos_rubrica);
			contatto_2 = leggere_contatto(rubrica, pos_rubrica + 1);
			confronto_stringhe = strcmp(leggere_nome(contatto_1), leggere_nome(contatto_2)); // Confronta i nomi dei due contatti
			if(confronto_stringhe == 0){ // Se i nomi sono uguali, confronta i cognomi
				confronto_stringhe = strcmp(leggere_cognome(contatto_1), leggere_cognome(contatto_2));
			}
			if(confronto_stringhe > 0){ // Se il contatto corrente deve essere dopo il successivo, li scambia
				tmp = contatto_1;
				scrivere_contatto(&rubrica, pos_rubrica, contatto_2);
				scrivere_contatto(&rubrica, pos_rubrica + 1, tmp);
				ordinato = 0; // Segna che è stato fatto uno scambio, quindi l'ordinamento non è completo
			}
			pos_rubrica++; // Passa alla coppia successiva
		}
	} while(ordinato == 0); // Ripete finché non sono più necessari scambi
	return rubrica; // Restituisce la rubrica ordinata
}

Rubrica ordinare_nome_decrescente(Rubrica rubrica)
{
	int pos_rubrica;
	int confronto_stringhe;
	bool ordinato;
	Contatto contatto_1;
	Contatto contatto_2;
	Contatto tmp;

	do{
		ordinato = 1; // Assume che la rubrica sia ordinata
		pos_rubrica = 0;
		while(pos_rubrica < leggere_lunghezza(rubrica) - 1){ // Scorre la rubrica confrontando ogni coppia di contatti
			// Legge il contatto corrente e il successivo
			contatto_1 = leggere_contatto(rubrica, pos_rubrica);
			contatto_2 = leggere_contatto(rubrica, pos_rubrica + 1);
			confronto_stringhe = strcmp(leggere_nome(contatto_2), leggere_nome(contatto_1)); // Confronta i nomi dei due contatti in ordine inverso
			if(confronto_stringhe == 0){ // Se i nomi sono uguali, confronta i cognomi in ordine inverso
				confronto_stringhe = strcmp(leggere_cognome(contatto_2), leggere_cognome(contatto_1));
			}
			if(confronto_stringhe > 0){ // Se il contatto corrente deve essere prima del successivo, li scambia
				tmp = contatto_1;
				scrivere_contatto(&rubrica, pos_rubrica, contatto_2);
				scrivere_contatto(&rubrica, pos_rubrica + 1, tmp);
				ordinato = 0; // Segna che è stato fatto uno scambio, quindi l'ordinamento non è completo
			}
			pos_rubrica++; // Passa alla coppia successiva
		}
	} while(ordinato == 0); // Ripete finché non sono più necessari scambi
	return rubrica; // Restituisce la rubrica ordinata
}

Rubrica ordinare_cognome_crescente(Rubrica rubrica)
{
	int pos_rubrica;
	int confronto_stringhe;
	bool ordinato;
	Contatto contatto_1;
	Contatto contatto_2;
	Contatto tmp;

	do{
		ordinato = 1; // Assume che la rubrica sia ordinata
		pos_rubrica = 0;
		while(pos_rubrica < leggere_lunghezza(rubrica) - 1){ // Scorre la rubrica confrontando ogni coppia di contatti
			// Legge il contatto corrente e il successivo
			contatto_1 = leggere_contatto(rubrica, pos_rubrica);
			contatto_2 = leggere_contatto(rubrica, pos_rubrica + 1);
			confronto_stringhe = strcmp(leggere_cognome(contatto_1), leggere_cognome(contatto_2)); // Confronta i cognomi dei due contatti
			if(confronto_stringhe == 0){ // Se i cognomi sono uguali, confronta i nomi
				confronto_stringhe = strcmp(leggere_nome(contatto_1), leggere_nome(contatto_2));
			}
			if(confronto_stringhe > 0){ // Se il contatto corrente deve essere dopo il successivo, li scambia
				tmp = contatto_1;
				scrivere_contatto(&rubrica, pos_rubrica, contatto_2);
				scrivere_contatto(&rubrica, pos_rubrica + 1, tmp);
				ordinato = 0; // Segna che è stato fatto uno scambio, quindi l'ordinamento non è completo
			}
			pos_rubrica++; // Passa alla coppia successiva
		}
	} while(ordinato == 0); // Ripete finché non sono più necessari scambi
	return rubrica; // Restituisce la rubrica ordinata
}

Rubrica ordinare_cognome_decrescente(Rubrica rubrica)
{
	int pos_rubrica;
	int confronto_stringhe;
	bool ordinato;
	Contatto contatto_1;
	Contatto contatto_2;
	Contatto tmp;

	do{
		ordinato = 1; // Assume che la rubrica sia ordinata
		pos_rubrica = 0;
		while(pos_rubrica < leggere_lunghezza(rubrica) - 1){ // Scorre la rubrica confrontando ogni coppia di contatti
			contatto_1 = leggere_contatto(rubrica, pos_rubrica);
			contatto_2 = leggere_contatto(rubrica, pos_rubrica + 1);
			confronto_stringhe = strcmp(leggere_cognome(contatto_2), leggere_cognome(contatto_1)); // Confronta i cognomi dei due contatti in ordine inverso
			if(confronto_stringhe == 0){ // Se i cognomi sono uguali, confronta i nomi in ordine inverso
				confronto_stringhe = strcmp(leggere_nome(contatto_2), leggere_nome(contatto_1));
			}
			if(confronto_stringhe > 0){ // Se il contatto corrente deve essere prima del successivo, li scambia
				tmp = contatto_1;
				scrivere_contatto(&rubrica, pos_rubrica, contatto_2);
				scrivere_contatto(&rubrica, pos_rubrica + 1, tmp);
				ordinato = 0; // Segna che è stato fatto uno scambio, quindi l'ordinamento non è completo
			}
			pos_rubrica++; // Passa alla coppia successiva
		}
	} while(ordinato == 0); // Ripete finché non sono più necessari scambi
	return rubrica; // Restituisce la rubrica ordinata
}

void visualizzare_rubrica(Rubrica rubrica, FILE* interfaccia_visualizzare_rubrica, FILE* interfaccia_tipologia_visualizzazione, FILE* file_messaggi, FILE* file_errori)
{
	int tipologia_visualizzazione;

	tipologia_visualizzazione = -1;
	if(esiste_file(interfaccia_tipologia_visualizzazione) == 0){ // Controlla se il file di interfaccia per la tipologia di visualizzazione esiste
		do{
			// Stampa l'interfaccia della tipologia di visualizzazione
			system("cls");
			rewind(interfaccia_tipologia_visualizzazione);
			stampare_interfaccia(interfaccia_tipologia_visualizzazione, file_errori);
			gotoXY(13, 9);
			scanf("%d", &tipologia_visualizzazione); // Legge la scelta dell'utente
			pulire_stdin();
			if(tipologia_visualizzazione < 0 || tipologia_visualizzazione > 3) { // Controlla se la scelta è valida
				stampare_errore(ERRORE_SCELTA_UTENTE, file_errori); // Stampa un errore se la scelta non è valida
			}
		} while(tipologia_visualizzazione < 0 || tipologia_visualizzazione > 3); // Continua a chiedere finché la scelta non è valida
		if(tipologia_visualizzazione == 0){
			stampare_messaggio(MESSAGGIO_RUBRICA_NON_VISUALIZZATA, file_messaggi, file_errori); // Messaggio per indicare che la rubrica non sarà visualizzata
		} else{
			// Chiama la funzione per stampare la rubrica con la tipologia di visualizzazione scelta dall'utente
			stampare_rubrica(rubrica, tipologia_visualizzazione, interfaccia_visualizzare_rubrica, file_errori);
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia per la tipologia di visualizzazione non esiste
	}
	return;
}

void stampare_rubrica(Rubrica rubrica, int tipologia_visualizzazione, FILE* interfaccia_visualizzare_rubrica, FILE* file_errori)
{
	int pos;
	bool esci;
	char scelta_utente;

	pos = 0;
	esci = 0;
	if(esiste_file(interfaccia_visualizzare_rubrica) == 0){ // Controlla se il file di interfaccia per la visualizzazione della rubrica esiste
		do{
			// Stampa l'interfaccia per la visualizzazione della rubrica
			system("cls");
			rewind(interfaccia_visualizzare_rubrica);
			stampare_interfaccia(interfaccia_visualizzare_rubrica, file_errori);
			// Stampa i contatti della rubrica a partire dalla posizione corrente e aggiorna la posizione
			pos = stampare_contatti(rubrica, pos, tipologia_visualizzazione);
			do{
				gotoXY(13, 26);
				scanf("%c", &scelta_utente); // Legge la scelta dell'utente
				pulire_stdin();
				if(scelta_utente != 'S' && scelta_utente != 'E'){
					stampare_errore(ERRORE_SCELTA_UTENTE, file_errori); // Stampa un errore se la scelta non è valida
					pulire_schermata(26, 13, 26, 120);
				}
				if(scelta_utente == 'E'){ // Se l'utente ha scelto di uscire imposta esci a vero
					esci = 1;
				}
			} while(scelta_utente != 'S' && scelta_utente != 'E'); // Continua a chiedere finché la scelta non è valida
		} while((pos < leggere_lunghezza(rubrica) || scelta_utente == 'S') && (esci == 0)); // Continua la visualizzazione finché l'utente vuole continuare
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia per la visualizzazione della rubrica non esiste
	}
	return;
}

int stampare_contatti(Rubrica rubrica, int pos, int tipologia_visualizzazione)
{
	int contatti_stampati;
	int y;

	contatti_stampati = 0;
	y = 3;
	if(tipologia_visualizzazione == 1){ // Visualizzazione di tutti i contatti
		while(contatti_stampati < MAX_CONTATTI_VISUALIZZABILI && pos < leggere_lunghezza(rubrica)){
			// Stampa nome e cognome del contatto e aumenta y e pos per stampare il contatto successivo e aggiorna il contatore dei contatti stampati
			gotoXY(5, y);
			printf("%s %s", leggere_nome(leggere_contatto(rubrica, pos)), leggere_cognome(leggere_contatto(rubrica, pos)));
			y += 2;
			contatti_stampati++;
			pos++;
		}
	} else if(tipologia_visualizzazione == 2){ // Visualizzazione dei contatti preferiti
		while(contatti_stampati < MAX_CONTATTI_VISUALIZZABILI && pos < leggere_lunghezza(rubrica)){
			if(leggere_preferito(leggere_stato_contatto(leggere_contatto(rubrica, pos))) == 1){
				// Stampa nome e cognome del contatto e aumenta y e pos per stampare il contatto successivo e aggiorna il contatore dei contatti stampati
				gotoXY(5, y);
				printf("%s %s", leggere_nome(leggere_contatto(rubrica, pos)), leggere_cognome(leggere_contatto(rubrica, pos)));
				y += 2;
				contatti_stampati++;
			}
			pos++;
		}
	} else if(tipologia_visualizzazione == 3){ // Visualizzazione dei contatti bloccati
		while(contatti_stampati < MAX_CONTATTI_VISUALIZZABILI && pos < leggere_lunghezza(rubrica)){
			if(leggere_bloccato(leggere_stato_contatto(leggere_contatto(rubrica, pos))) == 1){
				// Stampa nome e cognome del contatto e aumenta y e pos per stampare il contatto successivo e aggiorna il contatore dei contatti stampati
				gotoXY(5, y);
				printf("%s %s", leggere_nome(leggere_contatto(rubrica, pos)), leggere_cognome(leggere_contatto(rubrica, pos)));
				y += 2;
				contatti_stampati++;
			}
			pos++;
		}
	}
	return pos; // Restituisce la nuova posizione corrente nella rubrica dopo la stampa dei contatti
}
