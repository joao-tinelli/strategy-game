#ifndef ALIANCA_H
#define ALIANCA_H

/**
 * @brief Nó da lista;
 * @typedef TAlianca;
*/
typedef struct _alianca TAlianca;
/**
 * @brief Cabeça da lista;
 * @typedef CAlianca;
*/
typedef struct _calianca CAlianca;

/**
 * @brief Aloca uma struct do tipo TAlianca;
 * @param nome;
 * @return TAlianca;
*/
TAlianca *talianca_aloca(const char *nome);
/**
 * @brief Cria a cabeça da lista;
 * @param void;
 * @return CAlianca;
*/
CAlianca *calianca_cria(void);
/**
 * @brief Desaloca a lista;
 * @param cabeca;
 * @return CAlianca;
*/
void calianca_desaloca(CAlianca **cabeca);

/**
 * @brief Verifica se a aliança está vazia;
 * @param cabeca;
 * @return (0 ou 1);
*/
int calianca_vazia(const CAlianca *cabeca);
/**
 * @brief Insere uma nova aliança na lista;
 * @param cabeca, nome;
 * @return void;
*/
void calianca_insere(CAlianca *cabeca, const char *nome);
/**
 * @brief Mostra o conteúdo da lista, caso não esteja vazia;
 * @param cabeca;
 * @return void;
*/
void calianca_display(const CAlianca *cabeca);
void alianca_aliados(const CAlianca *cabeca);


#endif 

