#include <stdio.h>
#include "pilha.h"
#include <stdlib.h>
#include <string.h>

t_pilha* alocaPilha(){
    t_pilha* pilha = (t_pilha*) malloc(sizeof(t_pilha));

    if(!pilha){
        exit(0);
    }

    pilha->primeiro = NULL;
    pilha->topo = -1;

    return pilha;
}

t_elemento* alocaElemento(char* caractere, t_pilha* pilha){
    t_elemento* elemento = (t_elemento*) malloc(sizeof(t_elemento));
    elemento->caractere = (char*) malloc((strlen(caractere)+1) * sizeof(char));

    if(!elemento){
        free(pilha);
        exit(0);
    }

    strcpy(elemento->caractere, caractere);
    elemento->proximo = NULL;

    return elemento;
}

int inserirPilha(char* caractere, t_pilha* pilha){
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

// void printarPilha(t_pilha* pilha){
//     if((pilha->primeiro != NULL) && (pilha->topo >=0)){
//         t_elemento* aux_printar = pilha->primeiro;

//         while(aux_printar != NULL){
//             printf("%c\n", *aux_printar->caractere);

//             aux_printar = aux_printar->proximo;
//         }
//     }else {
//         printf("Nao tem nada na pilha! \n");
//     }    
// }

void desalocaPilha(t_pilha* pilha){
    t_elemento* elemento = pilha->primeiro;
    pilha->primeiro = elemento->proximo;

    free(elemento->caractere);
    free(elemento);
    elemento = NULL;
    pilha->topo --;
}

int resolveExpressao(char* caractere, t_pilha* pilha){
    cabecalho();
    int contador = 0;
    char aux;

    while(caractere[contador] != '\0'){
        aux = caractere[contador];
        
        if((caractere[contador] == '(') || (caractere[contador] == '[') || (caractere[contador] == '{')){
            inserirPilha(&aux, pilha);
        }else if(caractere[contador] == ')'){
            if((pilha->primeiro != NULL) && (pilha->topo > -1)){
                if(*pilha->primeiro->caractere == '('){
                    desalocaPilha(pilha);
                }else{
                    expressaoInvalida(pilha);
                    return -1;
                }
            }else {
                expressaoInvalida(pilha);
                return -1;
            }
        }else if(caractere[contador] == ']'){
            if((pilha->primeiro != NULL) && (pilha->topo > -1)){
                if(*pilha->primeiro->caractere == '['){
                    desalocaPilha(pilha);
                }else{
                    expressaoInvalida(pilha);
                    return -1;
                }    
            }else {
                expressaoInvalida(pilha);
                return -1;
            }
        }else if(caractere[contador] == '}'){
            if((pilha->primeiro != NULL) && (pilha->topo > -1)){
                if(*pilha->primeiro->caractere == '{'){
                    desalocaPilha(pilha);
                }else{
                    expressaoInvalida(pilha);
                    return -1;
                }    
            }else {
                expressaoInvalida(pilha);
                return -1;
            }
        }

        contador ++;
    }
    
    if((pilha->primeiro != NULL) && (pilha->topo > -1)){
        expressaoInvalida(pilha);
        return -1;
    }else{
        free(pilha);
        expressaoResolvida(caractere);
    }
}

int expressaoResolvida(char* caractere){
    cabecalho();

    printf("Agora vamos resolver a expressao \n");

    return 1;
}

int expressaoInvalida(t_pilha* pilha){
    cabecalho();
    printf("Expressão invalida! \n");
    
    if((pilha->primeiro != NULL) && (pilha->topo > -1)){
        do{
            t_elemento* elemento = pilha->primeiro;

            pilha->primeiro = elemento->proximo;

            free(elemento->caractere);
            free(elemento);
            elemento = NULL;
            pilha->topo --;
        }while(pilha->primeiro != NULL);   
    }
    free(pilha);
    getchar();
    getchar();
    menu(pilha);

    return 1;
}

int calculadora(){
    cabecalho();
    printf("Modo calculadora! \n");

    return 1;
}

void menu(t_pilha* pilha){
    cabecalho();
    
    int opcao;
    printf("1 - Resolver Expressão \n");
    printf("2 - Modo Calculadora \n");
    printf("0 - Sair \n");
    printf("\n-> ");
    scanf("%d", &opcao);

    resposta(opcao,pilha);
}

void cabecalho(){
    system(CLEAR);
    printf("================================== \n");
    printf("\t PURA MATEMATICA \n");
    printf("================================== \n"); 
}

void resposta(int opcao, t_pilha* pilha){
    if(pilha == NULL){
       t_pilha* pilha = alocaPilha(); 
    }

    if(opcao == 0){
        system(CLEAR);
        cabecalho();
        printf("Saindo...");
        getchar();
        getchar();
        printf("\n");
    }else if(opcao == 1){
        cabecalho();
        char caractere[50];
        printf("-> ");
        scanf("%s", caractere);
        resolveExpressao(caractere,pilha);
    }else if(opcao == 2){
        calculadora();
    }else{
        system(CLEAR);
        cabecalho();
        printf("Comando Invalido...");
        getchar();
        getchar();
        menu(pilha);
    }
}