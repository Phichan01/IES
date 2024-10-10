#ifndef ATENDENTE_H
#define ATENDENTE_H

#include <ncurses.h>

#define MAX_C 50

typedef struct {
    char usuario[MAX_C];
    char senha[MAX_C];
} Usuario;

int verificarCadastro(FILE* usuariosExistentes, Usuario novoUsuario);
void cadastrarNovoUsuario();
void loginUsuario();
void inputNcurses(char* input, int size);  // Declaração da função

#endif
