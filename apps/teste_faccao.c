#include "bibliotecas.h"

int main(int argc, char const *argv[])
{
    CFaccao *cfaccao = Cfaccao_cria();
    faccoes_converte_txt_lista(cfaccao, "./input/faccoes.txt");
    
    faccao_coleta(cfaccao, 'a', 1, 20);
    faccao_coleta(cfaccao, 'b', 2, 20);
    faccao_coleta(cfaccao, 'c', 1, 20);

    faccao_teste(cfaccao);

    puts("teste 1");
    faccoes_display(cfaccao);

    puts("teste 2");
    faccao_combate(cfaccao, "FA", "FC");

    puts("teste 3");
    faccoes_display(cfaccao);  

    puts("teste 4");
    faccao_combate(cfaccao, "FA", "FB");
    faccoes_display(cfaccao);
       
    cfaccao_desaloca(&cfaccao);

    return 0;
}