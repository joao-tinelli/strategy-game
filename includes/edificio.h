#ifndef EDIFICIO_H
#define EDIFICIO_H

typedef struct edificio TEdificio;
typedef struct _cedificio CEdificio;

TEdificio *Tedificio_aloca(const int x, const int y, const int tipo);
CEdificio *CEdificio_cria(void);
int Tedificio_vazio(const CEdificio *cabeca);
void edificio_inserir(CEdificio *cabeca, const int x, const int y, const int tipo);
void edificio_desaloca(CEdificio **cabeca);
void edificio_display(const CEdificio *cabeca);

#endif

