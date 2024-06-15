#ifndef UNIDADE_H
#define UNIDADE_H

#include "mapa.h"

/**
 * @brief Nó da lista;
 * @typedef TUnidade;
*/
typedef struct _unidade TUnidade;
/**
 * @brief Cabeça da lista;
 * @typedef CUnidade;
*/
typedef struct _cunidade CUnidade;

/**
 * @brief Aloca uma struct do tipo TUnidade;
 * @param chave, id, tipo, x, y;
 * @return TUnidade;
*/
TUnidade *tunidade_aloca(const char chave, const int id, const int tipo, const int x, const int y);
/**
 * @brief Cria a cabeça da lista;
 * @param void;
 * @return CUnidade;
*/
CUnidade *cunidade_cria(void);
/**
 * @brief Desaloca toda lista, incluindo a cabeça;
 * @param cabeca;
 * @return void;
*/
void cunidade_desaloca(CUnidade **cabeca);
void tunidade_desaloca(CUnidade *cabeca, const int id);

/**
 * @brief Verifica se a lista está vazia;
 * @param cabeca;
 * @return (0 ou 1);
*/
int unidade_vazia(const CUnidade *cabeca);
/**
 * @brief Insere uma nova unidade na lista;
 * @param cabeca, chave, id, tipo, x, y;
 * @return void;
*/
void unidade_inserir(CUnidade *cabeca, const char chave, const char id, const int tipo, const int x, const int y);
/**
 * @brief Mostra o conteúdo da lista, caso não esteja vazia;
 * @param cabeca;
 * @return void;
*/
void unidade_display(const CUnidade *cabeca);
/**
 * @brief Busca uma unidade na lista;
 * @param cabeca, id;
 * @return TUnidade;
*/
TUnidade *unidade_buscar(CUnidade *cabeca, const int id);
/**
 * @brief Função para mover uma unidade;
 * @param cabeca, nome, tipo, novo_x, novo_y;
 * @return void;
*/
void unidade_move(CUnidade *cabeca, char *nome, const int tipo, const int novo_x, const int novo_y);
/**
 * @brief Função para juntar duas unidades;
 * @param cabeca_1, cabeca_2;
 * @return void;
*/
void unidade_merge(CUnidade *cabeca_1, CUnidade *cabeca_2);
void mapa_unidade_atualiza(CUnidade *cabeca, char **mapa_unidade);

#endif

