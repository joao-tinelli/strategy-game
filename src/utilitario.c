#include "bibliotecas.h"

void unidade_para_faccao(char *nome) // Ex: A1 --> FA
{
    nome[1] = nome[0];
    nome[0] = 'F';
}

void gera_log(const char *acao, const char *peca, const char *peca2, const int tipo, const int tipo2, const int qtd, const int x, const int y)
{
    FILE *arq_log = fopen("./output/saida.txt", "a");
    if (arq_log == NULL) {
        msg_erro("Erro ao abrir o arquivo.", "gera_log");
        return;
    }

    if (strcmp(acao, "pos") == 0)
    {
        fprintf(arq_log, "%s %s %d %d %d\n", peca, acao, tipo, x, y);
    }
    if (strcmp(acao, "move") == 0)
    {
        fprintf(arq_log, "%s %s %d %d %d\n", peca, acao, tipo, x, y);
    }
    if (strcmp(acao, "coleta") == 0)
    {
        fprintf(arq_log, "%s %s %d\n", peca, acao, qtd);
    }
    if (strcmp(acao, "constroi") == 0)
    {
        fprintf(arq_log, "%s %s %d %d %d %d\n", peca, acao, qtd, tipo, x, y);
    }
    if (strcmp(acao, "combate") == 0)
    {
        fprintf(arq_log, "%s %d %s %s %d\n", peca, tipo, acao, peca2, tipo2);
    }
    if (strcmp(acao, "ataca") == 0)
    {
        fprintf(arq_log, "%s %s %s\n", peca, acao, peca2);
    }
    if (strcmp(acao, "alianca") == 0)
    {
        fprintf(arq_log, "%s %s %s\n", peca, acao, peca2);
    }

    fclose(arq_log);
}