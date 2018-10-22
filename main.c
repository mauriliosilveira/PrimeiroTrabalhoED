/*
* ALUNO = MAURILIO DE JESUS SILVEIRA
* MATRICULA = 17/0152294
* CURSO = CIENCIA DA COMPUTACAO BACHARELADO
*/

#include <stdio.h>
#include "pilha.h"

int main(void){
    t_pilha* pilha = alocaPilha();
    
    menu(pilha);
    
    return 0;
}