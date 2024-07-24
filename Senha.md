#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

#define MAX_ENTRIES 3
#define MAX_LENGTH 80

typedef struct {
    char senha[MAX_LENGTH];
    char local[MAX_LENGTH];
    char dataHora[MAX_LENGTH];
} Chamada;

Chamada chamadas[MAX_ENTRIES];
int chamadasIndex = 0;

// Função para gerar senha prioritária (1 letra + 3 números)
void gerarSenhaPrioritaria() {
    char letra = 'P';
    int num1 = rand() % 10;  // Números de 0 a 9
    int num2 = rand() % 10;
    int num3 = rand() % 10;

    char senha[MAX_LENGTH];
    snprintf(senha, MAX_LENGTH, "%c%d%d%d", letra, num1, num2, num3);

    snprintf(chamadas[chamadasIndex].senha, MAX_LENGTH, "%s", senha);
    snprintf(chamadas[chamadasIndex].local, MAX_LENGTH, "GUICHE %d", (rand() % 3) + 1);

    // Obtém data e hora atuais
    time_t agora;
    struct tm *infoTempo;
    time(&agora);
    infoTempo = localtime(&agora);
    strftime(chamadas[chamadasIndex].dataHora, MAX_LENGTH, "%m-%d %H:%M:%S", infoTempo);

    chamadasIndex = (chamadasIndex + 1) % MAX_ENTRIES;
}

void gerarSenhaNormal() {
    char letra = 'N';
    int num1 = rand() % 10;  // Números de 0 a 9
    int num2 = rand() % 10;
    int num3 = rand() % 10;
    
    char senha[MAX_LENGTH];
    snprintf(senha, MAX_LENGTH, "%c%d%d%d", letra, num1, num2, num3);

    snprintf(chamadas[chamadasIndex].senha, MAX_LENGTH, "%s", senha);
    snprintf(chamadas[chamadasIndex].local, MAX_LENGTH, "GUICHE %d", (rand() % 3) + 1);

    // Obtém data e hora atuais
    time_t agora;
    struct tm *infoTempo;
    time(&agora);
    infoTempo = localtime(&agora);
    strftime(chamadas[chamadasIndex].dataHora, MAX_LENGTH, "%m-%d %H:%M:%S", infoTempo);

    chamadasIndex = (chamadasIndex + 1) % MAX_ENTRIES;
}

void mostrarTabela(WINDOW *win) {
    wclear(win);
    box(win, 0, 0);

    mvwprintw(win, 1, 1, "ULTIMAS       CHAMADAS");
    mvwprintw(win, 2, 1, "SENHA      LOCAL       DATA/HORA");

    for (int i = 0; i < MAX_ENTRIES; i++) {
        int row = 3 + i;
        mvwprintw(win, row, 1, "%-10s %-10s %-20s", chamadas[i].senha, chamadas[i].local, chamadas[i].dataHora);
    }

    wrefresh(win);
}

int main() {
    srand(time(NULL)); 

    initscr();
    noecho();
    cbreak();

    WINDOW *win = newwin(10, 60, 0, 0);

    char tipoSenha;
    while (1) {
        mostrarTabela(win);
        mvprintw(12, 0, "Aperte P para senha prioritaria, N para senha normal, ou S para sair: ");
        tipoSenha = getch();
        
        if (tipoSenha == 'P' || tipoSenha == 'p') {
            gerarSenhaPrioritaria();
        } else if (tipoSenha == 'N' || tipoSenha == 'n') {
            gerarSenhaNormal();
        } else if (tipoSenha == 'S' || tipoSenha == 's') {
            break;  // Sai do loop
        } else {
            mvprintw(14, 0, "Opção invalida.\n");
        }
    }

    endwin();
    return 0;
}
