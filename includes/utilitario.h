#ifndef UTILITARIO_H
#define UTILITARIO_H

/**
 * @brief Abre o arquivo txt;
 * @param path_arquivo, operacao;
 * @return FILE;
*/
FILE *abrir_arquivo(char *path_arquivo, char *operacao);

/**
 * @brief Converte o nome da unidade para o nome da facção;
 * @param nome;
 * @return void;
*/
void unidade_para_faccao(char *nome);

/**
 * @brief Gera o arquivo log com as ações feitas;
 * @param acao, peca, peca2, tipo, tipo2, qtd, x, y;
 * @return void;
*/
void gera_log(const char *acao, const char *peca, const char *peca2, const int tipo, const int tipo2, const int qtd, const int x, const int y);

#endif