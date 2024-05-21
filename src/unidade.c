#include <stdio.h>
#include <stdlib.h>
#include "unidade.h"

// Estrutura para representar uma unidade
typedef struct unidade{
    int x, y;
    int tipo; // 1-soldado, 2-explorador
    struct unidade *prox;
} TUnidade;

typedef struct{
    TUnidade *ini, *fim;
    int tam;
} CUnidade;

TUnidade *unidade_aloca(int x, int y, int tipo)
{
    TUnidade *novo = (TUnidade*)malloc(sizeof(TUnidade));
    if(!novo){
        printf("Falha ao alocar memoria.\n");
        return NULL;
    }
    novo->x = x; 
    novo->y = y;
    novo->tipo = tipo;
    novo->prox = NULL;
    return novo;
}