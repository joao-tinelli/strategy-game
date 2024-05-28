#ifndef EDIFICIO_H
#define EDIFICIO_H

#include "mapa.h"

typedef struct edificio TEdificio;
typedef struct _cedificio CEdificio;

TEdificio *tedificio_aloca(const char chave, const int tipo, const int qtd, const int x, const int y);
CEdificio *cedificio_cria(void);
int edificio_vazio(const CEdificio *cabeca);
void edificio_insere(CEdificio *cabeca, TEdificio *novo);
void edificio_display(const CEdificio *cabeca);
void cedificio_desaloca(CEdificio **cabeca);
void edificio_constroi(CEdificio *cabeca, char *identificador, int qtd, int tipo, int x, int y);

#endif

