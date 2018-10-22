/*
* ALUNO = MAURILIO DE JESUS SILVEIRA
* MATRICULA = 17/0152294
* CURSO = CIENCIA DA COMPUTACAO BACHARELADO
*/

#include <stdio.h>
#include "pilha.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Alocando uma pilha que vai armazenar a conversao de char para double*/
t_pilhaNumero* alocaPilhaNumero(){
    t_pilhaNumero* pilha = (t_pilhaNumero*) malloc(sizeof(t_pilhaNumero));

    if(!pilha){
        exit(-1);
    }

    pilha->primeiro = NULL;
    pilha->topo = -1;

    return pilha;
}/*end alocaPilhaNumero();*/

/*Alocando uma pilha que vai armazenar a expressao*/
t_pilha* alocaPilha(){
    t_pilha* pilha = (t_pilha*) malloc(sizeof(t_pilha));

    if(!pilha){
        exit(-1);
    }

    pilha->primeiro = NULL;
    pilha->topo = -1;

    return pilha;
}/*end alocaPilha();*/

/*Alocando elementos que vao ser da pilha de char*/
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
}/*end alocaElemento(char* caractere, t_pilha* pilha);*/

/*Inserindo na pilha que vai ser do tipo de char*/
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
}/*end inserirPilha(char* caractere, t_pilha* pilha);*/

/*Desalocando da pilha que vai ser do tipo char*/
void desalocaPilha(t_pilha* pilha){
    t_elemento* elemento = pilha->primeiro;
    pilha->primeiro = elemento->proximo;

    free(elemento->caractere);
    free(elemento);
    elemento = NULL;
    pilha->topo --;
}/*end desalocaPilha(t_pilha* pilha);*/

/*Validacao da expressao informada pelo usuario para saber se e valida ou invalida*/
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
}/*end resolveExpressao(char* caractere, t_pilha* pilha);*/

/*Transformacao de uma expressao valida em PosFixa*/
int posFixa(t_pilha* pilha, char* caractere){
    cabecalho();
    int contador = 0, nContador = 0;
    char aux, nCaractere [100];

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

    int cont = 0, contPos = 0;
    char expressaoPosFixa[100];

    while(nCaractere[cont] != '\0'){
        if(((nCaractere[cont] != ' ') && (nCaractere[cont+1] == '+')) || 
           ((nCaractere[cont] != ' ') && (nCaractere[cont+1] == '-')) ||
           ((nCaractere[cont] != ' ') && (nCaractere[cont+1] == '*')) ||
           ((nCaractere[cont] != ' ') && (nCaractere[cont+1] == '/'))){
            expressaoPosFixa[contPos] = nCaractere[cont];
            contPos ++;
            expressaoPosFixa[contPos] = ' ';
        }else if(((nCaractere[cont] == '+') && (nCaractere[cont+1] != ' ')) || 
                 ((nCaractere[cont] == '-') && (nCaractere[cont+1] != ' ')) ||
                 ((nCaractere[cont] == '/') && (nCaractere[cont+1] != ' ')) ||
                 ((nCaractere[cont] == '*') && (nCaractere[cont+1] != ' '))){
            expressaoPosFixa[contPos] = nCaractere[cont];
            contPos ++;
            expressaoPosFixa[contPos] = ' ';
        }else{
            expressaoPosFixa[contPos] = nCaractere[cont];
        }
        contPos ++;
        cont ++;
    }

    expressaoPosFixa[contPos] = '\0';
    int i = 0, j = 0;
    char expressao[100];
    double valor = 0, a = 0 , b = 0, r = 0;

    t_pilhaNumero* pilha2 = alocaPilhaNumero();
    
    while((expressaoPosFixa[i] != '\0') && (i < strlen(expressaoPosFixa))) {
        j=0;
        if((expressaoPosFixa[i]>=65 && expressaoPosFixa[i]<=90) || (expressaoPosFixa[i]>=97 && expressaoPosFixa[i]<=122)){
            printf("Forma Posfixa: ");
            printf("%s\n", expressaoPosFixa);
            printf("Não é possível calcular a expressao!\n");
            getchar();
            if(pilha2->primeiro != NULL){
                t_numero* elemento = pilha2->primeiro;

                while(elemento != NULL){
                    desalocaPilhaNumero(pilha2);
                }
            }
            if(pilha2->primeiro == NULL){
                free(pilha2);
                pilha2 = NULL;
            }
            menu(pilha);
        }else if(expressaoPosFixa[i]<=57 && expressaoPosFixa[i]>=48){
            while(expressaoPosFixa[i] != ' ') {
                expressao[j] = expressaoPosFixa[i]; 
                i++;
                j++;
            }
            expressao[j] = '\0';
            valor = stringDouble(expressao); 
            inserirNumero(pilha2,valor);
        }else if(expressaoPosFixa[i] == '+'){
            a = pilha2->primeiro->valor;
            desalocaPilhaNumero(pilha2);
            b = pilha2->primeiro->valor;
            desalocaPilhaNumero(pilha2);
            r = b+a;
            inserirNumero(pilha2,r);
        }else if(expressaoPosFixa[i] == '-'){
            a = pilha2->primeiro->valor;
            desalocaPilhaNumero(pilha2);
            b = pilha2->primeiro->valor;
            desalocaPilhaNumero(pilha2);
            r = b-a;
            inserirNumero(pilha2,r);
        }else if(expressaoPosFixa[i] == '*'){
            a = pilha2->primeiro->valor;
            desalocaPilhaNumero(pilha2);
            b = pilha2->primeiro->valor;
            desalocaPilhaNumero(pilha2);
            r = b*a;
            inserirNumero(pilha2,r);
        }else if(expressaoPosFixa[i] == '/'){
            a = pilha2->primeiro->valor;
            desalocaPilhaNumero(pilha2);
            b = pilha2->primeiro->valor;
            desalocaPilhaNumero(pilha2);
            r = b/a;
            inserirNumero(pilha2,r);
        }
        i++;
    }
    printf("Forma Posfixa: ");
    printf("%s\n", expressaoPosFixa);
    printf("Valor da Expressao: %lf\n", pilha2->primeiro->valor);
    getchar();
    desalocaPilhaNumero(pilha2);
    if(pilha2->primeiro == NULL){
        free(pilha2);
        pilha2 = NULL;
    }
    menu(pilha);

    return 1;
}/*end posFixa(t_pilha* pilha, char* caractere);*/

