#ifndef EDIFICIO_H
#define EDIFICIO_H

#include "mapa.h"

/**
 * @brief Nó da lista;
 * @typedef TEdificio;
*/
typedef struct edificio TEdificio;

/**
 * @brief Cabeça da lista;
 * @typedef CEdificio;
*/
typedef struct _cedificio CEdificio;

/**
 * @brief Aloca uma struct do tipo TEdificio;
 * @param chave, qtd, tipo, x, y;
 * @return TEdificio;
*/
TEdificio *tedificio_aloca(const char chave, const int qtd, const int tipo, const int x, const int y);

/**
 * @brief Aloca uma struct do tipo CFaccao;
 * @param void;
 * @return CEdificio;
*/
CEdificio *cedificio_cria(void);

/**
 * @brief Desaloca todo os edificios;
 * @param cabeca;
 * @return void;
*/
void cedificio_desaloca(CEdificio **cabeca);

/**
 * @brief Verifica se a lista está vazia;
 * @param cabeca;
 * @return (0 ou 1);
*/
int cedificio_vazio(const CEdificio *cabeca);

/**
 * @brief Insere um edificio na lista;
 * @param cabeca, novo;
 * @return void;
*/
void edificio_insere(CEdificio *cabeca, TEdificio *novo);

/**
 * @brief Utilizada quando um novo edificio for construído;
 * @param cabeca, identificador, qtd, tipo, x, y;
 * @return void;
*/
void edificio_constroi(CEdificio *cabeca, char *identificador, int qtd, int tipo, int x, int y);

/**
 * @brief Junta duas listas do tipo CEdificio;
 * @param cabeca_1, cabeca_2;
 * @return void;
*/
void edificio_merge(CEdificio *cabeca_1, CEdificio *cabeca_2);

#endif

