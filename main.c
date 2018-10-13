#include <stdio.h>
#include "pilha.h"

int main(void){
    t_pilha* pilha = alocaPilha();
    char letra[50];
    
    scanf("%s", letra);

    resolveExpressao(letra,pilha);

    return 0;
}