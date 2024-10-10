#include "persistencia.h"

Chamada chamadas[MAX_ENTRIES];
Chamada chamadasAntigas[MAX_OLD_ENTRIES];
Chamada senhasPendentesNormais[MAX_PENDING];
Chamada senhasPendentesPrioritarias[MAX_PENDING];
int numPendentesNormais = 0;
int numPendentesPrioritarias = 0;
