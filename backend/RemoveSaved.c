#include <windows.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if(argc >= 2) {
        if(strcmp(argv[1], "--all") == 0) {
            if (system("rmdir /s /q \"C:\\Usual\"")) {
                printf("Cartella rimossa con successo!\n");
            } else {
                printf("Errore durante la rimozione. Codice: %lu\n", GetLastError());
            }
        }
    } else {
        if (system("rmdir /s /q \"C:\\Usual\\saved\"")) {
            printf("Cartella rimossa con successo!\n");
        } else {
            printf("Errore durante la rimozione. Codice: %lu\n", GetLastError());
        }
    }
    return 0;
}