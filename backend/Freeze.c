#include <windows.h>
#include <stdio.h>




// int main() {
//     // 1. Installiamo il gancio a basso livello
//     hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);

//     if (hKeyboardHook == NULL) {
//         printf("Errore nell'installazione dell'hook!\n");
//         return 1;
//     }

//     printf("Tastiera filtrata: solo numeri ammessi.\n");
//     printf("Premi ESC per terminare il blocco.\n");

//     // 2. Windows richiede un "Message Loop" per far funzionare l'hook
//     MSG msg;
//     while (GetMessage(&msg, NULL, 0, 0)) {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
        
//         // Se l'utente preme ESC, usciamo dal loop (gestito nella callback)
//         // Ma per sicurezza controlliamo se il thread deve chiudersi
//     }

//     // 3. Disinstalliamo l'hook prima di chiudere
//     UnhookWindowsHookEx(hKeyboardHook);
//     printf("Tastiera ripristinata.\n");

//     return 0;
// }