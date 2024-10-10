#include "controle.h"
#include "persistencia.h"

void gerarSenhaPrioritaria() {
    char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char senha[MAX_LENGTH];
    snprintf(senha, MAX_LENGTH, "P%c%c%d%d%d", letras[rand() % 26], letras[rand() % 26], rand() % 10, rand() % 10, rand() % 10);
    char local[MAX_LENGTH];
    snprintf(local, MAX_LENGTH, "GUICHE %d", (rand() % 3) + 1);

    if (numPendentesPrioritarias < MAX_PENDING) {
        snprintf(senhasPendentesPrioritarias[numPendentesPrioritarias].senha, MAX_LENGTH, "%s", senha);
        snprintf(senhasPendentesPrioritarias[numPendentesPrioritarias].local, MAX_LENGTH, "%s", local);
        numPendentesPrioritarias++;
    }
}

void gerarSenhaNormal() {
    char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char senha[MAX_LENGTH];
    snprintf(senha, MAX_LENGTH, "N%c%c%d%d%d", letras[rand() % 26], letras[rand() % 26], rand() % 10, rand() % 10, rand() % 10);
    char local[MAX_LENGTH];
    snprintf(local, MAX_LENGTH, "GUICHE %d", (rand() % 3) + 1);

    if (numPendentesNormais < MAX_PENDING) {
        snprintf(senhasPendentesNormais[numPendentesNormais].senha, MAX_LENGTH, "%s", senha);
        snprintf(senhasPendentesNormais[numPendentesNormais].local, MAX_LENGTH, "%s", local);
        numPendentesNormais++;
    }
}

void chamarProximaSenhaPrioritaria(FILE* fp) {
    if (numPendentesPrioritarias > 0) {
        inserirNovaChamada(senhasPendentesPrioritarias[0].senha, senhasPendentesPrioritarias[0].local);
        fprintf(fp, "Prioritária: %s, %s\n", senhasPendentesPrioritarias[0].senha, senhasPendentesPrioritarias[0].local);
        for (int i = 0; i < numPendentesPrioritarias - 1; i++) {
            senhasPendentesPrioritarias[i] = senhasPendentesPrioritarias[i + 1];
        }
        numPendentesPrioritarias--;
    }
}


void chamarProximaSenhaNormal(FILE* fp) {
    if (numPendentesNormais > 0) {
        inserirNovaChamada(senhasPendentesNormais[0].senha, senhasPendentesNormais[0].local);
        fprintf(fp, "Normal:      %s, %s\n", senhasPendentesNormais[0].senha, senhasPendentesNormais[0].local);
        for (int i = 0; i < numPendentesNormais - 1; i++) {
            senhasPendentesNormais[i] = senhasPendentesNormais[i + 1];
        }
        numPendentesNormais--;
    }
}

void inserirNovaChamada(const char* senha, const char* local) {
    for (int i = MAX_OLD_ENTRIES - 1; i > 0; i--) {
        chamadasAntigas[i] = chamadasAntigas[i - 1];
    }

    chamadasAntigas[0] = chamadas[MAX_ENTRIES - 1];

    for (int i = MAX_ENTRIES - 1; i > 0; i--) {
        chamadas[i] = chamadas[i - 1];
    }

    snprintf(chamadas[0].senha, MAX_LENGTH, "%s", senha);
    snprintf(chamadas[0].local, MAX_LENGTH, "%s", local);
}
