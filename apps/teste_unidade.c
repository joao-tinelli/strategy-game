#include <stdio.h>
#include "mapa.h"
#include "unidade.h"

int main(int argc, char const *argv[])
{
  Dimensao *d = mapa_le_dimensao("./input/config.txt");
  char **mapa_unidade = mapa_aloca(d);
  mapa_gera(mapa_unidade, d);

  CUnidade *cunidade = cunidade_cria();

  puts("mostrar: ");
  unidade_display(cunidade);

  puts("Inserir:");
  
  unidade_insere(cunidade, '1', 2, 2, 3);
  unidade_insere(cunidade, '2', 1, 6, 1);
  unidade_insere(cunidade, '3', 2, 5, 7);

  puts("Mostrar: ");
  unidade_display(cunidade);

  puts("unidades posicionadas no mapa:");
  unidade_posiciona_mapa(mapa_unidade,cunidade, '1');
  unidade_posiciona_mapa(mapa_unidade,cunidade, '2');
  unidade_posiciona_mapa(mapa_unidade,cunidade, '3');

  mapa_display(mapa_unidade, d);

  cunidade_desaloca(&cunidade);
  desaloca_mapa(&mapa_unidade, d);
  
  return 0;
}
