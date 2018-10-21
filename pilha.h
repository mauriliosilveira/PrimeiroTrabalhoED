#ifndef __PILHA_H__
#define __PILHA_H__

#define CLEAR "clear"

typedef struct elemento{
    char* caractere;
    struct elemento* proximo;
} t_elemento;

typedef struct numero{
    double valor;
    struct numero* proximo;
} t_numero;

typedef struct{
    t_numero* primeiro;
    int topo;
} t_pilhaNumero;

typedef struct{
    t_elemento* primeiro;
    int topo;
} t_pilha;


t_pilha* alocaPilha();
t_elemento* alocaElemento(char* caractere, t_pilha* pilha);

int inserirPilha(char* caractere, t_pilha* pilha);


double stringDouble(char expressao[]);
int inserirNumero(t_pilhaNumero* pilha, double valor);
t_numero* alocaNumero(t_pilhaNumero* pilha, double valor);
void printaPilha(t_pilhaNumero* pilha);
void desalocaPilhaNumero(t_pilhaNumero* pilha);


int expressaoInvalida(t_pilha* pilha);
void desalocaPilha(t_pilha* pilha);
int resolveExpressao(char* caractere, t_pilha* pilha);

int posFixa(t_pilha* pilha, char* caractere);
float valorExpressao(t_pilha* pilha, char* expressao);

void resposta(int opcao,t_pilha* pilha);
void menu(t_pilha* pilha);
void cabecalho();
int calculadora(t_pilha* pilha);

#endif