#include "bibliotecas.h"
// Estrutura para representar uma edifício
typedef struct edificio
{
    char chave;
    int x, y;
    int tipo, qtd; // 1-edifício de recursos, 2-campo de treinamento 3-laboratório de pesquisa
    struct edificio *prox;
} TEdificio;

typedef struct _cedificio
{
    TEdificio *ini, *fim;
    int tam;
} CEdificio;

TEdificio *tedificio_aloca(const char chave, const int qtd, const int tipo, const int x, const int y)
{
    TEdificio *novo = (TEdificio*)malloc(sizeof(TEdificio));
    if(!novo)
    {
        msg_erro("Falha ao criar edificio.", "Tedificio_aloca");
        return NULL;
    }
    novo->chave = chave;
    novo->tipo = tipo;
    novo->qtd = qtd;
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

void cedificio_desaloca(CEdificio **cabeca) 
{
    assert(cabeca);
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

int cedificio_vazio(const CEdificio *cabeca) 
{
    return(cabeca == NULL || cabeca->tam == 0);
}

void edificio_insere(CEdificio *cabeca, TEdificio *novo)
{   
    if (cedificio_vazio(cabeca))
    {
        cabeca->ini = cabeca->fim = novo;
    } else {
        novo->prox = cabeca->ini;
        cabeca->ini = novo;
    }
    cabeca->tam++;
}

void edificio_display(const CEdificio *cabeca)
{
    if (cedificio_vazio(cabeca))
    {
        msg_erro("Edificio vazio.", "edificio_display");
        return;
    }
    TEdificio *aux = cabeca->ini;
    while(aux)
    {
        printf("CHAVE: %c\nQTD: %d\nPOS: (%d, %d) \nTIPO: %d\n\n", aux->chave, aux->qtd, aux->x, aux->y, aux->tipo);
        aux = aux->prox;
    }
}

void edificio_constroi(CEdificio *cabeca, char *identificador, int qtd, int tipo, int x, int y)
{
    char chave = tolower(identificador[1]); // a, b, ..., z
    TEdificio *novo_edificio = tedificio_aloca(chave, qtd, tipo, x, y);    
    edificio_insere(cabeca, novo_edificio);  
}

void edificio_merge(CEdificio *cabeca_1, CEdificio *cabeca_2) 
{
    TEdificio *aux_2 = cabeca_2->ini, *temp = NULL;

    while(aux_2 != NULL)
    {
        temp = aux_2;
        aux_2 = aux_2->prox;
        edificio_insere(cabeca_1, temp);
    }
}