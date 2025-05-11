#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
  //  Definindo nomes e valores
  char titulo[50], descricao[100], prioridade[50];
  int necessidade, impacto, valor;

  //  Definindo o nome do Requisito e Descrição
  printf("Qual o nome do requisito? ");
  scanf("%s", titulo);
  printf("De uma descricao para o requisito: ");
  scanf("%s", descricao);

  //  Definindo a prioridade do requisito
  printf("Qual a necessidade do requisito (1 a 5): ");
  scanf("%i", &necessidade);
  printf("Qual o impacto do requisito (1 a 5): ");
  scanf("%i", &impacto);
  printf("Qual nivel do valor (1 a 5): ");
  scanf("%i", &valor);

  //  Definindo o valor da prioridade
  float media = (necessidade + impacto + valor) / 3.0;

  // Condicional para definir nivel da Prioridade
  if (media < 2)
  {
    strcpy(prioridade, "Baixa");
  }
  else if (media >= 2 && media < 3)
  {
    strcpy(prioridade, "Media");
  }
  else if (media >= 3 && media < 4)
  {
    strcpy(prioridade, "Alta");
  }
  else if (media >= 4)
  {
    strcpy(prioridade, "Muito Alta");
  }

  //  Resultado
  printf(
      "\n\tRequisito: %s\n"
      "\tDescricao: %s \n"
      "\tPrioridade: %s\n",
      titulo, descricao, prioridade);

  return 0;
}
