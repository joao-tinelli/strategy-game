#include <stdio.h>
#include "edificio.h"
#include "mapa.h"

int main(int argc, char const *argv[])
{
    Dimensao *d = mapa_le_dimensao("./input/config.txt");
    char **mapa_oficial = mapa_aloca(d);
    char **mapa_edificio = mapa_aloca(d);

    mapa_gera(mapa_oficial, d);
    mapa_replica(mapa_oficial, mapa_edificio, d);
    //Fazer o resto para os outros 

    CEdificio *cedificio = cedificio_cria();
    edificio_insere(cedificio, '1', 2, 4, 6);
    edificio_insere(cedificio, '2', 1, 1, 9);
    edificio_insere(cedificio, '3', 3, 2, 3);

    puts("Mostrar edificios:");
    edificio_display(cedificio);
    puts("");

    puts("Mapa inicial:");
    mapa_display(mapa_edificio, d);
    puts("");

    edificio_posiciona_mapa(mapa_edificio, cedificio, '1');
    edificio_posiciona_mapa(mapa_edificio, cedificio, '2');
    edificio_posiciona_mapa(mapa_edificio, cedificio, '3');
    edificio_retira_mapa(mapa_edificio, mapa_oficial, cedificio, '1');
    
    puts("Mapa final:");
    mapa_display(mapa_edificio, d);

    cedificio_desaloca(&cedificio);
    desaloca_mapa(&mapa_oficial, d);
    desaloca_mapa(&mapa_edificio, d);  
    //Desalocar todos os mapas     
    return 0;
}