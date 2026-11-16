#include "Globali.h"
#include "Gestire_Tipi.h"
#include "Gestire_Schermo.h"
#include "Gestire_File.h"
#include "Gestire_Contatto.h"
#include "Ricercare_Contatto.h"
#include "Visualizzare_Rubrica.h"

// Operazioni menù principale
void mostrare_menu();
Rubrica scegliere_nuovo_contatto(Rubrica rubrica, char* interfaccia_nuovo_contatto_path, FILE* file_messaggi, FILE* file_errori);
Rubrica scegliere_cancellare_contatto(Rubrica rubrica, char* interfaccia_cancellare_contatto_path, char* interfaccia_inserire_nome_path, char* interfaccia_inserire_cognome_path, FILE* file_messaggi, FILE* file_errori);
void scegliere_ricercare_contatto(Rubrica rubrica, char* interfaccia_ricercare_contatto_path, char* interfaccia_ricercare_contatto_stato_path, char* interfaccia_inserire_nome_path, char* interfaccia_inserire_cognome_path, FILE* file_messaggi, FILE* file_errori);
Rubrica scegliere_modificare_contatto(Rubrica rubrica, char* interfaccia_modificare_contatto_path, char* interfaccia_modificare_nome_path, char* interfaccia_modificare_cognome_path, char* interfaccia_modificare_numero_path, char* interfaccia_opzioni_modifica_path, char* interfaccia_inserire_nome_path, char* interfaccia_inserire_cognome_path, FILE* file_messaggi, FILE* file_errori);
Rubrica scegliere_ordinare_rubrica(Rubrica rubrica, char* interfaccia_ordinare_rubrica_path, FILE* file_messaggi, FILE* file_errori);
void scegliere_visualizzare_rubrica(Rubrica rubrica, char* interfaccia_visualizzare_rubrica_path, char* interfaccia_tipologia_visualizzazione_path, FILE* file_messaggi, FILE* file_errori);
Rubrica scegliere_gestire_stati(Rubrica rubrica, char* interfaccia_gestire_stati_path, char* interfaccia_inserire_nome_path, char* interfaccia_inserire_cognome_path, char* interfaccia_aggiungere_preferiti_path, char* interfaccia_rimuovere_preferiti_path, char* interfaccia_aggiungere_bloccati_path, char* interfaccia_rimuovere_bloccati_path, FILE* file_messaggi, FILE* file_errori);
Rubrica scegliere_importare_rubrica(Rubrica rubrica, char* file_rubrica_path, FILE* file_messaggi, FILE* file_errori);
void scegliere_esportare_rubrica(Rubrica rubrica, char* file_rubrica_path, FILE* file_messaggi, FILE* file_errori);
// Operazioni per poter visualizzare le interfacce da qualsiasi utente senza cambiare manualmente i percorsi dei file
void set_absolute_path(char* executible_path);
char* relative_to_absolute_path(char* relative_path);

char* absolute_path; // Dichiarazione della variabile esterna

int main(int argc, char *argv[])
{
	set_absolute_path(argv[0]); // Imposta il percorso assoluto del programma basato sul percorso dell'eseguibile
	mostrare_menu(); // Mostra il menu principale del programma
    return 0; // Termina il programma con stato di uscita 0
}

