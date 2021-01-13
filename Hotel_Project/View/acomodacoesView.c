#include "../Model/acomodacoesModel.h"
#include "../Model/categoriaAcomodacaoModel.h"

/*
 * Nome: menuAcomodacoesView()
 * Parâmetro¹: int pCodigo.
 * Return: void
 * Author: Yuri
 * Função: Mostra as opções do menu e chama a função selecionada.
 */

static int contAcomodacao = 0;


void menuAcomodacoesView(int pCodigo) {


  int condicao;

  acomodacoes temp;

  if (pCodigo == 5) {
    opcao = 5;
    goto parametro_5_Acomodacao;
  }

  do {

    printf("-------///////MENU///////-------\n\n\n");
    printf("Numero de Acomodaçoes: %d\n\n", contAcomodacao);
    printf("1. Cadastrar Acomodação\n"
           "2. Excluir Acomodação\n"
           "3. Ver Acomodações\n"
           "4. Atualizar Acomodacao\n"
           "5. Mostrar Todas Acomodações\n"
           "0. Sair\n");

    scanf("%d", &opcao);

    switch (opcao) {

    case 0:

      break;

    case 1:

      temp = cadastrarAcomodacaoView(contAcomodacao);

      if (temp.situacao == 0) {

        recebeAcomodacaoController(temp, contAcomodacao);

        contAcomodacao++;
        printf("\nCadastrado!\n\n");
      }

      break;

    case 2:

      condicao = excluirAcomodacoesView(contAcomodacao);

      if (condicao == 0) {

        contAcomodacao--;
        printf("Excluido!\n");

      } else {

        printf("A acomodação não foi excluida!\n");
      }

      break;

    case 3:

      verAcomodacoesView(contAcomodacao);

      break;

    case 4:

      temp = alterarAcomodacaoView(contAcomodacao);

      if (temp.situacao == 0) {

        atualizarAcomodacoesController(temp);
      }

      break;

    case 5:

    parametro_5_Acomodacao:

      if (pCodigo == 5) {
        opcao = 0;
      }

      mostrarTodasAcomodacoesView(contAcomodacao);

      break;
    }

  } while (opcao != 0);
}

/*
 * Nome: cadastrarAcomodacaoView()
 * Parâmetro¹: int contAcomodacao.
 * Return: Struct acomodacoes
 * Author: Yuri
 * Função: Recebe os dados para o cadastro da acomodação e posteriormente
 * salva no controller
 */
acomodacoes cadastrarAcomodacaoView(int contAcomodacao) {

  int qtdCadastrados, codigoAcomodacaoTemp;

  acomodacoes cadastroAcomodacao;

  categoria *categoriaTemporaria;

  cadastroAcomodacao.categoria = 0;

  cadastroAcomodacao.situacao = 1;

  cadastroAcomodacao.codigo = contAcomodacao + 1;

  getchar();

  printf("Descrição da Acomodação: ");
  fgets(cadastroAcomodacao.descricao, sizeof(cadastroAcomodacao.descricao),
        stdin);
  toUpperCase(cadastroAcomodacao.descricao);

  printf("Facilidades: ");
  fgets(cadastroAcomodacao.facilidades, sizeof(cadastroAcomodacao.facilidades),
        stdin);
  toUpperCase(cadastroAcomodacao.facilidades);
  qtdCadastrados = menuCategoriaAcomodacaoView(3);

  if (qtdCadastrados == 0) {

    cadastroAcomodacao.situacao = 1;

    printf("Não foi possivel fazer o cadastro!\n\n");

    return cadastroAcomodacao;

  } else {

    categoriaTemporaria = retornarListaController();

    do {

      printf("Digite o código da categoria valido: ");
      scanf("%d%*c", &codigoAcomodacaoTemp);

      int i;
      for (i = 0; i < qtdCadastrados; i++) {

        if (categoriaTemporaria[i].codigo == codigoAcomodacaoTemp) {

          cadastroAcomodacao.categoria = codigoAcomodacaoTemp;
        }
      }

    } while (cadastroAcomodacao.categoria == 0);

    cadastroAcomodacao.situacao = 0;

    return cadastroAcomodacao;
  }
}

/*
 * Nome: verAcomodacoesView()
 * Parâmetro¹: int contAcomodacao.
 * Return: Void
 * Author: Yuri
 * Função: Busca no controller a acomodação de acordo com o codigo lido e exibe
 * esses dados
 */
void verAcomodacoesView(int contAcomodacao) {

  int codigo, resposta;
  acomodacoes temp;

  printf("Digite o código da acomodação: ");
  scanf("%d", &codigo);

  temp = retornaAcomodacaoPorCodigoController(codigo);

  if (temp.situacao == 0) {

    printf("\n\nErro!, código inexistente!\n\n");

  } else {

    printf("\nDescrição: %s\n", temp.descricao);
    printf("\nFacilidades: %s\n", temp.facilidades);
    printf("\nCódigo: %d\n", temp.codigo);
    printf("Categoria: \n");

    informacaoCategoriaView(temp.categoria);
  }
}

