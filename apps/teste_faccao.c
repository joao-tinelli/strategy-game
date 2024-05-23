#include <stdio.h>
#include "faccao.h"
#include "mapa.h"

int main(int argc, char const *argv[])
{
    CFaccao *faccao = Cfaccao_cria();

    faccoes_converte_txt_lista(faccao, "./input/faccoes.txt");
    Dimensao *d = mapa_le_dimensao("./input/config.txt");
    char **mapa = mapa_aloca(d);
    mapa_gera(mapa, d);
    faccoes_inicializar_mapa(faccao, mapa);
    mapa_display(mapa, d);
       
    return 0;
}