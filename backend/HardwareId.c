#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// La funzione ora accetta il puntatore al buffer dove scrivere
int get_bios_uuid(char *dest_uuid, size_t size) {
    FILE *fp;
    char buffer[256];

    const char* cmd = "powershell -Command \"(Get-WmiObject Win32_ComputerSystemProduct).UUID\"";

    fp = _popen(cmd, "r");
    if (fp == NULL) return 0;

    if (fgets(buffer, 256, fp) != NULL) {
        strtok(buffer, "\r\n ");
        // Copiamo i dati nel buffer del main
        strncpy(dest_uuid, buffer, size - 1);
        dest_uuid[size - 1] = '\0'; // Assicuriamoci che finisca con lo zero
    }

    _pclose(fp);

    // Controllo se è valido
    if (strlen(dest_uuid) == 0 || strstr(dest_uuid, "FFFFFFFF")) {
        return 0; // Fallimento
    }

    return 1; // Successo
}

int main() {
    char uuid[256] = {0}; // Prepariamo lo spazio qui nel main

    if (get_bios_uuid(uuid, sizeof(uuid))) {
        printf("%s", uuid);
    }
    
    return 0;
}