#include"../Model/basicoModel.h"

static int gQuantidadeLancamentos = 0, gQuantidadeRetiradas = 0;
static int gTamanhoVetorLancamento = TAMANHO, gTamanhoVetorRetirada = TAMANHO;
static int gCodigoLancamento = 1, gCodigoRetirada = 1;

static lancamento *gVetorLancamentos;
static retirada *gVetorRetirada;
static caixa gCaixa;


/*
 * Nome: registrarLancamentoController()
 * Parâmetro: float pValor
 * Return: Void
 * Author: João Geraldo
 * Função: Recebe um valor e uma string com a origem por parâmetro e adiciona no caixa
*/
void registrarLancamentoController(char *pOrigem , float pValor) {


    if (gQuantidadeLancamentos == 0) {


      gVetorLancamentos = malloc(gTamanhoVetorLancamento * sizeof(lancamento));

    } else if(gQuantidadeLancamentos == gTamanhoVetorLancamento) {


        gTamanhoVetorLancamento ++;
        gVetorLancamentos = realloc(gVetorLancamentos, gTamanhoVetorLancamento * sizeof(lancamento));
    }

    gVetorLancamentos[gQuantidadeLancamentos].codigoPagamento = gCodigoLancamento;
    gVetorLancamentos[gQuantidadeLancamentos].valorPagamento = pValor;
    strcpy(gVetorLancamentos[gQuantidadeLancamentos].origem, pOrigem);
    gCaixa.totalEmCaixa = pValor + gCaixa.totalEmCaixa;
    gCodigoLancamento ++;
    gQuantidadeLancamentos ++;

}

lancamento* retornaListaLancamentosController() {
    return gVetorLancamentos;
}

int retornarQuantidadeLancamentos() {
    return gQuantidadeLancamentos;
}


void registrarRetiradaController(char *pOrigem, float pValor) {

  if (gQuantidadeRetiradas == 0) {

    gVetorRetirada = malloc(gTamanhoVetorRetirada * sizeof(retirada));

  } else if(gTamanhoVetorRetirada == gQuantidadeRetiradas) {

    gTamanhoVetorRetirada = TAMANHO + gTamanhoVetorRetirada;

    gVetorRetirada = realloc(gVetorRetirada, gTamanhoVetorRetirada * sizeof(retirada));
  }

  gVetorRetirada[gQuantidadeRetiradas].codigoRetirada = gCodigoRetirada;
  gVetorRetirada[gQuantidadeRetiradas].valorRetirada = pValor;
  strcpy(gVetorRetirada[gQuantidadeRetiradas].origem, pOrigem);


  gCaixa.totalEmCaixa -= pValor;
  gQuantidadeRetiradas++;
  gCodigoRetirada++;

}
int retornaQuantidadeRetirada(){

  return gQuantidadeRetiradas;

}

retirada* retornaListaRetiradaController() {
    return gVetorRetirada;
}

caixa retornaCaixaController() {

  return gCaixa;

}


void exportarRetiradaController() {

  FILE *arquivoRetirada;

  arquivoRetirada = fopen("arquivoRetirada.bin", "wb");

  if (!arquivoRetirada) {
      erroExportarRetiradaView();
      exit(1);
  }

  fwrite(&gQuantidadeRetiradas, sizeof(int), 1, arquivoRetirada);
  fwrite(gVetorRetirada, sizeof(retirada), gQuantidadeRetiradas, arquivoRetirada);


  int fflush(FILE *arquivoRetirada);
  fclose(arquivoRetirada);


}

void importarRetiradaController(){

  FILE *arquivoRetirada;

  arquivoRetirada = fopen("arquivoRetirada.bin", "rb");

  if (!arquivoRetirada) {
      erroImportarRetiradaView();
      exit(1);
  }

  fread(&gQuantidadeRetiradas, sizeof(int), 1, arquivoRetirada);

  gVetorRetirada = malloc(gQuantidadeRetiradas * sizeof(retirada));

  gTamanhoVetorRetirada = gQuantidadeRetiradas;

  gCodigoRetirada = gQuantidadeRetiradas + 1;


  fread(gVetorRetirada, sizeof(retirada), gQuantidadeRetiradas, arquivoRetirada);


  fclose(arquivoRetirada);

}


/*----------------------------------------------------------------------------*/
/*                             EXPORTAR LANÇAMENTOS                            */
/*----------------------------------------------------------------------------*/

/*
 * Nome: ()
 * Parâmetro:
 * Return:
 * Author: João Geraldo
 * Função:
*/
void exportarLancamentoBinController(){
    FILE *arquivoLancamento;
    arquivoLancamento = fopen("arquivoLancamento.bin", "wb");

    if (!arquivoLancamento) {
        erroExportarLancamentoView();
        exit(1);
    }

    fwrite(&gQuantidadeLancamentos, sizeof(int), 1, arquivoLancamento);

    fwrite(gVetorLancamentos, sizeof(lancamento), gQuantidadeLancamentos, arquivoLancamento);
    int fflush(FILE *arquivoLancamento);
    fclose(arquivoLancamento);


}

void importarLancamentoBinController() {
    FILE *arquivoLancamento;
    arquivoLancamento = fopen("arquivoLancamento.bin", "rb");

    if (!arquivoLancamento) {
        erroImportarLancamentoView();
        exit(1);
    }

    fread(&gQuantidadeLancamentos, sizeof(int), 1, arquivoLancamento);

    gVetorLancamentos = malloc(gQuantidadeLancamentos * sizeof(lancamento));

    fread(gVetorLancamentos, sizeof(lancamento), gQuantidadeLancamentos, arquivoLancamento);

    gCodigoLancamento = gQuantidadeLancamentos + 1;
    gTamanhoVetorLancamento = gQuantidadeLancamentos;
    fclose(arquivoLancamento);
}





void exportarCaixaController() {

  FILE *arquivoCaixa;

  arquivoCaixa = fopen("arquivoCaixa.bin", "wb");

  if (!arquivoCaixa) {
      erroExportarCaixaView();
      exit(1);
  }

  fwrite(&gCaixa, sizeof(caixa), 1, arquivoCaixa);


  int fflush(FILE *arquivoCaixa);
  fclose(arquivoCaixa);


}

void importarCaixaController(){

  FILE *arquivoCaixa;

  arquivoCaixa = fopen("arquivoCaixa.bin", "rb");

  if (!arquivoCaixa) {
      erroImportarCaixaView();
      exit(1);
  }

  fread(&gCaixa, sizeof(caixa), 1, arquivoCaixa);

  fclose(arquivoCaixa);

}