void mostrare_menu()
{
	Rubrica rubrica;
	FILE* interfaccia_rubrica_telefonica;
	FILE* file_errori;
	FILE* file_messaggi;
	int scelta;
	char* file_errori_path;
	char* file_messaggi_path;
	char* interfaccia_rubrica_telefonica_path;
	char* interfaccia_nuovo_contatto_path;
	char* interfaccia_cancellare_contatto_path;
	char* interfaccia_inserire_nome_path;
	char* interfaccia_inserire_cognome_path;
	char* interfaccia_ricercare_contatto_path;
	char* interfaccia_ricercare_contatto_stato_path;
	char* interfaccia_modificare_contatto_path;
	char* interfaccia_modificare_nome_path;
	char* interfaccia_modificare_cognome_path;
	char* interfaccia_modificare_numero_path;
	char* interfaccia_opzioni_modifica_path;
	char* interfaccia_ordinare_rubrica_path;
	char* interfaccia_visualizzare_rubrica_path;
	char* interfaccia_tipologia_visualizzazione_path;
	char* interfaccia_gestire_stati_path;
	char* interfaccia_aggiungere_preferiti_path;
	char* interfaccia_rimuovere_preferiti_path;
	char* interfaccia_aggiungere_bloccati_path;
	char* interfaccia_rimuovere_bloccati_path;
	char* file_rubrica_path;

	// Percorsi assoluti dei file necessari
	file_errori_path = 							 relative_to_absolute_path("Interfacce/file_errori.txt");
	file_messaggi_path =                         relative_to_absolute_path("Interfacce/file_messaggi.txt");
	interfaccia_rubrica_telefonica_path = 		 relative_to_absolute_path("Interfacce/interfaccia_rubrica_telefonica.txt");
	interfaccia_nuovo_contatto_path = 			 relative_to_absolute_path("Interfacce/interfaccia_nuovo_contatto.txt");
	interfaccia_cancellare_contatto_path  =      relative_to_absolute_path("Interfacce/interfaccia_cancellare_contatto.txt");
	interfaccia_inserire_nome_path = 			 relative_to_absolute_path("Interfacce/interfaccia_inserire_nome.txt");
	interfaccia_inserire_cognome_path = 		 relative_to_absolute_path("Interfacce/interfaccia_inserire_cognome.txt");
	interfaccia_ricercare_contatto_path = 		 relative_to_absolute_path("Interfacce/interfaccia_ricercare_contatto.txt");
	interfaccia_ricercare_contatto_stato_path =  relative_to_absolute_path("Interfacce/interfaccia_ricercare_contatto_stato.txt");
	interfaccia_modificare_contatto_path = 		 relative_to_absolute_path("Interfacce/interfaccia_modificare_contatto.txt");
	interfaccia_modificare_nome_path = 			 relative_to_absolute_path("Interfacce/interfaccia_modificare_nome.txt");
	interfaccia_modificare_cognome_path = 		 relative_to_absolute_path("Interfacce/interfaccia_modificare_cognome.txt");
	interfaccia_modificare_numero_path = 		 relative_to_absolute_path("Interfacce/interfaccia_modificare_numero.txt");
	interfaccia_opzioni_modifica_path = 		 relative_to_absolute_path("Interfacce/interfaccia_opzioni_modifica.txt");
	interfaccia_ordinare_rubrica_path =          relative_to_absolute_path("Interfacce/interfaccia_ordinare_rubrica.txt");
	interfaccia_visualizzare_rubrica_path =      relative_to_absolute_path("Interfacce/interfaccia_visualizzare_rubrica.txt");
	interfaccia_tipologia_visualizzazione_path = relative_to_absolute_path("Interfacce/interfaccia_tipologia_visualizzazione.txt");
	interfaccia_gestire_stati_path = 			 relative_to_absolute_path("Interfacce/interfaccia_gestire_stati.txt");
	interfaccia_aggiungere_preferiti_path =      relative_to_absolute_path("Interfacce/interfaccia_aggiungere_preferiti.txt");
	interfaccia_rimuovere_preferiti_path =       relative_to_absolute_path("Interfacce/interfaccia_rimuovere_preferiti.txt");
	interfaccia_aggiungere_bloccati_path =       relative_to_absolute_path("Interfacce/interfaccia_aggiungere_bloccati.txt");
	interfaccia_rimuovere_bloccati_path =        relative_to_absolute_path("Interfacce/interfaccia_rimuovere_bloccati.txt");
	file_rubrica_path =                          relative_to_absolute_path("Rubrica/file_rubrica.bin");

	scrivere_lunghezza(&rubrica, 0); // Inizializza la lunghezza della rubrica a 0
	file_errori = fopen(file_errori_path, "r"); // Apre il file degli errori in modalità lettura
	if(esiste_file(file_errori) == 0){ // Controlla che il file degli errori esiste
		file_messaggi = fopen(file_messaggi_path, "r"); // Apre il file dei messaggi in modalità lettura
		if(esiste_file(file_messaggi) == 0){ // Controlla che il file dei messaggi esiste
			do{
				// Apre l'interfaccia della rubrica telefonica in modalità lettura
				interfaccia_rubrica_telefonica = fopen(interfaccia_rubrica_telefonica_path, "r");
				if(esiste_file(interfaccia_rubrica_telefonica) == 0){ // Controlla che l'interfaccia della rubrica telefonica esiste
					scelta = -1;
					system("cls");
					rewind(interfaccia_rubrica_telefonica);
					stampare_interfaccia(interfaccia_rubrica_telefonica, file_errori); // Stampa l'interfaccia
					fclose(interfaccia_rubrica_telefonica); // Chiude l'interfaccia della rubrica telefonica
					gotoXY(13, 23);
					scanf("%d", &scelta); // Legge l'input dell'utente per la scelta
					pulire_stdin();
					if(scelta == 1){ // Aggiunge un nuovo contatto alla rubrica
						rubrica = scegliere_nuovo_contatto(rubrica, interfaccia_nuovo_contatto_path, file_messaggi, file_errori);
					} else if(scelta == 2){ // Cancella un contatto dalla rubrica
						if(leggere_lunghezza(rubrica) != 0){
							rubrica = scegliere_cancellare_contatto(rubrica, interfaccia_cancellare_contatto_path, interfaccia_inserire_nome_path, interfaccia_inserire_cognome_path, file_messaggi, file_errori);
						} else{
							stampare_errore(ERRORE_RUBRICA_VUOTA, file_errori);
						}
					} else if(scelta == 3){ // Ricerca un contatto nella rubrica
						if(leggere_lunghezza(rubrica) != 0){
							scegliere_ricercare_contatto(rubrica, interfaccia_ricercare_contatto_path, interfaccia_ricercare_contatto_stato_path, interfaccia_inserire_nome_path, interfaccia_inserire_cognome_path, file_messaggi, file_errori);
						} else{
							stampare_errore(ERRORE_RUBRICA_VUOTA, file_errori);
						}
					} else if(scelta == 4){ // Modifica un contatto nella rubrica
						if(leggere_lunghezza(rubrica) != 0){
							rubrica = scegliere_modificare_contatto(rubrica, interfaccia_modificare_contatto_path, interfaccia_modificare_nome_path, interfaccia_modificare_cognome_path, interfaccia_modificare_numero_path, interfaccia_opzioni_modifica_path, interfaccia_inserire_nome_path, interfaccia_inserire_cognome_path, file_messaggi, file_errori);
						} else{
							stampare_errore(ERRORE_RUBRICA_VUOTA, file_errori);
						}
					} else if(scelta == 5){ // Ordina la rubrica
						if(leggere_lunghezza(rubrica) != 0){
							rubrica = scegliere_ordinare_rubrica(rubrica, interfaccia_ordinare_rubrica_path, file_messaggi, file_errori);
						} else{
							stampare_errore(ERRORE_RUBRICA_VUOTA, file_errori);
						}
					} else if(scelta == 6){ // Visualizza la rubrica
						if(leggere_lunghezza(rubrica) != 0){
							scegliere_visualizzare_rubrica(rubrica, interfaccia_visualizzare_rubrica_path, interfaccia_tipologia_visualizzazione_path, file_messaggi, file_errori);
						} else{
							stampare_errore(ERRORE_RUBRICA_VUOTA, file_errori);
						}
					} else if(scelta == 7){ // Gestisce gli stati dei contatti
						if(leggere_lunghezza(rubrica) != 0){
							rubrica = scegliere_gestire_stati(rubrica, interfaccia_gestire_stati_path, interfaccia_inserire_nome_path, interfaccia_inserire_cognome_path, interfaccia_aggiungere_preferiti_path, interfaccia_rimuovere_preferiti_path, interfaccia_aggiungere_bloccati_path, interfaccia_rimuovere_bloccati_path, file_messaggi, file_errori);
						} else{
							stampare_errore(ERRORE_RUBRICA_VUOTA, file_errori);
						}
					} else if(scelta == 8){ // Importa la rubrica da un file
						rubrica = scegliere_importare_rubrica(rubrica, file_rubrica_path, file_messaggi, file_errori);
					} else if(scelta == 9){ // Esporta la rubrica in un file
						if(leggere_lunghezza(rubrica) != 0){
							scegliere_esportare_rubrica(rubrica, file_rubrica_path, file_messaggi, file_errori);
						} else{
							stampare_errore(ERRORE_RUBRICA_VUOTA, file_errori);
						}
					} else if(scelta != 0){ // Stampa un errore per una scelta non valida
						stampare_errore(ERRORE_SCELTA_UTENTE, file_errori);
					}
				} else{
					stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Stampa un errore se manca l'interfaccia della rubrica telefonica
				}
			} while(scelta != 0); // Continua finché l'utente non sceglie di uscire
		} else{
			stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Se il file non esiste, stampa un messaggio di errore
		}
		fclose(file_messaggi); // Chiude il file dei messaggi
	} else{
		// Se manca il file degli errori, stampa un messaggio di errore
		system("cls");
		gotoXY(2, 2);
		printf("FILE ERRORI MANCANTE.\n");
		system("pause");
	}
	fclose(file_errori); // Chiude il file degli errori
	return;
}

