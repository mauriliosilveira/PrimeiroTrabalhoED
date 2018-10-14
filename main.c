#include <stdio.h>
#include "pilha.h"

int main(void){
    t_pilha* pilha = alocaPilha();
    
    menu(pilha);
    
    return 0;
}