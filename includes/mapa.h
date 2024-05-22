#ifndef MAPA_H
#define MAPA_H

typedef struct _Dimensao Dimensao;
Dimensao *mapa_le_dimensao(const char *nome_arquivo);
int **mapa_aloca(Dimensao *d);
void mapa_gera(int **mapa, Dimensao *d);
void mapa_display(int **mapa, Dimensao *d);
void desaloca_mapa(int ***mapa, Dimensao *d);
void desaloca_dimensao(Dimensao **d);
int mapa_vazio(int **matriz, int linhas, int colunas);

#endif 