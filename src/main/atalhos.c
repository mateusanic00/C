#define UNICODE
#define _UNICODE

#include <windows.h>
#include <shellapi.h>
#include <stdio.h>

#define HOTKEY_NOTEPAD 1
#define HOTKEY_CALCULATOR 2
#define HOTKEY_BROWSER 3

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

static void OpenTarget(const wchar_t *target, const wchar_t *description)
{
    HINSTANCE result = ShellExecuteW(NULL, L"open", target, NULL, NULL, SW_SHOWNORMAL);

    if ((INT_PTR)result <= 32) {
        wprintf(L"[ERRO] Nao foi possivel abrir: %ls\n", description);
    }
}

int wmain(void)
{
    const UINT modifiers = MOD_CONTROL | MOD_ALT;
    MSG msg;

    wprintf(L"Gerenciador de atalhos (C + WinAPI)\n");
    wprintf(L"Ctrl + Alt + N: Bloco de Notas\n");
    wprintf(L"Ctrl + Alt + C: Calculadora\n");
    wprintf(L"Ctrl + Alt + B: navegador (Google)\n");
    wprintf(L"Feche esta janela para encerrar.\n\n");

    RegisterShortcut(HOTKEY_NOTEPAD, modifiers, 'N',
                     L"Ctrl+Alt+N -> Bloco de Notas");
    RegisterShortcut(HOTKEY_CALCULATOR, modifiers, 'C',
                     L"Ctrl+Alt+C -> Calculadora");
    RegisterShortcut(HOTKEY_BROWSER, modifiers, 'B',
                     L"Ctrl+Alt+B -> navegador");

    while (GetMessageW(&msg, NULL, 0, 0) > 0) {
        if (msg.message == WM_HOTKEY) {
            switch ((int)msg.wParam) {
                case HOTKEY_NOTEPAD:
                    OpenTarget(L"notepad.exe", L"Bloco de Notas");
                    break;

                case HOTKEY_CALCULATOR:
                    OpenTarget(L"calc.exe", L"Calculadora");
                    break;

                case HOTKEY_BROWSER:
                    OpenTarget(L"https://www.google.com", L"navegador");
                    break;
            }
        }

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    UnregisterHotKey(NULL, HOTKEY_NOTEPAD);
    UnregisterHotKey(NULL, HOTKEY_CALCULATOR);
    UnregisterHotKey(NULL, HOTKEY_BROWSER);

    return 0;
}