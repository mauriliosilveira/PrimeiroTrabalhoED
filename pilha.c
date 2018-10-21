#include <stdio.h>
#include "pilha.h"
#include <stdlib.h>
#include <string.h>

t_pilha* alocaPilha(){
    t_pilha* pilha = (t_pilha*) malloc(sizeof(t_pilha));

    if(!pilha){
        exit(-1);
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
        exit(-1);
    }

    strcpy(elemento->caractere, caractere);
    elemento->proximo = NULL;

    return elemento;
}

int inserirPilha(char* caractere, t_pilha* pilha){
    if(pilha == NULL){
        exit(-1);
    }

    t_elemento* aux_inserir = alocaElemento(caractere, pilha);
        
    if(!aux_inserir){
        exit(-1);
    }else if(pilha->topo == -1){
        pilha->primeiro = aux_inserir;
    }else{
        aux_inserir->proximo = pilha->primeiro;
        pilha->primeiro = aux_inserir;
    }

    pilha->topo ++;

    return 1;    
}

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

    if(pilha == NULL){
        pilha = alocaPilha();
    }

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
        pilha = NULL;
        posFixa(pilha,caractere);
    }

    return 1;
}

int posFixa(t_pilha* pilha, char* caractere){
    cabecalho();
    int contador = 0, nContador = 0;
    char aux, nCaractere [1000];

    pilha = alocaPilha();

    while(caractere[contador] != '\0'){
        aux = caractere[contador];
        
        if((caractere[contador] == '(') || (caractere[contador] == '[') || (caractere[contador] == '{') || (caractere[contador] == '+') || (caractere[contador] == '-') || (caractere[contador] == '*') || (caractere[contador] == '/')){
            if((pilha->primeiro == NULL) || (pilha->topo == -1)){    
                inserirPilha(&aux,pilha);
            }else if((*pilha->primeiro->caractere == '(') || (*pilha->primeiro->caractere == '{') || (*pilha->primeiro->caractere == '[')){
                inserirPilha(&aux,pilha);
            }else if(((caractere[contador] == '*') && (*pilha->primeiro->caractere == '-')) || ((caractere[contador] == '*') && (*pilha->primeiro->caractere == '+'))){
                inserirPilha(&aux,pilha);
            }else if(((caractere[contador] == '*') && (*pilha->primeiro->caractere == '*')) || ((caractere[contador] == '*') && (*pilha->primeiro->caractere == '/'))){
                while((pilha->primeiro != NULL) && ((*pilha->primeiro->caractere == '*') || (*pilha->primeiro->caractere == '/'))){
                    nCaractere[nContador] = *pilha->primeiro->caractere;
                    nContador ++;
                    desalocaPilha(pilha);
                }
                inserirPilha(&aux,pilha);
            }else if(((caractere[contador] == '/') && (*pilha->primeiro->caractere == '-')) || ((caractere[contador] == '/') && (*pilha->primeiro->caractere == '+'))){
                inserirPilha(&aux,pilha);
            }else if(((caractere[contador] == '/') && (*pilha->primeiro->caractere == '/')) || ((caractere[contador] == '/') && (*pilha->primeiro->caractere == '*'))){
                while((pilha->primeiro != NULL) && ((*pilha->primeiro->caractere == '/') || (*pilha->primeiro->caractere == '*'))){
                    nCaractere[nContador] = *pilha->primeiro->caractere;
                    nContador ++;
                    desalocaPilha(pilha);
                } 
                inserirPilha(&aux,pilha);
            }else if(((caractere[contador] == '+') && (*pilha->primeiro->caractere == '*')) || ((caractere[contador] == '+') && (*pilha->primeiro->caractere == '/')) || ((caractere[contador] == '+') && (*pilha->primeiro->caractere == '+')) || ((caractere[contador] == '+') && (*pilha->primeiro->caractere == '-'))){
                while((pilha->primeiro != NULL) && ((*pilha->primeiro->caractere == '/') || (*pilha->primeiro->caractere == '*') || (*pilha->primeiro->caractere == '-') || (*pilha->primeiro->caractere == '+'))){
                    nCaractere[nContador] = *pilha->primeiro->caractere;
                    nContador ++;
                    desalocaPilha(pilha);
                }
                inserirPilha(&aux,pilha);
            }else if(((caractere[contador] == '-') && (*pilha->primeiro->caractere == '*')) || ((caractere[contador] == '-') && (*pilha->primeiro->caractere == '/')) || ((caractere[contador] == '-') && (*pilha->primeiro->caractere == '-')) || ((caractere[contador] == '-') && (*pilha->primeiro->caractere == '+'))){
                while((pilha->primeiro != NULL) && ((*pilha->primeiro->caractere == '/') || (*pilha->primeiro->caractere == '*') || (*pilha->primeiro->caractere == '-') || (*pilha->primeiro->caractere == '+'))){
                    nCaractere[nContador] = *pilha->primeiro->caractere;
                    nContador ++;
                    desalocaPilha(pilha);
                } 
                inserirPilha(&aux,pilha);
            }else{
                inserirPilha(&aux,pilha);
            }
        }else if(caractere[contador] == ')'){
            t_elemento* elemento = pilha->primeiro;

            while(elemento != NULL){
                if(*elemento->caractere == '('){
                    desalocaPilha(pilha);
                    elemento->proximo = NULL;
                }else{
                    nCaractere[nContador] = *elemento->caractere;
                    nContador ++;
                    desalocaPilha(pilha);
                }
                elemento = elemento->proximo;
            }

        }else if(caractere[contador] == ']'){
            t_elemento* elemento = pilha->primeiro;

            while(elemento != NULL){
                if(*elemento->caractere == '['){
                    desalocaPilha(pilha);
                    elemento->proximo = NULL;
                }else{
                    nCaractere[nContador] = *elemento->caractere;
                    nContador ++;
                    desalocaPilha(pilha);
                }
                elemento = elemento->proximo;
            }

        }else if(caractere[contador] == '}'){
            t_elemento* elemento = pilha->primeiro;

            while(elemento != NULL){
                if(*elemento->caractere == '{'){
                    desalocaPilha(pilha);
                    elemento->proximo = NULL;
                }else{
                    nCaractere[nContador] = *elemento->caractere;
                    nContador ++;
                    desalocaPilha(pilha);
                }
                elemento = elemento->proximo;
            }

        }else if(caractere[contador] != ' '){
            nCaractere[nContador] = aux;
            nContador ++;

            if((caractere[contador+1] == '+') || (caractere[contador+1] == '-') || (caractere[contador+1] == '*') || (caractere[contador+1] == '/')){
                nCaractere[nContador] = ' ';
                nContador ++;             
            }
        }else if((caractere[contador] == ' ') && ((caractere[contador+1] == '+') || (caractere[contador+1] == '-') || (caractere[contador+1] == '*') || (caractere[contador+1] == '/'))){
            nCaractere[nContador] = ' ';
            nContador ++;
        }

        contador ++;
    }

    if(pilha->primeiro != NULL){
        t_elemento* elemento = pilha->primeiro;

        while(elemento != NULL){
            nCaractere[nContador] = *elemento->caractere;
            nContador ++;
            elemento = elemento->proximo;
            desalocaPilha(pilha);
        }
    }

    if(pilha->primeiro == NULL){
        free(pilha);
        pilha = NULL;
    }

    nCaractere[nContador] = '\0';
    
    printf("Expressão Valida!\n");
    printf("Forma Posfixa: ");

    int cont = 0;
    while(nCaractere[cont] != '\0'){
        if(((nCaractere[cont] != ' ') && (nCaractere[cont+1] == '+')) || 
           ((nCaractere[cont] != ' ') && (nCaractere[cont+1] == '-')) ||
           ((nCaractere[cont] != ' ') && (nCaractere[cont+1] == '*')) ||
           ((nCaractere[cont] != ' ') && (nCaractere[cont+1] == '/'))){
            printf("%c", nCaractere[cont]);
            printf(" ");
        }else if(((nCaractere[cont] == '+') && (nCaractere[cont+1] != ' ')) || 
                 ((nCaractere[cont] == '-') && (nCaractere[cont+1] != ' ')) ||
                 ((nCaractere[cont] == '/') && (nCaractere[cont+1] != ' ')) ||
                 ((nCaractere[cont] == '*') && (nCaractere[cont+1] != ' '))){
            printf("%c", nCaractere[cont]);
            printf(" ");
        }else{
            printf("%c", nCaractere[cont]);
        }
        cont ++;
    }

    printf("\n");
    printf("Valor da Expressao: \n");
    getchar();
    menu(pilha);

    return 1;
}

int expressaoInvalida(t_pilha* pilha){
    cabecalho();
    printf("Expressão Invalida! \n");
    
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
    pilha = NULL;
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
    setbuf(stdin, NULL);
    resposta(opcao,pilha);
}

void cabecalho(){
    system(CLEAR);
    printf("================================== \n");
    printf("\t PURA MATEMATICA \n");
    printf("================================== \n"); 
}

void resposta(int opcao, t_pilha* pilha){
    if(opcao == 0){
        system(CLEAR);
        cabecalho();
        printf("Saindo...");
        getchar();
        printf("\n");
    }else if(opcao == 1){
        cabecalho();
        char caractere[1000];
        printf("-> ");
        scanf("%[^\n]s", caractere);
        getchar();
        resolveExpressao(caractere,pilha);
    }else if(opcao == 2){
        calculadora();
    }else{
        system(CLEAR);
        cabecalho();
        printf("Comando Invalido...");
        getchar();
        menu(pilha);
    }
}