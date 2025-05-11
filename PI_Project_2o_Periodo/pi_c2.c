#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
  setlocale(LC_ALL, "Portuguese_Brasil");

  printf("Este programa permite que você avalie o progresso de um projeto em cinco etapas:\n");
  printf("1. Levantamento de Requisitos\n");
  printf("2. Arquitetura e Design\n");
  printf("3. Desenvolvimento\n");
  printf("4. Testes\n");
  printf("5. Implantação\n");
  printf("\nVocê pode adicionar valores entre 1 e 5 para cada etapa.\n");
  printf("O valor 5 é o máximo e indica que a etapa está concluída.\n");
  printf("O programa solicitará o progresso de uma etapa de cada vez e só avançará\n");
  printf("para a próxima etapa quando a etapa atual atingir o valor 5.\n\n");

  int i, progresso[5] = {0}; // Inicializa o progresso de cada etapa com 0
  char *fases[5] = {"Levantamento de Requisitos", "Arquitetura e Design", "Desenvolvimento", "Testes", "Implantação"};
  int entrada;

  // Itera sobre cada etapa até que todas sejam concluídas
  for (i = 0; i < 5; i++)
  {
    // Enquanto a etapa atual não atingir o valor 5, continue pedindo entradas
    while (progresso[i] < 5)
    {
      printf("\n\t%s (atual: %d). Quanto deseja adicionar? ", fases[i], progresso[i]);
      scanf("%d", &entrada);

      // Valida a entrada
      if (entrada < 1 || entrada > 5)
      {
        printf("\nValor inválido! Digite um número entre 1 e 5.\n");
        continue; // Solicita novamente a entrada
      }

      // Atualiza o progresso, garantindo que não ultrapasse 5
      progresso[i] += entrada;
      if (progresso[i] > 5)
      {
        progresso[i] = 5; // Ajusta para não ultrapassar 5
      }

      // Exibe o progresso atualizado
      printf("\nProgresso atualizado de %s: %d\n", fases[i], progresso[i]);
    }

    // Indica que a etapa atual foi concluída
    printf("\n%s está concluído!\n", fases[i]);
  }

  system("cls");
  printf("\nTodas as etapas estão concluídas!\n");
  return 0;
}
