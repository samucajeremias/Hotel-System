#include "../Model/basicoModel.h"


void menuTransacaoView() {
  do {
    printf("1 -> CHECK-IN\n"
           "2 -> CHECK-OUT\n"
           "3 -> SAIDA DE PRODUTOS \n"
           "4 -> CONTROLE DE CAIXA\n"
           "5 -> CONTAS A RECEBER\n"
           "6 -> ENTRADA DE PRODUTOS INDUSTRIALIZADOS\n"
           "7 -> CONTAS A PAGAR\n"
           "0 -> SAIR\n");

    scanf("%d%*c", &opcao);

    if (opcao == 1) {

      menuCheckinView();

    } else if (opcao == 2) {

      menuCheckOutView();

    } else if (opcao == 3) {
        menuSaidaProdutosView();
    } else if (opcao == 4) {

        controleDeCaixaView();

    } else if (opcao == 5) {

    } else if (opcao == 6) {

    } else if (opcao == 7) {

    } else if (opcao == 8) {

    } else if (opcao == 9) {

    } else if (opcao == 10) {

    }

  } while (opcao != 0);
}
