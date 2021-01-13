#include "../Model/basicoModel.h"

static int gContadorVendas;

void menuSaidaProdutosView() {

  int opcao;

  do {

    printf(
        "------------------------------------------------------------------\n"
        "\t\t\t\tMENU \n"
        "------------------------------------------------------------------\n"
        "1 -> REGISTRAR UMA VENDA \n"
        "2 -> LISTAR VENDAS\n"
        "3 -> BUSCAR VENDA\n"
        "0 -> [Sair] \n\n\n");

    scanf("%d%*c", &opcao);

    switch (opcao) {

    case 0:
      // Sair do programa
      break;

    case 1:

      cadastrarVendaView();

      break;

    case 2:

      listarVendas();

      break;

    case 3:

      break;
    }

  } while (opcao != 0);
}

void cadastrarVendaView() {

  int codigoHospede;
  produtos *listaProdutos; // Receber a lista de produtos cadastrados
  produtos receberProduto;
  int quantidadeProdutosRegistrados = 0, quantidadeProdutoTemp;
  int p, i; // usar no for(repeticao)
  int codigoProdutoTemp, contadorItensVenda = 0, resultado = 0;

  saidaProdutos registroVendaTemp;

  // Verifica se hospede esta registrado
  codigoHospede = buscarHospedeView();

  if (codigoHospede == 0) { // Nao esta cadastrado
    printf("Hospede nao cadastrado\n");

  } else { // Existe e pode seguir com a venda

  /*Verifica se o hospede realizou o check-in*/


    listaProdutos = retornarProdutoController(); // Recebendo todos os produtos
    quantidadeProdutosRegistrados = retornaQuantidadeProdutos();

    contadorItensVenda = 0; //Zerando a lista de compras
    registroVendaTemp.total = 0;
    system("clear");
    if (quantidadeProdutosRegistrados > 0) {
        for (p = 0; p < quantidadeProdutosRegistrados; p++) {

          printf("------------------------------------------------------------\n");
          printf("\t\tLISTA DE PRODUTOS\n");
          printf("------------------------------------------------------------\n");

          for (i = 0; i < quantidadeProdutosRegistrados; i++) {

            printf("Produto: %s", listaProdutos[i].descricao);
            printf("Código do produto: %d\n", listaProdutos[i].codigo);
            printf("Preço de Venda: %.2f\n\n", listaProdutos[i].precoDeVenda);

          }
        }

        do {

            printf("ZERO PARA FINALIZAR\n" );

            printf("CÓDIGO DO PRODUTO: \n" );
            scanf("%d%*c", &codigoProdutoTemp);

            if (codigoProdutoTemp == 0) {
                break;
            } else {

                estoque_excedido:
                printf("QUANTIDADE:\n");
                scanf("%d%*c", &quantidadeProdutoTemp);

                receberProduto = retornaPorCodigo(codigoProdutoTemp);

                if (receberProduto.estoque < quantidadeProdutoTemp) {
                    printf("NAO TEMOS ESSA QUANTIA EM ESTOQUE\n" );
                    goto estoque_excedido;
                }

                registroVendaTemp.carrinho.codigoProduto[contadorItensVenda] = codigoProdutoTemp;
                registroVendaTemp.carrinho.quantidade[contadorItensVenda] = quantidadeProdutoTemp;
                registroVendaTemp.total = registroVendaTemp.total + (receberProduto.precoDeVenda * quantidadeProdutoTemp);
                contadorItensVenda++;
            }


        } while(codigoProdutoTemp != 0);

        registroVendaTemp.carrinho.contadorItem = contadorItensVenda;
        registroVendaTemp.codigoHospede = quantidadeProdutoTemp;

        //Recebendo a forma de pagamento 0-> anotar 1-> a vista
        printf("FORMA DE PAGAMENTO \n0->ANOTAR\n1->A VISTA\n");
        scanf("%d%*c", &registroVendaTemp.formaDePagamento);

        if (registroVendaTemp.formaDePagamento == 0) { //Anotar a conta
            /*GERAR NOTA PARA ASSINAR*/
            notaFiscalController(registroVendaTemp);

            /*ADICIONANDO O VALOR NA CONTA DO HOSPEDE*/
            receberContasHospedeController(registroVendaTemp.total, registroVendaTemp.codigoHospede);

            /* COLOCAR EM CONTAS A RECEBE */

        } else { // Pagar a vista

            /*Enviando o valor compra para o caixa*/
            printf("entrou no caixa\n" );
            registrarLancamentoController("VENDA", registroVendaTemp.total);
            printf("saiu do caixa\n" );

        }

        resultado = salvaVendasController(registroVendaTemp);

        if (resultado == 1) {
            printf("VENDA REALIZADA COM SUCESSO!!\n" );

            atualizarEstoqueController(registroVendaTemp);

        }else{
            printf("ERRO AO REALIZAR VENDA\n" );
        }


    } else {

        printf("Não existe produtos registrados do sistema\n" );

    }

  }
}
  void listarVendas() {
      int quantidadeVendasRegistradas, i, p;
      saidaProdutos *listaVendasTemp;
      produtos receberProduto;
      hospede hospedeTemp;
      listaVendasTemp = retornaTodasVendasController();

      quantidadeVendasRegistradas = retornaVendasRegistradas();

      if (quantidadeVendasRegistradas > 0) {
          printf("------------------------------------------------------------\n");
          printf("\t\tLISTA DE VENDAS\n");
          printf("------------------------------------------------------------\n");


          for (i = 0; i < quantidadeVendasRegistradas; i++) {
              hospedeTemp = buscarHospedeController(listaVendasTemp[i].codigoHospede);
              printf("HOSPEDE: %s", hospedeTemp.nome);
              for ( p = 0; p < listaVendasTemp[i].carrinho.contadorItem; p++) {
                  receberProduto = retornaPorCodigo(listaVendasTemp[i].carrinho.codigoProduto[p]);
                  printf("CODIGO PRODUTO: %d\n", listaVendasTemp[i].carrinho.codigoProduto[p]);
                  printf("PRODUTO: %s", receberProduto.descricao);
                  printf("QUANTIDADE: %d\n", listaVendasTemp[i].carrinho.quantidade[p]);
              }
              printf("TOTAL R$ %.2f\n\n\n", listaVendasTemp[i].total);
          }
      }

  }

void erroExportarNotaFiscal() {

  printf("ERRO AO CRIAR ARQUIVO DE TEXTO\n");

}
void erroExportarVendasView() {

  printf("ERRO AO CRIAR ARQUIVO DE TEXTO\n");
}

void inicializarContadoresView(int pContador) {

  gContadorVendas = pContador;


}

void erroImportarVendasView() {

    printf("ERRO AO IMPORTAR ARQUIVO BINARIO DE VENDAS\n");

}
