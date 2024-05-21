#include <stdio.h>
#include "unidade.h"

int main(int argc, char const *argv[])
{
  CUnidade *cunidade = cunidade_cria();

  puts("mostrar: ");
  cunidade_display(cunidade);

  puts("Inserir:");
  
  cunidade_insere(cunidade, 10, 2, 1);
  cunidade_insere(cunidade, 12, 6, 1);
  cunidade_insere(cunidade, 13, 5, 1);

  puts("Mostrar: ");
  cunidade_display(cunidade);

  cunidade_desaloca(&cunidade);
  
  return 0;
}
