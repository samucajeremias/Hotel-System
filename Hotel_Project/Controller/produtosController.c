#include "../Model/produdosModel.h"
#include "../Model/basicoModel.h"


static produtos *gVetorProdutos;
static int tamVetorProdutos = 0;
static int gQtdProdutosRegistrados = 0;

/*
 * Nome: cadastrarProdutosController
 * Parâmetro¹: struct produtos temp, int contCadastro.
 * Return: Void
 * Author: Yuri
 * Função: Salva o produto cadastrado no view.
 */

void cadastrarProdutosController(produtos temp, int contCadastro) {

    if (contCadastro == 0) {

        gVetorProdutos = malloc(TAMANHO*sizeof(produtos));

        tamVetorProdutos = TAMANHO;
        gQtdProdutosRegistrados++;

    } else if (tamVetorProdutos == contCadastro) {

        tamVetorProdutos = tamVetorProdutos + TAMANHO;
        gQtdProdutosRegistrados++;

        gVetorProdutos = realloc(gVetorProdutos, tamVetorProdutos*sizeof(produtos));

    }

    gVetorProdutos[contCadastro] = temp;


}

/*
 * Nome: retornarProdutosController
 * Parâmetro¹: void.
 * Return: struct produtos*
 * Author: Yuri
 * Função: retorna o vetor de produtos cadastrados.
 */


produtos* retornarProdutoController() {

    return gVetorProdutos;

}

/*
 * Nome: retornaPorCodigoController
 * Parâmetro¹: int codigo, int contCadastro.
 * Return: struct produtos
 * Author: Yuri
 * Função: retorna o vetor de acordo com o codigo digitado.
 */


produtos retornarPorCodigoController(int codigo, int contCadastro) {

    int i;
    produtos temp;


    for(i = 0; i < contCadastro; i++) {

        if (gVetorProdutos[i].codigo == codigo) {

            temp = gVetorProdutos[i];

            i = contCadastro + 1;

        } else {

            temp.codigo = -1;

        }

    }

    return temp;



}
/*
 * Nome: alterarProdutosController()
 * Parâmetro¹: struct produtos auxTemp, int codigo e int
 * Return: Void
 * Author: Yuri
 * Função: Recebe o código do produto que será excluido, se ele existir, será
 * deletado
 */
void alterarProdutosController(produtos auxTemp, int contCadastro) {

    int i;

    for(i = 0; i < contCadastro; i++) {

        if (gVetorProdutos[i].codigo == auxTemp.codigo) {

            gVetorProdutos[i] = auxTemp;

        }

    }


}

/*
 * Nome:excluirProdutosController
 * Parâmetro¹: int codigo, int contCadastro.
 * Return: int
 * Author: Yuri
 * Função: Exclui um produto de acordo com o código.
 */


int excluirProdutosController(int codigo, int contCadastro) {

    int i, condicao;
    produtos temp;

    temp = gVetorProdutos[contCadastro - 1];

    for(i = 0; i < contCadastro; i++) {

        if (gVetorProdutos[i].codigo == codigo) {

            gVetorProdutos[i] = temp;



            if(tamVetorProdutos == 1) {

                tamVetorProdutos--;
                free(gVetorProdutos);
                condicao = 1;
                i = contCadastro;


            } else {

                tamVetorProdutos = tamVetorProdutos - TAMANHO;

                gVetorProdutos = realloc(gVetorProdutos, tamVetorProdutos*sizeof(produtos));

                condicao = 1;

                i = contCadastro;
            }


        } else {

            condicao = 0;

        }

    }


    return condicao;

}

int retornaQuantidadeProdutos() {


  return gQtdProdutosRegistrados;
}


void importarProdutoController(){

  FILE *arquivoProdutos;

  arquivoProdutos = fopen("arquivoProdutos.bin", "rb");

  if (!arquivoProdutos) {

      erroImportarProdutos();
      exit(1);
  }

  fread(&tamVetorProdutos, sizeof(int), 1, arquivoProdutos);

  importarProdutoBinarioView(tamVetorProdutos);

  gVetorProdutos = malloc(tamVetorProdutos*sizeof(produtos));
  gQtdProdutosRegistrados = tamVetorProdutos;
  fread(gVetorProdutos, sizeof(produtos), tamVetorProdutos, arquivoProdutos);
  fclose(arquivoProdutos);

}

void exportarProdutoController(){

  FILE *arquivoProdutos;

  arquivoProdutos = fopen("arquivoProdutos.bin", "wb");

  if (!arquivoProdutos) {

      erroExportarProdutos();
      exit(1);
  }

  fwrite(&tamVetorProdutos, sizeof(int), 1, arquivoProdutos);

  importarProdutoBinarioView(tamVetorProdutos);

  fwrite(gVetorProdutos, sizeof(produtos), tamVetorProdutos, arquivoProdutos);
  int fflush(FILE *arquivoProdutos);
  fclose(arquivoProdutos);

}

void atualizarEstoqueController(saidaProdutos pVenda) {

    int i, k;

    for ( i = 0; i < pVenda.carrinho.contadorItem; i++) { //Percorre os itens vendidos

        for ( k = 0; k < gQtdProdutosRegistrados; k++) { //Percorre o vetor de produtos registrados

            if (pVenda.carrinho.codigoProduto[i] == gVetorProdutos[k].codigo) {
                gVetorProdutos[k].estoque -= pVenda.carrinho.quantidade[i];
            }

        }

    }
}
produtos retornaPorCodigo(int pCodigo){

  int i, posicao;

  for(i = 0; i < tamVetorProdutos; i++) {

    if(pCodigo == gVetorProdutos[i].codigo) {

      posicao = i;

    }

  }

  return gVetorProdutos[posicao];

}
