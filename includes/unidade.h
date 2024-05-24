#ifndef UNIDADE_H
#define UNIDADE_H

#include "mapa.h"

typedef struct _unidade TUnidade;
typedef struct _cunidade CUnidade;

TUnidade *tunidade_aloca(const char chave, const int tipo, const int x, const int y);
CUnidade *cunidade_cria(void);
int unidade_vazia(const CUnidade *cabeca);
int unidade_existente(const CUnidade *cabeca, const char chave);
void unidade_insere(CUnidade *cabeca, const char chave, const int tipo, const int x, const int y);
void unidade_display(const CUnidade *cabeca);
void unidade_posiciona_mapa(char **mapa, CUnidade *cabeca, char chave);
void unidade_retira_mapa(char **mapa, char **mapa_oficial, CUnidade *cabeca, char chave);
void cunidade_desaloca(CUnidade **cabeca);

#endif

