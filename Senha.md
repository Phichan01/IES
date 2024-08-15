#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

#define MAX_ENTRIES 3    
#define MAX_PENDING 10
#define MAX_LENGTH 80
#define MAX_OLD_ENTRIES 3

typedef struct {
    char senha[MAX_LENGTH];
    char local[MAX_LENGTH];
} Chamada;

Chamada chamadas[MAX_ENTRIES];
Chamada chamadasAntigas[MAX_OLD_ENTRIES];
Chamada senhasPendentesNormais[MAX_PENDING];
Chamada senhasPendentesPrioritarias[MAX_PENDING];
int numPendentesNormais = 0;
int numPendentesPrioritarias = 0;

// Função para inserir uma nova chamada no topo da lista
void inserirNovaChamada(const char* senha, const char* local) {
    // Move todas as entradas em chamadasAntigas para baixo
    for (int i = MAX_OLD_ENTRIES - 1; i > 0; i--) {
        chamadasAntigas[i] = chamadasAntigas[i - 1];
    }

    // Insere a última entrada de chamadas em chamadasAntigas
    chamadasAntigas[0] = chamadas[MAX_ENTRIES - 1];

    // Move todas as entradas em chamadas para baixo
    for (int i = MAX_ENTRIES - 1; i > 0; i--) {
        chamadas[i] = chamadas[i - 1];
    }

    // Insere a nova chamada no topo de chamadas
    snprintf(chamadas[0].senha, MAX_LENGTH, "%s", senha);
    snprintf(chamadas[0].local, MAX_LENGTH, "%s", local);
}

// Função para gerar senha prioritária (P + 2 letras + 3 números)
void gerarSenhaPrioritaria() {
    char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char senha[MAX_LENGTH];
    snprintf(senha, MAX_LENGTH, "P%c%c%d%d%d",
             letras[rand() % 26], letras[rand() % 26],
             rand() % 10, rand() % 10, rand() % 10);
    char local[MAX_LENGTH];
    snprintf(local, MAX_LENGTH, "GUICHE %d", (rand() % 3) + 1);

    // Armazena na fila de senhas pendentes prioritárias
    if (numPendentesPrioritarias < MAX_PENDING) {
        snprintf(senhasPendentesPrioritarias[numPendentesPrioritarias].senha, MAX_LENGTH, "%s", senha);
        snprintf(senhasPendentesPrioritarias[numPendentesPrioritarias].local, MAX_LENGTH, "%s", local);
        numPendentesPrioritarias++;
    }
}

// Função para gerar senha normal (N + 2 letras + 3 números)
void gerarSenhaNormal() {
    char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char senha[MAX_LENGTH];
    snprintf(senha, MAX_LENGTH, "N%c%c%d%d%d",
             letras[rand() % 26], letras[rand() % 26],
             rand() % 10, rand() % 10, rand() % 10);
    char local[MAX_LENGTH];
    snprintf(local, MAX_LENGTH, "GUICHE %d", (rand() % 3) + 1);

    // Armazena na fila de senhas pendentes normais
    if (numPendentesNormais < MAX_PENDING) {
        snprintf(senhasPendentesNormais[numPendentesNormais].senha, MAX_LENGTH, "%s", senha);
        snprintf(senhasPendentesNormais[numPendentesNormais].local, MAX_LENGTH, "%s", local);
        numPendentesNormais++;
    }
}

// Função para chamar a próxima senha prioritária
void chamarProximaSenhaPrioritaria() {
    if (numPendentesPrioritarias > 0) {
        inserirNovaChamada(senhasPendentesPrioritarias[0].senha, senhasPendentesPrioritarias[0].local);

        // Remove a senha da fila de pendentes prioritárias
        for (int i = 0; i < numPendentesPrioritarias - 1; i++) {
            senhasPendentesPrioritarias[i] = senhasPendentesPrioritarias[i + 1];
        }
        numPendentesPrioritarias--;
    }
}

