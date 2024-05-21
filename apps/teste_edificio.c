#include <stdio.h>
#include "edificio.h"

int main(int argc, char const *argv[])
{
    CEdificio *edificio = CEdificio_cria();
    edificio_inserir(edificio, 2, 3, 1);
    edificio_inserir(edificio, 2, 5, 2);
    
    edificio_display(edificio);
    edificio_desaloca(&edificio);
    edificio_display(edificio);
    
    return 0;
}