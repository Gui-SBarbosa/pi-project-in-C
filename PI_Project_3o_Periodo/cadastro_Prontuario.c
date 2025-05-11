#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <ctype.h>

#define MAX_REGISTROS 100
#define MAX_NOME 50
#define MAX_SEXO 20
#define MAX_DESCRICAO 150
#define MAX_TELEFONE 15
#define LIMPAR_TELA "cls"

typedef struct
{
  int id;
  int ativo;
  char nomeMedico[MAX_NOME];
  char nomePaciente[MAX_NOME];
  char sexo[MAX_SEXO]; // Masc / Fem
  char contato[MAX_TELEFONE];
  int idade;
  char descricao[MAX_DESCRICAO];
} Prontuario;

Prontuario prontuarios[MAX_REGISTROS];

int totalProntuarios = 0;
int proximoId = 0;

void inicializar();
void menuPrincipal();
void criar();
void listar();
void buscar();
void atualizar();
void deletar();
void limparTela();

int main()
{
  SetConsoleOutputCP(CP_UTF8);
  setlocale(LC_ALL, "Portuguese_Brazil.1252");

  inicializar();
  menuPrincipal();
  return 0;
};

void inicializar()
{
  for (int i = 0; i < MAX_REGISTROS; i++)
  {
    prontuarios[i].id = 0;
  };
  printf("Sistema inicializado.\n");
}

void limparTela()
{
  system(LIMPAR_TELA);
};

int validarTelefone(const char *telefone)
{
  int len = strlen(telefone);

  if (len < 9 || len > 15)
  {
    return 0; // Inválido
  }

  int digitos = 0;
  for (int i = 0; i < len; i++)
  {
    if (isdigit(telefone[i]))
    {
      digitos++;
    }
    else if (telefone[i] != '(' && telefone[i] != ')' &&
             telefone[i] != '-' && telefone[i] != ' ' &&
             telefone[i] != '+')
    {

      return 0;
    }
  }

  if (digitos < 9)
  {
    return 0;
  }

  return 1; // Válido
}

