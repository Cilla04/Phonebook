#ifndef GESTIRE_FILE_H_
#define GESTIRE_FILE_H_

#include "Globali.h"
#include "Gestire_Tipi.h"
#include "Gestire_Schermo.h"

// Operazione importre rubrica da file
Rubrica importare_rubrica(FILE* file_rubrica, FILE* file_messaggi, FILE* file_errori);
// Operazione esportare rubrica su file
void esportare_rubrica(Rubrica rubrica, FILE* file_rubrica, FILE* file_messaggi, FILE* file_errori);
// Operazione che verifica se esiste il file
bool esiste_file(FILE* file);

#endif /* GESTIRE_FILE_H_ */
