#ifndef CONTROLE_H
#define CONTROLE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarSenhaPrioritaria();
void gerarSenhaNormal();
void chamarProximaSenhaPrioritaria();
void chamarProximaSenhaNormal();
void inserirNovaChamada(const char* senha, const char* local);

#endif
