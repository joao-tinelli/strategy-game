#ifndef UNIDADE_H
#define UNIDADE_H

#include "faccao.h"
#include "mapa.h"

typedef struct _unidade TUnidade;
typedef struct _cunidade CUnidade;

TUnidade *tunidade_aloca(const char chave, const int tipo, const int x, const int y);
CUnidade *cunidade_cria(void);
void cunidade_desaloca(CUnidade **cabeca);

int unidade_vazia(const CUnidade *cabeca);
void unidade_insere(CUnidade *cabeca, const char chave, const int tipo, const int x, const int y);
void unidade_display(const CUnidade *cabeca);
int unidade_existente(const CUnidade *cabeca, const char chave);

void unidade_posiciona_mapa(char **mapa, CUnidade *cabeca, char chave);
//void unidade_remove(CUnidade *cabeca, const int tipo, const int x, const int y);

#endif

