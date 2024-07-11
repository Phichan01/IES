#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar senha prioritária (1 letra + 3 números)
void gerarSenhaPrioritaria() {
    char *letra = "P";
    int num1 = rand() % 10;  // Números de 0 a 9
    int num2 = rand() % 10;
    int num3 = rand() % 10;

    printf("Senha prioritária gerada: %c%d%d%d\n", *letra, num1, num2, num3);
}

void gerarSenhaNormal() {
    char *letra = "N";
    int num1 = rand() % 10;  // Números de 0 a 9
    int num2 = rand() % 10;
    int num3 = rand() % 10;
    
    printf("Senha normal gerada: %c%d%d%d\n", *letra, num1, num2, num3);
}

int main() {
    srand(time(NULL)); 
    
    char tipoSenha;
    
    printf("Aperte P para senha prioritária ou N para senha normal: ");
    scanf(" %c", &tipoSenha);
    
    if (tipoSenha == 'P' || tipoSenha == 'p') {
        gerarSenhaPrioritaria();
    } else if (tipoSenha == 'N' || tipoSenha == 'n') {
        gerarSenhaNormal();
    } else {
        printf("Opção inválida.\n");
        return 1;  // Encerra o programa com código de erro
    }
    
    // Obtém data e hora atuais
    time_t agora;
    struct tm *infoTempo;
    char dataHora[80];

    time(&agora);
    infoTempo = localtime(&agora);

    strftime(dataHora, sizeof(dataHora), "%m-%d %H:%M:%S", infoTempo);
    
    printf("Data e hora: %s\n", dataHora);
    
    return 0;
}
