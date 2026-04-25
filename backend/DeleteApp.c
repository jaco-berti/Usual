#include <windows.h>
#include <stdio.h>

int main(void) {
	system("taskkill/im usual.exe");
	
	char nome_file[] = "usual.exe"; // Il file da cercare
    char percorso_trovato[MAX_PATH];  // Qui verrà salvato il path completo
    char *file_part;                  // Puntatore richiesto dalla funzione

    // Cerca il file nelle directory del PATH
    DWORD risultato = SearchPath(
        NULL,            // NULL usa il percorso di ricerca predefinito (PATH)
        nome_file,       // Nome del file da cercare
        NULL,            // Estensione (non serve se già inclusa nel nome)
        MAX_PATH,        // Dimensione del buffer di destinazione
        percorso_trovato,// Dove scrivere il percorso completo
        &file_part       // Riceve l'indirizzo della parte finale (nome file)
    );

    if (risultato > 0) {
    	char* command = "del ";
    	char* tot_command = strcpy(command, percorso_trovato);
        system("del ")
    } else {
        printf("File '%s' non trovato nel PATH.\n", nome_file);
    }
}