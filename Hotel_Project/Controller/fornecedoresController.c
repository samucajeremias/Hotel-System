#include "../Model/basicoModel.h"

fornecedores *gVetorFornecedores;
int gTamanhoVetor = TAMANHO;
int gQtdFornecedores = 0;
int gCodigoFornecedor = 1;

/*
 * Nome: salvarFornecedorController
 * Parâmetro: fornecedores registro, int contador
 * Return: int
 * Author: Igor Jeremias
 * Função: Cadastrar fornecedor
 */

int salvarFornecedorController(fornecedores registro, int contador){

    int resultado = 1;

    if (contador == 0){
        gVetorFornecedores = malloc(TAMANHO*sizeof(fornecedores));
    } else
        if (gTamanhoVetor == gQtdFornecedores){
            gTamanhoVetor++;
            gVetorFornecedores = realloc(gVetorFornecedores,
                    gTamanhoVetor*sizeof(fornecedores));
        }
    strcpy(gVetorFornecedores[gQtdFornecedores].nome, registro.nome);
    strcpy(gVetorFornecedores[gQtdFornecedores].razao, registro.razao);
    strcpy(gVetorFornecedores[gQtdFornecedores].inscricao, registro.inscricao);
    strcpy(gVetorFornecedores[gQtdFornecedores].cnpj, registro.cnpj);
    strcpy(gVetorFornecedores[gQtdFornecedores].endereco, registro.endereco);
    strcpy(gVetorFornecedores[gQtdFornecedores].telefone, registro.telefone);
    strcpy(gVetorFornecedores[gQtdFornecedores].email, registro.email);
    gVetorFornecedores[gQtdFornecedores].codigo = gCodigoFornecedor;
    gCodigoFornecedor++;
    gQtdFornecedores++;

    //Cadastro bem-sucedido
    resultado = 0;
    return resultado;
}

/*
 * Nome: removerFornecedorController
 * Parâmetro: int cod
 * Return: int
 * Author: Igor Jeremias
 * Função: Remover fornecedor
 */

int removerFornecedorController(int cod){

    int i, posicao, condicao = 1, resultado = 1;

    for (i = 0; i < gQtdFornecedores; i++){
        if (gVetorFornecedores[i].codigo == cod){
            posicao = i;
        }
    }

    if (posicao == gTamanhoVetor-1){
        gQtdFornecedores--;
        if (gTamanhoVetor == 1){
            gTamanhoVetor = TAMANHO;
            gVetorFornecedores = malloc(TAMANHO*sizeof(fornecedores));
        } else {
            gTamanhoVetor--;
            gVetorFornecedores = realloc(gVetorFornecedores, gTamanhoVetor*sizeof(fornecedores));
        }
    } else {
        for (i = posicao+1; i < gQtdFornecedores; i++){
            strcpy(gVetorFornecedores[i-1].nome, gVetorFornecedores[i].nome);
            strcpy(gVetorFornecedores[i-1].razao, gVetorFornecedores[i].razao);
            strcpy(gVetorFornecedores[i-1].inscricao, gVetorFornecedores[i].inscricao);
            strcpy(gVetorFornecedores[i-1].cnpj, gVetorFornecedores[i].cnpj);
            strcpy(gVetorFornecedores[i-1].endereco, gVetorFornecedores[i].endereco);
            strcpy(gVetorFornecedores[i-1].telefone, gVetorFornecedores[i].telefone);
            strcpy(gVetorFornecedores[i-1].email, gVetorFornecedores[i].email);
            gVetorFornecedores[i-1].codigo = gVetorFornecedores[i].codigo;
        }
        gQtdFornecedores--;
        if (gTamanhoVetor == 1){
            gTamanhoVetor = TAMANHO;
            gVetorFornecedores = malloc(TAMANHO*sizeof(fornecedores));
        } else {
            gTamanhoVetor--;
            gVetorFornecedores = realloc(gVetorFornecedores, gTamanhoVetor*sizeof(fornecedores));
        }
    }
    condicao = 0;
    return condicao;
}

/*
 * Nome: atualizarFornecedorController
 * Parâmetro: fornecedores registro, int cod
 * Return: int
 * Author: Igor Jeremias
 * Função: Atualizar fornecedor
 */

int atualizarFornecedorController(fornecedores registro, int cod){

    int resultado = 1, posicao, i;

    for (i = 0; i < gQtdFornecedores; i++){
        if (gVetorFornecedores[i].codigo == cod){
            posicao = i;
        }
    }

    strcpy(gVetorFornecedores[posicao].nome, registro.nome);
    strcpy(gVetorFornecedores[posicao].razao, registro.razao);
    strcpy(gVetorFornecedores[posicao].inscricao, registro.inscricao);
    strcpy(gVetorFornecedores[posicao].cnpj, registro.cnpj);
    strcpy(gVetorFornecedores[posicao].endereco, registro.endereco);
    strcpy(gVetorFornecedores[posicao].telefone, registro.telefone);
    strcpy(gVetorFornecedores[posicao].email, registro.email);

    //Cadastro bem-sucedido
    resultado = 0;
    return resultado;
}

/*
 * Nome: informacaoFornecedorController
 * Parâmetro: int codigo, int *achou
 * Return: fornecedores
 * Author: Igor Jeremias
 * Função: Encontrar informações sobre o fornecedor
 */

fornecedores informacaoFornecedorController(int codigo, int *achou){

    int i, i2;

    for (i = 0; i < gQtdFornecedores; i++){
        if (codigo == gVetorFornecedores[i].codigo){
            *achou = 1;
            i2 = i;
        }
    }
    if (*achou == 1){
        return gVetorFornecedores[i2];
    }

}

/*
 * Nome: retornarListaController
 * Parâmetro: -
 * Return: fornecedores
 * Author: Igor Jeremias
 * Função: Retornar lista de fornecedores
 */

fornecedores* retornarListaFornecedoresController(){

    return gVetorFornecedores;
}


void exportarFornecedoresController() {

  FILE *arquivoFornecedores;

  arquivoFornecedores = fopen("arquivoFornecedores.bin", "wb");

  if (!arquivoFornecedores) {
      erroExportarFornecedor();
      exit(1);
  }

  fwrite(&gQtdFornecedores, sizeof(int), 1, arquivoFornecedores);
  fwrite(gVetorFornecedores, sizeof(fornecedores), gQtdFornecedores, arquivoFornecedores);


  int fflush(FILE *arquivoFornecedores);
  fclose(arquivoFornecedores);


}

void importarFornecedoresController(){

  FILE *arquivoFornecedores;

  arquivoFornecedores = fopen("arquivoFornecedores.bin", "rb");

  if (!arquivoFornecedores) {
      erroExportarFornecedor();
      exit(1);
  }

  fread(&gQtdFornecedores, sizeof(int), 1, arquivoFornecedores);

  gVetorFornecedores = malloc(gQtdFornecedores * sizeof(fornecedores));

  inicializarContadorFornecedor(gQtdFornecedores);

  gTamanhoVetor = gQtdFornecedores;

  gCodigoFornecedor = gQtdFornecedores + 1;


  fread(gVetorFornecedores, sizeof(fornecedores), gQtdFornecedores, arquivoFornecedores);


  fclose(arquivoFornecedores);

}
