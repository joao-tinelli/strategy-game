#include "bibliotecas.h"

// Estrutura para representar uma alinça
typedef struct _alianca{
    char nome[15];
    struct _alianca *prox;
} TAlianca;

typedef struct _calianca{
    TAlianca *ini, *fim;
    int tam;
} CAlianca;

TAlianca *talianca_aloca(const char *nome)
{
    TAlianca *novo = (TAlianca*)malloc(sizeof(TAlianca));
    if(!novo)
    {
        msg_erro("Falha ao alocar memoria.", "talianca_aloca");
        return NULL;
    }
    strcpy(novo->nome, nome);
    novo->prox = NULL;    
    return novo;
}

CAlianca *calianca_cria(void)
{
    CAlianca *novo = (CAlianca*) malloc(sizeof(CAlianca));
    if(!novo){
        msg_erro("Falha ao alocar memoria.", "calianca_cria");
        return NULL;
    }

    novo->ini = novo->fim = NULL;
    novo->tam = 0;

    return novo;
}

void calianca_desaloca(CAlianca **cabeca)
{
    assert(cabeca);
    if (*cabeca == NULL) return;

    CAlianca *C = *cabeca;
    TAlianca *aux = C->ini, *temp = NULL;
    while(aux){
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    free(C);
    *cabeca = NULL;
}

int calianca_vazia(const CAlianca *cabeca)
{
    return(cabeca->tam == 0);
}

void calianca_insere(CAlianca *cabeca, const char *nome)
{
    TAlianca *novo = talianca_aloca(nome);
    if(!novo)
    {
        msg_erro("Falha ao inserir uma alianca.", "calianca_insere");
        return;
    }
    if (calianca_vazia(cabeca)){
        cabeca->ini = cabeca->fim = novo;

    } else {
        novo->prox = cabeca->ini;
        cabeca->ini = novo;
    }
    cabeca->tam++;
}

void alianca_aliados(const CAlianca *cabeca)
{
    TAlianca *aux = cabeca->ini;
    while(aux)
    {
        printf(" %s ", aux->nome);
        aux = aux->prox;
    }
    puts("");
}



