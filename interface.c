#include "interface.h"

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

void mostrarInformacoes(WINDOW *win) {
    wclear(win);
    box(win, 0, 0);
    setenv("TZ", "America/Sao_Paulo", 1);
    tzset();
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
