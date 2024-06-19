#include "libraries.h"
// Estrutura para representar um edifício
typedef struct building
{
    char key;
    int x, y;
    int type, amount;
    struct building *next;
} TBuilding;

typedef struct _hbuilding
{
    TBuilding *beg, *end;
    int sz;
} Hbuilding;

TBuilding *tbuilding_allocates(const char key, const int amount, const int type, const int x, const int y)
{
    TBuilding *new = (TBuilding*)malloc(sizeof(TBuilding));
    if(!new)
    {
        msg_erro("Failed to create building.", "building_allocates");
        return NULL;
    }
    new->key = key;
    new->type = type;
    new->amount = amount;
    new->x = x; 
    new->y = y;    
    new->next = NULL;
    return new;
}

Hbuilding *hbuilding_creates(void)
{
    Hbuilding *new = (Hbuilding*)malloc(sizeof(Hbuilding));

    if(!new)
    {
        msg_erro("Failed to create building's list.", "hbuilding_creates");
        return NULL;
    }

    new->beg = new->end = NULL;
    new->sz = 0;

    return new;
}

void hbuilding_deallocates(Hbuilding **head) 
{
    assert(head);
    if (*head == NULL) return;

    Hbuilding *C = *head;
    TBuilding *aux = C->beg, *temp = NULL;
    while(aux)
    {
        temp = aux;
        aux = aux->next;
        free(temp);
    }

    free(C);
    *head = NULL;
}

int is_hbuilding_empty(const Hbuilding *head) 
{
    return(head == NULL || head->sz == 0);
}

void building_insert(Hbuilding *head, TBuilding *new)
{   
    if (is_hbuilding_empty(head))
    {
        head->beg = head->end = new;
    } else {
        new->next = head->beg;
        head->beg = new;
    }
    head->sz++;
}

void building_makes(Hbuilding *head, char *identifier, int amount, int type, int x, int y)
{
    char key = tolower(identifier[1]);
    TBuilding *new_building = tbuilding_allocates(key, amount, type, x, y);    
    building_insert(head, new_building);  
}

void building_merge(Hbuilding *head_1, Hbuilding *head_2) 
{
    TBuilding *aux_2 = head_2->beg, *temp = NULL;

    while(aux_2 != NULL)
    {
        temp = aux_2;
        aux_2 = aux_2->next;
        building_insert(head_1, temp);
    }
}