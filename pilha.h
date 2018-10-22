/*
* ALUNO = MAURILIO DE JESUS SILVEIRA
* MATRICULA = 17/0152294
* CURSO = CIENCIA DA COMPUTACAO BACHARELADO
*/

#ifndef __PILHA_H__
#define __PILHA_H__

#define CLEAR "clear"

/*Struct para pegar os caracteres da expressão fornecida pelo usuario*/
typedef struct elemento{
    char* caractere;
    struct elemento* proximo;
} t_elemento;

/*Struct auxiliar para o calculo da expressao final apos ser validada*/
typedef struct numero{
    double valor;
    struct numero* proximo;
} t_numero;

/*Pilha auxiliar que só irá ser utilizada quando a expressão for validada para calcular seu resultado*/
typedef struct{
    t_numero* primeiro;
    int topo;
} t_pilhaNumero;

/*Pilha que tem irá ser utilizada no decorrer da validação da expressão*/
typedef struct{
    t_elemento* primeiro;
    int topo;
} t_pilha;


t_pilha* alocaPilha(); /*aloca a pilha que irá ser utilizada na validação da expressão*/
t_elemento* alocaElemento(char* caractere, t_pilha* pilha); /*aloca um elemento que irá ser utilizado na validação da expressão*/

int inserirPilha(char* caractere, t_pilha* pilha); /*funcao para inserir caracteres na pilha*/

double stringDouble(char expressao[]); /*função que tem como objetivo converter char para double*/
int inserirNumero(t_pilhaNumero* pilha, double valor); /*funcao que tem como objetivo alocar um double depois de convertido*/
t_numero* alocaNumero(t_pilhaNumero* pilha, double valor); /*funcao que aloca um double na pilha de numeros*/
void desalocaPilhaNumero(t_pilhaNumero* pilha); /*desalocando um double armazenado na pilha de numeros*/

int expressaoInvalida(t_pilha* pilha); /*funcao que informa que a expressao fornecida e invalida*/
void desalocaPilha(t_pilha* pilha); /*desalocando elementos da pilha de caracteres*/
int resolveExpressao(char* caractere, t_pilha* pilha); /*funcao que analisa e informa se a expressao e valida ou invalida*/

int posFixa(t_pilha* pilha, char* caractere); /*foncao que transforma a expressao valida em uma expressao posfixa*/

void resposta(int opcao,t_pilha* pilha); /*analiza a resposta que o usuario informou*/
void menu(t_pilha* pilha); /*menu do programa*/
void cabecalho(); /*printa o cabecalho do programa*/
int calculadora(t_pilha* pilha); /*modo calculadora*/

#endif