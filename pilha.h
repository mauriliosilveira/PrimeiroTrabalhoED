#ifndef __PILHA_H__
#define __PILHA_H__

#define CLEAR "clear"

typedef struct elemento{
    char* caractere;
    struct elemento* proximo;
} t_elemento;

typedef struct{
    t_elemento* primeiro;
    int topo;
} t_pilha;

t_pilha* alocaPilha();
t_elemento* alocaElemento(char* caractere, t_pilha* pilha);

int inserirPilha(char* caractere, t_pilha* pilha);
void printarPilha(t_pilha* pilha);

int expressaoInvalida(t_pilha* pilha);
void desalocaPilha(t_pilha* pilha);
int resolveExpressao(char* caractere, t_pilha* pilha);

void resposta(int opcao,t_pilha* pilha);
void menu(t_pilha* pilha);
void cabecalho();

#endif