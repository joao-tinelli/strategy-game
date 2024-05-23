#ifndef UNIDADE_H
#define UNIDADE_H

#include "faccao.h"

typedef struct _unidade TUnidade;
typedef struct _cunidade CUnidade;

TUnidade *tunidade_aloca(const char *nome, const int tipo, const int x, const int y);
CUnidade *cunidade_cria(void);
void cunidade_desaloca(CUnidade **cabeca);

int unidade_vazia(const CUnidade *cabeca);
void unidade_insere(CUnidade *cabeca, const char *nome, const int tipo, const int x, const int y);
void unidade_display(const CUnidade *cabeca);

//void unidade_posiciona(TFaccao *faccao, const char *nome, const int tipo, const int x, const int y);
//void unidade_remove(CUnidade *cabeca, const int tipo, const int x, const int y);

#endif

