#ifndef FACCAO_H
#define FACCAO_H

#include "mapa.h"

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
TFaccao *Tfaccao_aloca(const char *nome, const int x, const int y);
/**
 * @brief Cria a cabeça da lista;
 * @param void;
 * @return CFaccao;
*/
CFaccao *Cfaccao_cria(void);
/**
 * @brief Desaloca a cabeça da lista;
 * @param cabeca;
 * @return CUnidade;
*/
void cfaccao_desaloca(CFaccao **cabeca);
/**
 * @brief Desaloca toda lista;
 * @param cabeca, nome_faccao;
 * @return TFaccao;
*/
void tfaccao_desaloca(CFaccao *cabeca, char *nome_faccao);
/**
 * @brief Verifica se a facção está vazia;
 * @param cabeca;
 * @return (0 ou 1);
*/
int Cfaccao_vazia(const CFaccao *cabeca);
/**
 * @brief Verifica se a facção existe;
 * @param cabeca, nome;
 * @return (0 ou 1);
*/
int faccao_existe(const CFaccao *cabeca, const char *nome);
/**
 * @brief Verifica se a facção existe;
 * @param cabeca, x, y;
 * @return (0 ou 1);
*/
int faccao_verifica_posicao(CFaccao *cabeca, const int x, const int y);
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
 * @brief Verifica se a facção existe;
 * @param cabeca, nome;
 * @return (0 ou 1);
*/
void faccoes_display(const CFaccao *cabeca);
/**
 * @brief Posiciona as facções no mapa;
 * @param cabeca, mapa;
 * @return void;
*/
void faccoes_posicionar_mapa(const CFaccao *cabeca, char **mapa);
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
 * @param cabeca, f1, f2;
 * @return void;
*/
void faccao_combate(CFaccao *cabeca, char *f1, char *f2);
/**
 * @brief Função para testar as funcionalidades das facções;
 * @param cabeca;
 * @return void;
*/
void faccao_teste(CFaccao *cabeca);
/**
 * @brief Realiaza a aliança e junta os recursos de cada facção;
 * @param cabeca, f1, f2;
 * @return void;
*/
void faccao_alianca(CFaccao *cabeca, char *f1, char *f2);
/**
 * @brief Atualiza o mapa das faccoes;
 * @param cabeca, mapa_faccao, dimensao;
 * @return void;
*/
void mapa_faccao_atualiza(CFaccao *cabeca, char **mapa_faccao, Dimensao *dimensao);
void faccao_unidade_inserir(TFaccao *faccao, const char chave, const char id, const int tipo, const int x, const int y);
void faccao_mapa_unidade_atualiza(CFaccao *cabeca, char **mapa_oficial, char **mapa_unidade, Dimensao *dimensao);
void faccao_unidade_move(CFaccao *cabeca, char **mapa_unidade, Dimensao *dimensao, char *nome, const int tipo, const int x, const int y);
void faccao_edificio_constroi(CFaccao *cabeca, char **mapa_edificio, char *identificador, int qtd, int tipo, int x, int y);

#endif