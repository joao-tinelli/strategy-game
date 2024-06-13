#ifndef UTILITARIO_H
#define UTILITARIO_H

FILE *abrir_arquivo(char *path_arquivo, char *operacao);
void unidade_para_faccao(char *nome);
void gera_log(const char *acao, const char *peca, const char *peca2, const int tipo, const int tipo2, const int qtd, const int x, const int y);

#endif