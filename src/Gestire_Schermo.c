#include "Gestire_Schermo.h"

void gotoXY(int x, int y)
{
	// Imposta la posizione del cursore della console alle coordinate specificate
	COORD CursorPos = {x, y};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, CursorPos);
	return;
}

void pulire_schermata(int riga_inizio, int colonna_inizio, int riga_fine, int colonna_fine)
{
	int i;
	int j;

	i = riga_inizio;
	while(i <= riga_fine){ // Ciclo esterno per attraversare le righe dalla riga_inizio alla riga_fine
		j = colonna_inizio;
		while(j <= colonna_fine){ // Ciclo interno per attraversare le colonne dalla colonna_inizio alla colonna_fine
			// Sposta il cursore alla posizione corrente e stampa uno spazio vuoto per cancellarne il contenuto
			gotoXY(j, i);
			printf(" ");
			j++;
		}
		i++;
	}
	gotoXY(0, 0);
	return;
}

void stampare_interfaccia(FILE* file, FILE* file_errori)
{
	char carattere;

	if(esiste_file(file) == 0){ // Controlla se il file esiste
		while((carattere = fgetc(file)) != EOF){  // Legge il file carattere per carattere fino a raggiungere la fine del file (EOF)
			printf("%c", carattere); // Stampa il carattere corrente sulla console
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Se il file non esiste, stampa un messaggio di errore
	}
	return;
}

void stampare_riga(int riga_desiderata, FILE* file, FILE* file_errori)
{
	char carattere;
	int riga;
	bool esci;

	riga = 1;
	esci = 0;
	if(esiste_file(file) == 0){ // Controlla se il file esiste
		rewind(file);
		// Legge il file carattere per carattere fino a raggiungere la fine del file (EOF) o fino a quando la riga desiderata è stata trovata
		while((carattere = fgetc(file)) != EOF && esci == 0){
			if(riga == riga_desiderata){ // Se la riga corrente è quella desiderata stampa i caratteri della riga desiderata
				do{
					printf("%c", carattere);
				} while((carattere = fgetc(file)) != EOF && carattere != '\n');
				printf("\n"); // Stampa un carattere di nuova riga per completare la stampa della riga
				esci = 1;  // Imposta esci a vero per indicare che la riga desiderata è stata trovata
			}
			if(carattere == '\n'){ // Se il carattere corrente è una nuova riga, incrementa il contatore delle righe
				riga++;
			}
		}
	} else{
		stampare_errore(ERRORE_FILE_MANCANTE, file_errori); // Se il file non esiste, stampa un messaggio di errore
	}
	return;
}

void stampare_errore(int errore, FILE* file_errori)
{
	// Stampa la riga specificata dal file degli errori
	gotoXY(55, 15);
	stampare_riga(errore, file_errori, file_errori);
	Sleep(1500);
	pulire_schermata(15, 55, 15, 100);
	return;
}

void stampare_messaggio(int messaggio, FILE* file_messaggi, FILE* file_errori)
{
	// Stampa la riga specificata dal file dei messaggi
	system("cls");
	gotoXY(2, 2);
	stampare_riga(messaggio, file_messaggi, file_errori);
	Sleep(1500);
	return;
}

void pulire_stdin()
{
    int c;

    while((c = getchar()) != '\n' && c != EOF); // Ciclo per leggere e scartare i caratteri fino a trovare un nuova riga o la fine del file
    return;
}

void pulire_buffer_input(char* stringa)
{
    if(strchr(stringa, '\n') == NULL){ // Controlla se la stringa contiene un carattere di nuova riga
        int ch;
        while((ch = getchar()) != '\n' && ch != EOF); // Ciclo per leggere e scartare i caratteri fino a trovare un nuova riga o la fine del file
        stringa[0] = '\0'; // Imposta il primo carattere della stringa a '\0' per indicare una stringa vuota
    } else{
    	// Se c'è un nuova riga nella stringa, trova la posizione del nuova riga e lo sostituisce con il terminatore di stringa '\0'
        stringa[strcspn(stringa, "\n")] = 0;
    }
    return;
}