void menuPrincipal()
{
  int opcao = 0;

  do
  {
    printf("\n====== MENU PRINCIPAL ======\n");
    printf("1. Criar Prontuário\n");
    printf("2. Listar Prontuários\n");
    printf("3. Buscar Prontuário\n");
    printf("4. Atualizar Prontuário\n");
    printf("5. Deletar pontuário\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    limparTela();

    switch (opcao)
    {
    case 1:
      criar();
      break;

    case 2:
      listar();
      break;

    case 3:
      buscar();
      break;

    case 4:
      atualizar();
      break;

    case 5:
      deletar();
      break;

    default:
      printf("Opção inválida!\n");
    }
  } while (opcao != 0);

  if (opcao == 0)
  {
    limparTela();
  }
}

void criar()
{
  if (totalProntuarios >= MAX_REGISTROS)
  {
    printf("Erro . . . Limite total de registros atingidos!");
    return;
  }

  Prontuario novo;
  novo.id = proximoId++;
  novo.ativo = 1;

  printf("\n=== Cadastro de Prontuário ===\n");

  // Adicionando nome do Médico
  printf("Nome do Médico: ");
  fgets(novo.nomeMedico, MAX_NOME, stdin);
  novo.nomeMedico[strcspn(novo.nomeMedico, "\n")] = 0;

  // Adicionando nome do Paciente
  printf("\nNome do Paciente: ");
  fgets(novo.nomePaciente, MAX_NOME, stdin);
  novo.nomePaciente[strcspn(novo.nomePaciente, "\n")] = 0;

  // Adicionar idade do paciente
  int idade;

  do
  {
    printf("\nIdade: ");
    scanf("%d", &idade);
    getchar(); // Limpa o buffer

    if (idade <= 0)
    {
      printf("Erro: A idade deve ser um valor positivo. Tente novamente.\n");
    }
  } while (idade <= 0);

  novo.idade = idade;

  // Adicionar gênero do paciente
  int opcao;

  printf("\n1) Feminino\n");
  printf("2) Masculino\n");
  printf("3) Outro\n");
  printf("4) Prefiro não dizer\n");
  printf("Qual gênero se identifica:");
  scanf("%d", &opcao);

  switch (opcao)
  {
  case 1:
    strcpy(novo.sexo, "Feminino");
    break;
  case 2:
    strcpy(novo.sexo, "Masculino");
    break;
  case 3:
    strcpy(novo.sexo, "Outro");
    break;
  case 4:
    strcpy(novo.sexo, "Prefiro não dizer");
    break;

  default:
    printf("Opção inválida, escolha algumas válida!\n");
    break;
  }

  printf("\nSexo: %s\n", novo.sexo);

  // Adicionar numero de telefone
  char contato[MAX_TELEFONE];
  int contatoValido = 0;

  do
  {
    printf("\nTelefone (formato: (99) 99999-9999): ");
    fgets(contato, MAX_TELEFONE, stdin);
    contato[strcspn(contato, "\n")] = 0;

    contatoValido = validarTelefone(contato);
    if (!contatoValido)
    {
      printf("Erro: Telefone inválido. Use apenas números, parênteses, hífen, espaço e +.\n");
      printf("O telefone deve ter pelo menos 8 dígitos. Tente novamente.\n");
    }
  } while (!contatoValido);

  strcpy(novo.contato, contato);

  printf("\nDescrição: ");
  fgets(novo.descricao, MAX_DESCRICAO, stdin);
  novo.descricao[strcspn(novo.descricao, "\n")] = '\0';

  limparTela();

  for (int i = 0; i < MAX_REGISTROS; i++)
  {
    if (prontuarios[i].ativo == 0)
    {
      prontuarios[i] = novo;
      totalProntuarios++;

      printf("Prontuário cadastrado com sucesso! ID: %d\n", novo.id);
      return;
    }
  }
}

void listar()
{
  printf("=== Lista de Prontuários ===\n");

  if (totalProntuarios == 0)
  {
    printf("Nenhum prontuário foi cadastrado!");
    return;
  }

  printf("\n%-5s %-25s %-25s %-15s %-6s %-15s\n",
         "ID", "Médico", "Paciente", "Sexo", "Idade", "Contato");

  printf("--------------------------------------------------------------------------------\n");

  for (int i = 0; i < MAX_REGISTROS; i++)
  {
    if (prontuarios[i].ativo == 1)
    {
      printf("%-5d %-25s %-25s %-15s %-6d %-15s\n", // Note o %s para contato
             prontuarios[i].id,
             prontuarios[i].nomeMedico,
             prontuarios[i].nomePaciente,
             prontuarios[i].sexo,
             prontuarios[i].idade,
             prontuarios[i].contato);
    }
  }
}

// Buscar dados
void buscar()
{
  int id;

  printf("\n=== Buscar Prontuário ===\n");
  printf("Digite o ID do prontúário: ");
  scanf("%d", &id);
  getchar();
  limparTela();

  for (int i = 0; i < MAX_REGISTROS; i++)
  {
    if (prontuarios[i].id == id && prontuarios[i].ativo == 1)
    {
      printf("\nProntuário encontrado!\n");
      printf("\nID: %d", prontuarios[i].id);
      printf("\nNome do médico: %s", prontuarios[i].nomeMedico);
      printf("\nNome do paciente: %s", prontuarios[i].nomePaciente);
      printf("\nIdade: %d", prontuarios[i].idade);
      printf("\nSexo: %s", prontuarios[i].sexo);
      printf("\nDescrição: %s", prontuarios[i].descricao);
      printf("\nPressione Enter para continuar. . .");
      getchar();
      return;
    }
  }
  printf("Prontuário não encontrado!\n");
  printf("\nPressione Enter para continuar...");
  getchar();
}

// Atualizar dados
void atualizar()
{
  int id;
  int opcao;

  printf("\n=== Atualizar Funcionário ===\n");
  printf("Digite o ID do funcionário: ");
  scanf("%d", &id);
  getchar(); // Limpa o buffer

  for (int i = 0; i < MAX_REGISTROS; i++)
  {
    if (prontuarios[i].id == id && prontuarios[i].ativo == 1)
    {
      printf("\nFuncionário encontrado. O que deseja atualizar?\n");
      printf("1. Nome do Médico\n");
      printf("2. Nome do Paciente\n");
      printf("3. Idade\n");
      printf("4. Sexo\n");
      printf("5. Contato\n");
      printf("6. Descrição\n");
      printf("0. Cancelar\n");
      printf("Escolha uma opção: ");
      scanf("%d", &opcao);
      getchar(); // Limpa o buffer

      switch (opcao)
      {
      case 1:
        printf("Novo nome: ");
        fgets(prontuarios[i].nomePaciente, MAX_NOME, stdin);
        prontuarios[i].nomePaciente[strcspn(prontuarios[i].nomePaciente, "\n")] = 0;

        limparTela();
        printf("Nome do Paciente atualizado com sucesso!\n");
        break;
      case 2:
        printf("Novo nome: ");
        fgets(prontuarios[i].nomeMedico, MAX_NOME, stdin);
        prontuarios[i].nomeMedico[strcspn(prontuarios[i].nomeMedico, "\n")] = 0;

        limparTela();
        printf("Nome do Médico atualizado com sucesso!\n");
        break;
      case 3:
        // Validação para idade positiva
        do
        {
          printf("Nova idade: ");
          scanf("%d", &prontuarios[i].idade);
          getchar(); // Limpa o buffer

          if (prontuarios[i].idade <= 0)
          {
            printf("Erro: A idade deve ser um valor positivo. Tente novamente.\n");
          }
        } while (prontuarios[i].idade <= 0);

        limparTela();
        printf("Idade atualizada com sucesso!\n");
        break;
      case 4:;
        int opcao;

        printf("\n1) Feminino\n");
        printf("2) Masculino\n");
        printf("3) Outro\n");
        printf("4) Prefiro não dizer\n");
        printf("Qual gênero se identifica:");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
          strcpy(prontuarios[i].sexo, "Feminino");
          break;
        case 2:
          strcpy(prontuarios[i].sexo, "Masculino");
          break;
        case 3:
          strcpy(prontuarios[i].sexo, "Outro");
          break;
        case 4:
          strcpy(prontuarios[i].sexo, "Prefiro não dizer");
          break;

        default:
          printf("Opção inválida, escolha algumas válida!\n");
          break;
        }

        limparTela();
        printf("\nSexo atualizado: %s\n", prontuarios[i].sexo);
        break;
      case 5:;
        // Validação de telefone
        char contato[MAX_TELEFONE];
        int contatoValido = 0;

        do
        {
          printf("Novo telefone (formato: (99) 99999-9999): ");
          fgets(contato, MAX_TELEFONE, stdin);
          contato[strcspn(contato, "\n")] = 0;

          contatoValido = validarTelefone(contato);
          if (!contatoValido)
          {
            printf("Erro: Telefone inválido. Use apenas números, parênteses, hífen, espaço e +.\n");
            printf("O telefone deve ter pelo menos 8 dígitos. Tente novamente.\n");
          }
        } while (!contatoValido);

        strcpy(prontuarios[i].contato, contato);
        limparTela();
        printf("Telefone atualizado com sucesso!\n");
        break;
      case 6:
        printf("\nAtualizar nova descrição descrição: ");
        fgets(prontuarios[i].descricao, MAX_DESCRICAO, stdin);
        prontuarios[i].descricao[strcspn(prontuarios[i].descricao, "\n")] = '\0';

        limparTela();
        printf("Descrição atualizada com sucesso!");
        break;
      case 0:
        printf("Operação cancelada.\n");
        break;
      default:
        printf("Opção inválida!\n");
      }
      printf("\nPressione Enter para continuar...");
      getchar();
      return;
    }
  }

  printf("Funcionário não encontrado!\n");
  printf("\nPressione Enter para continuar...");
  getchar();
}

