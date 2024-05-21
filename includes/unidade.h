#ifndef UNIDADE_H
#define UNIDADE_H

typedef struct _unidade TUnidade;
typedef struct _cunidade CUnidade;

TUnidade *tunidade_aloca(const int x, const int y, const int tipo);
CUnidade *cunidade_cria(void);
void cunidade_desaloca(CUnidade **cabeca);

int cunidade_vazia(const CUnidade *cabeca);
void cunidade_insere(CUnidade *cabeca, const int x, const int y, const int tipo);
void cunidade_display(const CUnidade *cabeca);

#endif

