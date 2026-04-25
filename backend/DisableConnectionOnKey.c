#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>

void disable_conn();
void enable_conn();

int main(int argc, char *argv[]) {
    // To use argv variable call argv[index]
    // argc is the amount of element passed on argv, the first is always the program name
    int isPressed = 0;
    int isLetter = 0;
    char key = 0;

    if (strcmp(argv[1], "ALT") == 0) {
        key = VK_MENU;
    } 
    else if (strcmp(argv[1], "CTRL") == 0) {
        key = VK_CONTROL;
    } 
    else if (strcmp(argv[1], "LEFT_MOUSE") == 0) {
        key = VK_LBUTTON;
    } 
    else if (strcmp(argv[1], "RIGHT_MOUSE") == 0) {
        key = VK_RBUTTON;
    } 
    else if (strcmp(argv[1], "MIDDLE_MOUSE") == 0) {
        key = VK_MBUTTON;
    } 
    else if (strcmp(argv[1], "BACKSPACE") == 0) {
        key = VK_BACK;
    } 
    else if (strcmp(argv[1], "TAB") == 0) {
        key = VK_TAB;
    } 
    else if (strcmp(argv[1], "ENTER") == 0) {
        key = VK_RETURN;
    } 
    else if (strcmp(argv[1], "SHIFT") == 0) {
        key = VK_SHIFT;
    } 
    else if (strcmp(argv[1], "PAUSE") == 0) {
        key = VK_PAUSE;
    } 
    else if (strcmp(argv[1], "SPACE") == 0) {
        key = VK_SPACE;
    } 
    else if (strcmp(argv[1], "CAPITAL") == 0) {
        key = VK_CAPITAL;
    } 
    else if (strcmp(argv[1], "ESC") == 0) {
        key = VK_ESCAPE;
    } 
    else if (strcmp(argv[1], "HOME") == 0) {
        key = VK_HOME;
    } 
    else if (strcmp(argv[1], "INSERT") == 0) {
        key = VK_INSERT;
    } 
    else if (strcmp(argv[1], "0") == 0) {
        key = 48;
    }
    else if (strcmp(argv[1], "1") == 0) {
        key = 49;
    }
    else if (strcmp(argv[1], "2") == 0) {
        key = 50;
    }
    else if (strcmp(argv[1], "3") == 0) {
        key = 51;
    }
    else if (strcmp(argv[1], "4") == 0) {
        key = 52;
    }
    else if (strcmp(argv[1], "5") == 0) {
        key = 53;
    }
    else if (strcmp(argv[1], "6") == 0) {
        key = 54;
    }
    else if (strcmp(argv[1], "7") == 0) {
        key = 55;
    }
    else if (strcmp(argv[1], "8") == 0) {
        key = 56;
    }
    else if (strcmp(argv[1], "9") == 0) {
        key = 57;
    } else {
        key = (argv[1][0] - 32) + '\0';
        isLetter = 1;
    }
   
    printf("Key: %c\n", key);
    printf("Is Letter: %d", isLetter);

    if(argc >= 2) {
        if(isLetter) {
            while(1) {
                if(GetAsyncKeyState(key) || GetAsyncKeyState(key + 32)) {
                    if(isPressed == 0) {
                        disable_conn();
                        printf("Internet Off\n");
                        isPressed = 1;
                    }
                    else {
                        enable_conn();
                        printf("Internet On\n");
                        isPressed = 0;
                    }
                } 
            }  
        } else {
            while(1) {
                if(GetAsyncKeyState(key)) {
                    if(isPressed == 0) {
                        disable_conn();
                        printf("Internet Off\n");
                        isPressed = 1;
                    }
                    else {
                        enable_conn();
                        printf("Internet On\n");
                        isPressed = 0;
                    }
                }
            }
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