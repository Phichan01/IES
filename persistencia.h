#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#define MAX_ENTRIES 3
#define MAX_PENDING 10
#define MAX_LENGTH 80
#define MAX_OLD_ENTRIES 3

typedef struct {
    char senha[MAX_LENGTH];
    char local[MAX_LENGTH];
} Chamada;

extern Chamada chamadas[MAX_ENTRIES];
extern Chamada chamadasAntigas[MAX_OLD_ENTRIES];
extern Chamada senhasPendentesNormais[MAX_PENDING];
extern Chamada senhasPendentesPrioritarias[MAX_PENDING];
extern int numPendentesNormais;
extern int numPendentesPrioritarias;

#endif
