#ifndef UNIDADE_H
#define UNIDADE_H

typedef struct _unidade TUnidade;
typedef struct _cunidade CUnidade;

TUnidade *tunidade_aloca(const int x, const int y, const int tipo);
CUnidade *cunidade_cria(void);
void cunidade_desaloca(CUnidade **cabeca);

int unidade_vazia(const CUnidade *cabeca);
void unidade_insere(CUnidade *cabeca, const int x, const int y, const int tipo);
void unidade_display(const CUnidade *cabeca);

void unidade_remove(CUnidade *cabeca, const int tipo, const int x, const int y);

#endif

