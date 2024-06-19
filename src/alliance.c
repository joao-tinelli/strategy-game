#include "libraries.h"

// Estrutura para representar uma alinça
typedef struct _alliance{
    char nome[15];
    struct _alliance *prox;
} TAlliance;

typedef struct _halliance{
    TAlliance *beg, *end;
    int sz;
} HAlliance;

TAlliance *alliance_allocates(const char *name)
{
    TAlliance *new = (TAlliance*)malloc(sizeof(TAlliance));
    if(!new)
    {
        msg_erro("Failed to allocate memory.", "alliance_allocates");
        return NULL;
    }
    strcpy(new->nome, name);
    new->prox = NULL;    
    return new;
}

HAlliance *halliance_creates(void)
{
    HAlliance *new = (HAlliance*) malloc(sizeof(HAlliance));
    if(!new){
        msg_erro("Failed to allocate memory.", "halliance_creates");
        return NULL;
    }

    new->beg = new->end = NULL;
    new->sz = 0;

    return new;
}

void halliance_deallocates(HAlliance **head)
{
    assert(head);
    if (*head == NULL) return;

    HAlliance *C = *head;
    TAlliance *aux = C->beg, *temp = NULL;
    while(aux){
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    free(C);
    *head = NULL;
}

int is_halliance_empty(const HAlliance *head)
{
    return(head->sz == 0);
}

void halliance_insert(HAlliance *head, const char *name)
{
    TAlliance *new = alliance_allocates(name);
    if(!new)
    {
        msg_erro("Failed to insert an alliance.", "halliance_insert");
        return;
    }
    if (is_halliance_empty(head)){
        head->beg = head->end = new;

    } else {
        new->prox = head->beg;
        head->beg = new;
    }
    head->sz++;
}

void alliance_allies(const HAlliance *head)
{
    TAlliance *aux = head->beg;
    while(aux)
    {
        printf(" %s ", aux->nome);
        aux = aux->prox;
    }
    puts("");
}



