#include "libraries.h"

// Estrutura para representar uma unidade
typedef struct _unidade
{
    char chave;
    int id; 
    int x, y;
    int tipo;
    struct _unidade *prox;
} TUnidade;

typedef struct _cunidade
{
    TUnidade *ini, *fim;
    int tam;
} CUnidade;

TUnidade *tunidade_aloca(const char chave, const int id, const int tipo, const int x, const int y)
{
    TUnidade *novo = (TUnidade*)malloc(sizeof(TUnidade));
    if(!novo){
        msg_erro("Falha ao alocar memoria.\n", "tunidade_aloca");
        return NULL;
    }

    novo->chave = chave;
    novo->id = id;
    novo->tipo = tipo;
    novo->x = x;  
    novo->y = y;
    novo->prox = NULL;

    return novo;
}

CUnidade *cunidade_cria(void) 
{
    CUnidade *novo = (CUnidade*) malloc(sizeof(CUnidade));
    if(!novo)
    {
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

void unidade_inserir(CUnidade *cabeca, const char chave, const char id, const int tipo, const int x, const int y)
{
    TUnidade *novo = tunidade_aloca(chave, id, tipo, x, y);
    if(!novo)
    {
        msg_erro("\nFalha ao inserir unidade.", "unidade_inserir");
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

void cunidade_desaloca(CUnidade **cabeca) 
{
    assert(cabeca);
   if (*cabeca == NULL) return;

    CUnidade *C = *cabeca;
    TUnidade *aux = C->ini, *temp = NULL;
    while(aux)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    free(C);
    *cabeca = NULL;
}

void tunidade_desaloca(CUnidade *cabeca, const int id)
{
    assert(cabeca);
    if (unidade_vazia(cabeca))
    {
        msg_erro("Unidade nao existe.", "tunidade_desaloca");
        return;
    }

    TUnidade *aux = cabeca->ini, *temp;

    if(aux->id == id){ 
        cabeca->ini = aux->prox;
        free(aux);

    } else {
        temp = aux;
        aux = aux->prox;
        while(aux)
        {
            if(aux->id == id){
                temp->prox = aux->prox;
                free(aux);
                return;
            }
            temp = aux;
            aux = aux->prox;            
        }
        msg_erro("Unidade nao encontrada!", "tunidade_desaloca");
    }
}

TUnidade *unidade_buscar(CUnidade *cabeca, const int id)
{
    TUnidade *aux = cabeca->ini;
    while(aux)
    {
        if (aux->id == id)
        {
            return aux;
        }
        aux = aux->prox;
    }
    msg_erro("Não foi possível localizar a unidade.", "unidade_buscar");

    return NULL;
}

void unidade_move(CUnidade *cabeca, char *nome, const int tipo, const int novo_x, const int novo_y)
{
    int id = (int)nome[1] - 48;

    TUnidade *unidade = unidade_buscar(cabeca, id);
    unidade->x = novo_x;
    unidade->y = novo_y;
}

void unidade_merge(CUnidade *cabeca_1, CUnidade *cabeca_2) 
{
    TUnidade *aux_2 = cabeca_2->ini;

    while (aux_2)
    {
        unidade_inserir(cabeca_1, aux_2->chave, aux_2->id, aux_2->tipo, aux_2->x, aux_2->y);
        aux_2 = aux_2->prox;
    }
}

void mapa_unidade_atualiza(CUnidade *cabeca, char **mapa_unidade) 
{
    TUnidade *aux = cabeca->ini;
    while (aux)
    {
        int x = aux->x, y = aux->y;
        mapa_unidade[x][y] = aux->chave;
        aux = aux->prox;
    }    
}