#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "interface.h"
#include "controle.h"
#include "persistencia.h"
#include "atendente.h"

int main() {
    FILE* fp;
    fp = fopen("atendimento.txt", "a");
    srand(time(NULL)); // Inicializa a semente para senhas aleatórias

    initscr();   // Inicializa o ncurses
    noecho();    // Desabilita a exibição da entrada do usuário
    cbreak();    // Modo de entrada direta (sem buffer)

    // Primeira etapa: Gerar a senha
    perguntarTipoSenha();

    int opcao1;
    char login[50];
    do {
        clear(); // Limpa a tela
        mvprintw(0, 0, "==== Sistema de Cadastro e Login ====");
        mvprintw(1, 0, "1. Cadastrar novo usuário");
        mvprintw(2, 0, "2. Fazer login");
        mvprintw(3, 0, "3. Sair");
        mvprintw(4, 0, "Escolha uma opção: ");
        refresh();

        opcao1 = wgetch(stdscr) - '0'; // Captura a opção escolhida (transforma de char para int)

        switch (opcao1) {
            case 1:
                clear();
                mvprintw(5, 0, "Menu de Cadastro novo funcionario!\n");
                mvprintw(6, 0, "Entre com um novo login: ");
                refresh();
                // Removido inputNcurses(login, 50);
                cadastrarNovoUsuario(); // Executa cadastro com o login
                break;
            case 2:
                clear();
                mvprintw(5, 0, "Fazer login\n");
                mvprintw(6, 0, "Entre com seu login: ");
                refresh();
                // Removido inputNcurses(login, 50);
                loginUsuario(); // Executa login com o login capturado
                break;
            case 3:
                mvprintw(6, 0, "Saindo...");
                refresh();
                break; // Adicionei um refresh para garantir que a mensagem seja mostrada antes de sair
            default:
                mvprintw(6, 0, "Opção inválida, tente novamente!");
                refresh();
        }
        refresh(); // Atualiza a tela para mostrar o resultado
    } while (opcao1 != 3); // Sai quando a opção 3 é escolhida

    // Interface para controle de senhas
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX); // Obtém o tamanho da tela

    // Criação de janelas para exibição
    WINDOW *winChamadas = newwin(15, 60, 0, 0);
    WINDOW *winInfo = newwin(5, 30, 10, 30);
    WINDOW *winChamadasAntigas = newwin(7, 34, 1, 25);

    char opcao;
    while (1) {
        mostrarTabela(winChamadas);  // Exibe a tabela de chamadas
        mostrarInformacoes(winInfo); // Exibe informações adicionais
        mostrarChamadasAntigas(winChamadasAntigas); // Exibe chamadas antigas

        mvprintw(16, 0, "Aperte N para chamar senha normal, P para senha prioritária, G para gerar nova senha, ou S para sair: ");
        refresh();
        opcao = getch(); // Captura a tecla pressionada

        // Lógica para as opções
        if (opcao == 'N' || opcao == 'n') {
            chamarProximaSenhaNormal(fp);
        } else if (opcao == 'P' || opcao == 'p') {
            chamarProximaSenhaPrioritaria(fp);
        } else if (opcao == 'G' || opcao == 'g') {
            perguntarTipoSenha(); // Gera uma nova senha
        } else if (opcao == 'S' || opcao == 's') {
            break;
        } else {
            mvprintw(18, 0, "Opção inválida.");
        }
        refresh(); // Atualiza a tela
    }

    // Encerramento
    endwin(); // Finaliza o ncurses
    fclose(fp); // Fecha o arquivo
    return 0;
}
