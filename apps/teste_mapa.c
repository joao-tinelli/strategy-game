#include <stdio.h>
#include "alianca.h"
#include "edificio.h"
#include "faccao.h"
#include "mapa.h"
#include "mensagens.h"
#include "unidade.h"

int main(int argc, char const *argv[])
{
    Dimensao *d = mapa_le_dimensao("./input/config.txt");
    int **mapa = mapa_aloca(d);
    mapa_gera(mapa, d);
    mapa_display(mapa, d);

    desaloca_mapa(&mapa, d);
     
    mapa_display(mapa, d);

    return 0;
}