void deletar()
{
  int id;
  char confirmacao;

  printf("\n=== Deletar Funcionário ===\n");
  printf("Digite o ID do funcionário: ");
  scanf("%d", &id);
  getchar(); // Limpa o buffer

  for (int i = 0; i < MAX_REGISTROS; i++)
  {
    if (prontuarios[i].id == id && prontuarios[i].ativo == 1)
    {
      printf("\nFuncionário encontrado:\n");
      printf("ID: %d\n", prontuarios[i].id);
      printf("Nome Paciente: %s\n", prontuarios[i].nomePaciente);
      printf("Nome Médico: %s\n", prontuarios[i].nomeMedico);

      printf("\nConfirma exclusão? (S/N): ");
      scanf("%c", &confirmacao);
      getchar(); // Limpa o buffer

      if (confirmacao == 'S' || confirmacao == 's')
      {
        prontuarios[i].ativo = 0; // Marca como inativo (exclusão lógica)
        totalProntuarios--;
        limparTela();
        printf("Funcionário deletado com sucesso!\n");
      }
      else
      {
        printf("Operação cancelada.\n");
      }
      printf("\nPressione Enter para continuar...");
      getchar();
      limparTela();
      return;
    }
  }

  printf("Funcionário não encontrado!\n");
  printf("\nPressione Enter para continuar...");
  getchar();
}