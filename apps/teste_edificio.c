#include <stdio.h>
#include "edificio.h"
#include "mapa.h"

int main(int argc, char const *argv[])
{
    CEdificio *cedificio = cedificio_cria();
    edificio_constroi(cedificio, "FA", 1, 2, 2, 1);
    edificio_constroi(cedificio, "FA", 2, 1, 2, 3);
    edificio_display(cedificio);
    cedificio_desaloca(&cedificio);
    
    return 0;
}