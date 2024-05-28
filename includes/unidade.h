#ifndef UNIDADE_H
#define UNIDADE_H

#include "mapa.h"

typedef struct _unidade TUnidade;
typedef struct _cunidade CUnidade;

TUnidade *tunidade_aloca(const char chave, const int id, const int tipo, const int x, const int y);
CUnidade *cunidade_cria(void);
void cunidade_desaloca(CUnidade **cabeca);

int unidade_vazia(const CUnidade *cabeca);
void unidade_insere(CUnidade *cabeca, TUnidade *novo);
void unidade_display(const CUnidade *cabeca);
TUnidade *unidade_buscar(CUnidade *cabeca, const int id);
void unidade_posiciona(CUnidade *cabeca, char *identificador, const int tipo, const int x, const int y);
void unidade_move(CUnidade *cabeca, char *identificador, const int tipo, const int novo_x, const int novo_y);

#endif

