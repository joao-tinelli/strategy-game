#include <stdio.h>
#include <stdlib.h>
#include "edificio.h"

// Estrutura para representar uma edifício
typedef struct edificio{
    int x, y;
    int tipo; // 1-edifício de recursos, 2-campo de treinamento 3-laboratório de pesquisa
    struct edificio *prox;
} TEdificio;

typedef struct{
    TEdificio *ini, *fim;
    int tam;
} CEdificio;

TEdificio *edificio_aloca(int x, int y, int tipo)
{
    TEdificio *novo = (TEdificio*)malloc(sizeof(TEdificio));
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
