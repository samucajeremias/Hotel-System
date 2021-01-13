#include "../Model/basicoModel.h"

void controleDeCaixaView() {

    int opcao;

  do {


    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("@\t          CONTROLE DE CAIXA              @\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n");

    printf("1 -> Saldo\n"
           "2 -> Lançamentos\n"
           "3 -> Retirada\n"
           "0 -> [Sair]\n");

    scanf("%d%*c", &opcao);

    switch (opcao) {

    case 1:

      consultaSaldoView();
      break;

    case 2:

      verLancamentosView();
      break;

    case 3:

      verRetiradaView();
      break;
    }
  } while (opcao != 0);
}

void verLancamentosView() {
  lancamento *temp;
  int i, contadorRegistros = 0;

  contadorRegistros = retornarQuantidadeLancamentos();
  if (contadorRegistros > 0) {

    printf("--------------------------------------------------\n");
    printf("\t\t\tLANCAMENTOS\n");
    printf("--------------------------------------------------\n");

  } else {
    printf("Não há lancamentos ainda \n");
  }

  temp = retornaListaLancamentosController();

  for (i = 0; i < contadorRegistros; i++) {

    printf("%dº ", i + 1);
    printf("CÓDIGO DO PAGAMENTO: %d\nVALOR DO PAGAMENTO %.2f\nORIGEM: %s\n\n",
           temp[i].codigoPagamento, temp[i].valorPagamento, temp[i].origem);
  }
}

void verRetiradaView() {

  retirada *temp;
  int i, quantidadeRetirada;

  quantidadeRetirada = retornaQuantidadeRetirada();

  if (quantidadeRetirada > 0) {

    printf("--------------------------------------------------\n");
    printf("\t\t RETIRADAS\n");
    printf("--------------------------------------------------\n");

  } else {
    printf("Não há retiradas ainda \n");
  }

  temp = retornaListaRetiradaController();

  for (i = 0; i < quantidadeRetirada; i++) {

    printf("%dº \n", i + 1);
    printf("CÓDIGO DA RETIRADA: %d\nVALOR DA RETIRADA %f\nORIGEM: %s\n",
           temp[i].codigoRetirada, temp[i].valorRetirada, temp[i].origem);
  }
}

void consultaSaldoView() {

  caixa saldo;

  saldo = retornaCaixaController();

  printf("Saldo: %.2f\n", saldo.totalEmCaixa);
}
void erroExportarRetiradaView() {

  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");
}

void erroExportarCaixaView() {
  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");
}
void erroImportarRetiradaView() {

  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");
}

void erroImportarCaixaView() {
  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");
}

void erroExportarLancamentoView() {
  printf("PROBLEMA NA CRIACAO DO ARQUIVO LANCAMENTO BINÁRIO\n");
}

void erroImportarLancamentoView() {
  printf("PROBLEMA NA LEITURA DO ARQUIVO LANCAMENTO BINÁRIO\n");
}
