#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mensagens.h"

typedef struct _Dimensao
{
    int n, m;
} Dimensao;

Dimensao *mapa_le_dimensao(const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    Dimensao *d = (Dimensao*)malloc(sizeof(Dimensao));

    if (!arquivo){
        msg_erro("Nao foi possível abrir o arquivo.", "mapa_le_dimensao");
        free(d);  // Libera a memória alocada
        return NULL;
    }

    // Lê as dimensoes do mapa
    int n, m;
    if (fscanf(arquivo, "%d %d", &n, &m) != 2){
        msg_erro("Erro ao ler a dimensao do mapa", "mapa_inicializa");
        fclose(arquivo);
        free(d);  // Libera a memória alocada
        return NULL;
    }
    fclose(arquivo);
    d->n = n;
    d->m = m;
    return d;
}

int **mapa_aloca(Dimensao *d)
{
    int **mapa = (int **)malloc(d->n * sizeof(int*));
    if (mapa == NULL){
        msg_erro("Erro na alocação de memoria para linhas", "mapa_aloca");
        return NULL;
    }
    // Aloca memória para cada linha
    for (int i = 0; i < d->n; i++) {
        mapa[i] = (int*)malloc(d->m * sizeof(int));
        if (mapa[i] == NULL){
            msg_erro("Erro na alocação de memoria para coluna", "mapa_aloca");
            // Libera todas as linhas já alocadas
            for (int j = 0; j < i; j++) {
                free(mapa[j]);
            }
            free(mapa);
            return NULL;
        }
    }
    return mapa;
}

void mapa_gera(int **mapa, Dimensao *d)
{
    srand(time(NULL));
   
    for (int i = 0; i < d->n; i++){
        for (int j = 0; j < d->m; j++){
            int tipo = 1 + (rand() % 3);
            mapa[i][j] = tipo;
        }
    }
}

// Função para verificar se uma matriz está vazia
int mapa_vazio(int **matriz, int linhas, int colunas)
{
    if (matriz == NULL) {
        return 1; // Ponteiro da matriz é NULL
    }
    if (linhas == 0 || colunas == 0) {
        return 1; // Número de linhas ou colunas é zero
    }
    for (int i = 0; i < linhas; i++) {
        if (matriz[i] == NULL) {
            return 1; // Linha da matriz é NULL
        }
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] != 0) {
                return 0; // Encontrou um elemento diferente de zero
            }
        }
    }
    return 1; // Todos os elementos são zero
}

void mapa_display(int **mapa, Dimensao *d)
{
    if(mapa_vazio(mapa, d->n, d->m) == 1)
    {
        msg_erro("Mapa vazio", "mapa_display");
        return;
    }

    for (int i = 0; i < d->n; i++){
        for (int j = 0; j < d->m; j++){
            switch(mapa[i][j]){
                case 1:
                    printf("P ");
                    break;
                case 2:
                    printf("F ");
                    break;
                case 3:
                    printf("M ");
                    break;
            }
        }
        printf("\n");
    }
}

void desaloca_mapa(int ***mapa, Dimensao *d)
{
    for (int i = 0; i < d->n; i++)
        free((*mapa)[i]);
    free(*mapa);
    *mapa = NULL;
}

void desaloca_dimensao(Dimensao **d)
{
    free(*d);
    *d = NULL;
}
