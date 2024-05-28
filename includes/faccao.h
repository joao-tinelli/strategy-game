#ifndef FACCAO_H
#define FACCAO_H

typedef struct _faccao TFaccao;
typedef struct _cfaccao CFaccao;

TFaccao *Tfaccao_aloca(const char *nome, const int x, const int y);
CFaccao *Cfaccao_cria(void);
int Tfaccao_vazia(const CFaccao *cabeca);
void faccao_desaloca(CFaccao **cabeca);
void faccao_inserir(CFaccao *cabeca, const char *nome, const int x, const int y);
int faccao_existe(const CFaccao *cabeca, const char *nome);
void faccoes_converte_txt_lista(CFaccao *cabeca, const char *nome_arquivo);
void faccoes_display(const CFaccao *cabeca);
void faccoes_posicionar_mapa(const CFaccao *cabeca, char **mapa);
TFaccao *faccao_buscar(CFaccao *cabeca, char *nome);
void faccao_coleta(CFaccao *cabeca, const char identificador, const int tipo, const int qtd);

#endif