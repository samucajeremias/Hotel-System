#include "../Model/basicoModel.h"
static saidaProdutos *gVetorVendas;
static int gQuantidadeVendasRegistradas = 0;
static int gCodigoVendas = 1;
static int gTamanhoVetorVendas;

int salvaVendasController(saidaProdutos pVendas) {
  int verificador = 0;

  if (gQuantidadeVendasRegistradas == 0) {

    gVetorVendas = malloc(TAMANHO * sizeof(saidaProdutos));

    gTamanhoVetorVendas = TAMANHO;

  } else if (gTamanhoVetorVendas == gQuantidadeVendasRegistradas) {

    gTamanhoVetorVendas++;
    gVetorVendas = realloc(gVetorVendas, gTamanhoVetorVendas * sizeof(saidaProdutos));
  }

  pVendas.codigoSaidaProduto = gCodigoVendas;

  gCodigoVendas++;

  gVetorVendas[gQuantidadeVendasRegistradas] = pVendas;

  gQuantidadeVendasRegistradas++;

  verificador = 1;

  return verificador;
}


saidaProdutos *retornaTodasVendasController(){
  return gVetorVendas;
}

int retornaVendasRegistradas() {

  return gQuantidadeVendasRegistradas; //Quantidade registrada
}

saidaProdutos retornaVendaPorCodigo(int pCodigo) {
  int i, posicao;

  for(i = 0; i < gTamanhoVetorVendas; i++){

    if(pCodigo == gVetorVendas[i].codigoSaidaProduto) {

      posicao = i;

    }

  }
  return gVetorVendas[posicao];
}

void notaFiscalController(saidaProdutos pVendas){

  int p;

  produtos receberProduto;

  FILE *notaFiscal;

  notaFiscal = fopen("notaFiscal.txt", "w");

  if(notaFiscal == NULL) {

    erroExportarNotaFiscal();
    exit(1);

  }

  fprintf(notaFiscal, "CODIGO HOSPEDE: %d\nTOTAL: %f\n\n\n", pVendas.codigoHospede, pVendas.total);

  for ( p = 0; p < pVendas.carrinho.contadorItem; p++) {
      receberProduto = retornaPorCodigo(pVendas.carrinho.codigoProduto[p]);
      fprintf(notaFiscal, "CODIGO PRODUTO: %d\n", pVendas.carrinho.codigoProduto[p]);
      fprintf(notaFiscal, "PRODUTO: %s", receberProduto.descricao);
      fprintf(notaFiscal, "QUANTIDADE %d:\n", pVendas.carrinho.quantidade[p]);
      fprintf(notaFiscal, "TOTAL R$ %.2f\n\n", pVendas.total);
  }

  fprintf(notaFiscal, "ASSINATURA:_____________________________________________________________\n\n\n");

    int fflush(FILE *notaFiscal);
    fclose(notaFiscal);
}

void exportarVendasController() {

  FILE *arquivoVendas;


  arquivoVendas = fopen("arquivoVendas.bin", "wb");


  if(arquivoVendas == NULL) {

    erroExportarVendasView();
    exit(1);
  }



  fwrite(&gQuantidadeVendasRegistradas, sizeof(int), 1, arquivoVendas);
  fwrite(gVetorVendas, sizeof(saidaProdutos), gQuantidadeVendasRegistradas, arquivoVendas);


  int fflush(FILE * arquivoVendas);

  fclose(arquivoVendas);

}



void importarVendasController() {

    FILE *arquivoVendas;

    arquivoVendas = fopen("arquivoVendas.bin", "rb");

    if (!arquivoVendas) {
        erroImportarVendasView();
        exit(1);
    }

    fread(&gQuantidadeVendasRegistradas, sizeof(int), 1,arquivoVendas);

    gVetorVendas = malloc(gQuantidadeVendasRegistradas * sizeof(saidaProdutos));

    gTamanhoVetorVendas = gQuantidadeVendasRegistradas;

    inicializarContadoresView(gQuantidadeVendasRegistradas);

    gCodigoVendas = gQuantidadeVendasRegistradas + 1;

    fread(gVetorVendas, sizeof(saidaProdutos), gQuantidadeVendasRegistradas,arquivoVendas);

    fclose(arquivoVendas);
}
