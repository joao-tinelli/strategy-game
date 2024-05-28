#include "bibliotecas.h"

// Estrutura para representar uma unidade
typedef struct _unidade
{
    char chave; 
    int x, y;
    int tipo; // 1-soldado, 2-explorador
    struct _unidade *prox;
} TUnidade;

typedef struct _cunidade
{
    TUnidade *ini, *fim;
    int tam;
} CUnidade;

TUnidade *tunidade_aloca(const char chave, const int tipo, const int x, const int y)
{
    TUnidade *novo = (TUnidade*) malloc(sizeof(TUnidade));
    if(!novo){
        msg_erro("Falha ao alocar memoria.\n", "tunidade_aloca");
        return NULL;
    }

    novo->chave = chave;
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

void cunidade_desaloca(CUnidade **cabeca) 
{
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

int unidade_vazia(const CUnidade *cabeca) 
{
    return(cabeca == NULL || cabeca->tam == 0);
}

void unidade_insere(CUnidade *cabeca, TUnidade *novo)
{
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
    while(aux)
    {
        printf("chave: %c. \npos: (%d, %d). Tipo: %d.\n",aux->chave, aux->x, aux->y, aux->tipo);
        aux = aux->prox;
    }
}

void unidade_posiciona_mapa(char **mapa_unidade, TUnidade *novo)
{
    int x = novo->x, y = novo->y;
    mapa_unidade[x][y] = novo->chave;
}

void unidade_retira_mapa(char **mapa_unidade, char **mapa_oficial, TUnidade *unidade)
{
    int x = unidade->x, y = unidade->y;
    mapa_unidade[x][y] = mapa_oficial[x][y];  
}

// Funcao principal de posicionamento
void unidade_posiciona(char *nome_faccao, CUnidade *cabeca, int tipo, int x, int y, char **mapa_unidade)
{
    char chave = obter_chave(nome_faccao); // a, b, ..., z
    TUnidade *nova_unidade = tunidade_aloca(chave, tipo, x, y);
    unidade_insere(cabeca, nova_unidade);
    unidade_posiciona_mapa(mapa_unidade, nova_unidade);  
}

// Funcao principal de movimento
void unidade_move(TUnidade *unidade, int x, int y, char **mapa_unidade, char **mapa_oficial)
{
    unidade_retira_mapa(mapa_unidade, mapa_oficial, unidade);
    mapa_unidade[x][y] = unidade->chave;
}