Rubrica scegliere_nuovo_contatto(Rubrica rubrica, char* interfaccia_nuovo_contatto_path, FILE* file_messaggi, FILE* file_errori)
{
	FILE* interfaccia_nuovo_contatto;

	// Apre i file dell'interfaccia in modalità lettura
	interfaccia_nuovo_contatto = fopen(interfaccia_nuovo_contatto_path, "r");
	// Chiamata alla funzione per inserire un nuovo contatto nella rubrica
	rubrica = inserire_nuovo_contatto(rubrica, interfaccia_nuovo_contatto, file_messaggi, file_errori);
	// Chiude i file dell'interfaccia
	fclose(interfaccia_nuovo_contatto);
	return rubrica; // Restituisce la rubrica aggiornata
}

Rubrica scegliere_cancellare_contatto(Rubrica rubrica, char* interfaccia_cancellare_contatto_path, char* interfaccia_inserire_nome_path, char* interfaccia_inserire_cognome_path, FILE* file_messaggi, FILE* file_errori)
{
	FILE* interfaccia_cancellare_contatto;
	FILE* interfaccia_inserire_nome;
	FILE* interfaccia_inserire_cognome;

	// Apre i file dell'interfaccia in modalità lettura
	interfaccia_cancellare_contatto = fopen(interfaccia_cancellare_contatto_path, "r");
	interfaccia_inserire_nome = fopen(interfaccia_inserire_nome_path, "r");
	interfaccia_inserire_cognome = fopen(interfaccia_inserire_cognome_path, "r");
	// Chiamata alla funzione per cancellare un contatto dalla rubrica
	rubrica = cancellare_contatto(rubrica, interfaccia_cancellare_contatto, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_messaggi, file_errori);
	// Chiude i file dell'interfaccia
	fclose(interfaccia_cancellare_contatto);
	fclose(interfaccia_inserire_nome);
	fclose(interfaccia_inserire_cognome);
	return rubrica; // Restituisce la rubrica aggiornata
}

