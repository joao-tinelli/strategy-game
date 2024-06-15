#ifndef MAPA_H
#define MAPA_H

/**
 * @brief Dimensão do mapa;
 * @typedef Dimensao;
*/
typedef struct _Dimensao Dimensao;

/**
 * @brief Lê dimensao do mapa;
 * @param nome_arquivo;
 * @return Dimensao;
*/
Dimensao *mapa_le_dimensao(const char *nome_arquivo);

/**
 * @brief Seta linha e coluna na variável e retorna;
 * @param n, m;
 * @return Dimensao;
*/
Dimensao *seta_dimensao(const int n, const int m);

/**
 * @brief Faz alocação dinâmica do mapa;
 * @param d;
 * @return char;
*/
char **mapa_aloca(Dimensao *d);

/**
 * @brief Gera o mapa com os tipos de terreno aleatoriamente;
 * @param mapa, d;
 * @return void;
*/
void mapa_gera(char **mapa, Dimensao *d);

/**
 * @brief Desaloca mapa;
 * @param mapa, d;
 * @return void;
*/
void desaloca_mapa(char ***mapa, Dimensao *d);

/**
 * @brief Desaloca a struct dimensão;
 * @param d;
 * @return void;
*/
void desaloca_dimensao(Dimensao **d);

/**
 * @brief Verifica se o mapa está vazio;
 * @param mapa, dimensao;
 * @return (0 ou 1);
*/
int mapa_vazio(char **mapa, Dimensao *dimensao);

/**
 * @brief Imprime o mapa;
 * @param mapa, d;
 * @return void;
*/
void mapa_display(char **mapa, Dimensao *d);

/**
 * @brief Replica o mapa em outra matriz;
 * @param mapa_oficial, mapa_copia, d;
 * @return void;
*/
void mapa_replica(char **mapa_oficial, char **mapa_copia, Dimensao *d);

/**
 * @brief Constroi os mapas;
 * @param mapa_oficial, mapa_faccao, mapa_edificio, mapa_unidade, dimensao;
 * @return void;
*/
void construir_mapas(char ***mapa_oficial, char ***mapa_faccao, char ***mapa_edificio, char ***mapa_unidade, Dimensao *dimensao);

/**
 * @brief Verifica o tipo de terreno do mapa;
 * @param mapa, dimensao, x, y;
 * @return char;
*/
char mapa_tipo_terreno(char **mapa, Dimensao *dimensao, const int x, const int y);


#endif 