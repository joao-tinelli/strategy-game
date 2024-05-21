#include <stdio.h>

#include "faccao.h"

int main(int argc, char const *argv[])
{
    CFaccao *faccao = Cfaccao_cria();

    faccoes_converte_txt_lista(faccao, "./input/faccoes.txt");

    faccoes_display(faccao);

    faccao_desaloca(&faccao);
    return 0;
}