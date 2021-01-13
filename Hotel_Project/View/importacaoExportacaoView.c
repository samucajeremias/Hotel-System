#include "../Model/basicoModel.h"

void menuImportacaoExportacaoView() {

  int opc, opcao2;

  do {
    printf("********MENU********\n\n");
    printf("Escolha a Opção: \n");
    printf("1-> [IMPORTAR]\n");
    printf("2->[EXPORTAR]\n");
    printf("0->[SAIR]\n");
    scanf("%d", &opc);

    if (opc == 1) {

      do {

        printf("{$$$$$$IMPORTAÇÂO DE DADOS$$$$$$}\n\n");
        printf("Quais dados deseja importar: \n");
        printf("1. Acomodação\n");
        printf("2. Categoria de Acomodação\n");
        printf("3. Fornecedores\n");
        printf("4. Hóspede\n");
        printf("5. Hotel\n");
        printf("6. Operadores do Sistema\n");
        printf("7. Produtos\n");
        printf("8. Reserva\n");
        printf("9. Check-in\n");
        printf("10 Controle de caixa\n" );
        printf("11. Todos\n");
        printf("0. Sair\n");

        scanf("%d", &opcao2);

        switch (opcao2) {

        case 1:

          importarAcomodacaoController();

          printf("Importado com sucesso!\n");

          break;

        case 2:

          importarCategoriaAcomodacaoController();
          printf("Importado com sucesso!\n");

          break;

        case 3:

          importarFornecedoresController();
          printf("Importado com sucesso!\n");

          break;

        case 4:
          importarHospedeBinarioController();
          printf("Importado com sucesso!\n");
          break;

        case 5:
          importarHotelController();
          printf("Importado com sucesso!\n");
          break;

        case 6:
          importarOperadoresBinarioController();
          printf("Importado com sucesso!\n");
          break;
        case 7:
          importarProdutoController();
          printf("Importado com sucesso!\n");
          break;

        case 8:
          importarReservaController();
          printf("Importado com sucesso!\n");
          break;

        case 9:
          importarCheckinController();
          printf("Importado com sucesso!\n");
          break;

          case 10:
            importarLancamentoBinController();
            importarRetiradaController();
            importarCaixaController();
            printf("Importado com sucesso!\n");

          break;
        case 11:

          importarAcomodacaoController();
          importarCategoriaAcomodacaoController();
          importarFornecedoresController();
          importarHospedeBinarioController();
          importarHotelController();
          importarOperadoresBinarioController();
          importarProdutoController();
          importarReservaController();
          importarCheckinController();
          importarLancamentoBinController();
          importarRetiradaController();
          importarCaixaController();
          importarVendasController();
         // importarCheckOutController();
          printf("Importado com sucesso!\n");

          break;
        }

      } while (opcao2 != 0);

    } else if (opc == 2) {

      do {

        printf("{$$$$$$EXPORTAÇÃO DE DADOS$$$$$$}\n\n");
        printf("Quais dados deseja exportar: \n");
        printf("1. Acomodação\n");
        printf("2. Categoria de Acomodação\n");
        printf("3. Fornecedores\n");
        printf("4. Hóspede\n");
        printf("5. Hotel\n");
        printf("6. Operadores do Sistema\n");
        printf("7. Produtos\n");
        printf("8. Reserva\n");
        printf("9. Check-in\n");
        printf("10 Controle de caixa\n" );
        printf("11. Todos\n");
        printf("0. Sair\n");

        scanf("%d", &opcao2);

        switch (opcao2) {
        case 1:

          exportarAcomodacaoController();
          printf("Exportado com sucesso!\n");

          break;

        case 2:

          exportarCategoriaAcomodacaoController();
          printf("Exportado com sucesso!\n");

          break;

        case 3:

          exportarFornecedoresController();
          printf("Exportado com sucesso!\n");

          break;

        case 4:
          exportarHospedeBinarioController();
          printf("Exportado com sucesso!\n");
          break;

        case 5:
          exportarHotelController();
          printf("Exportado com sucesso!\n");
          break;

        case 6:
          exportarOperadoresBinarioController();
          printf("Exportado com sucesso!\n");
          break;
        case 7:
          exportarProdutoController();
          printf("Exportado com sucesso!\n");
          break;

        case 8:
          exportarReservaController();
          printf("Exportado com sucesso!\n");
          break;

        case 9:
            exportarCheckinController();
            printf("Exportado com sucesso!\n");
          break;

          case 10:
            exportarLancamentoBinController();
            exportarRetiradaController();
            exportarCaixaController();
            printf("Exportado com sucesso!\n");
          break;
        case 11:
          exportarAcomodacaoController();
          exportarCategoriaAcomodacaoController();
          exportarFornecedoresController();
          exportarHospedeBinarioController();
          exportarHotelController();
          exportarOperadoresBinarioController();
          exportarProdutoController();
          exportarReservaController();
          exportarCheckinController();
          exportarLancamentoBinController();
          exportarRetiradaController();
          exportarCaixaController();
          exportarVendasController();
          exportarCheckOutController();
          printf("Exportado com sucesso!\n");

          break;
        }

      } while (opcao2 != 0);
    }

  } while (opc != 0);
}
