#include "../Model/acomodacoesModel.h"
#include "../Model/categoriaAcomodacaoModel.h"

// Variaveis Globais:
acomodacoes *gVetorAcomodacoes;
int gTamVetorAcomodacoes = 0, gQuantidadeAcomodacaoCadastrado = 0;

/*
 * Nome: recebeAcomodacaoController
 * Parâmetro¹: struct acomodacoes acomodacaoTemporaria, int cont.
 * Return: void
 * Author: Yuri
 * Função: recebe a acomodação do view e a salva.
 */

void recebeAcomodacaoController(acomodacoes acomodacaoTemporaria, int cont) {

  if (cont == 0) {

    gVetorAcomodacoes = malloc(TAMANHO * sizeof(acomodacoes));

    gTamVetorAcomodacoes = TAMANHO;

  } else if (cont == gTamVetorAcomodacoes) {

    gTamVetorAcomodacoes = gTamVetorAcomodacoes + TAMANHO;

    gVetorAcomodacoes =
        realloc(gVetorAcomodacoes, gTamVetorAcomodacoes * sizeof(acomodacoes));
  }

  gVetorAcomodacoes[cont].categoria = acomodacaoTemporaria.categoria;
  gVetorAcomodacoes[cont].codigo = acomodacaoTemporaria.codigo;
  strcpy(gVetorAcomodacoes[cont].descricao, acomodacaoTemporaria.descricao);
  strcpy(gVetorAcomodacoes[cont].facilidades, acomodacaoTemporaria.facilidades);
  gQuantidadeAcomodacaoCadastrado++;
}

/*
 * Nome: ExcluirAcomodacaoController
 * Parâmetro¹: int pCodigo.
 * Return: void
 * Author: Yuri
 * Função: recebe a acomodação enviada pelo view de acordo com o código e faz a
 exclusao.
 */

void excluirAcomodacoesController(int pCodigo) {

  int posicao;
  acomodacoes auxTemp;

  for (int i = 0; i < gTamVetorAcomodacoes; i++) {

    if (pCodigo == gVetorAcomodacoes[i].codigo) {
      posicao = i;
    }
  }

  if (gTamVetorAcomodacoes == 1) {

    gTamVetorAcomodacoes--;
    free(gVetorAcomodacoes);

  } else {

    gVetorAcomodacoes[posicao] = gVetorAcomodacoes[gTamVetorAcomodacoes - 1];
    gTamVetorAcomodacoes = gTamVetorAcomodacoes - 1;
    gVetorAcomodacoes =
        realloc(gVetorAcomodacoes, gTamVetorAcomodacoes * sizeof(acomodacoes));
  }
}
/*
 * Nome: retornarTodasAcomodacoesController
 * Parâmetro¹: void.
 * Return: void
 * Author: Yuri
 * Função: Manda a lista de acomodaçoes cadastradas.
 */
acomodacoes *retornarTodasAcomodacoesController() {
   return gVetorAcomodacoes; }

   /*
    * Nome: atualizarAcomodacoesController
    * Parâmetro¹: struct acomodacoes temp.
    * Return: void
    * Author: Yuri
    * Função: Altera os dados da acomodação desejada de acordo com o código.
    */

void atualizarAcomodacoesController(acomodacoes temp) {

  int posicao;

  for (int i = 0; i < gTamVetorAcomodacoes; i++) {

    if (temp.codigo == gVetorAcomodacoes[i].codigo) {
      posicao = i;
    }
  }

  gVetorAcomodacoes[posicao] = temp;
}

/*
 * Nome: retornaAcomodacaoPorCodigoController
 * Parâmetro¹: int pCodigo.
 * Return: struct acomodacoes
 * Author: Yuri
 * Função: Retorna a acomodação de acordo com o código digitado.
 */

acomodacoes retornaAcomodacaoPorCodigoController(int pCodigo) {
  int posicao, i;

  for (i= 0; i < gTamVetorAcomodacoes; i++) {

    gVetorAcomodacoes[i].situacao = 0;

    if (pCodigo == gVetorAcomodacoes[i].codigo) {
      gVetorAcomodacoes[i].situacao = 1;
      posicao = i;
      return gVetorAcomodacoes[posicao];
    }
  }

  return gVetorAcomodacoes[i];
}

/*
 * Nome: retornaQuantidadeAcomodacao
 * Parâmetro¹: void.
 * Return: int
 * Author: Yuri
 * Função: Retorna a quantidade de acomodaçoes cadastradas.
 */

int retornaQuantidadeAcomodacao() {

  return gQuantidadeAcomodacaoCadastrado;
}

void importarAcomodacaoController() {

  FILE *arquivoAcomodacao;
  arquivoAcomodacao = fopen("arquivoAcomodacao.bin", "rb");

  if (!arquivoAcomodacao) {
      erroImportarAcomodacao();
      exit(1);
  }

  fread(&gTamVetorAcomodacoes, sizeof(int), 1, arquivoAcomodacao);


  gVetorAcomodacoes = malloc(gTamVetorAcomodacoes*sizeof(acomodacoes));

  inicializarContadorAcomodacao(gTamVetorAcomodacoes);

  fread(gVetorAcomodacoes, sizeof(acomodacoes), gTamVetorAcomodacoes, arquivoAcomodacao);

  gQuantidadeAcomodacaoCadastrado = gTamVetorAcomodacoes;

  fclose(arquivoAcomodacao);

}

void exportarAcomodacaoController(){

  FILE *arquivoAcomodacao;

  arquivoAcomodacao = fopen("arquivoAcomodacao.bin", "wb");

    if (!arquivoAcomodacao) {
        erroExportarAcomodacao();
        exit(1);
    }

  fwrite(&gTamVetorAcomodacoes, sizeof(int), 1, arquivoAcomodacao);


  fwrite(gVetorAcomodacoes, sizeof(acomodacoes), gTamVetorAcomodacoes, arquivoAcomodacao);


  int fflush(FILE *arquivoAcomodacao);
  fclose(arquivoAcomodacao);

}
