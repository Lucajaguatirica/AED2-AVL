#include <stdio.h>
#include <stdlib.h>
#include "TAVL.h"

int fatorBalanceamento(TAVL *main){
    return labs( altura(main->esq) - altura(main->dir) );
}

int retornaMaior(int x, int y){
    return ( ( x > y ) ? x : y );
}

int altura(TAVL *main){
    if(main){
		return main->fb;
	}
	return -1;
}

void rotacaoEE(TAVL **main){    //  Rotação Simples à Esquerda
    TAVL *temp = (*main)->esq;
    (*main)->esq = temp->dir;
    temp->dir = *main;
    (*main)->fb = retornaMaior(altura((*main)->esq), altura((*main)->dir)) + 1;
    temp->fb = retornaMaior(altura(temp->esq), (*main)->fb) + 1;
    *main = temp;
}

void rotacaoDD(TAVL **main){    //  Rotação Simples à Direita
    TAVL *temp = (*main)->dir;
    (*main)->dir = temp->esq;
    temp->esq = (*main);
    (*main)->fb = retornaMaior(altura((*main)->esq),altura((*main)->dir)) + 1;
    temp->fb = retornaMaior(altura(temp->dir), (*main)->fb) + 1;
    *main = temp;
}

void rotacaoDE(TAVL **main){    //  Rotação Dupla à Esquerda
    rotacaoEE(&((*main)->dir));
    rotacaoDD(main);
}

void rotacaoED(TAVL **main){    //  Rotação Dupla à Direita
    rotacaoDD(&((*main)->esq));
    rotacaoEE(main);
}

int inserir(TAVL **main, int num){
    int res;
    if(!(*main)){   //  Árvore vazia ou nó folha
        TAVL *aux = (TAVL *) malloc(sizeof(TAVL));
        aux->info = num; aux->fb = 0; aux->esq = aux->dir = NULL;
        (*main) = aux;
        return 1;
    }

    TAVL *temp = (*main);
    if(num < temp->info){
        if((res = inserir((&(temp->esq)), num)) == 1)
            if(fatorBalanceamento(temp) >= 2){
                if( num < (*main)->esq->info )
                    rotacaoEE(main);
                else
                    rotacaoED(main);
            }
    }
    else{
        if((res = inserir((&(temp->dir)), num)) == 1)
            if(fatorBalanceamento(temp) >= 2)
                if( num >= (*main)->dir->info )
                    rotacaoDD(main);
                else
                    rotacaoDE(main);
    }

    temp->fb = retornaMaior( altura(temp->esq), altura(temp->dir) ) + 1;

    return res;
}

TAVL* procuraMenor(TAVL *main){
    TAVL *aux = main, *temp = main->esq;
    while(temp){
        aux = temp;
        temp = temp->esq;
    }
    return aux;
}

int remover(TAVL **main, int num){
	if(!(*main)){	//	valor não existe
	    printf("Valor não existe!\n");
	    return 0;
	}

    int res;
	if(num < (*main)->info)
	    if( (res = remover(&(*main)->esq, num)) == 1 )
            if(fatorBalanceamento(*main) >= 2){
                if( altura((*main)->dir->esq) <= altura((*main)->dir->dir) )
                    rotacaoDD(main);
                else
                    rotacaoDE(main);
            }
    //  if((*main)->info < num)
	if(num > (*main)->info)
	    if( (res = remover(&(*main)->dir, num)) == 1 )
            if(fatorBalanceamento(*main) >= 2){
                if( altura((*main)->esq->dir) <= altura((*main)->esq->esq) )
                    rotacaoEE(main);
                else
                    rotacaoED(main);
            }

	if((*main)->info == num){
	    if( ( !(*main)->esq ) || ( !(*main)->dir ) ) {	//	nó tem 1 filho ou nenhum
			TAVL *aux = *main;
			if( (*main)->esq )
                *main = (*main)->esq;
            else
                *main = (*main)->dir;
			free(aux);
		}
		else {	//	nó tem 2 filhos
			TAVL *temp = procuraMenor( (*main)->dir );
			(*main)->info = temp->info;
			remover( &(*main)->dir, (*main)->info );
            if( fatorBalanceamento(*main) >= 2 ){
				if( altura((*main)->esq->dir) <= altura((*main)->esq->esq) )
					rotacaoEE(main);
				else
					rotacaoED(main);
			}
		}
		if (*main)
            (*main)->fb = retornaMaior( altura((*main)->esq), altura((*main)->dir) ) + 1;
		return 1;
	}

	(*main)->fb = retornaMaior( altura((*main)->esq), altura((*main)->dir) ) + 1;

	return res;
}

void imprimir(TAVL* main){
    //  Essa função imprime os elementos de forma recursiva

    printf("(");    //  notação para organizar na hora de mostrar os elementos
    if(main) {  //  se a árvore não for vazia...
        //  Mostra os elementos em pré-ordem
        printf("%d ", main->info);  //  mostra a raiz
        imprimir(main->esq);   //  mostra a sae (subárvore à esquerda)
        imprimir(main->dir);   //  mostra a sad (subárvore à direita)
    }
    printf(")");    //  notação para organizar na hora de mostrar os elementos
}