void scegliere_ricercare_contatto(Rubrica rubrica, char* interfaccia_ricercare_contatto_path, char* interfaccia_ricercare_contatto_stato_path, char* interfaccia_inserire_nome_path, char* interfaccia_inserire_cognome_path, FILE* file_messaggi, FILE* file_errori)
{
	FILE* interfaccia_ricercare_contatto;
	FILE* interfaccia_inserire_nome;
	FILE* interfaccia_inserire_cognome;
	FILE* interfaccia_ricercare_contatto_stato;

	// Apre i file dell'interfaccia in modalità lettura
	interfaccia_ricercare_contatto = fopen(interfaccia_ricercare_contatto_path, "r");
	interfaccia_inserire_nome = fopen(interfaccia_inserire_nome_path, "r");
	interfaccia_inserire_cognome = fopen(interfaccia_inserire_cognome_path, "r");
	interfaccia_ricercare_contatto_stato = fopen(interfaccia_ricercare_contatto_stato_path, "r");
	// Chiamata alla funzione per ricercare un contatto nella rubrica
	ricercare_contatto(rubrica, interfaccia_ricercare_contatto, interfaccia_ricercare_contatto_stato, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_messaggi, file_errori);
	// Chiude i file dell'interfaccia
	fclose(interfaccia_ricercare_contatto);
	fclose(interfaccia_inserire_nome);
	fclose(interfaccia_inserire_cognome);
	fclose(interfaccia_ricercare_contatto_stato);
	return;
}

