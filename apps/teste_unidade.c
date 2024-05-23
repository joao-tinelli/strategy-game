#include <stdio.h>
#include "unidade.h"

int main(int argc, char const *argv[])
{
  CUnidade *cunidade = cunidade_cria();

  puts("mostrar: ");
  unidade_display(cunidade);

  puts("Inserir:");
  
  unidade_insere(cunidade, 10, 2, 1);
  unidade_insere(cunidade, 12, 6, 1);
  unidade_insere(cunidade, 13, 5, 1);

  puts("Mostrar: ");
  unidade_display(cunidade);

  cunidade_desaloca(&cunidade);
  
  unidade_display(cunidade);

  return 0;
}
