#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

// Comunica al linker di usare la libreria di rete di Windows
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // 1. Inizializzazione Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Errore inizializzazione WSA. Codice: %d\n", WSAGetLastError());
        return 1;
    }

    // 2. Creazione del Socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Errore creazione socket. Codice: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // 3. Configurazione indirizzo e porta
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Ascolta su tutte le interfacce di rete
    address.sin_port = htons(8080);       // Porta 8080

    // 4. Bind (Legame socket-porta)
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        printf("Errore Bind. Codice: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // 5. Listen (Mettiti in ascolto)
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Errore Listen. Codice: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Server On! Listening...\n");
    // Il server aspetta un client
    new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (new_socket == INVALID_SOCKET) {
        printf("Errore Accept. Codice: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    int done = 1;
    while(done) {
        // 7. Ricevi il messaggio
        memset(buffer, 0, 1024);
        int valread = recv(new_socket, buffer, 1024, 0);
        if (valread > 0) {
            printf("%s", buffer);
        }
        else if (valread <= 0) {
            done = 0; // chiudi comunicazione
            HINSTANCE result = ShellExecute(NULL, "open", "ServerKeyboard.exe", NULL, NULL, SW_SHOWNORMAL);
        }
    }

    // 8. Pulizia finale
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();

    printf("Server spento.\n");
    return 0;
}