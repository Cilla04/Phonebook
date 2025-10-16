#include "Ricercare_Contatto.h"

void ricercare_contatto(Rubrica rubrica, FILE* interfaccia_ricercare_contatto, FILE* interfaccia_ricercare_contatto_stato, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_messaggi, FILE* file_errori)
{
	int scelta_ricerca;
	int contatto_esatto;
	int ricerca_stato;
	int tipologia_ricerca;
	int selezione_preferito_bloccato;
	char* criterio_selezione;
	Vettore contatti_trovati;

	// Inizializza il vettore che conterrà le posizioni in rubrica dei contatti trovati
	contatti_trovati.valori = (int *)malloc(sizeof(int) * DIMENSIONE_MASSIMA_RUBRICA);
	scrivere_dimensione_vettore(&contatti_trovati, 0);
	scelta_ricerca = -1;
	ricerca_stato = -1;
	tipologia_ricerca = -1;
	selezione_preferito_bloccato = -1;
	criterio_selezione = "VISUALIZZARE: ";
	// Controlla se il file di interfaccia per la ricerca del contatto esiste
	if(esiste_file(interfaccia_ricercare_contatto) == 0 && esiste_file(interfaccia_ricercare_contatto_stato) == 0 && esiste_file(interfaccia_inserire_nome) == 0 && esiste_file(interfaccia_inserire_cognome) == 0){
		do{
			// Stampa l'interfaccia per la ricerca del contatto
			system("cls");
			rewind(interfaccia_ricercare_contatto);
			stampare_interfaccia(interfaccia_ricercare_contatto, file_errori);
			gotoXY(13, 7);
			scanf("%d", &scelta_ricerca); //Fa inserire la scelta dall'utente
			pulire_stdin();
			if(scelta_ricerca < 0 || scelta_ricerca > 2){  // Verifica se la scelta dell'utente è valida
				stampare_errore(ERRORE_SCELTA_UTENTE, file_errori);
			}
		} while(scelta_ricerca < 0 || scelta_ricerca > 2);
		if(scelta_ricerca != 0){ // Se l'utente ha scelto di non uscire chiede all'utente di selezionare lo stato della ricerca
			ricerca_stato = scegliere_ricerca_stato(interfaccia_ricercare_contatto_stato, file_errori);
			if(ricerca_stato != 0){
				if(ricerca_stato == 1){ // Ricerca di tutti i contatti
					tipologia_ricerca = 0;
					selezione_preferito_bloccato = 0;
				} else if(ricerca_stato == 2){ // Ricerca di contatti preferiti
					tipologia_ricerca = 2;
					selezione_preferito_bloccato = 1;
				} else if(ricerca_stato == 3){ // Ricerca di contatti bloccati
					tipologia_ricerca = 2;
					selezione_preferito_bloccato = 2;
				}
				if(scelta_ricerca == 1){  // Se l'utente vuole cercare per nome chiama la funzione per inserire il nome da cercare
					system("cls");
					contatti_trovati = inserire_nome_da_ricercare(rubrica, contatti_trovati, tipologia_ricerca, selezione_preferito_bloccato, interfaccia_inserire_nome, file_errori);
				} else if(scelta_ricerca == 2){ // Se l'utente vuole cercare per cognome chiama la funzione per inserire il cognome da cercare
					system("cls");
					contatti_trovati = inserire_cognome_da_ricercare(rubrica, contatti_trovati, tipologia_ricerca, selezione_preferito_bloccato,interfaccia_inserire_cognome, file_errori);
				}
				// Se il vettore dei contatti trovati non è vuoto controlla se c'è un errore di contatto mancante e nel caso stampa il messaggio d'errore
				if(leggere_valore(contatti_trovati, 0) != -1){
					if(leggere_valore(contatti_trovati, 0) == ERRORE_FUNZIONE_CONTATTO_MANCANTE){
						stampare_errore(ERRORE_CONTATTO_MANCANTE, file_errori);
					} else{
						// Seleziona il contatto esatto tra quelli trovati
						contatto_esatto = selezionare_contatto(contatti_trovati, criterio_selezione, file_messaggi, file_errori);
						// Se un contatto è stato selezionato stampa i dettagli del contatto desiderato
						if(contatto_esatto != 0){
							stampare_contatto_desiderato(rubrica, contatti_trovati, contatto_esatto, file_messaggi, file_errori);
						} else{
							stampare_messaggio(MESSAGGIO_CONTATTO_NON_VISUALIZZATO, file_messaggi, file_errori); // Stampa che non ha visualizzato il contatto
						}
					}
				}
			}
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return;
}

int scegliere_ricerca_stato(FILE* interfaccia_ricercare_contatto_stato, FILE* file_errori)
{
	int scegliere_ricerca_stato;

	if(esiste_file(interfaccia_ricercare_contatto_stato) == 0){ // Verifica se il file di interfaccia per la selezione dello stato di ricerca esiste
		do{
			scegliere_ricerca_stato = -1;
			// Stampa l'interfaccia per la selezione dello stato di ricerca
			system("cls");
			rewind(interfaccia_ricercare_contatto_stato);
			stampare_interfaccia(interfaccia_ricercare_contatto_stato, file_errori);
			gotoXY(13, 9);
			scanf("%d", &scegliere_ricerca_stato); //Fa inserire la scelta dall'utente
			pulire_stdin();
			if(scegliere_ricerca_stato < 0 || scegliere_ricerca_stato > 3){ // Verifica se la scelta dell'utente è valida
				stampare_errore(ERRORE_SCELTA_UTENTE, file_errori); // Stampa un errore se la scelta non è valida
			}
		} while(scegliere_ricerca_stato < 0 || scegliere_ricerca_stato > 3);
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se il file di interfaccia non esiste
	}
	return scegliere_ricerca_stato; // Restituisce la scelta dell'utente
}

void stampare_contatto_desiderato(Rubrica rubrica, Vettore contatti_trovati, int contatto_esatto, FILE* file_messaggi, FILE* file_errori)
{
	int pos;
	int conferma;

	// Posiziona il cursore e stampa l'intestazione per il contatto desiderato
	system("cls");
	gotoXY(2, 2);
	stampare_riga(MESSAGGIO_CONTATTO_DESIDERATO, file_messaggi, file_errori);
	gotoXY(2, 4);
	pos = leggere_valore(contatti_trovati, contatto_esatto - 1);
	// Stampa le informazioni del contatto
	printf("%s ", leggere_nome(leggere_contatto(rubrica, pos)));
	printf("%s ", leggere_cognome(leggere_contatto(rubrica, pos)));
	printf("%s", leggere_numero_telefono(leggere_contatto(rubrica, pos)));
	do{
		conferma = -1;
		pulire_schermata(6, 24, 6, 120);
		gotoXY(2, 6);
		stampare_riga(MESSAGGIO_USCITA, file_messaggi, file_errori);
		gotoXY(24, 6);
		scanf("%d", &conferma); // Chiede all'utente di inserire '0' per uscire
		pulire_stdin();
		// Se l'utente inserisce un valore diverso da 0, stampa un messaggio di errore
		if(conferma != 0){
			stampare_errore(ERRORE_SCELTA_UTENTE, file_errori);
		}
	} while(conferma != 0); // Ripete il ciclo finché l'utente non inserisce '0' per confermare l'uscita
	return;
}

Vettore selezionare_nome_cognome(Rubrica rubrica, int tipologia_ricerca, int selezione_preferito_bloccato, FILE* interfaccia, FILE* interfaccia_inserire_nome, FILE* interfaccia_inserire_cognome, FILE* file_errori)
{
	int scelta_ricerca;
	Vettore contatti_trovati;

	contatti_trovati.valori = (int *)malloc(sizeof(int) * DIMENSIONE_MASSIMA_RUBRICA); // Alloca memoria per il vettore dei contatti trovati
	scrivere_dimensione_vettore(&contatti_trovati, 0);
	if(esiste_file(interfaccia) == 0){ // Controlla se il file di interfaccia esiste
		do{
			scelta_ricerca = -1;
			// Stampa l'interfaccia per la selezione della ricerca
			system("cls");
			rewind(interfaccia);
			stampare_interfaccia(interfaccia, file_errori);
			gotoXY(13, 7);
			scanf("%d", &scelta_ricerca); // Legge la scelta dell'utente
			pulire_stdin();
			if(scelta_ricerca == 1){ // Se l'utente ha scelto di cercare per nome
				contatti_trovati = inserire_nome_da_ricercare(rubrica, contatti_trovati, tipologia_ricerca, selezione_preferito_bloccato, interfaccia_inserire_nome, file_errori);
			} else if(scelta_ricerca == 2){ // Se l'utente ha scelto di cercare per cognome
				contatti_trovati = inserire_cognome_da_ricercare(rubrica, contatti_trovati, tipologia_ricerca, selezione_preferito_bloccato, interfaccia_inserire_cognome, file_errori);
			} else if(scelta_ricerca == 0){ // Se l'utente ha scelto di annullare l'operazione
				scrivere_valore(&contatti_trovati, 0, -1);
			} else{
				stampare_errore(ERRORE_SCELTA_UTENTE, file_errori); // Se la scelta dell'utente è invalida
			}
		} while(scelta_ricerca < 0 || scelta_ricerca > 2);
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Se il file di interfaccia non esiste, stampa un errore
	}
	return contatti_trovati; // Restituisce il vettore con i contatti trovati
}

Vettore inserire_nome_da_ricercare(Rubrica rubrica, Vettore contatti_trovati, int tipologia_ricerca, int selezione_preferito_bloccato, FILE* interfaccia_inserire_nome, FILE* file_errori)
{
	char nome_da_cercare[LUNGHEZZA_MASSIMA_NOME + 2];

	if(esiste_file(interfaccia_inserire_nome) == 0){  // Controlla se il file contenente l'interfaccia per l'inserimento del nome esiste
		// Stampa l'interfaccia per l'inserimento del nome
		system("cls");
		rewind(interfaccia_inserire_nome);
		stampare_interfaccia(interfaccia_inserire_nome, file_errori);
		gotoXY(23, 3);
		fgets(nome_da_cercare, LUNGHEZZA_MASSIMA_NOME + 2, stdin);  // Legge il nome da cercare dall'input dell'utente
		nome_da_cercare[strcspn(nome_da_cercare, "\n")] = 0; // Rimuove il carattere di newline se presente alla fine della stringa
		// Esegue la ricerca del nome nei contatti della rubrica e aggiorna il vettore contatti_trovati con i risultati della ricerca
		contatti_trovati = ricercare_per_nome(rubrica, contatti_trovati, tipologia_ricerca, selezione_preferito_bloccato, nome_da_cercare);
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Se il file di interfaccia non esiste, stampa un errore nel file degli errori
	}
	return contatti_trovati; // Restituisce il vettore aggiornato dei contatti trovati
}

Vettore inserire_cognome_da_ricercare(Rubrica rubrica, Vettore contatti_trovati, int tipologia_ricerca, int selezione_preferito_bloccato, FILE* interfaccia_inserire_cognome, FILE* file_errori)
{
	char cognome_da_cercare[LUNGHEZZA_MASSIMA_COGNOME + 2];

	if(esiste_file(interfaccia_inserire_cognome) == 0){ // Controlla se il file contenente l'interfaccia per l'inserimento del cognome esiste
		// Stampa l'interfaccia per l'inserimento del cognome
		system("cls");
		rewind(interfaccia_inserire_cognome);
		stampare_interfaccia(interfaccia_inserire_cognome, file_errori);
		gotoXY(26, 3);
		fgets(cognome_da_cercare, LUNGHEZZA_MASSIMA_COGNOME + 2, stdin); // Legge il cognome da cercare dall'input dell'utente
		cognome_da_cercare[strcspn(cognome_da_cercare, "\n")] = 0; // Rimuove il carattere di newline se presente alla fine della stringa
		// Esegue la ricerca del cognome nei contatti della rubrica e aggiorna il vettore contatti_trovati con i risultati della ricerca
		contatti_trovati = ricercare_per_cognome(rubrica, contatti_trovati, tipologia_ricerca, selezione_preferito_bloccato, cognome_da_cercare);
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Se il file di interfaccia non esiste, stampa un errore nel file degli errori
	}
	return contatti_trovati; // Restituisce il vettore aggiornato dei contatti trovati
}

Vettore ricercare_per_nome(Rubrica rubrica, Vettore contatti_trovati, int tipologia_ricerca, int selezione_preferito_bloccato, char* nome_da_cercare)
{
	int y;
	int pos;
	int pos_contatti_trovati;
	bool trovato;
	char stringa_da_paragonare[LUNGHEZZA_MASSIMA_NOME + 2];

	y = 5;
	pos = 0;
	pos_contatti_trovati = 0;
	trovato = 0;
	while(pos < leggere_lunghezza(rubrica)){ // Ciclo che scorre tutti i contatti nella rubrica
		strcpy(stringa_da_paragonare, leggere_nome(leggere_contatto(rubrica, pos))); // Copia il nome del contatto corrente nella stringa da paragonare
		if(contiene_stringa(stringa_da_paragonare, nome_da_cercare) == 1){ // Verifica se il nome da cercare è contenuto nel nome del contatto corrente
			if(tipologia_ricerca == 1){ // Controlla se il contatto corrente non è preferito o bloccato
				if(controlla_stato(rubrica, selezione_preferito_bloccato, pos) == 0){
					trovato = 1; // Indica che è stato trovato almeno un contatto
					scrivere_valore(&contatti_trovati, pos_contatti_trovati, pos); // Scrive la posizione del contatto trovato nel vettore dei contatti trovati
					pos_contatti_trovati++;
					// Aggiorna il vettore dei contatti trovati e incrementa la posizione verticale
					contatti_trovati = riempire_vettore(rubrica, contatti_trovati, y, pos, pos_contatti_trovati);
					y += 2;
				}
			} else if(tipologia_ricerca == 2){ // Controlla se il contatto corrente è preferito o bloccato
				if(controlla_stato(rubrica, selezione_preferito_bloccato, pos) == 1){
					trovato = 1; // Indica che è stato trovato almeno un contatto
					scrivere_valore(&contatti_trovati, pos_contatti_trovati, pos); // Scrive la posizione del contatto trovato nel vettore dei contatti trovati
					pos_contatti_trovati++;
					// Aggiorna il vettore dei contatti trovati e incrementa la posizione verticale
					contatti_trovati = riempire_vettore(rubrica, contatti_trovati, y, pos, pos_contatti_trovati);
					y += 2;
				}
			} else if(tipologia_ricerca == 0){
				trovato = 1; // Indica che è stato trovato almeno un contatto
				scrivere_valore(&contatti_trovati, pos_contatti_trovati, pos); // Scrive la posizione del contatto trovato nel vettore dei contatti trovati
				pos_contatti_trovati++;
				// Aggiorna il vettore dei contatti trovati e incrementa la posizione verticale
				contatti_trovati = riempire_vettore(rubrica, contatti_trovati, y, pos, pos_contatti_trovati);
				y += 2;
			}
		}
		pos++; // Passa al contatto successivo nella rubrica
	}
	if(trovato == 0){ // Se non è stato trovato nessun contatto scrive un valore di errore nel vettore dei contatti trovati
		scrivere_valore(&contatti_trovati, 0, ERRORE_FUNZIONE_CONTATTO_MANCANTE);
		scrivere_dimensione_vettore(&contatti_trovati, 1);
	}
	return contatti_trovati; // Restituisce il vettore aggiornato dei contatti trovati
}

Vettore ricercare_per_cognome(Rubrica rubrica, Vettore contatti_trovati, int tipologia_ricerca, int selezione_preferito_bloccato, char* cognome_da_cercare)
{
	int y;
	int pos;
	int pos_contatti_trovati;
	bool trovato;
	char stringa_da_paragonare[LUNGHEZZA_MASSIMA_COGNOME + 2];

	y = 5;
	pos = 0;
	pos_contatti_trovati = 0;
	trovato = 0;
	while(pos < leggere_lunghezza(rubrica)){ // Ciclo che scorre tutti i contatti nella rubrica
		strcpy(stringa_da_paragonare, leggere_cognome(leggere_contatto(rubrica, pos))); // Copia il cognome del contatto corrente nella stringa da paragonare
		if(contiene_stringa(stringa_da_paragonare, cognome_da_cercare) == 1){ // Verifica se il nome da cercare è contenuto nel cognome del contatto corrente
			if(tipologia_ricerca == 1){ // Controlla se il contatto corrente non è preferito o bloccato
				if(controlla_stato(rubrica, selezione_preferito_bloccato, pos) == 0){
					trovato = 1; // Indica che è stato trovato almeno un contatto
					scrivere_valore(&contatti_trovati, pos_contatti_trovati, pos); // Scrive la posizione del contatto trovato nel vettore dei contatti trovati
					pos_contatti_trovati++;
					// Aggiorna il vettore dei contatti trovati e incrementa la posizione verticale
					contatti_trovati = riempire_vettore(rubrica, contatti_trovati, y, pos, pos_contatti_trovati);
					y += 2;
				}
			} else if(tipologia_ricerca == 2){ // Controlla se il contatto corrente è preferito o bloccato
				if(controlla_stato(rubrica, selezione_preferito_bloccato, pos) == 1){
					trovato = 1; // Indica che è stato trovato almeno un contatto
					scrivere_valore(&contatti_trovati, pos_contatti_trovati, pos); // Scrive la posizione del contatto trovato nel vettore dei contatti trovati
					pos_contatti_trovati++;
					// Aggiorna il vettore dei contatti trovati e incrementa la posizione verticale
					contatti_trovati = riempire_vettore(rubrica, contatti_trovati, y, pos, pos_contatti_trovati);
					y += 2;
				}
			} else if(tipologia_ricerca == 0){
				trovato = 1; // Indica che è stato trovato almeno un contatto
				scrivere_valore(&contatti_trovati, pos_contatti_trovati, pos); // Scrive la posizione del contatto trovato nel vettore dei contatti trovati
				pos_contatti_trovati++;
				// Aggiorna il vettore dei contatti trovati e incrementa la posizione verticale
				contatti_trovati = riempire_vettore(rubrica, contatti_trovati, y, pos, pos_contatti_trovati);
				y += 2;
			}
		}
		pos++; // Passa al contatto successivo nella rubrica
	}
	if(trovato == 0){ // Se non è stato trovato nessun contatto scrive un valore di errore nel vettore dei contatti trovati
		scrivere_valore(&contatti_trovati, 0, ERRORE_FUNZIONE_CONTATTO_MANCANTE);
		scrivere_dimensione_vettore(&contatti_trovati, 1);
	}
	return contatti_trovati; // Restituisce il vettore aggiornato dei contatti trovati
}

Vettore riempire_vettore(Rubrica rubrica, Vettore contatti_trovati, int y, int pos, int pos_contatti_trovati)
{
	scrivere_dimensione_vettore(&contatti_trovati, pos_contatti_trovati);  // Aggiorna la dimensione del vettore dei contatti trovati con la posizione corrente
	// Visualizza il contatto nella rubrica nella posizione specificata, con il numero del contatto trovato
	gotoXY(5, y);
	visualizzare_contatto(leggere_contatto(rubrica, pos), pos_contatti_trovati);
	return contatti_trovati; // Restituisce il vettore dei contatti trovati aggiornato
}

void visualizzare_contatto(Contatto contatto_da_stampare, int pos_contatti_trovati)
{
	printf("%d. ", pos_contatti_trovati); // Stampa la posizione del contatto nella lista dei contatti trovati
	// Stampa nome e cognome del contatto
	printf("%s ", leggere_nome(contatto_da_stampare));
	printf("%s", leggere_cognome(contatto_da_stampare));
	return;
}

int selezionare_contatto(Vettore contatti_trovati, char* criterio_selezione, FILE* file_messaggi, FILE* file_errori)
{
	int contatto_esatto;

	do{ // Ciclo per consentire all'utente di inserire il numero del contatto corretto o uscire
		contatto_esatto = -1;
		gotoXY(47, 2);
		stampare_riga(MESSAGGIO_INSERIRE_NUMERO, file_messaggi, file_errori);
		gotoXY(91, 2);
		printf("%s", criterio_selezione);
		scanf("%d", &contatto_esatto); // Legge l'input dell'utente per il numero del contatto
		pulire_stdin();
		pulire_schermata(2, 47, 2, 110);
		// Controlla se il numero del contatto inserito non è valido e non è un'opzione di uscita
		if((contatto_esatto < 1 || contatto_esatto > leggere_dimensione_vettore(contatti_trovati)) && contatto_esatto != 0){
			pulire_schermata(2, 102, 2, 120);
			stampare_errore(ERRORE_SCELTA_UTENTE, file_errori); // Stampa un messaggio di errore per indicare una scelta non valida
		}
	} while((contatto_esatto < 1 || contatto_esatto > leggere_dimensione_vettore(contatti_trovati)) && contatto_esatto != 0);
	return contatto_esatto; // Restituisce il numero del contatto selezionato
}

bool contiene_stringa(char* stringa_da_paragonare, char* stringa_da_cercare)
{
	bool esito;
	char* risultato;

	esito = 0;
	risultato = strstr(stringa_da_paragonare, stringa_da_cercare); // Cerca la stringa_da_cercare all'interno di stringa_da_paragonare
	if(risultato != NULL){  // Se risulato è diverso da NULL, significa che la stringa_da_cercare è contenuta in stringa_da_paragonare
		esito = 1;
	}
	return esito; // Restituisce il valore di esito, che indica se la stringa_da_cercare è contenuta in stringa_da_paragonare
}

bool esiste_contatto(Rubrica rubrica, Contatto nuovo_contatto, FILE* file_errori)
{
	int pos;
	bool esiste;

	pos = 0;
	esiste = 0;
	while(pos < leggere_lunghezza(rubrica) && esiste == 0){ // Ciclo per scorrere tutti i contatti nella rubrica
		// Confronta il nome e il cognome del nuovo_contatto con quelli del contatto nella posizione pos
		if(strcmp(leggere_nome(nuovo_contatto), leggere_nome(leggere_contatto(rubrica, pos))) == 0 && strcmp(leggere_cognome(nuovo_contatto), leggere_cognome(leggere_contatto(rubrica, pos))) == 0){
			esiste = 1; // Imposta esiste a vero se trova un contatto corrispondente
			stampare_errore(ERRORE_CONTATTO_ESISTENTE, file_errori); // Stampa il messaggio di errore
		}
		pos++; // Passa al contatto successivo nella rubrica
	}
	return esiste; // Restituisce esiste che indica se il contatto è presente o meno nella rubrica
}

bool controlla_stato(Rubrica rubrica, int selezione_preferito_bloccato, int pos)
{
	bool controllo;

	controllo = 0;
	if(selezione_preferito_bloccato == 1){ // Se selezione_preferito_bloccato è 1, controlla lo stato preferito del contatto alla posizione pos
		if(leggere_preferito(leggere_stato_contatto(leggere_contatto(rubrica, pos))) == 1){
			controllo = 1; // Se il contatto è preferito, imposta controllo a vero
		}
	} else if(selezione_preferito_bloccato == 2){ // Se selezione_preferito_bloccato è 2, controlla lo stato bloccato del contatto alla posizione pos
		if(leggere_bloccato(leggere_stato_contatto(leggere_contatto(rubrica, pos))) == 1){
			controllo = 1; // Se il contatto è bloccato, imposta controllo a vero
		}
	}
	return controllo; // Restituisce il valore di controllo, che indica se il contatto è preferito o bloccato
}
