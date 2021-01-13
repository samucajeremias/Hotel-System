#include "../Model/categoriaAcomodacaoModel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

categoria *gVetorCategoriaAcomodacao;
int gTamVetorCatAcomodacao = TAMANHO;
int gQtdAcomodacoes = 0;
int gCodigoCategoriaAcomodacao = 1;

/*
 * Nome: salvarCategoriaAcomodacaoController
 * Parâmetro: categoria registro, int contador
 * Return: int
 * Author: Igor Jeremias
 * Função: Salva categorias de acomodação registradas
 */

int salvarCategoriaAcomodacaoController(categoria registro, int contador) {

  if (contador == 0) {
    gVetorCategoriaAcomodacao = malloc(TAMANHO * sizeof(categoria));

  } else if (gTamVetorCatAcomodacao == gQtdAcomodacoes) {

    gTamVetorCatAcomodacao++;
    gVetorCategoriaAcomodacao = realloc(gVetorCategoriaAcomodacao, gTamVetorCatAcomodacao * sizeof(categoria));
  }

  strcpy(gVetorCategoriaAcomodacao[gQtdAcomodacoes].descricao,
         registro.descricao);
  gVetorCategoriaAcomodacao[gQtdAcomodacoes].adultos = registro.adultos;
  gVetorCategoriaAcomodacao[gQtdAcomodacoes].criancas = registro.criancas;
  gVetorCategoriaAcomodacao[gQtdAcomodacoes].precoDiaria = registro.precoDiaria;
  gVetorCategoriaAcomodacao[gQtdAcomodacoes].codigo =
      gCodigoCategoriaAcomodacao;
  gCodigoCategoriaAcomodacao++;
  gQtdAcomodacoes++;

  // Cadastro bem-sucedido.
  return 0;
}

/*
 * Nome: retornarListaController
 * Parâmetro: -
 * Return: categoria*
 * Author: Igor Jeremias
 * Função: Retornar lista de acomodações
 */

categoria *retornarListaController() {
    return gVetorCategoriaAcomodacao;
}

/*
 * Nome: informacaoCategoriaController
 * Parâmetro: int codigo, int *achou
 * Return: categoria
 * Author: Igor Jeremias
 * Função: Verifica se há uma categoria com o código digitado e a retorna
 */

categoria informacaoCategoriaController(int codigo, int *achou) {

  int i, i2;

  for (i = 0; i < gQtdAcomodacoes; i++) {
    if (codigo == gVetorCategoriaAcomodacao[i].codigo) {
      *achou = 1;
      i2 = i;
    }
  }
  if (*achou == 1) {
    return gVetorCategoriaAcomodacao[i2];
  }
}

/*
 * Nome: atualizarCategoriaAcomodacaoController
 * Parâmetro: categoria registro, int cod
 * Return: int
 * Author: Igor Jeremias
 * Função: Atualiza a categoria de acomodação
 */

int atualizarCategoriaAcomodacaoController(categoria registro, int cod) {

  int i, posicao;
  // Relacionando o código da acomodação com sua posição no vetor
  for (i = 0; i < gQtdAcomodacoes; i++) {
    if (gVetorCategoriaAcomodacao[i].codigo == cod) {
      posicao = i;
    }
  }

  strcpy(gVetorCategoriaAcomodacao[posicao].descricao, registro.descricao);
  gVetorCategoriaAcomodacao[posicao].adultos = registro.adultos;
  gVetorCategoriaAcomodacao[posicao].criancas = registro.criancas;
  gVetorCategoriaAcomodacao[posicao].precoDiaria = registro.precoDiaria;
  // Cadastro bem-sucedido.
  return 0;
}

/*
 * Nome: removerCategoriaAcomodacaoController
 * Parâmetro: int cod
 * Return: int
 * Author: Igor Jeremias
 * Função: Remove a categoria de acomodação
 */

