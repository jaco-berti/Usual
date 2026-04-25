#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

void disable_conn();
void enable_conn();

int main() {
    int isPressed = 0;
    while(1) {
        if(GetAsyncKeyState(VK_TAB) && (GetAsyncKeyState(VK_MENU) & 0x8000) && !isPressed) {
            disable_conn();
            printf("Internet Off\n");
            isPressed = 1;
        }

        if(GetAsyncKeyState(VK_TAB) && (GetAsyncKeyState(VK_MENU) & 0x8000) && isPressed) {
            enable_conn();
            printf("Interner On\n");
            isPressed = 0;
        }
    }
    return 0;
}

void disable_conn() {
    system("netsh interface set interface \"Wi-Fi\" disable");
    system("netsh interface set interface \"Ethernet\" disable");
}

void enable_conn() {
    system("netsh interface set interface \"Wi-Fi\" enable");
    system("netsh interface set interface \"Ethernet\" enable");
}