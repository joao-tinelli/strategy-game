#include "bibliotecas.h"
// Estrutura para representar uma unidade
typedef struct _unidade
{
    char chave[3]; 
    int tipo; // 1-soldado, 2-explorador
    int x, y;
    struct _unidade *prox;
} TUnidade;

typedef struct _cunidade
{
    TUnidade *ini, *fim;
    int tam;
} CUnidade;

TUnidade *tunidade_aloca(const char *chave, const int tipo, const int x, const int y)
{
    TUnidade *novo = (TUnidade*)malloc(sizeof(TUnidade));
    if(!novo){
        msg_erro("Falha ao alocar memoria.\n", "tunidade_aloca");
        return NULL;
    }

    strcpy(novo->chave, chave);
    novo->tipo = tipo;
    novo->x = x;  
    novo->y = y;
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

int unidade_existente(const CUnidade *cabeca, const char *chave)
{
    if(unidade_vazia(cabeca)) return 0;
    TUnidade *aux = cabeca->ini;
    while(aux){
        if(strcmp(aux->chave, chave) == 0){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void unidade_insere(CUnidade *cabeca, const char *chave, const int tipo, const int x, const int y)
{
    if(unidade_existente(cabeca, chave))
    {
        msg_erro("Unidade ja inserida", "unidade_insere");
        return;
    }
    
    TUnidade *novo = tunidade_aloca(chave, tipo, x, y);
    if(!novo)
    {
        msg_erro("Falha ao alocar unidade.", "tunidade_aloca");
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
    while(aux)
    {
        printf("chave: %s. \npos: (%d, %d). Tipo: %d.\n",aux->chave, aux->x, aux->y, aux->tipo);
        aux = aux->prox;
    }
}

void unidade_posiciona_mapa(char **mapa, CUnidade *cabeca, char *chave, const int tipo, const int x, const int y)
{
       
}

void unidade_move(char **mapa, TUnidade *unidade, const char *chave)

{

}

void unidade_retira_mapa(char **mapa, char **mapa_oficial, TUnidade *unidade, const char *chave, const int tipo, const int x, const int y)
{
     
}