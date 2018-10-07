#include <stdio.h>
#include "pilha.h"
#include <stdlib.h>

t_pilha* alocaPilha(){
    t_pilha* pilha = (t_pilha*) malloc(sizeof(t_pilha));

    if(!pilha){
        exit(0);
    }

    pilha->primeiro = NULL;
    pilha->topo = -1;

    return pilha;
}

t_elemento* alocaElemento(char caractere, t_pilha* pilha){
    t_elemento* elemento = (t_elemento*) malloc(sizeof(t_elemento));

    if(!elemento){
        free(pilha);
        exit(0);
    }

    elemento->caractere = caractere;
    elemento->proximo = NULL;

    return elemento;
}

int inserirPilha(char caractere, t_pilha* pilha){
    /*VER SE A PILHA ESTPA VAZIA*/

    t_elemento* aux_inserir = alocaElemento(caractere, pilha);
        
    if(!aux_inserir){
        exit(0);
    }else if(pilha->topo == -1){
        pilha->primeiro = aux_inserir;
    }else{
        aux_inserir->proximo = pilha->primeiro;
        pilha->primeiro = aux_inserir;
    }

    pilha->topo ++;

    return 1;    
}

void printarPilha(t_pilha* pilha){
    if((pilha->primeiro != NULL) && (pilha->topo >=0)){
        t_elemento* aux_printar = pilha->primeiro;

        while(aux_printar != NULL){
            printf("%c\n", aux_printar->caractere);

            aux_printar = aux_printar->proximo;
        }
    }else {
        printf("Nao tem nada na pilha! \n");
    }    
}

int resolveExpressao(){
    char expressao[100];
    int contador = 0;

    scanf("%[^\n]", expressao);

    t_pilha* pilha = alocaPilha();

    while(expressao[contador] != '\0'){
        if(expressao[contador] != ' '){
            inserirPilha(expressao[contador], pilha);
        }
        contador ++;
    }

    printarPilha(pilha);

    return 1;
}

int calculadora(){
    
    return 1;
}

void menu(){
    system(CLEAR);
    cabecalho();
    
    int opcao;
    printf("1 - Resolver Expressão \n");
    printf("2 - Modo Calculadora \n");
    printf("0 - Sair \n");
    printf("\n-> ");
    scanf("%d", &opcao);

    resposta(opcao);
}

void cabecalho(){
    printf("================================== \n");
    printf("\t PURA MATEMATICA \n");
    printf("================================== \n"); 
}

void resposta(int opcao){
    if(opcao == 0){
        system(CLEAR);
        cabecalho();
        printf("Saindo...");
        getchar();
        getchar();
        printf("\n");
    }else if(opcao == 1){
        resolveExpressao();
    }else if(opcao == 2){
        calculadora();
    }else{
        system(CLEAR);
        cabecalho();
        printf("Comando Invalido...");
        getchar();
        getchar();
        menu();
    }
}