#ifndef FACCAO_H
#define FACCAO_H

#include "mapa.h"
#include "alliance.h"

/**
 * @brief Nó da lista;
 * @typedef TFaccao;
*/
typedef struct _faccao TFaccao;

/**
 * @brief Cabeça da lista;
 * @typedef CFaccao;
*/
typedef struct _cfaccao CFaccao;

/**
 * @brief Aloca uma struct do tipo TFaccao;
 * @param nome, x, y;
 * @return TFaccao;
*/
TFaccao *tfaccao_aloca(const char *nome, const int x, const int y);

/**
 * @brief Cria a cabeça da lista;
 * @param void;
 * @return CFaccao;
*/
CFaccao *cfaccao_cria(void);

/**
 * @brief Desaloca a cabeça da lista;
 * @param cabeca;
 * @return void;
*/
void cfaccao_desaloca(CFaccao **cabeca);

/**
 * @brief Desaloca toda lista;
 * @param cabeca, nome_faccao;
 * @return void;
*/
void tfaccao_desaloca(CFaccao *cabeca, char *nome_faccao);

/**
 * @brief Verifica se a facção está vazia;
 * @param cabeca;
 * @return (0 ou 1);
*/
int cfaccao_vazia(const CFaccao *cabeca);

/**
 * @brief Verifica se a facção existe;
 * @param cabeca, nome;
 * @return (0 ou 1);
*/
int faccao_existe(const CFaccao *cabeca, const char *nome);

/**
 * @brief Insere uma nova facção na lista;
 * @param cabeca, nome, x, y;
 * @return void;
*/
void faccao_inserir(CFaccao *cabeca, const char *nome, const int x, const int y);

/**
 * @brief Lê arquivo txt e converte em lista;
 * @param cabeca, nome_arquivo;
 * @return void;
*/
void faccoes_converte_txt_lista(CFaccao *cabeca, const char *nome_arquivo);

/**
 * @brief Busca alguma facção na lista;
 * @param cabeca, nome;
 * @return TFaccao;
*/
TFaccao *faccao_buscar(CFaccao *cabeca, char *nome);

/**
 * @brief Aumenta a quantidade de recursos ao serem coletados;
 * @param cabeca, chave, qtd;
 * @return void;
*/
void faccao_coleta(CFaccao *cabeca, const char chave, const int qtd);

/**
 * @brief Realiza o combate entre duas facções;
 * @param cabeca, f1, f2, x, y;
 * @return void;
*/
void faccao_ataca(CFaccao *cabeca, char *f1, char *f2, const int x, const int y);

/**
 * @brief Realiza a aliança entre duas faccções;
 * @param cabeca, f1, f2;
 * @return void;
*/
void faccao_alianca(CFaccao *cabeca, char *f1, char *f2);

/**
 * @brief Adiciona pontos de poder a facção;
 * @param cabeca, nome_faccao, qtd_pts_poder;
 * @return void;
*/
void faccao_ganha_pontos_poder(CFaccao *cabeca,  char *nome_faccao, const int qtd_pts_poder);

/**
 * @brief Atualiza o mapa das faccoes;
 * @param cabeca, mapa_faccao, dimensao;
 * @return void;
*/
void faccao_mapa_atualiza(CFaccao *cabeca, char **mapa_faccao, Dimensao *dimensao);

/**
 * @brief Insere unidades na facção;
 * @param faccao, chave, id, tipo, x, y;
 * @return void;
*/
void faccao_unidade_inserir(TFaccao *faccao, const char chave, const char id, const int tipo, const int x, const int y);

/**
 * @brief Atualiza o mapa de unidades;
 * @param cabeca, mapa_oficial, mapa_unidade, dimensao;
 * @return void;
*/
void faccao_mapa_unidade_atualiza(CFaccao *cabeca, char **mapa_oficial, char **mapa_unidade, Dimensao *dimensao);

/**
 * @brief Move as unidades no mapa;
 * @param cabeca, mapa_unidade, dimensao, nome, tipo, x, y;
 * @return void;
*/
void faccao_unidade_move(CFaccao *cabeca, char **mapa_unidade, Dimensao *dimensao, char *nome, const int tipo, const int x, const int y);

/**
 * @brief Constroi um edificio;
 * @param cabeca, mapa_edificio, identificador, qtd, tipo, x, y;
 * @return void;
*/
void faccao_edificio_constroi(CFaccao *cabeca, char **mapa_edificio, char *identificador, int qtd, int tipo, int x, int y);

/**
 * @brief Após o combate desaloca a unidade defensora (quem ataca sempre vence);
 * @param cabeca, mapa_unidade, unidade_defensora;
 * @return void;
*/
void faccao_unidade_combate(CFaccao *cabeca, char * unidade_defensora);

/**
 * @brief Retorna a cabeça da lista aliança;
 * @param cabeca, mapa_unidade, indentificador;
 * @return CAlianca;
*/
HAlliance *faccao_retorna_calianca(CFaccao *cabeca, char *identificador);

/**
 * @brief Verifica qual facção foi vencedora no combate;
 * @param cabeca;
 * @return void;
*/
void faccao_verifica_vencedor(CFaccao *cabeca);

#endif