Rubrica scegliere_modificare_contatto(Rubrica rubrica, char* interfaccia_modificare_contatto_path, char* interfaccia_modificare_nome_path, char* interfaccia_modificare_cognome_path, char* interfaccia_modificare_numero_path, char* interfaccia_opzioni_modifica_path, char* interfaccia_inserire_nome_path, char* interfaccia_inserire_cognome_path, FILE* file_messaggi, FILE* file_errori)
{
	FILE* interfaccia_modificare_contatto;
	FILE* interfaccia_modificare_nome;
	FILE* interfaccia_modificare_cognome;
	FILE* interfaccia_modificare_numero;
	FILE* interfaccia_opzioni_modifica;
	FILE* interfaccia_inserire_nome;
	FILE* interfaccia_inserire_cognome;

	// Apre i file dell'interfaccia in modalità lettura
	interfaccia_modificare_contatto = fopen(interfaccia_modificare_contatto_path, "r");
	interfaccia_modificare_nome = fopen(interfaccia_modificare_nome_path, "r");
	interfaccia_modificare_cognome = fopen(interfaccia_modificare_cognome_path, "r");
	interfaccia_modificare_numero = fopen(interfaccia_modificare_numero_path, "r");
	interfaccia_opzioni_modifica = fopen(interfaccia_opzioni_modifica_path, "r");
	interfaccia_inserire_nome = fopen(interfaccia_inserire_nome_path, "r");
	interfaccia_inserire_cognome = fopen(interfaccia_inserire_cognome_path, "r");
	// Chiamata alla funzione per modificare un contatto nella rubrica
	rubrica = modificare_contatto(rubrica, interfaccia_modificare_contatto, interfaccia_modificare_nome, interfaccia_modificare_cognome, interfaccia_modificare_numero, interfaccia_opzioni_modifica, interfaccia_inserire_nome, interfaccia_inserire_cognome, file_messaggi, file_errori);
	// Chiude i file dell'interfaccia
	fclose(interfaccia_modificare_contatto);
	fclose(interfaccia_modificare_nome);
	fclose(interfaccia_modificare_cognome);
	fclose(interfaccia_modificare_numero);
	fclose(interfaccia_inserire_nome);
	fclose(interfaccia_inserire_cognome);
	return rubrica; // Restituisce la rubrica aggiornata
}

Rubrica scegliere_ordinare_rubrica(Rubrica rubrica, char* interfaccia_ordinare_rubrica_path, FILE* file_messaggi, FILE* file_errori)
{
	FILE* interfaccia_ordinare_rubrica;

	// Apre i file dell'interfaccia in modalità lettura
	interfaccia_ordinare_rubrica = fopen(interfaccia_ordinare_rubrica_path, "r");
	// Chiamata alla funzione per ordinare la rubrica
	rubrica = ordinare_rubrica(rubrica, interfaccia_ordinare_rubrica, file_messaggi, file_errori);
	// Chiude i file dell'interfaccia
	fclose(interfaccia_ordinare_rubrica);
	return rubrica; // Restituisce la rubrica aggiornata
}

void scegliere_visualizzare_rubrica(Rubrica rubrica, char* interfaccia_visualizzare_rubrica_path, char* interfaccia_tipologia_visualizzazione_path, FILE* file_messaggi, FILE* file_errori)
{
	FILE* interfaccia_visualizzare_rubrica;
	FILE* interfaccia_tipologia_visualizzazione;

	// Apre i file dell'interfaccia in modalità lettura
	interfaccia_visualizzare_rubrica = fopen(interfaccia_visualizzare_rubrica_path, "r");
	interfaccia_tipologia_visualizzazione = fopen(interfaccia_tipologia_visualizzazione_path, "r");
	// Chiamata alla funzione per visualizzare la rubrica
	visualizzare_rubrica(rubrica, interfaccia_visualizzare_rubrica, interfaccia_tipologia_visualizzazione, file_messaggi, file_errori);
	// Chiude i file dell'interfaccia
	fclose(interfaccia_visualizzare_rubrica);
	fclose(interfaccia_tipologia_visualizzazione);
	return;
}

