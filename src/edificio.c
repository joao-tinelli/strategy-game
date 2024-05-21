#include <stdio.h>
#include <stdlib.h>
#include "mensagens.h"
#include "edificio.h"

// Estrutura para representar uma edifício
typedef struct edificio{
    int x, y;
    int tipo; // 1-edifício de recursos, 2-campo de treinamento 3-laboratório de pesquisa
    struct edificio *prox;
} TEdificio;

typedef struct _cedificio{
    TEdificio *ini, *fim;
    int tam;
} CEdificio;

TEdificio *Tedificio_aloca(const int x, const int y, const int tipo)
{
    TEdificio *novo = (TEdificio*)malloc(sizeof(TEdificio));
    if(!novo){
        msg_erro("Falha ao criar edificio.", "Tedificio_aloca");
        return NULL;
    }
    novo->x = x; 
    novo->y = y;
    novo->tipo = tipo;
    novo->prox = NULL;
    return novo;
}

CEdificio *CEdificio_cria(void)
{
    CEdificio *novo = (CEdificio*)malloc(sizeof(CEdificio));

    if(!novo){
        msg_erro("Falha ao criar o edificio.", "CEdificio_cria");
        return NULL;
    }

    novo->ini = novo->fim = NULL;
    novo->tam = 0;

    return novo;
}

int Tedificio_vazio(const CEdificio *cabeca)
{
    return(cabeca->tam == 0);
}

void edificio_inserir(CEdificio *cabeca, const int x, const int y, const int tipo)
{
    TEdificio *novo = Tedificio_aloca(x, y, tipo);
    if(!novo){
        msg_erro("Falha ao inserir edificio.", "edificio_inserir");
        return;
    }
    if (Tedificio_vazio(cabeca)){
        cabeca->ini = cabeca->fim = novo;

    } else {
        novo->prox = cabeca->ini;
        cabeca->ini = novo;
    }
    cabeca->tam++;
}

void edificio_desaloca(CEdificio **cabeca)
{
    if (Tedificio_vazio(*cabeca)) return;
    
    TEdificio *aux = (*cabeca)->ini, *temp;
    while(aux){
        temp = aux;
        aux = temp->prox;
        free(temp);
    }

    free(*cabeca);
    *cabeca = NULL;
}

void edificio_display(const CEdificio *cabeca)
{
    if (Tedificio_vazio(cabeca))
    {
        msg_erro("Edificio vazio.", "edificio_display");
        return;
    }
    TEdificio *aux = cabeca->ini;
    while(aux){
        printf("posicao '%d,%d, tipo: %d\n", aux->x, aux->y, aux->tipo);
        aux = aux->prox;
    }
}

