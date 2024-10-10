#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include "atendente.h"

// Função para capturar string com ncurses
void inputNcurses(char* input, int size) {
    echo();  // Habilita a exibição de caracteres digitados
    wgetnstr(stdscr, input, size); // Captura a string digitada no ncurses
    noecho(); // Desabilita novamente a exibição
}

// Função para verificar se o login já existe no arquivo de texto
int verificarCadastro(FILE* usuariosExistentes, Usuario novoUsuario) {
    char usuarioExistente[MAX_C], senhaExistente[MAX_C];
    
    rewind(usuariosExistentes); // Reinicia o ponteiro para o início do arquivo
    
    // Lê o arquivo linha por linha, assumindo que cada linha tem "usuário senha"
    while (fscanf(usuariosExistentes, "%s %s", usuarioExistente, senhaExistente) != EOF) {
        // Verifica se o login já existe
        if (strcmp(usuarioExistente, novoUsuario.usuario) == 0) {
            return 1; // Usuário já cadastrado
        }
    }
    return 0; // Usuário não encontrado
}

// Função para cadastrar um novo usuário
void cadastrarNovoUsuario() {
    Usuario novoUsuario;
    FILE* usuariosExistentes;
    
    usuariosExistentes = fopen("atendentes.txt", "a+"); // Usa modo de leitura e adição de texto
    if (usuariosExistentes == NULL) {
        mvprintw(10, 0, "Erro ao abrir o arquivo de usuários.");
        return;
    }
    
    mvprintw(5, 0, "Menu de Cadastro novo funcionario!");
    mvprintw(6, 0, "Entre com um novo login: ");
    refresh();
    inputNcurses(novoUsuario.usuario, MAX_C); // Captura o login com ncurses

    mvprintw(7, 0, "Entre com uma nova senha: ");
    refresh();
    inputNcurses(novoUsuario.senha, MAX_C); // Captura a senha com ncurses
    
    if (verificarCadastro(usuariosExistentes, novoUsuario)) {
        mvprintw(8, 0, "ERRO: usuário já cadastrado!");
    } else {
        // Adiciona o novo usuário ao arquivo no formato "usuário senha"
        fprintf(usuariosExistentes, "%s %s\n", novoUsuario.usuario, novoUsuario.senha);
        mvprintw(8, 0, "Usuário cadastrado com sucesso!");
    }

    refresh();
    fclose(usuariosExistentes);
}

// Função para fazer login
void loginUsuario() {
    Usuario usuario;
    FILE* usuariosExistentes;

    usuariosExistentes = fopen("usuariosExistentes.txt", "r");
    if (usuariosExistentes == NULL) {
        mvprintw(10, 0, "Erro ao abrir o arquivo de usuários.");
        return;
    }

    mvprintw(5, 0, "Entre com os dados para acessar sua conta!");
    mvprintw(6, 0, "Login: ");
    refresh();
    inputNcurses(usuario.usuario, MAX_C); // Captura o login com ncurses

    mvprintw(7, 0, "Senha: ");
    refresh();
    inputNcurses(usuario.senha, MAX_C); // Captura a senha com ncurses

    char usuarioExistente[MAX_C], senhaExistente[MAX_C];
    int loginEncontrado = 0;

    // Verifica se o login e a senha estão corretos
    while (fscanf(usuariosExistentes, "%s %s", usuarioExistente, senhaExistente) != EOF) {
        if (strcmp(usuario.usuario, usuarioExistente) == 0) {
            loginEncontrado = 1;
            if (strcmp(usuario.senha, senhaExistente) == 0) {
                mvprintw(8, 0, "Login bem-sucedido!");
            } else {
                mvprintw(8, 0, "Erro: senha incorreta!");
            }
            break;
        }
    }

    if (!loginEncontrado) {
        mvprintw(8, 0, "Erro: usuário não encontrado!");
    }

    refresh();
    fclose(usuariosExistentes);
}
