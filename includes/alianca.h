#ifndef ALIANCA_H
#define ALIANCA_H

typedef struct _alianca TAlianca;
typedef struct _calianca CAlianca;

TAlianca *talianca_aloca(const char *nome);
CAlianca *calianca_cria(void);
void calianca_desaloca(CAlianca **cabeca);

int calianca_vazia(const CAlianca *cabeca);
void calianca_insere(CAlianca *cabeca, const char *nome);
void calianca_display(const CAlianca *cabeca);

#endif 