int removerCategoriaController(int cod) {

  int i, posicao, resultado = 1;
  // Relacionando o código da acomodação com sua posição no vetor
  for (i = 0; i < gQtdAcomodacoes; i++) {
    if (gVetorCategoriaAcomodacao[i].codigo == cod) {
      posicao = i;
    }
  }

  if (posicao == gTamVetorCatAcomodacao - 1) {
    gQtdAcomodacoes--;
    if (gTamVetorCatAcomodacao == 1) {
      gTamVetorCatAcomodacao = TAMANHO;
      gVetorCategoriaAcomodacao = malloc(TAMANHO * sizeof(categoria));
    } else {
      gTamVetorCatAcomodacao--;
      gVetorCategoriaAcomodacao =
          realloc(gVetorCategoriaAcomodacao, gTamVetorCatAcomodacao * sizeof(categoria));
    }
  } else {
    for (i = posicao + 1; i < gQtdAcomodacoes; i++) {
      strcpy(gVetorCategoriaAcomodacao[i - 1].descricao,
             gVetorCategoriaAcomodacao[i].descricao);
      gVetorCategoriaAcomodacao[i - 1].adultos =
          gVetorCategoriaAcomodacao[i].adultos;
      gVetorCategoriaAcomodacao[i - 1].criancas =
          gVetorCategoriaAcomodacao[i].criancas;
      gVetorCategoriaAcomodacao[i - 1].precoDiaria =
          gVetorCategoriaAcomodacao[i].precoDiaria;
      gVetorCategoriaAcomodacao[i - 1].codigo =
          gVetorCategoriaAcomodacao[i].codigo;
    }
    gQtdAcomodacoes--;
    if (gTamVetorCatAcomodacao == 1) {
      gTamVetorCatAcomodacao = TAMANHO;
      gVetorCategoriaAcomodacao = malloc(TAMANHO * sizeof(categoria));
    } else {
      gTamVetorCatAcomodacao--;
      gVetorCategoriaAcomodacao =
          realloc(gVetorCategoriaAcomodacao, gTamVetorCatAcomodacao * sizeof(categoria));
    }
  }
  resultado = 0;
  return resultado;
}
int retornaQuantidadeCategoria() {
    return gQtdAcomodacoes;
}


void exportarCategoriaAcomodacaoController() {

  FILE *arquivoCategoriaAcomodacao;

  arquivoCategoriaAcomodacao = fopen("arquivoCategoriaAcomodacao.bin", "wb");

    if (!arquivoCategoriaAcomodacao) {
        erroExportarCategoriaAcomodacao();
        exit(1);
    }

  fwrite(&gQtdAcomodacoes, sizeof(int), 1, arquivoCategoriaAcomodacao);

  fwrite(gVetorCategoriaAcomodacao, sizeof(categoria), gQtdAcomodacoes, arquivoCategoriaAcomodacao);

  int fflush(FILE *arquivoCategoriaAcomodacao);

  fclose(arquivoCategoriaAcomodacao);


}

void importarCategoriaAcomodacaoController() {

  FILE *arquivoCategoriaAcomodacao;

  arquivoCategoriaAcomodacao = fopen("arquivoCategoriaAcomodacao.bin", "rb");

  if (!arquivoCategoriaAcomodacao) {
      erroImportarCategoriaAcomodacao();
      exit(1);
  }

  fread(&gQtdAcomodacoes, sizeof(int), 1, arquivoCategoriaAcomodacao);

  gCodigoCategoriaAcomodacao = gQtdAcomodacoes + 1;

  gVetorCategoriaAcomodacao = malloc(gQtdAcomodacoes * sizeof(categoria));

  inicializarContadorCatAcomodacao(gQtdAcomodacoes);

  gTamVetorCatAcomodacao = gQtdAcomodacoes;

  fread(gVetorCategoriaAcomodacao, sizeof(categoria), gQtdAcomodacoes, arquivoCategoriaAcomodacao);

  fclose(arquivoCategoriaAcomodacao);
}

/*Devolve a categoria de acomodacao de acordo com o codigo passado por parametro*/
categoria buscarCatAcomodacaoCodigoController(int pCodigoReserva) {
  int i, posicao = 0;

  for (i = 0; i < gTamVetorCatAcomodacao; i++) {

    if (pCodigoReserva == gVetorCategoriaAcomodacao[i].codigo) {
        posicao = i;

    }
  }

  return gVetorCategoriaAcomodacao[posicao];

}
