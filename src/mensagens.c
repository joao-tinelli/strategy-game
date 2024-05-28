#include "bibliotecas.h"

void msg_erro(char *S, char *funcao)
{
    fprintf(stderr, "Erro em: '%s'.\n", funcao);
    fprintf(stderr, "Mensagem: '%s'\n", S);
}

void msg_sucesso(char *S, char *funcao) {
    fprintf(stdout, "Sucesso: '%s'.\n", funcao);
    fprintf(stdout, "Mensagem: '%s'.\n", S);
}
