#include "bibliotecas.h"

void msg_erro(char *S, char *funcao)
{
    fprintf(stderr, "Erro em: '%s'.\n", funcao);
    fprintf(stderr, "Mensagem: '%s'\n", S);
}

