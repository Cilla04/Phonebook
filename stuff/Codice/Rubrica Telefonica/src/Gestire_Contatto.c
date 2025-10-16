#include "Gestire_Contatto.h"

Rubrica inserire_nuovo_contatto(Rubrica rubrica, FILE* interfaccia_nuovo_contatto, FILE* file_messaggi, FILE* file_errori)
{
	Contatto nuovo_contatto;
	Stato stato;
	bool ristampa_contatto;

	ristampa_contatto = 1; // Inizializza la variabile di controllo per la ristampa del contatto
	if(esiste_file(interfaccia_nuovo_contatto) == 0){ // Verifica se il file di interfaccia esiste
		do{
			// Inserisce i dettagli del nuovo contatto
			nuovo_contatto = inserire_nuovo_nome(nuovo_contatto, interfaccia_nuovo_contatto, file_errori);
			nuovo_contatto = inserire_nuovo_cognome(nuovo_contatto, ristampa_contatto, interfaccia_nuovo_contatto, file_errori);
			nuovo_contatto = inserire_nuovo_numero_telefono(nuovo_contatto, ristampa_contatto, interfaccia_nuovo_contatto, file_errori);
			// Imposta lo stato del nuovo contatt
			stato = leggere_stato_contatto(nuovo_contatto);
			scrivere_preferito(&stato, 0); // Il contatto non è preferito di default
			scrivere_bloccato(&stato, 0); // Il contatto non è bloccato di default
			scrivere_stato_contatto(&nuovo_contatto, stato);
		} while(esiste_contatto(rubrica, nuovo_contatto, file_errori) == 1); // Ripete finché il contatto non è unico
		// Controlla se i dati inseriti sono validi
		if(strcmp(leggere_nome(nuovo_contatto), "0") != 0 && strcmp(leggere_cognome(nuovo_contatto), "0") != 0 && strcmp(leggere_numero_telefono(nuovo_contatto), "000000") != 0){
			// Aggiunge il nuovo contatto alla rubrica
			scrivere_lunghezza(&rubrica, leggere_lunghezza(rubrica) + 1);
			scrivere_contatto(&rubrica, leggere_lunghezza(rubrica) - 1, nuovo_contatto);
			stampare_messaggio(MESSAGGIO_AGGIUNTO, file_messaggi, file_errori); // Messaggio che il contatto è stato aggiunto
		} else{
			stampare_messaggio(MESSAGGIO_NON_AGGIUNTO, file_messaggi, file_errori); // Messaggio che il contatto non è stato aggiunto
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return rubrica; // Restituisce la rubrica aggiornata
}

Contatto inserire_nuovo_nome(Contatto nuovo_contatto, FILE* interfaccia_nome, FILE* file_errori)
{
	char nome[LUNGHEZZA_MASSIMA_NOME + 2];

	if(esiste_file(interfaccia_nome) == 0){ // Verifica se il file di interfaccia esiste
		do{
			system("cls");
			rewind(interfaccia_nome);
			stampare_interfaccia(interfaccia_nome, file_errori); // Stampa l'interfaccia per l'inserimento del nome
			gotoXY(11, 3);
			fgets(nome, sizeof(nome), stdin); // Legge l'input dell'utente per il nome
			pulire_buffer_input(nome);
			if(strlen(nome) <= 0 || strlen(nome) > LUNGHEZZA_MASSIMA_NOME){ // Controlla se il nome inserito ha una lunghezza valida
				stampare_errore(ERRORE_INPUT_UTENTE, file_errori); // Stampa un messaggio di errore se la lunghezza del nome non è valida
			}
		} while(strlen(nome) <= 0 || strlen(nome) > LUNGHEZZA_MASSIMA_NOME); // Ripete finché il nome inserito non è valido
		scrivere_nome(&nuovo_contatto, nome); // Scrive il nome valido nel nuovo contatto
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return nuovo_contatto; // Restituisce il contatto aggiornato con il nome inserito
}

Contatto inserire_nuovo_cognome(Contatto nuovo_contatto, bool ristampa_contatto, FILE* interfaccia_cognome, FILE* file_errori)
{
	char cognome[LUNGHEZZA_MASSIMA_COGNOME + 2];

	if(esiste_file(interfaccia_cognome) == 0){ // Verifica se il file di interfaccia esiste
		do{
			system("cls");
			rewind(interfaccia_cognome);
			stampare_interfaccia(interfaccia_cognome, file_errori); // Stampa l'interfaccia per l'inserimento del nome
			// Se ristampa_contatto è vero, mostra il nome del nuovo contatto
			if(ristampa_contatto == 1){
				gotoXY(11, 3);
				printf("%s", leggere_nome(nuovo_contatto));
			}
			gotoXY(14, 5);
			fgets(cognome, sizeof(cognome), stdin); // Legge l'input dell'utente per il cognome
			pulire_buffer_input(cognome);
			if(strlen(cognome) <= 0 || strlen(cognome) > LUNGHEZZA_MASSIMA_COGNOME){ // Controlla se il cognome inserito ha una lunghezza valida
				stampare_errore(ERRORE_INPUT_UTENTE, file_errori); // Stampa un messaggio di errore se la lunghezza del cognome non è valida
			}
		} while(strlen(cognome) <= 0 || strlen(cognome) > LUNGHEZZA_MASSIMA_COGNOME); // Ripete finché il cognome inserito non è valido
		scrivere_cognome(&nuovo_contatto, cognome); // Scrive il cognome valido nel nuovo contatto
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return nuovo_contatto; // Restituisce il contatto aggiornato con il cognome inserito
}

Contatto inserire_nuovo_numero_telefono(Contatto nuovo_contatto, bool ristampa_contatto, FILE* interfaccia_numero, FILE* file_errori)
{
	char numero_telefono[LUNGHEZZA_MASSIMA_NUMERO_TELEFONICO + 2];
	int pos_numero;
	bool ripeti_numero;

	if(esiste_file(interfaccia_numero) == 0){ // Verifica se il file di interfaccia esiste
		do{
			system("cls");
			rewind(interfaccia_numero);
			stampare_interfaccia(interfaccia_numero, file_errori); // Stampa l'interfaccia per l'inserimento del numero di telefono
			// Se ristampa_contatto è vero, mostra il nome e cognome del nuovo contatto
			if(ristampa_contatto == 1){
				gotoXY(11, 3);
				printf("%s", leggere_nome(nuovo_contatto));
				gotoXY(14, 5);
				printf("%s", leggere_cognome(nuovo_contatto));
			}
			gotoXY(5, 8);
			fgets(numero_telefono, sizeof(numero_telefono), stdin); // Legge l'input dell'utente per il numero di telefono
			pulire_buffer_input(numero_telefono);
			// Controlla se il numero di telefono contiene solo cifre
			pos_numero = 0;
			ripeti_numero = 0;
			while(pos_numero < strlen(numero_telefono)){
				if(numero_telefono[pos_numero] < '0' || numero_telefono[pos_numero] > '9'){
					ripeti_numero = 1; // Se trova un carattere non numerico, imposta ripeti_numero a vero
				}
				pos_numero++;
			}
			// Verifica se il numero di telefono inserito è valido
			if(strlen(numero_telefono) < LUNGHEZZA_MINIMA_NUMERO_TELEFONICO || strlen(numero_telefono) > LUNGHEZZA_MASSIMA_NUMERO_TELEFONICO || ripeti_numero == 1){
				stampare_errore(ERRORE_INPUT_UTENTE, file_errori); // Stampa un errore se il numero di telefono non è valido
			}
			// Ripete finché il numero di telefono inserito non è valido
		} while(strlen(numero_telefono) < LUNGHEZZA_MINIMA_NUMERO_TELEFONICO || strlen(numero_telefono) > LUNGHEZZA_MASSIMA_NUMERO_TELEFONICO || ripeti_numero == 1);
		scrivere_numero_telefono(&nuovo_contatto, numero_telefono); // Scrive il numero di telefono nel nuovo contatto
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return nuovo_contatto; // Restituisce il contatto aggiornato con il numero di telefono inserito
}

Rubrica cancellare_contatto(Rubrica rubrica, FILE* interfaccia_cancellare_contatto, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori)
{
	int contatto_esatto;
	int pos;
	int tipologia_ricerca;
	int selezione_preferito_bloccato;
	char* criterio_selezione;
	Vettore contatti_trovati;

	// Inizializzazione delle variabili in modo tale che cerchi tutti i contatti senza far caso agli stati
	tipologia_ricerca = 0;
	selezione_preferito_bloccato = 0;
	criterio_selezione = "CANCELLARE: ";
	// Verifica se il file di interfaccia esiste
	if(esiste_file(interfaccia_cancellare_contatto) == 0 && esiste_file(interfaccia_inserire_nome) == 0 && esiste_file(interfaccia_inserire_cognome) == 0){
		// Riempie il vettore con le posizioni in rubrica dei contatti trovati dalla ricerca effettuata per nome o per cognome
		contatti_trovati = selezionare_nome_cognome(rubrica, tipologia_ricerca, selezione_preferito_bloccato, interfaccia_cancellare_contatto, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_errori);
		if(leggere_valore(contatti_trovati, 0) != -1){ // Verifica se sono stati trovati contatti da cancellare
			// Se il primo valore è un errore di contatto mancante, stampa l'errore
			if(leggere_valore(contatti_trovati, 0) == ERRORE_FUNZIONE_CONTATTO_MANCANTE){
				stampare_errore(ERRORE_CONTATTO_MANCANTE, file_errori);
			} else{
				contatto_esatto = selezionare_contatto(contatti_trovati, criterio_selezione, file_messaggi, file_errori); // Selezione del contatto esatto da cancellare
				if(contatto_esatto != 0){ // Verifica se è stato selezionato un contatto da cancellare
					pos = leggere_valore(contatti_trovati, contatto_esatto - 1);
					// Sposta tutti i contatti successivi indietro di una posizione per sovrascrivere il contatto da cancellare
					while(pos < leggere_lunghezza(rubrica)){
						scrivere_contatto(&rubrica, pos, leggere_contatto(rubrica, pos + 1));
						pos++;
					}
					// Riduce la lunghezza della rubrica di uno
					scrivere_lunghezza(&rubrica, leggere_lunghezza(rubrica) - 1);
					stampare_messaggio(MESSAGGIO_CANCELLATO, file_messaggi, file_errori); // Messaggio di successo per la cancellazione
				} else{
					stampare_messaggio(MESSAGGIO_NON_CANCELLATO, file_messaggi, file_errori); // Messaggio che il contatto non è stato cancellato
				}
			}
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return rubrica; // Restituisce la rubrica aggiornata
}

Rubrica modificare_contatto(Rubrica rubrica, FILE* interfaccia_modificare_contatto, FILE* interfaccia_modificare_nome, FILE* interfaccia_modificare_cognome, FILE* interfaccia_modificare_numero, FILE* interfaccia_opzioni_modifica, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori)
{
	int scelta_modifica;
	int contatto_esatto;
	int pos;
	int tipologia_ricerca;
	int selezione_preferito_bloccato;
	char* criterio_selezione;
	Vettore contatti_trovati;
	Contatto contatto_da_modificare;

	// Inizializzazione delle variabili in modo tale che cerchi tutti i contatti senza far caso agli stati
	tipologia_ricerca = 0;
	selezione_preferito_bloccato = 0;
	criterio_selezione = "MODIFICARE: ";
	// Verifica se il file di interfaccia esiste
	if(esiste_file(interfaccia_modificare_contatto) == 0 && esiste_file(interfaccia_inserire_nome) == 0 && esiste_file(interfaccia_inserire_cognome) == 0){
		// Riempie il vettore con le posizioni in rubrica dei contatti trovati dalla ricerca effettuata per nome o per cognome
		contatti_trovati = selezionare_nome_cognome(rubrica, tipologia_ricerca, selezione_preferito_bloccato, interfaccia_modificare_contatto, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_errori);
		if(leggere_valore(contatti_trovati, 0) != -1){ // Verifica se sono stati trovati contatti da modificare
			// Se il primo valore è un errore di contatto mancante, stampa l'errore
			if(leggere_valore(contatti_trovati, 0) == ERRORE_FUNZIONE_CONTATTO_MANCANTE){
				stampare_errore(ERRORE_CONTATTO_MANCANTE, file_errori);
			} else{
				contatto_esatto = selezionare_contatto(contatti_trovati, criterio_selezione, file_messaggi, file_errori); // Selezione del contatto esatto da modificare
				if(contatto_esatto != 0){ // Verifica se è stato selezionato un contatto da modificare
					do{
						scelta_modifica = -1;
						// Mostra le opzioni di modifica e chiede all'utente di scegliere
						stampare_interfaccia(interfaccia_opzioni_modifica, file_errori);
						gotoXY(61, 11);
						scanf("%d", &scelta_modifica);
						pulire_stdin();
						pulire_schermata(11, 61, 11, 120);
						if(scelta_modifica < 0 || scelta_modifica > 3){ // Verifica se la scelta dell'utente è valida
							stampare_errore(ERRORE_SCELTA_UTENTE, file_errori); // Mostra un errore se la scelta non è valida
						}
					} while(scelta_modifica < 0 || scelta_modifica > 3);
					// Ottiene la posizione del contatto da modificare nella rubrica
					pos = leggere_valore(contatti_trovati, contatto_esatto - 1);
					contatto_da_modificare = leggere_contatto(rubrica, pos);
					// Chiama la funzione per modificare i campi del contatto selezionato
					rubrica = modificare_campi_contatto(rubrica, contatto_da_modificare, scelta_modifica, pos, interfaccia_modificare_nome, interfaccia_modificare_cognome, interfaccia_modificare_numero, file_messaggi, file_errori);
				} else{
					stampare_messaggio(MESSAGGIO_NON_MODIFICATO, file_messaggi, file_errori); // Messaggio che il contatto non è stato modificato
				}
			}
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return rubrica; // Restituisce la rubrica aggiornata
}

Rubrica modificare_campi_contatto(Rubrica rubrica, Contatto contatto_da_modificare, int scelta_modifica, int pos, FILE* interfaccia_modificare_nome, FILE* interfaccia_modificare_cognome, FILE* interfaccia_modificare_numero, FILE* file_messaggi, FILE* file_errori)
{
	bool ristampa_contatto;

	ristampa_contatto = 0;
	system("cls");
	// Verifica quale campo del contatto deve essere modificato in base alla scelta dell'utente
	if(scelta_modifica == 1){
		// Modifica del nome del contatto
		contatto_da_modificare = inserire_nuovo_nome(contatto_da_modificare, interfaccia_modificare_nome, file_errori);
	} else if(scelta_modifica == 2){
		// Modifica del cognome del contatto
		contatto_da_modificare = inserire_nuovo_cognome(contatto_da_modificare, ristampa_contatto, interfaccia_modificare_cognome, file_errori);
	} else if(scelta_modifica == 3){
		// Modifica del numero di telefono del contatto
		contatto_da_modificare = inserire_nuovo_numero_telefono(contatto_da_modificare, ristampa_contatto, interfaccia_modificare_numero, file_errori);
	}
	// Verifica se sono stati inseriti valori validi per nome, cognome e numero di telefono e se il contatto modificato non esiste già nella rubrica
	if(strcmp(leggere_nome(contatto_da_modificare), "0") != 0 && strcmp(leggere_cognome(contatto_da_modificare), "0") != 0 && strcmp(leggere_numero_telefono(contatto_da_modificare), "000000") != 0 && scelta_modifica != 0){
		if(scelta_modifica != 3 && esiste_contatto(rubrica, contatto_da_modificare, file_errori) == 0){
			scrivere_contatto(&rubrica, pos, contatto_da_modificare); // Scrive il contatto modificato nella rubrica alla posizione specificata
			stampare_messaggio(MESSAGGIO_MODIFICATO, file_messaggi, file_errori); // Messaggio di successo per la modifica del contatto
		} else if(scelta_modifica == 3){
			scrivere_contatto(&rubrica, pos, contatto_da_modificare); // Scrive il contatto modificato nella rubrica alla posizione specificata
			stampare_messaggio(MESSAGGIO_MODIFICATO, file_messaggi, file_errori); // Messaggio di successo per la modifica del contatto
		} else{
			stampare_messaggio(MESSAGGIO_NON_MODIFICATO, file_messaggi, file_errori); // Messaggio che il contatto non è stato modificato
		}
	} else{
		stampare_messaggio(MESSAGGIO_NON_MODIFICATO, file_messaggi, file_errori); // Messaggio che il contatto non è stato modificato
	}
	return rubrica; // Restituisce la rubrica aggiornata
}

Rubrica gestire_stati(Rubrica rubrica, FILE* interfaccia_gestire_stati, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* interfaccia_aggiungere_preferiti, FILE* interfaccia_rimuovere_preferiti, FILE* interfaccia_aggiungere_bloccati, FILE* interfaccia_rimuovere_bloccati, FILE* file_messaggi, FILE* file_errori)
{
	int scelta_modifica_stato;

	// Verifica se il file di interfaccia esiste
	if(esiste_file(interfaccia_gestire_stati) == 0 && esiste_file(interfaccia_inserire_nome) == 0 && esiste_file(interfaccia_inserire_cognome) == 0){
		do{
			scelta_modifica_stato = -1;
			// Pulisce la console e stampa l'interfaccia per la gestione degli stati
			system("cls");
			rewind(interfaccia_gestire_stati);
			stampare_interfaccia(interfaccia_gestire_stati, file_errori);
			gotoXY(13, 11);
			scanf("%d", &scelta_modifica_stato); // Chiede all'utente di inserire la scelta per la modifica dello stato
			pulire_stdin();
			if(scelta_modifica_stato < 0 || scelta_modifica_stato > 4){ // Verifica se la scelta dell'utente è valida
				stampare_errore(ERRORE_SCELTA_UTENTE, file_errori); // Stampa un errore se la scelta non è valida
			}
		} while(scelta_modifica_stato < 0 || scelta_modifica_stato > 4);
		// Esegue l'operazione corrispondente alla scelta dell'utente
		if(scelta_modifica_stato == 1){
			rubrica = aggiungere_preferiti(rubrica, interfaccia_aggiungere_preferiti, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_messaggi, file_errori);
		} else if(scelta_modifica_stato == 2){
			rubrica = rimuovere_preferiti(rubrica, interfaccia_rimuovere_preferiti, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_messaggi, file_errori);
		} else if(scelta_modifica_stato == 3){
			rubrica = aggiungere_bloccati(rubrica, interfaccia_aggiungere_bloccati, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_messaggi, file_errori);
		} else if(scelta_modifica_stato == 4){
			rubrica = rimuovere_bloccati(rubrica, interfaccia_rimuovere_bloccati, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_messaggi, file_errori);
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return rubrica; // Restituisce la rubrica aggiornata
}

Rubrica aggiungere_preferiti(Rubrica rubrica, FILE* interfaccia_aggiungere_preferiti, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori)
{
	Vettore contatti_trovati;
	Contatto contatto;
	Stato stato;
	int pos;
	int contatto_esatto;
	int tipologia_ricerca;
	int selezione_preferito_bloccato;
	char* criterio_selezione;

	// Inizializzazione delle variabili in modo tale che cerchi tutti i contatti che non fanno parte dei preferiti
	tipologia_ricerca = 1;
	selezione_preferito_bloccato = 1;
	if(esiste_file(interfaccia_aggiungere_preferiti) == 0){ // Verifica se il file di interfaccia esiste
		system("cls");
		criterio_selezione = "AGGIUNGERE AI PREFERITI: ";
		// Riempie il vettore con le posizioni in rubrica dei contatti trovati dalla ricerca effettuata per nome o per cognome
		contatti_trovati = selezionare_nome_cognome(rubrica, tipologia_ricerca, selezione_preferito_bloccato, interfaccia_aggiungere_preferiti, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_errori);
		if(leggere_valore(contatti_trovati, 0) != -1){ // Verifica se sono stati trovati contatti da aggiungere ai preferiti
			// Se il primo valore è un errore di contatto mancante, stampa l'errore
			if(leggere_valore(contatti_trovati, 0) == ERRORE_FUNZIONE_CONTATTO_MANCANTE){
				stampare_errore(ERRORE_CONTATTO_MANCANTE, file_errori);
			} else{
				// Selezione del contatto esatto da aggiungere ai preferiti
				contatto_esatto = selezionare_contatto(contatti_trovati, criterio_selezione, file_messaggi, file_errori);
				if(contatto_esatto != 0){ // Verifica se è stato selezionato un contatto da aggiungere ai preferiti
					pos = leggere_valore(contatti_trovati, contatto_esatto - 1);
					contatto = leggere_contatto(rubrica, pos);
					stato = leggere_stato_contatto(leggere_contatto(rubrica, pos));
					// Imposta il contatto come preferito e lo aggiorna nella rubrica
					scrivere_preferito(&stato, 1);
					scrivere_stato_contatto(&contatto, stato);
					scrivere_contatto(&rubrica, pos, contatto);
					stampare_messaggio(MESSAGGIO_PREFERITO, file_messaggi, file_errori); // Messaggio di successo per l'aggiunta ai preferiti
				} else{
					stampare_messaggio(MESSAGGIO_NON_PREFERITO, file_messaggi, file_errori); // Messaggio che il contatto non è stato aggiunto ai preferiti
				}
			}
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return rubrica; // Restituisce la rubrica aggiornata
}

Rubrica aggiungere_bloccati(Rubrica rubrica, FILE* interfaccia_aggiungere_bloccati, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori)
{
	Vettore contatti_trovati;
	Contatto contatto;
	Stato stato;
	int pos;
	int contatto_esatto;
	int tipologia_ricerca;
	int selezione_preferito_bloccato;
	char* criterio_selezione;

	// Inizializzazione delle variabili in modo tale che cerchi tutti i contatti che non fanno parte dei bloccati
	tipologia_ricerca = 1;
	selezione_preferito_bloccato = 2;
	if(esiste_file(interfaccia_aggiungere_bloccati) == 0){ // Verifica se il file di interfaccia esiste
		system("cls");
		criterio_selezione = "AGGIUNGERE AI BLOCCATI: ";
		// Riempie il vettore con le posizioni in rubrica dei contatti trovati dalla ricerca effettuata per nome o per cognome
		contatti_trovati = selezionare_nome_cognome(rubrica, tipologia_ricerca, selezione_preferito_bloccato, interfaccia_aggiungere_bloccati, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_errori);
		if(leggere_valore(contatti_trovati, 0) != -1){ // Verifica se sono stati trovati contatti da aggiungere ai bloccati
			// Se il primo valore è un errore di contatto mancante, stampa l'errore
			if(leggere_valore(contatti_trovati, 0) == ERRORE_FUNZIONE_CONTATTO_MANCANTE){
				stampare_errore(ERRORE_CONTATTO_MANCANTE, file_errori);
			} else{
				// Selezione del contatto esatto da aggiungere ai bloccati
				contatto_esatto = selezionare_contatto(contatti_trovati, criterio_selezione, file_messaggi, file_errori);
				if(contatto_esatto != 0){ // Verifica se è stato selezionato un contatto da aggiungere ai bloccati
					pos = leggere_valore(contatti_trovati, contatto_esatto - 1);
					contatto = leggere_contatto(rubrica, pos);
					stato = leggere_stato_contatto(leggere_contatto(rubrica, pos));
					// Imposta il contatto come bloccato e lo aggiorna nella rubrica
					scrivere_bloccato(&stato, 1);
					scrivere_stato_contatto(&contatto, stato);
					scrivere_contatto(&rubrica, pos, contatto);
					stampare_messaggio(MESSAGGIO_BLOCCATO, file_messaggi, file_errori); // Messaggio di successo per l'aggiunta ai bloccati
				} else{
					stampare_messaggio(MESSAGGIO_NON_BLOCCATO, file_messaggi, file_errori); // Messaggio che il contatto non è stato aggiunto ai bloccati
				}
			}
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return rubrica; // Restituisce la rubrica aggiornata
}

Rubrica rimuovere_preferiti(Rubrica rubrica, FILE* interfaccia_rimuovere_preferiti, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori)
{
	Vettore contatti_trovati;
	Contatto contatto;
	Stato stato;
	int pos;
	int contatto_esatto;
	int tipologia_ricerca;
	int selezione_preferito_bloccato;
	char* criterio_selezione;

	// Inizializzazione delle variabili in modo tale che cerchi tutti i contatti che fanno parte dei preferiti
	tipologia_ricerca = 2;
	selezione_preferito_bloccato = 1;
	if(esiste_file(interfaccia_rimuovere_preferiti) == 0){ // Verifica se il file di interfaccia esiste
		system("cls");
		criterio_selezione = "RIMUOVERE DAI PREFERITI: ";
		// Riempie il vettore con le posizioni in rubrica dei contatti trovati dalla ricerca effettuata per nome o per cognome
		contatti_trovati = selezionare_nome_cognome(rubrica, tipologia_ricerca, selezione_preferito_bloccato, interfaccia_rimuovere_preferiti, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_errori);
		if(leggere_valore(contatti_trovati, 0) != -1){ // Verifica se sono stati trovati contatti da rimuovere dai preferiti
			// Se il primo valore è un errore di contatto mancante, stampa l'errore
			if(leggere_valore(contatti_trovati, 0) == ERRORE_FUNZIONE_CONTATTO_MANCANTE){
				stampare_errore(ERRORE_CONTATTO_MANCANTE, file_errori);
			} else{
				// Selezione del contatto esatto da rimuovere dai preferiti
				contatto_esatto = selezionare_contatto(contatti_trovati, criterio_selezione, file_messaggi, file_errori);
				if(contatto_esatto != 0){ // Verifica se è stato selezionato un contatto da rimuovere dai preferiti
					pos = leggere_valore(contatti_trovati, contatto_esatto - 1);
					contatto = leggere_contatto(rubrica, pos);
					stato = leggere_stato_contatto(leggere_contatto(rubrica, pos));
					// Imposta il contatto come non preferito e lo aggiorna nella rubrica
					scrivere_preferito(&stato, 0);
					scrivere_stato_contatto(&contatto, stato);
					scrivere_contatto(&rubrica, pos, contatto);
					stampare_messaggio(MESSAGGIO_RIMOSSO_PREFERITO, file_messaggi, file_errori); // Messaggio di successo per la rimozione dai preferiti
				} else{
					stampare_messaggio(MESSAGGIO_NON_RIMOSSO_PREFERITO, file_messaggi, file_errori); // Messaggio che il contatto non è stato rimosso dai preferiti
				}
			}
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return rubrica; // Restituisce la rubrica aggiornata
}

Rubrica rimuovere_bloccati(Rubrica rubrica, FILE* interfaccia_rimuovere_bloccati, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori)
{
	Vettore contatti_trovati;
	Contatto contatto;
	Stato stato;
	int pos;
	int contatto_esatto;
	int tipologia_ricerca;
	int selezione_preferito_bloccato;
	char* criterio_selezione;

	// Inizializzazione delle variabili in modo tale che cerchi tutti i contatti che fanno parte dei bloccati
	tipologia_ricerca = 2;
	selezione_preferito_bloccato = 2;
	if(esiste_file(interfaccia_rimuovere_bloccati) == 0){ // Verifica se il file di interfaccia esiste
		system("cls");
		criterio_selezione = "RIMUOVERE DAI BLOCCATI: ";
		// Riempie il vettore con le posizioni in rubrica dei contatti trovati dalla ricerca effettuata per nome o per cognome
		contatti_trovati = selezionare_nome_cognome(rubrica, tipologia_ricerca, selezione_preferito_bloccato, interfaccia_rimuovere_bloccati, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_errori);
		if(leggere_valore(contatti_trovati, 0) != -1){ // Verifica se sono stati trovati contatti da rimuovere dai bloccati
			// Se il primo valore è un errore di contatto mancante, stampa l'errore
			if(leggere_valore(contatti_trovati, 0) == ERRORE_FUNZIONE_CONTATTO_MANCANTE){
				stampare_errore(ERRORE_CONTATTO_MANCANTE, file_errori);
			} else{
				// Selezione del contatto esatto da rimuovere dai bloccati
				contatto_esatto = selezionare_contatto(contatti_trovati, criterio_selezione, file_messaggi, file_errori);
				if(contatto_esatto != 0){ // Verifica se è stato selezionato un contatto da rimuovere dai bloccati
					pos = leggere_valore(contatti_trovati, contatto_esatto - 1);
					contatto = leggere_contatto(rubrica, pos);
					stato = leggere_stato_contatto(leggere_contatto(rubrica, pos));
					// Imposta il contatto come non bloccato e lo aggiorna nella rubrica
					scrivere_bloccato(&stato, 0);
					scrivere_stato_contatto(&contatto, stato);
					scrivere_contatto(&rubrica, pos, contatto);
					stampare_messaggio(MESSAGGIO_RIMOSSO_BLOCCATO, file_messaggi, file_errori); // Messaggio di successo per la rimozione dai bloccati
				} else{
					stampare_messaggio(MESSAGGIO_NON_RIMOSSO_BLOCCATO, file_messaggi, file_errori); // Messaggio che il contatto non è stato rimosso dai bloccati
				}
			}
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return rubrica; // Restituisce la rubrica aggiornata
}
