#include "bibliotecas.h"

int main(int argc, char const *argv[])
{
    CFaccao *cfaccao = Cfaccao_cria();

    faccoes_converte_txt_lista(cfaccao, "./input/faccoes.txt");
    
    faccao_coleta(cfaccao, 'a', 1, 20);
    faccao_coleta(cfaccao, 'b', 2, 20);
    faccao_coleta(cfaccao, 'c', 1, 20);

    faccao_teste(cfaccao);

    faccao_alianca(cfaccao, "FA", "FD");
    
    faccoes_display(cfaccao);    
       
    cfaccao_desaloca(&cfaccao);

    return 0;
}