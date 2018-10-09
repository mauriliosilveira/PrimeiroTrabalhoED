#include <stdio.h>
#include "pilha.h"

int main(void){
    int resultado = 0;

    resultado = resolveExpressao();

    if(resultado == 1){
        printf("Expressao Valida \n");
    }else if(resultado == -1){
        printf("Expressao Invalida \n");
    }else{
        printf("Nenhum Resultado \n");
    }

    return 0;
}