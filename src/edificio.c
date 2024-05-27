#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edificio.h"
#include "faccao.h"
#include "mapa.h"
#include "mensagens.h"

// Estrutura para representar uma edifício
typedef struct edificio
{
    char chave;
    int x, y;
    int tipo; // 1-edifício de recursos, 2-campo de treinamento 3-laboratório de pesquisa
    struct edificio *prox;
} TEdificio;

typedef struct _cedificio
{
    TEdificio *ini, *fim;
    int tam;
} CEdificio;

TEdificio *tedificio_aloca(const char chave, const int tipo, const int x, const int y)
{
    TEdificio *novo = (TEdificio*)malloc(sizeof(TEdificio));
    if(!novo)
    {
        msg_erro("Falha ao criar edificio.", "Tedificio_aloca");
        return NULL;
    }
    novo->chave = chave;
    novo->tipo = tipo;
    novo->x = x; 
    novo->y = y;    
    novo->prox = NULL;
    return novo;
}

CEdificio *cedificio_cria(void)
{
    CEdificio *novo = (CEdificio*)malloc(sizeof(CEdificio));

    if(!novo)
    {
        msg_erro("Falha ao criar o edificio cabeca.", "cedificio_cria");
        return NULL;
    }

    novo->ini = novo->fim = NULL;
    novo->tam = 0;

    return novo;
}

int edificio_vazio(const CEdificio *cabeca) 
{
    return(cabeca == NULL || cabeca->tam == 0);
}

int edificio_existente(const CEdificio *cabeca, const char chave)
{
    if(edificio_vazio(cabeca)) return 0;
    TEdificio *aux = cabeca->ini;
    while(aux)
    {
        if(aux->chave == chave)
        {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void edificio_insere(CEdificio *cabeca, const char chave, const int tipo, const int x, const int y)
{
    if(edificio_existente(cabeca, chave))
    {
        msg_erro("Edificio ja inserido", "edificio_insere");
        return;
    }
    
    TEdificio *novo = tedificio_aloca(chave, tipo, x, y);
    if(!novo)
    {
        msg_erro("Falha ao alocar edificio.", "tedificio_aloca");
        return;
    }
    if (edificio_vazio(cabeca)){
        cabeca->ini = cabeca->fim = novo;

    } else {
        novo->prox = cabeca->ini;
        cabeca->ini = novo;
    }
    cabeca->tam++;
}

void edificio_display(const CEdificio *cabeca)
{
    if (edificio_vazio(cabeca))
    {
        msg_erro("Edificio vazio.", "edificio_display");
        return;
    }
    TEdificio *aux = cabeca->ini;
    while(aux)
    {
        printf("chave: %c, posicao '%d,%d, tipo: %d\n", aux->chave, aux->x, aux->y, aux->tipo);
        aux = aux->prox;
    }
}

void edificio_posiciona_mapa(char **mapa, CEdificio *cabeca, char chave)
{
    TEdificio *aux = cabeca->ini;
    int x, y;
    while(aux)
    {
        if (aux->chave == chave)
        {
            x = aux->x, y = aux->y;
            mapa[x][y] = chave;
            return;
        }
        aux = aux->prox;
    }   
}

void edificio_retira_mapa(char **mapa, char **mapa_oficial, CEdificio *cabeca, char chave)
{
    TEdificio *aux = cabeca->ini;
    int x, y;
    while(aux)
    {
        if (aux->chave == chave)
        {
            x = aux->x, y = aux->y;
            mapa[x][y] = mapa_oficial[x][y];
            return;
        }
        aux = aux->prox;
    }   
}

void cedificio_desaloca(CEdificio **cabeca) 
{
   if (*cabeca == NULL) return;

    CEdificio *C = *cabeca;
    TEdificio *aux = C->ini, *temp = NULL;
    while(aux)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    free(C);
    *cabeca = NULL;
}


