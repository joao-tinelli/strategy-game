#include <stdio.h>
#include "mapa.h"
#include "unidade.h"

int main(int argc, char const *argv[])
{

  CUnidade *cunidade = cunidade_cria();

  unidade_posiciona(cunidade, "A1", 1, 1, 1);
  unidade_posiciona(cunidade, "A2", 2, 8, 8);

  unidade_display(cunidade);

  puts("MOVE: ");

  unidade_move(cunidade, "A1", 1, 9, 9);

  unidade_display(cunidade);

  cunidade_desaloca(&cunidade);
  return 0;
}
