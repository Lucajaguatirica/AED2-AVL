#ifndef TAVL_H_INCLUDED
#define TAVL_H_INCLUDED

typedef struct AVL{
    int info;
    int fb;
    struct AVL *esq;
    struct AVL *dir;
}TAVL;

int fatorBalanceamento(TAVL *main);
int retornaMaior(int x, int y);
int altura(TAVL *main);
void rotacaoEE(TAVL **main);
void rotacaoRR(TAVL **main);
void rotacaoDE(TAVL **main);
void rotacaoED(TAVL **main);
int inserir(TAVL **main, int num);
TAVL* procuraMenor(TAVL *main);
int remover(TAVL **main, int num);
void imprimir(TAVL* main);

#endif // TAVL_H_INCLUDED
