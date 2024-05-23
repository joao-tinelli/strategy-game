#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "faccao.h"
#include "alianca.h"
#include "edificio.h"
#include "unidade.h"
#include "mapa.h"
#include "mensagens.h"

// Estrutura para representar uma facção
typedef struct _faccao{
    char nome[15];
    int pts_recurso, pts_poder;
    int x, y; // posicao da faccao
    struct _faccao *prox;
    CAlianca *proxalianca;
    CEdificio *proxedificio;
    CUnidade *proxunidade;
} TFaccao;

typedef struct _cfaccao{
    TFaccao *ini, *fim;
    int tam;
} CFaccao;

TFaccao *Tfaccao_aloca(const char *nome, const int x, const int y, const int pts_recurso, const int pts_poder)
{
    TFaccao *novo = (TFaccao*)malloc(sizeof(TFaccao));
    if(!novo){
        msg_erro("Falha ao criar a faccao.", "Tfaccao_aloca");
        return NULL;
    }
    strcpy(novo->nome, nome);
    novo->x = x;
    novo->y = y;
    novo->pts_recurso = pts_recurso;
    novo->pts_poder = pts_poder;
    novo->proxunidade = NULL;
    novo->proxedificio = NULL;
    novo->proxalianca = NULL;   
    return novo;
}

CFaccao *Cfaccao_cria(void)
{
    CFaccao *novo = (CFaccao*) malloc(sizeof(CFaccao)); 

    if(!novo){
        msg_erro("Falha ao criar a faccao.", "faccao_cria");
        return NULL;
    }

    novo->ini = novo->fim = NULL;
    novo->tam = 0;

    return novo;
}

int Tfaccao_vazia(const CFaccao *cabeca)
{
    return(cabeca == NULL || cabeca->tam == 0);
}

void faccao_inserir(CFaccao *cabeca, const char *nome, const int x, const int y, const int pts_recurso, const int pts_poder)
{
    TFaccao *novo = Tfaccao_aloca(nome, x, y, pts_recurso, pts_poder);
    if(!novo){
        msg_erro("Falha ao inserir faccao.", "faccao_inserir");
        return;
    }
    if (Tfaccao_vazia(cabeca)){
        cabeca->ini = cabeca->fim = novo;

    } else {
        novo->prox = cabeca->ini;
        cabeca->ini = novo;
    }
    cabeca->tam++;
}

int faccao_existe(const CFaccao *cabeca, const char *nome)
{
    if(Tfaccao_vazia(cabeca)) return 0;
    TFaccao *aux = cabeca->ini;
    while(aux){
        if(strcmp(aux->nome, nome) == 0){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void faccao_desaloca(CFaccao **cabeca)
{
    if (!*cabeca) return;
    /*
    desaloca_edificio(cabeca);
    desaloca_alianca(cabeca);
    */
   TFaccao *aux = (*cabeca)->ini, *temp;
   while(aux){
        temp = aux;
        aux = temp->prox;

        //cunidade_desaloca(&aux->proxunidade);

        free(temp);
   }

    free(*cabeca);
    *cabeca = NULL;
    return;
}

void faccoes_converte_txt_lista(CFaccao *cabeca, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo){
        msg_erro("Erro ao abrir arquivo.", "faccoes_converte_txt_lista");
        return;
    }

    TFaccao aux;

    while(!feof(arquivo))
    {
        fscanf(arquivo, "%s %d %d", aux.nome, &(aux.x), &(aux.y));
        faccao_inserir(cabeca, aux.nome, aux.x, aux.y, 0, 0);
    }
    fclose(arquivo);
    
}

void faccoes_display(const CFaccao *cabeca)
{
    if (Tfaccao_vazia(cabeca))
    {
        msg_erro("Faccao vazia.", "faccoes_display");
        return;
    }
    TFaccao *aux = cabeca->ini;
    while(aux){
        printf("Faccao '%s', posicao '%d,%d', pts_poder '%d', pts_recurso '%d\n", aux->nome, aux->x, aux->y, aux->pts_recurso, aux->pts_poder);
        aux = aux->prox;
    }
}

void faccoes_inicializar_mapa(const CFaccao *cabeca, int **mapa)
{
    if (Tfaccao_vazia(cabeca))
    {
        msg_erro("Faccao vazia.", "faccoes_inicializar_mapa");
        return;
    }
    TFaccao *aux = cabeca->ini;
    int i, j;
    char c = 'A';
    while(aux){
        i = aux->x, j = aux->y;
        mapa[i][j] = c++;
        aux = aux->prox;
    }
}



