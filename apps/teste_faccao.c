#include <stdio.h>
#include "faccao.h"
#include "mapa.h"

int main(int argc, char const *argv[])
{
    CFaccao *cfaccao = Cfaccao_cria();
    faccoes_converte_txt_lista(cfaccao, "./input/faccoes.txt");
    
    puts("display 1");
    faccoes_display(cfaccao);

    faccao_coleta(cfaccao, 'a', 1, 20);
    faccao_coleta(cfaccao, 'b', 2, 20);

    puts("display 2");
    faccoes_display(cfaccao);
       
    faccao_desaloca(&cfaccao);

    return 0;
}