/*Desalocando um double da pilha de numeros*/
void desalocaPilhaNumero(t_pilhaNumero* pilha){
    t_numero* elemento = pilha->primeiro;
    pilha->primeiro = elemento->proximo;

    free(elemento);
    elemento = NULL;
    pilha->topo --;
}/*end desalocaPilhaNumero(t_pilhaNumero* pilha);*/

/*Convertendo char em double*/
double stringDouble(char expressao[]){
    char *token;                 
    int i;
    const char delimitador[3] = ".,";
    double valor;

    valor = 0;

    token = strtok(expressao, delimitador);

    for(i=0; i<strlen(token); i++) { 
        valor = valor + ((double)token[i] - 48) * pow(10, strlen(token) - (i + 1));
    }

    while(token != NULL) {
        token = strtok(NULL, delimitador);  

        if(token != NULL) {
            for(i=0; i<strlen(token); i++) { 
                valor = valor + ((double) token[i] - 48) * pow(10, -1*(i + 1));
            }
        }
    }

    return valor;

}/*end stringDouble(char expressao[]);*/

/*Inserindo um numero na pilha de doubles*/
int inserirNumero(t_pilhaNumero* pilha, double valor){
    if(pilha == NULL){
        exit(-1);
    }

    t_numero* aux_inserir = alocaNumero(pilha,valor);
        
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
}/*end inserirNumero(t_pilhaNumero* pilha, double valor);*/

/*A alocando a struct auxiliar que vai alocar apenas double*/
t_numero* alocaNumero(t_pilhaNumero* pilha, double valor){
    t_numero* numero = (t_numero*) malloc(sizeof(t_numero));

    if(!numero){
        free(pilha);
        exit(-1);
    }

    numero->valor = valor;
    numero->proximo = NULL;

    return numero;
}/*end alocaNumero(t_pilhaNumero* pilha, double valor);*/

/*Funcao para quando a expressao fornecida for invalida*/
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
}/*end expressaoInvalida(t_pilha* pilha);*/

int calculadora(t_pilha* pilha){
    /*if(pilha == NULL){
        pilha = alocaPilha();
    }

    char comando[100];

    while(comando != 'x'){
        cabecalho();
        printf("\t Modo Calculadora\n");

        if(pilha->primeiro == NULL){
            printf("A pilha esta vazia! \n");
        }

        printf("-> ");
        scanf("%s", comando);
    }*/

    return 1;
}

/*Menu do programa*/
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
}/*end menu(t_pilha* pilha);*/

/*Cabecalho do programa*/
void cabecalho(){
    system(CLEAR);
    printf("================================== \n");
    printf("\t PURA MATEMATICA \n");
    printf("================================== \n"); 
}/*end cabecalho();*/

/*Pegando a resposta do usuario*/
void resposta(int opcao, t_pilha* pilha){
    if(opcao == 0){
        system(CLEAR);
        cabecalho();
        printf("Saindo...");
        getchar();
        printf("\n");
    }else if(opcao == 1){
        cabecalho();
        char caractere[100];
        printf("-> ");
        scanf("%[^\n]s", caractere);
        getchar();
        resolveExpressao(caractere,pilha);
    }else if(opcao == 2){
        calculadora(pilha);
    }else{
        system(CLEAR);
        cabecalho();
        printf("Comando Invalido...");
        getchar();
        menu(pilha);
    }
}/*end resposta(int opcao, t_pilha* pilha);*/