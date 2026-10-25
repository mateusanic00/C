#include <stdio.h> 
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>


#define HOTKEY_NEXT 1
#define HOTKEY_PREVIOUS 2
#define HOTKEY_PLAY_PAUSE 3

 static BOOL registerShortcut(int id, UINT modifiers, UINT vk) {
        if (RegisterHotKey(NULL, id, modifiers, vk)) {
            wprintf(L"[OK] Shortcut successfully registered.\n");
            return true;
        }
        else {
            wprintf(L"[ERROR] Could not register shortcut. maybe the shortcut is already in use.\n");
            return false;
        }

    }

static void sendMediaKey (WORD vk) {
    INPUT inputs[2] = {0};

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = vk;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = vk;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT sent = SendInput(2, inputs, sizeof(INPUT));
}


int wmain(void) {
    
    const UINT modifiers = MOD_CONTROL | MOD_ALT | MOD_NOREPEAT;
    MSG msg;

    wprintf(L"CTRL + ALT + X -> Play/Pause\n");
    wprintf(L"CTRL + ALT + D -> Next\n");
    wprintf(L"CTRL + ALT + A -> Previous\n");
    
    registerShortcut(HOTKEY_NEXT, modifiers, 'D');

    registerShortcut(HOTKEY_PREVIOUS, modifiers, 'A');

    registerShortcut(HOTKEY_PLAY_PAUSE, modifiers, 'X');


    while (GetMessageW(&msg, NULL, 0, 0) > 0) 
    {
        if (msg.message == WM_HOTKEY) //let me know when the shortcut is triggered
        {
            switch ((int)msg.wParam) 
            {
                case HOTKEY_NEXT:
                    sendMediaKey(VK_MEDIA_NEXT_TRACK);
                    break;
                case HOTKEY_PREVIOUS:
                    sendMediaKey(VK_MEDIA_PREV_TRACK);
                    break;
                case HOTKEY_PLAY_PAUSE:
                    sendMediaKey(VK_MEDIA_PLAY_PAUSE);
                    break;
            }
        }
    }

    // shortcuts : ctrl+alt+d
    // funcao pra trocar as teclas
    //v2.0 -> colocar musica por nome no terminal (listar opções se tiver mais de uma opção para o nome)


    return (0);
}