Rubrica scegliere_gestire_stati(Rubrica rubrica, char* interfaccia_gestire_stati_path, char* interfaccia_inserire_nome_path, char* interfaccia_inserire_cognome_path, char* interfaccia_aggiungere_preferiti_path, char* interfaccia_rimuovere_preferiti_path, char* interfaccia_aggiungere_bloccati_path, char* interfaccia_rimuovere_bloccati_path, FILE* file_messaggi, FILE* file_errori)
{
	FILE* interfaccia_gestire_stati;
	FILE* interfaccia_inserire_nome;
	FILE* interfaccia_inserire_cognome;
	FILE* interfaccia_aggiungere_preferiti;
	FILE* interfaccia_rimuovere_preferiti;
	FILE* interfaccia_aggiungere_bloccati;
	FILE* interfaccia_rimuovere_bloccati;

	// Apre i file dell'interfaccia in modalità lettura
	interfaccia_gestire_stati = fopen(interfaccia_gestire_stati_path, "r");
	interfaccia_inserire_nome = fopen(interfaccia_inserire_nome_path, "r");
	interfaccia_inserire_cognome = fopen(interfaccia_inserire_cognome_path, "r");
	interfaccia_aggiungere_preferiti = fopen(interfaccia_aggiungere_preferiti_path, "r");
	interfaccia_rimuovere_preferiti = fopen(interfaccia_rimuovere_preferiti_path, "r");
	interfaccia_aggiungere_bloccati = fopen(interfaccia_aggiungere_bloccati_path, "r");
	interfaccia_rimuovere_bloccati = fopen(interfaccia_rimuovere_bloccati_path, "r");
	// Chiamata alla funzione per gestire gli stati dei contatti nella rubrica
	rubrica = gestire_stati(rubrica, interfaccia_gestire_stati, interfaccia_inserire_nome, interfaccia_inserire_cognome, interfaccia_aggiungere_preferiti, interfaccia_rimuovere_preferiti, interfaccia_aggiungere_bloccati, interfaccia_rimuovere_bloccati, file_messaggi, file_errori);
	// Chiude i file dell'interfaccia
	fclose(interfaccia_gestire_stati);
	fclose(interfaccia_inserire_nome);
	fclose(interfaccia_inserire_cognome);
	fclose(interfaccia_aggiungere_preferiti);
	fclose(interfaccia_rimuovere_preferiti);
	fclose(interfaccia_aggiungere_bloccati);
	fclose(interfaccia_rimuovere_bloccati);
	return rubrica; // Restituisce la rubrica aggiornata
}

Rubrica scegliere_importare_rubrica(Rubrica rubrica, char* file_rubrica_path, FILE* file_messaggi, FILE* file_errori)
{
	FILE* file_rubrica;

	// Apre il file della rubrica in modalità lettura binaria
	file_rubrica = fopen(file_rubrica_path, "rb");
	// Chiamata alla funzione per importare la rubrica dal file
	rubrica = importare_rubrica(file_rubrica, file_messaggi, file_errori);
	// Chiude il file della rubrica dopo aver completato l'importazione
	fclose(file_rubrica);
	return rubrica; // Restituisce la rubrica aggiornata
}

void scegliere_esportare_rubrica(Rubrica rubrica, char* file_rubrica_path, FILE* file_messaggi, FILE* file_errori)
{
	FILE* file_rubrica;

	// Apre il file della rubrica in modalità scrittura binaria
	file_rubrica = fopen(file_rubrica_path, "wb");
	// Chiamata alla funzione per esportare la rubrica nel file
	esportare_rubrica(rubrica, file_rubrica, file_messaggi, file_errori);
	// Chiude il file della rubrica dopo aver completato l'esportazione
	fclose(file_rubrica);
	return;
}

void set_absolute_path(char* executible_path)
{
	char* file_path = executible_path; // Puntatore al percorso dell'eseguibile
	char* application_name = strrchr(executible_path, '\\'); // Trova il nome dell'applicazione nell'eseguibile
	// Imposta il carattere di fine stringa per ottenere il percorso della cartella dell'applicazione
	file_path[strlen(file_path) - strlen(application_name) + 1] = '\0';
	absolute_path = file_path; // Assegna il percorso assoluto risultante alla variabile esterna "absolute_path"
	return;
}

char* relative_to_absolute_path(char* relative_path)
{
	// Allocazione della memoria per la nuova stringa che conterrà il percorso assoluto
	char* new_string = (char *)malloc(strlen(absolute_path) + strlen(relative_path) + 1);
	strcpy(new_string, absolute_path); // Copia del percorso assoluto nella nuova stringa
	strcat(new_string, relative_path); // Concatenazione del percorso relativo alla fine del percorso assoluto
	return new_string; // Restituzione della nuova stringa che contiene il percorso assoluto completo
}
