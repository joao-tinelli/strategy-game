#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alianca.h"

// Estrutura para representar uma alinça
typedef struct alianca{
    char nome[15];
    struct alianca *prox;
} TAlianca;

typedef struct{
    TAlianca *ini, *fim;
    int tam;
} CAlianca;

TAlianca *alianca_aloca(char *nome)
{
    TAlianca *novo = (TAlianca*)malloc(sizeof(TAlianca));
    if(!novo){
        printf("Falha ao alocar memoria.\n");
        return NULL;
    }
    strcpy(novo->nome, nome);
    novo->prox = NULL;    
    return novo;
}


