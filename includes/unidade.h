#ifndef UNIDADE_H
#define UNIDADE_H

#include "mapa.h"

typedef struct _unidade TUnidade;
typedef struct _cunidade CUnidade;

TUnidade *tunidade_aloca(const char chave, const int tipo, const int x, const int y);
CUnidade *cunidade_cria(void);
void cunidade_desaloca(CUnidade **cabeca);

int unidade_vazia(const CUnidade *cabeca);
void unidade_insere(CUnidade *cabeca, TUnidade *novo);
void unidade_display(const CUnidade *cabeca);
void unidade_posiciona_mapa(char **mapa_unidade, TUnidade *novo);
void unidade_retira_mapa(char **mapa_unidade, char **mapa_oficial, TUnidade *unidade);
void unidade_posiciona(char *nome_faccao, CUnidade *cabeca, int tipo, int x, int y, char **mapa_unidade);
void unidade_move(TUnidade *unidade, int x, int y, char **mapa_unidade, char **mapa_oficial);

#endif

