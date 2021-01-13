#include "Model/basicoModel.h"

//#include "Model/reservaModel.h"

int main(int argc, char **argv) {

  int opcao;

  do {
    printf("1 -> HOTEL\n"
           "2 -> CATEGORIA DE ACOMODAÇÃO\n"
           "3 -> ACOMODAÇÕES\n"
           "4 -> RESERVA\n"
           "5 -> PRODUTOS\n"
           "6 -> HOSPEDE\n"
           "7 -> FORNECEDORES\n"
           "8 -> OPERADORES DO SISTEMA\n"
           "9 -> TRANSAÇÕES\n"
           "11 -> IMPORTAÇÃO / EXPORTAÇÃO DE DADOS \n"
           "0 -> SAIR\n");

    scanf("%d%*c", &opcao);

    if (opcao == 1) {

      menuHotelView();

    } else if (opcao == 2) {

      menuCategoriaAcomodacaoView(0);

    } else if (opcao == 3) {

      menuAcomodacoesView(0);

    } else if (opcao == 4) {
        menuReservaView();

    } else if (opcao == 5) {

      menuProdutosView();

    } else if (opcao == 6) {
      menuHospedeView(0);

    } else if (opcao == 7) {

        fornecedoresView();

    } else if (opcao == 8) {
        menuFuncionarioView(0);

    } else if (opcao == 9) {
        menuTransacaoView();

    } else if (opcao == 10) {



    } else if(opcao == 11) {

        menuImportacaoExportacaoView();
    }

  } while (opcao != 0);

  return (EXIT_SUCCESS);
}