// Função para chamar a próxima senha normal
void chamarProximaSenhaNormal() {
    if (numPendentesNormais > 0) {
        inserirNovaChamada(senhasPendentesNormais[0].senha, senhasPendentesNormais[0].local);

        // Remove a senha da fila de pendentes normais
        for (int i = 0; i < numPendentesNormais - 1; i++) {
            senhasPendentesNormais[i] = senhasPendentesNormais[i + 1];
        }
        numPendentesNormais--;
    }
}

// Função para mostrar a tabela de chamadas
void mostrarTabela(WINDOW *win) {
    wclear(win);
    box(win, 0, 0);

    mvwprintw(win, 1, 1, "ULTIMAS       CHAMADAS");
    mvwprintw(win, 2, 1, "SENHA      LOCAL");

    for (int i = 0; i < MAX_ENTRIES; i++) {
        int row = 3 + i;
        mvwprintw(win, row, 1, "%-10s %-10s", chamadas[i].senha, chamadas[i].local);
    }

    wrefresh(win);
}

// Função para mostrar informações adicionais
void mostrarInformacoes(WINDOW *win) {
    wclear(win);
    box(win, 0, 0);

    time_t agora;
    struct tm *infoTempo;
    time(&agora);

    infoTempo = localtime(&agora);

    char horaAtual[MAX_LENGTH];
    char dataAtual[MAX_LENGTH];

    strftime(horaAtual, MAX_LENGTH, "%H:%M", infoTempo);
    strftime(dataAtual, MAX_LENGTH, "%d-%m-%Y", infoTempo);

    mvwprintw(win, 1, 1, "HORA: %s", horaAtual);
    mvwprintw(win, 2, 1, "LOCAL: Foz do Iguaçu");
    mvwprintw(win, 3, 1, "DATA: %s", dataAtual);

    wrefresh(win);
}

// Função para mostrar chamadas antigas
void mostrarChamadasAntigas(WINDOW *win) {
    wclear(win);
    box(win, 0, 0);

    mvwprintw(win, 1, 1, "ULTIMAS 3 CHAMADAS");
    mvwprintw(win, 2, 1, "SENHA      LOCAL");

    for (int i = 0; i < MAX_OLD_ENTRIES; i++) {
        int row = 3 + i;
        mvwprintw(win, row, 1, "%-10s %-10s", chamadasAntigas[i].senha, chamadasAntigas[i].local);
    }

    wrefresh(win);
}

// Função para perguntar ao cliente o tipo de senha desejada
void perguntarTipoSenha() {
    char tipoSenha;
    printw("Escolha o tipo de senha que deseja:\n");
    printw("P - Senha Prioritária\n");
    printw("N - Senha Normal\n");
    
    tipoSenha = getch();
    
    if (tipoSenha == 'P' || tipoSenha == 'p') {
        gerarSenhaPrioritaria();
    } else if (tipoSenha == 'N' || tipoSenha == 'n') {
        gerarSenhaNormal();
    } else {
        printw("Opção inválida, tente novamente.\n");
        perguntarTipoSenha();
    }
}

int main() {
    srand(time(NULL));

    initscr();
    noecho();
    cbreak();

    // Pergunta o tipo de senha ao cliente antes de mostrar a interface principal
    perguntarTipoSenha();

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    WINDOW *winChamadas = newwin(15, 60, 0, 0);
    WINDOW *winInfo = newwin(5, 30, 10, 30);
    WINDOW *winChamadasAntigas = newwin(7, 34, 1, 25);

    char opcao;
    while (1) {
        mostrarTabela(winChamadas);
        mostrarInformacoes(winInfo);
        mostrarChamadasAntigas(winChamadasAntigas);

        mvprintw(16, 0, "Aperte C para chamar senha normal, P para chamar senha prioritaria, G para gerar nova senha, ou S para sair: ");
        opcao = getch();
        
        if (opcao == 'C' || opcao == 'c') {
            chamarProximaSenhaNormal();
        } else if (opcao == 'P' || opcao == 'p') {
            chamarProximaSenhaPrioritaria();
        } else if (opcao == 'G' || opcao == 'g') {
            perguntarTipoSenha();  // Gera nova senha
        } else if (opcao == 'S' || opcao == 's') {
            break;
        } else {
            mvprintw(18, 0, "Opção inválida.\n");
        }
    }

    endwin();
    return 0;
}
