// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// int main()
// {
//   char nome[3][100], sexo[3][10], naturalidade[3][30], confirmacao[3][3], observacao[3][100];
//   int i, idade[3];

//   for (i = 0; i < 3; i++)
//   {
//     // Proteção de erro para garantir que o nome tenha mais que 3 caracteres
//     do
//     {
//       printf("Nome Completo: ");
//       scanf("%s", nome[i]);
//     } while (strlen(nome[i]) < 3);

//     // Coletando o sexo do usuário e evitando que não seja escrito nada diferente de "Fem" e "Masc", Feminino e Masculino respectivamente
//     while (strcmp("Masc", sexo[i]) != 0 && strcmp("Fem", sexo[i]) != 0)
//     {
//       printf("Qual sexo - Fem | Masc: ");
//       scanf("%s", sexo[i]);
//     }

//     // Coletando idade do usuário e garantindo que seja um número positivo
//     do
//     {
//       printf("Idade: ");
//       scanf("%i", &idade[i]);
//     } while (100 > idade[i] < 1);

//     do
//     {
//       printf("Naturalidade: ");
//       scanf("%s", naturalidade[i]);
//     } while (strlen(naturalidade[i]) < 1);

//     while (strcmp("Sim", confirmacao[i]) != 0 && strcmp("Nao", confirmacao[i]) != 0)
//     {
//       printf("Alguma observação - Sim ou Nao? ");
//       scanf("%s", confirmacao[i]);
//       if (strcmp(confirmacao[i], "Sim") == 0)
//       {
//         printf("Qual a observação? (limite 100 char) \n");
//         fgets(observacao[i], 100, stdin);
//       }
//       else if (strcmp(confirmacao[i], "Nao") == 0)
//       {
//         strcpy(observacao[i], "N/A");
//       }
//       else
//       {
//         printf("\nValor inválido!\n\n");
//       }
//     }

//     system("cls");
//   }

//   for (i = 0; i < 3; i++)
//   {
//     printf("Paciente numero %i", i + 1);
//     printf("\n\tNome: %s", nome[i]);
//     printf("\n\tIdade: %i", idade[i]);
//     printf("\n\tSexo: %s", sexo[i]);
//     printf("\n\tNaturalidade: %s", naturalidade[i]);
//     printf("\n\tObservacao: %s", observacao[i]);
//     printf("\n");
//   }

//   return 0;
// }

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char nome[3][100], sexo[3][10], naturalidade[3][30], confirmacao[3][3], observacao[3][100];
  int i, idade[3];

  for (i = 0; i < 3; i++)
  {
    // Proteção de erro para garantir que o nome tenha mais que 3 caracteres
    do
    {
      printf("Nome Completo: ");
      fgets(nome[i], 100, stdin);
      nome[i][strcspn(nome[i], "\n")] = '\0'; // Remove o caractere de nova linha
    } while (strlen(nome[i]) < 3);

    // Coletando o sexo do usuário
    strcpy(sexo[i], ""); // Inicializa com string vazia
    while (strcmp("Masc", sexo[i]) != 0 && strcmp("Fem", sexo[i]) != 0)
    {
      printf("Qual sexo - Fem | Masc: ");
      scanf("%s", sexo[i]);
    }

    // Coletando idade do usuário e garantindo que seja um número positivo
    do
    {
      printf("Idade: ");
      scanf("%i", &idade[i]);
    } while (idade[i] < 1 || idade[i] > 100);

    getchar();

    // Coletando a naturalidade
    do
    {
      printf("Naturalidade: ");
      fgets(naturalidade[i], 30, stdin);
      naturalidade[i][strcspn(naturalidade[i], "\n")] = '\0'; // Remove nova linha
    } while (strlen(naturalidade[i]) < 1);

    // Coletando a confirmação e observação
    while (strcmp("Sim", confirmacao[i]) != 0 && strcmp("Nao", confirmacao[i]) != 0)
    {
      printf("Alguma observação - Sim ou Nao? ");
      scanf("%s", confirmacao[i]);
      getchar();

      if (strcmp(confirmacao[i], "Sim") == 0)
      {
        printf("Qual a observação? (limite 100 char) \n");
        fgets(observacao[i], 100, stdin);
        observacao[i][strcspn(observacao[i], "\n")] = '\0'; // Remove nova linha
      }
      else if (strcmp(confirmacao[i], "Nao") == 0)
      {
        strcpy(observacao[i], "N/A");
      }
      else
      {
        printf("\nValor inválido!\n\n");
      }
    }

    system("cls");
  }

  for (i = 0; i < 3; i++)
  {
    printf("Paciente numero %i", i + 1);
    printf("\n\tNome: %s", nome[i]);
    printf("\n\tIdade: %d", idade[i]);
    printf("\n\tSexo: %s", sexo[i]);
    printf("\n\tNaturalidade: %s", naturalidade[i]);
    printf("\n\tObservacao: %s", observacao[i]);
    printf("\n");
  }

  return 0;
}