/*
 * Nome: mostrarTodasAcomodacoesView()
 * Parâmetro¹: int contAcomodacao.
 * Return: Void
 * Author: Yuri
 * Função: Busca no controller a lista de acomodações e as exibe
 */
void mostrarTodasAcomodacoesView(int contAcomodacao) {

  int i = 0;
  acomodacoes *tempAcomodacoes;

  categoria *tempCategoriaAcomodacao;

  tempAcomodacoes = retornarTodasAcomodacoesController();

  tempCategoriaAcomodacao = retornarListaController();

  printf("-----------------------------------------------------------------\n");
  printf("\t\t\t\tLISTA DE ACOMODAÇÕES\n");
  printf("-----------------------------------------------------------------\n");

  for (i = 0; i < contAcomodacao; i++) {

    printf("\n%d.\n Descrição: %s\n"
           " Facilidades: %s\n"
           " Código: %d\n",
           i + 1, tempAcomodacoes[i].descricao, tempAcomodacoes[i].facilidades,
           tempAcomodacoes[i].codigo);

    printf("Categoria: \n");

    informacaoCategoriaView(tempAcomodacoes[i].categoria);
  }
}

/*
 * Nome: excluirAcomodacoesView()
 * Parâmetro¹: int cont.
 * Return: int.
 * Author: Yuri
 * Função: Verifica se existe o codigo digitado para a exclusão, se exitir o
 * exclui e avisa a função a que o chamou
 */
int excluirAcomodacoesView(int contAcomodacao) {

  int codigo, condicao, resposta;
  acomodacoes temp;
  condicao = 1;

  printf("Digite o  código da acomodação que deseja excluir: ");
  scanf("%d", &codigo);

  temp = retornaAcomodacaoPorCodigoController(codigo);

  if (temp.situacao == 0) {

    printf("\n\nErro!, código inexistente!\n\n");

  } else {

    printf("Tem certeza que deseja excluir a acomodação de códgio %d "
           "?\n1->SIM\n2->NÃO",
           temp.codigo);
    scanf("%d", &resposta);

    if (resposta == 1) {

      excluirAcomodacoesController(temp.codigo);
      condicao = 0;
    }
  }

  return condicao;
}

/*
 * Nome: alterarAcomodacaoView()
 * Parâmetro¹: int contAcomodacao.
 * Return: Struct acomodacoes
 * Author: Yuri
 * Função: Verifica se existe a acomodação informada pelo usuário, recebe novos
 * dados, caso exista, e posteriormente modifica no controller
 */
acomodacoes alterarAcomodacaoView(int contAcomodacao) {

  acomodacoes temp;

  categoria *categoriaTemporaria;

  temp.categoria = 0;

  int codigo, opc, codigoAcomodacaoTemp, qtdCadastrados;

  temp.situacao = 1;

  printf("Digite o código da acomodação que deseja alterar: ");
  scanf("%d", &codigo);

  temp = retornaAcomodacaoPorCodigoController(codigo);

  if (temp.situacao == 0) {

    printf("\n\nErro!, código inexistente!\n\n");

  } else {

    do {

      printf("/******/MENU DE ALTERAÇÃO/******/\n");
      printf("O que deseja alterar: \n"
             "1. Descrição\n"
             "2. Facilidades\n"
             "3. Categoria"
             "0. Salvar\n");

      scanf("%d", &opc);

      getchar();

      if (opc == 1) {

        printf("Digite a descrição: ");
        fgets(temp.descricao, sizeof(temp.descricao), stdin);
        toUpperCase(temp.descricao);

      } else if (opc == 2) {

        printf("Digite as facilidades: ");
        fgets(temp.facilidades, sizeof(temp.facilidades), stdin);
        toUpperCase(temp.facilidades);

      } else if (opc == 3) {

        categoriaTemporaria = retornarListaController();
        qtdCadastrados = menuCategoriaAcomodacaoView(3);

        do {

          printf("Novo código de categoria da acomodação[VALIDO]: ");
          scanf("%d%*c", &codigoAcomodacaoTemp);

          int i;
          for (i = 0; i < qtdCadastrados; i++) {

            if (categoriaTemporaria[i].codigo == codigoAcomodacaoTemp) {

              temp.categoria = codigoAcomodacaoTemp;
            }
          }

        } while (temp.categoria == 0);
      }

    } while (opc != 0);

    temp.situacao = 0;

    return temp;
  }
}
void erroExportarAcomodacao() {

  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");

}

void erroImportarAcomodacao() {

  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");

}

void inicializarContadorAcomodacao(int contador) {

 contAcomodacao = contador;

}
