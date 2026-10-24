#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//made by Claude

int delay_ms   = 100;  // intervalo entre cliques
int duration_s = 0;    // tempo ativo em segundos (0 = até apertar F6)
int button     = 0;    // 0 = esquerdo, 1 = direito, 2 = meio


void click(void) {
    DWORD down = MOUSEEVENTF_LEFTDOWN;
    DWORD up   = MOUSEEVENTF_LEFTUP;

    if (button == 1) { down = MOUSEEVENTF_RIGHTDOWN;  up = MOUSEEVENTF_RIGHTUP;  }
    if (button == 2) { down = MOUSEEVENTF_MIDDLEDOWN; up = MOUSEEVENTF_MIDDLEUP; }

    INPUT in[2] = {0};              // zera tudo antes de preencher
    in[0].type = INPUT_MOUSE;
    in[0].mi.dwFlags = down;        // aperta
    in[1].type = INPUT_MOUSE;
    in[1].mi.dwFlags = up;          // solta
    SendInput(2, in, sizeof(INPUT));
}


void cmd_delay(const char *arg) {
    int v = atoi(arg);
    if (v < 1) { printf("Uso: /delay <ms>   ex: /delay 100\n"); return; }
    delay_ms = v;
    printf("Delay = %d ms\n", delay_ms);
}

void cmd_tempo(const char *arg) {
    if (arg[0] == '\0') { printf("Uso: /tempo <segundos>   (0 = sem limite)\n"); return; }
    duration_s = atoi(arg);
    printf("Tempo ativo = %d s\n", duration_s);
}

void cmd_botao(const char *arg) {
    if      (strcmp(arg, "esq")  == 0) button = 0;
    else if (strcmp(arg, "dir")  == 0) button = 1;
    else if (strcmp(arg, "meio") == 0) button = 2;
    else { printf("Uso: /botao esq|dir|meio\n"); return; }
    printf("Botao = %s\n", arg);
}

void cmd_status(void) {
    const char *nomes[] = {"esquerdo", "direito", "meio"};
    printf("Delay: %d ms | Tempo: %d s | Botao: %s\n",
           delay_ms, duration_s, nomes[button]);
}

void cmd_start(void) {
    printf("Comecando em 3 segundos... mova o mouse para o alvo.\n");
    printf("Aperte F6 para parar.\n");
    Sleep(3000);

    DWORD inicio = GetTickCount();

    // roda enquanto F6 NAO estiver apertado
    while (!(GetAsyncKeyState(VK_F6) & 0x8000)) {
        if (duration_s > 0 && GetTickCount() - inicio >= (DWORD)duration_s * 1000) {
            break;  // acabou o tempo
        }
        click();
        Sleep(delay_ms);
    }
    printf("Parado.\n");
}

void cmd_ajuda(void) {
    printf("Comandos:\n");
    printf("  /delay <ms>         intervalo entre cliques\n");
    printf("  /tempo <segundos>   tempo ativo (0 = sem limite)\n");
    printf("  /botao esq|dir|meio botao do mouse\n");
    printf("  /status             mostra as configuracoes\n");
    printf("  /start              comeca a clicar (F6 para parar)\n");
    printf("  /ajuda              mostra esta lista\n");
    printf("  /sair               fecha o programa\n");
}


int main(void) {
    char linha[100];
    char cmd[32];
    char arg[32];

    printf("=== AutoClicker === (digite /ajuda)\n");

    for (;;) {
        printf("> ");
        if (fgets(linha, sizeof linha, stdin) == NULL) break;

        cmd[0] = '\0';
        arg[0] = '\0';
        sscanf(linha, "%31s %31s", cmd, arg);   // separa em comando + argumento

        if      (strcmp(cmd, "/delay")  == 0) cmd_delay(arg);
        else if (strcmp(cmd, "/tempo")  == 0) cmd_tempo(arg);
        else if (strcmp(cmd, "/botao")  == 0) cmd_botao(arg);
        else if (strcmp(cmd, "/status") == 0) cmd_status();
        else if (strcmp(cmd, "/start")  == 0) cmd_start();
        else if (strcmp(cmd, "/ajuda")  == 0) cmd_ajuda();
        else if (strcmp(cmd, "/sair")   == 0) break;
        else if (cmd[0] != '\0')              printf("Comando desconhecido. Digite /ajuda\n");
    }
    return 0;
}