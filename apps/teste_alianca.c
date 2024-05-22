#include <stdio.h>
#include "alianca.h"

int main(int argc, char const *argv[])
{
  CAlianca *calianca = calianca_cria();

  puts("mostrar: ");
  calianca_display(calianca);

  puts("Inserir:");
  
  calianca_insere(calianca, "OsGalaticos");
  calianca_insere(calianca, "TrioMSN");
  calianca_insere(calianca, "TrioParada");

  puts("Mostrar: ");
  calianca_display(calianca);

  calianca_desaloca(&calianca);
  
  return 0;
}
