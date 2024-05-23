#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unidade.h"
#include "faccao.h"
#include "mensagens.h"

// Estrutura para representar uma unidade
typedef struct _unidade{
    char nome[3]; // A1 / A2 / B1 / B2
    int x, y;
    int tipo; // 1-soldado, 2-explorador
    struct _unidade *prox;
} TUnidade;

typedef struct _cunidade{
    TUnidade *ini, *fim;
    int tam;
} CUnidade;

TUnidade *tunidade_aloca(const char *nome, const int tipo, const int x, const int y)
{
    TUnidade *novo = (TUnidade*)malloc(sizeof(TUnidade));
    if(!novo){
        msg_erro("Falha ao alocar memoria.\n", "tunidade_aloca");
        return NULL;
    }

    strcpy(novo->nome, nome);
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

int unidade_vazia(const CUnidade *cabeca) 
{
    return(cabeca == NULL || cabeca->tam == 0);
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

void unidade_insere(CUnidade *cabeca, const char *nome, const int tipo, const int x, const int y) {
    TUnidade *novo = tunidade_aloca(nome, tipo, x, y);
    if(!novo){
        msg_erro("Falha ao inserir unidade.", "cunidade_insere");
        return;
    }
    if (unidade_vazia(cabeca)){
        cabeca->ini = cabeca->fim = novo;

    } else {
        novo->prox = cabeca->ini;
        cabeca->ini = novo;
    }
    cabeca->tam++;
}

void unidade_display(const CUnidade *cabeca) 
{
    if (unidade_vazia(cabeca))
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



