#ifndef EDIFICIO_H
#define EDIFICIO_H

#include "mapa.h"

typedef struct edificio TEdificio;
typedef struct _cedificio CEdificio;

TEdificio *tedificio_aloca(const char chave, const int tipo, const int qtd, const int x, const int y);
CEdificio *cedificio_cria(void);
int edificio_vazio(const CEdificio *cabeca);
int edificio_existente(const CEdificio *cabeca, const char chave);
void edificio_insere(CEdificio *cabeca, TEdificio *novo);
void edificio_display(const CEdificio *cabeca);
void edificio_posiciona_mapa(char **mapa_edificio, TEdificio *novo);
void edificio_retira_mapa(char **mapa, char **mapa_oficial, CEdificio *cabeca, char chave);
void cedificio_desaloca(CEdificio **cabeca);
void edificio_constroi(char *nome_faccao, CEdificio *cabeca, int qtd, int tipo, int x, int y, char **mapa_edificio);
#endif

