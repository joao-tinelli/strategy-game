#ifndef FACCAO_H
#define FACCAO_H

typedef struct _faccao TFaccao;
typedef struct _cfaccao CFaccao;

TFaccao *Tfaccao_aloca(const char *nome, const int x, const int y, const int pts_recurso, const int pts_poder);
CFaccao *Cfaccao_cria(void);
int Tfaccao_vazia(const CFaccao *cabeca);
void faccao_desaloca(CFaccao **cabeca);
void faccao_inserir(CFaccao *cabeca, const char *nome, const int x, const int y, const int pts_recurso, const int pts_poder);
int faccao_existe(const CFaccao *cabeca, const char *nome);
void faccoes_converte_txt_lista(CFaccao *cabeca, const char *nome_arquivo);
void faccoes_display(const CFaccao *cabeca);
void faccoes_inicializar_mapa(const CFaccao *cabeca, char **mapa);

#endif