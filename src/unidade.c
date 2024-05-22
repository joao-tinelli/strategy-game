#include <stdio.h>
#include <stdlib.h>

#include "unidade.h"
#include "mensagens.h"

// Estrutura para representar uma unidade
typedef struct _unidade{
    int x, y;
    int tipo; // 1-soldado, 2-explorador
    struct _unidade *prox;
} TUnidade;

typedef struct _cunidade{
    TUnidade *ini, *fim;
    int tam;
} CUnidade;

TUnidade *tunidade_aloca(int x, int y, int tipo)
{
    TUnidade *novo = (TUnidade*)malloc(sizeof(TUnidade));
    if(!novo){
        msg_erro("Falha ao alocar memoria.\n", "tunidade_aloca");
        return NULL;
    }

    novo->x = x; 
    novo->y = y;
    novo->tipo = tipo;
    novo->prox = NULL;

    return novo;
}

CUnidade *cunidade_cria(void) 
{
    CUnidade *novo = (CUnidade*) malloc(sizeof(CUnidade));
    if(!novo){
        msg_erro("Falha ao alocar memoria.\n", "cunidade_cria");
        return NULL;
    }

    novo->ini = novo->fim = NULL;
    novo->tam = 0;

    return novo;
}

int cunidade_vazia(const CUnidade *cabeca) 
{
    return(cabeca->tam == 0);
}

void cunidade_desaloca(CUnidade **cabeca) 
{
   if (*cabeca == NULL) return;

    CUnidade *C = *cabeca;
    TUnidade *aux = C->ini, *temp = NULL;
    while(aux){
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    free(C);
    *cabeca = NULL;
}

void cunidade_insere(CUnidade *cabeca, const int x, const int y, const int tipo) {
    TUnidade *novo = tunidade_aloca(x, y, tipo);
    if(!novo){
        msg_erro("Falha ao inserir unidade.", "cunidade_insere");
        return;
    }
    if (cunidade_vazia(cabeca)){
        cabeca->ini = cabeca->fim = novo;

    } else {
        novo->prox = cabeca->ini;
        cabeca->ini = novo;
    }
    cabeca->tam++;
}

void cunidade_display(const CUnidade *cabeca) 
{
    if (cunidade_vazia(cabeca))
    {
        msg_erro("Unidade vazia.", "cunidade_display");
        return;
    }
    TUnidade *aux = cabeca->ini;
    while(aux){
        printf("pos: (%d, %d). Tipo: %d.\n", aux->x, aux->y, aux->tipo);
        aux = aux->prox;
    }
}
