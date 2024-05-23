#include <stdio.h>
#include "mapa.h"
#include "unidade.h"

int main(int argc, char const *argv[])
{
  Dimensao *d = mapa_le_dimensao("./input/config.txt");
  char **mapa = mapa_aloca(d);
  mapa_gera(mapa, d);

  CUnidade *cunidade = cunidade_cria();

  puts("mostrar: ");
  unidade_display(cunidade);

  puts("Inserir:");
  
  unidade_insere(cunidade, "B2", 2, 2, 3);
  unidade_insere(cunidade, "A1", 1, 6, 1);
  unidade_insere(cunidade, "A2", 2, 5, 7);

  puts("Mostrar: ");
  unidade_display(cunidade);

  mapa_display(mapa, d);

  cunidade_desaloca(&cunidade);
  desaloca_mapa(&mapa, d);
  
  return 0;
}
