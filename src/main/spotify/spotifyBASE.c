#define UNICODE
#define _UNICODE

#include <windows.h>
#include <stdio.h>

#define HOTKEY_PLAY_PAUSE 1
#define HOTKEY_NEXT       2
#define HOTKEY_PREV       3

static BOOL RegisterShortcut(int id, UINT modifiers, UINT key, const wchar_t *description)
{
    if (RegisterHotKey(NULL, id, modifiers, key)) {
        wprintf(L"[OK] %ls\n", description);
        return TRUE;
    }

    wprintf(L"[ERRO] Nao foi possivel registrar %ls. Talvez o atalho ja esteja em uso.\n",
            description);
    return FALSE;
}

// Simula o pressionamento de uma tecla de midia (press + release)
static void SendMediaKey(WORD vk)
{
    INPUT inputs[2] = {0};

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = vk;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = vk;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, inputs, sizeof(INPUT));
}

int wmain(void)
{
    const UINT modifiers = MOD_CONTROL | MOD_ALT | MOD_NOREPEAT;
    MSG msg;

    wprintf(L"Controle de musica (C + WinAPI)\n");
    wprintf(L"Ctrl + Alt + P: Play/Pause\n");
    wprintf(L"Ctrl + Alt + Seta Direita: Proxima musica\n");
    wprintf(L"Ctrl + Alt + Seta Esquerda: Musica anterior\n");
    wprintf(L"Feche esta janela para encerrar.\n\n");

    RegisterShortcut(HOTKEY_PLAY_PAUSE, modifiers, 'P',
                     L"Ctrl+Alt+P -> Play/Pause");
    RegisterShortcut(HOTKEY_NEXT, modifiers, VK_RIGHT,
                     L"Ctrl+Alt+Direita -> Proxima");
    RegisterShortcut(HOTKEY_PREV, modifiers, VK_LEFT,
                     L"Ctrl+Alt+Esquerda -> Anterior");

    while (GetMessageW(&msg, NULL, 0, 0) > 0) {
        if (msg.message == WM_HOTKEY) {
            switch ((int)msg.wParam) {
                case HOTKEY_PLAY_PAUSE:
                    SendMediaKey(VK_MEDIA_PLAY_PAUSE);
                    break;

                case HOTKEY_NEXT:
                    SendMediaKey(VK_MEDIA_NEXT_TRACK);
                    break;

                case HOTKEY_PREV:
                    SendMediaKey(VK_MEDIA_PREV_TRACK);
                    break;
            }
        }

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    UnregisterHotKey(NULL, HOTKEY_PLAY_PAUSE);
    UnregisterHotKey(NULL, HOTKEY_NEXT);
    UnregisterHotKey(NULL, HOTKEY_PREV);

    return 0;
}