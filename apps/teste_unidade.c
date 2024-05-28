#include <stdio.h>
#include "mapa.h"
#include "unidade.h"

int main(int argc, char const *argv[])
{
  
  Dimensao *d = mapa_le_dimensao("./input/config.txt");
  char **mapa_oficial = mapa_aloca(d);
  char **mapa_unidade = mapa_aloca(d);
  mapa_gera(mapa_oficial, d);
  mapa_replica(mapa_oficial, mapa_unidade, d);

  CUnidade *cunidade = cunidade_cria();

  unidade_posiciona("FA", cunidade, 1, 1, 1, mapa_unidade);

  unidade_posiciona("FB", cunidade, 2, 9, 2, mapa_unidade);

  mapa_display(mapa_unidade, d);


  cunidade_desaloca(&cunidade);
  return 0;
}
