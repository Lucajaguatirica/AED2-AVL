/**
*   @author Patrick Araújo: https://github.com/patrickaraujo
*   Árvore AVL
*/

#include <stdio.h>
#include <stdlib.h>
#include "TAVL.h"
#include "TAVL.c"

int main(){
    TAVL *avl = NULL;
    int res, i, N = 10, dados[10] = {1, 2, 3, 10, 4, 5, 9, 7, 8, 6};

    for(i = 0; i < N; i++)
        res = inserir(&avl, dados[i]);

    printf("Arvore AVL:\t");
    imprimir(avl);
    printf("\nFator de balanceamento: %i\n", fatorBalanceamento(avl));
    int r = 6;
    remover(&avl, r);
    printf("Remocao do numero %i\n", r);
    printf("Arvore AVL:\t");
    imprimir(avl);
    return 0;
}
