#ifndef INTERFACE_H
#define INTERFACE_H
#include <ncurses.h>
#include "controle.h"
#include "persistencia.h"
#include <time.h>
#include <stdio.h>

void mostrarTabela(WINDOW *win);
void mostrarInformacoes(WINDOW *win);
void mostrarChamadasAntigas(WINDOW *win);
void perguntarTipoSenha();

#endif
