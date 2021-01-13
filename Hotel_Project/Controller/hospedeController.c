#include "../Model/hospedeModel.h"

/*----------------------------------------------------------------------------*/
/*                                FUNÇÕES DO VETOR                            */
/*----------------------------------------------------------------------------*/

/*
 * Nome: vetorHospedeController()
 * Parâmetro: int pEscolha
 * Return: vetorHospede*
 * Author: João Geraldo
 * Função: Criar vetor static, retornar endereço de memoria do mesmo e realloc
 * o vetor se preciso
*/
hospede* vetorHospedeController(int pEscolha) {

    hospede static *vetorHospede;
    int quantidadeCadastros = quantidadeHospedeCadastradoController(0);
    int tamanhoVetor;



    if (quantidadeCadastros == 0) {

        vetorHospede = (hospede*) malloc(TAMANHO * sizeof(hospede));

        if (vetorHospede == NULL) {

            //MALLOC NAO FUNCIONOU
            errorView(19);

        }
    }


    if (pEscolha == 1) { //Realloc + 1 Posição

        tamanhoVetor = tamanhoVetorHospedeController(1);

        vetorHospede = realloc(vetorHospede, tamanhoVetor * sizeof(hospede));

        if (vetorHospede == NULL) {

            //REALLOC NAO FUNCIONOU
            errorView(20);

        }

    } else if (pEscolha == 2) { //Realloc - 1 Posição

        if (quantidadeCadastros == 1) {
            free(vetorHospede);
            quantidadeHospedeCadastradoController(2);
            if (vetorHospede == NULL) {

                //REALLOC NAO FUNCIONOU
                errorView(20);

            }
        } else {

            tamanhoVetor = tamanhoVetorHospedeController(2); //Pegando tamanho do vetor
            quantidadeHospedeCadastradoController(2); //Subtraindo 1 da quantidade de cadastrados

            vetorHospede = realloc(vetorHospede, tamanhoVetor * sizeof(hospede));
            if (vetorHospede == NULL) {

                //REALLOC NAO FUNCIONOU
                errorView(20);

            }
        }

    } else if(pEscolha == 88) {

        int contadorHospede = 0;

        FILE *arquivoHospede;
        arquivoHospede = fopen("arquivoHospede.bin", "rb");

        if (!arquivoHospede) {
            erroHospedeImportarView();
            exit(1);
        }

        fread(&contadorHospede, sizeof(int), 1, arquivoHospede);

        vetorHospede = (hospede*) malloc(contadorHospede * sizeof(hospede));

        if (vetorHospede == NULL) {

            //MALLOC NAO FUNCIONOU
            errorView(19);

        }

        fread(vetorHospede, sizeof(hospede), contadorHospede, arquivoHospede);
        fclose(arquivoHospede);
    }

    return vetorHospede;
}


/*
 * Nome: tamanhoVetorHospedeController()
 * Parâmetro: int pEscolha
 * Return: tamanhoVetor
 * Author: João Geraldo
 * Função: Retorna o tamanho atual do vetor, e acrescenta ou subtrai o mesmo
*/
int tamanhoVetorHospedeController(int pEscolha) {

    int static tamanhoVetor = TAMANHO;

    if (pEscolha == 1) { //Acrescenta 1

        tamanhoVetor ++;

    } else if (pEscolha == 2) { // Subtraí 1
        tamanhoVetor --;
    } else if(pEscolha == 88) {

        int contadorHospede = 0;

        FILE *arquivoHospede;
        arquivoHospede = fopen("arquivoHospede.bin", "rb");

        if (!arquivoHospede) {

            erroHospedeImportarView();
            exit(1);
        }

        fread(&contadorHospede, sizeof(int), 1, arquivoHospede);
        fclose(arquivoHospede);
        tamanhoVetor = contadorHospede;
    }


    return tamanhoVetor;
}

/*
 * Nome: quantidadeHospedeCadastradoController()
 * Parâmetro: int pEscolha
 * Return: hospedesCadastrados
 * Author: João Geraldo
 * Função: Retorna a quantidade de hospedes cadastrados no sistema e também
 * pode acrescentar ou diminuir essa quantidade de acordo com o parâmetro
*/
int quantidadeHospedeCadastradoController(int pEscolha) {

    int static hospedesCadastrados = 0; //Embora Static já começar em zero

    if (pEscolha == 1) { //Acrescenta 1

        hospedesCadastrados ++;

    } else if (pEscolha == 2) { // Subtraí 1
        hospedesCadastrados --;

    } else if(pEscolha == 88){

        int contadorHospede = 0;

        FILE *arquivoHospede;
        arquivoHospede = fopen("arquivoHospede.bin", "rb");

        if (!arquivoHospede) {
            erroHospedeImportarView();
            exit(1);
        }

        fread(&contadorHospede, sizeof(int), 1, arquivoHospede);

        fclose(arquivoHospede);
        hospedesCadastrados = contadorHospede;
    }

    return hospedesCadastrados;
}

/*
 * Nome: codigoHospedeController()
 * Parâmetro: Void
 * Return: int codigoHospede
 * Author: João Geraldo
 * Função: Gera o código de cada hospede e retorna esse número
*/
int codigoHospedeController(int pOpcao) {
    int static codigoHospede = 0;

    codigoHospede ++;

    if (pOpcao == 88) {
        importarHospedeBin(&codigoHospede);
    }

    return codigoHospede;
}

/*----------------------------------------------------------------------------*/
/*                                    CREATE                                  */
/*----------------------------------------------------------------------------*/
/*
 * Nome: salvarHospedeController
 * Parâmetro¹: hospede pRegistro.
 * Parâmetro²: int pSetMalloc. Código para saber se precisa de alocar memoria
 * Return: void
 * Author: João Geraldo
 * Função: Recebe os dados coletados pelo hospedeView e realiza o cadastro.
 */
int salvarHospedeController(hospede pRegistro, int pcontadorCadastro) {

    system("clear");
    int hospedesCadastrados = quantidadeHospedeCadastradoController(0);
    int tamanhoVetor = tamanhoVetorHospedeController(0);
    hospede static *vetorHospede;
    pRegistro.situacao = 0;

    if ((pcontadorCadastro == 0) ) {
        vetorHospede = vetorHospedeController(0);

    } else if (hospedesCadastrados == tamanhoVetor) {

        vetorHospede = vetorHospedeController(1);
    }

    vetorHospede[hospedesCadastrados] = pRegistro;

    vetorHospede[hospedesCadastrados].codigo = codigoHospedeController(0);

    retornaCodigoCadastradoView(vetorHospede[hospedesCadastrados]);

    quantidadeHospedeCadastradoController(1);
    pRegistro.situacao = 1;


    return pRegistro.situacao;

}
/*----------------------------------------------------------------------------*/
/*                                    READ                                    */
/*----------------------------------------------------------------------------*/

/*
 * Nome: listarHospedesController()
 * Parâmetro¹: void.
 * Return: hospede*. (Vetor do tipo hospede)
 * Author: João Geraldo
 * Função: Retorna para o view a lista de hospedes já cadastrados.
 */
hospede* listarHospedesController() {
    hospede *temp;

    temp = vetorHospedeController(0);

    return temp;
}

/*
 * Nome: buscarHospedeController()
 * Parâmetro¹: pCodigoHospede.
 * Return: hospede gVetorHospede
 * Author: João Geraldo
 * Função: Busca o hospede via registro e o retorna para o o lugar que chamou a função,
  * caso esteja cadastrado, do contrário manda um numero qualquer para informar que nao existe
 */
 hospede buscarHospedeController(int pCodigoHospede) {
    int i, hospedesCadastrados = quantidadeHospedeCadastradoController(0);

    hospede *vetorHospede, temp;

    vetorHospede = vetorHospedeController(0);

    for (i = 0; i < hospedesCadastrados; i++) {

        if (pCodigoHospede == vetorHospede[i].codigo) {

            vetorHospede[i].situacao = 1;
            return vetorHospede[i];
        }

    }

    /*
     * Retornando um numero qualquer para informar que nao existe o hospede
     * com esse codigo
     */
    temp.situacao = 0;

    return temp;
}

/*
 * Nome: buscarHospedeNomeController()
 * Parâmetro¹: char nome[40]
 * Return: hospede* temp
 * Author: João Geraldo
 * Função: Retorna todos os hospedes com o nome do parâmetro
 */

hospede* buscarHospedeNomeController(char pNome[40]) {

    int i, contadorTemp = 1, contadorHospede = 0;
    hospede *temp, *vetorHospede;
    vetorHospede = vetorHospedeController(0);
    int hospedesCadastrados = quantidadeHospedeCadastradoController(0);

    temp = malloc(contadorTemp * sizeof (hospede));

    for (i = 0; i < hospedesCadastrados; i++) {

        //Verificar se o vetor temporário está cheio
        if (contadorTemp == contadorHospede) {

            contadorTemp++;
            temp = (hospede*) realloc(temp, contadorTemp * sizeof (hospede));
        }

        if (strstr(vetorHospede[i].nome, pNome)) {

            //Guarda informações no vetor caso tenha o nome que foi buscado
            temp[contadorHospede] = vetorHospede[i];

            contadorHospede++;

        }

    }

    //armazenando a quantidade de hospedes com o nome buscado
    temp[0].contador = contadorHospede;

    return temp;
}
/*----------------------------------------------------------------------------*/
/*                                    UPDATE                                  */
/*----------------------------------------------------------------------------*/
/*
 * Nome: atualizarHospedeController()
 * Parâmetro¹: hospede pRegistro.
 * Return: pRegistro.situacao
 * Author: João Geraldo
 * Função: Atualiza os dados dos hospedes de acordo com a sua posição cadastrada
 * E retorna 1 para informar que atualizou com sucesso
 */
int atualizarHospedeController(hospede pRegistro) {

    pRegistro.situacao = 0;
    int posicao = 0;
    hospede *vetorHospede;
    vetorHospede = vetorHospedeController(0);
    int hospedesCadastrados = quantidadeHospedeCadastradoController(0);

    for (posicao = 0; posicao < hospedesCadastrados; posicao++) {
        if (vetorHospede[posicao].codigo == pRegistro.codigo) {
            break;
        }
    }

    vetorHospede[posicao] = pRegistro;

    pRegistro.situacao = 1;

    return pRegistro.situacao;
}

/*----------------------------------------------------------------------------*/
/*                                    DELETE                                  */
/*----------------------------------------------------------------------------*/
/*
 * Nome: deletarHospedeController()
 * Parâmetro¹: int pCodigo.
 * Return: int resultado.
 * Author: João Geraldo
 * Função: Deleta um hospede de acordo com o código recebido por parâmetro
 */
int deletarHospedeController(int pCodigo) {

    int posicao = 0, resultado = 0;

    hospede *vetorHospede;

    vetorHospede = vetorHospedeController(0);
    int hospedesCadastrados = quantidadeHospedeCadastradoController(0);

    //Buscar a posição que o usuário está no vetor
    for (size_t i = 0; i < hospedesCadastrados; i++) {
        if (vetorHospede[i].codigo == pCodigo) {
            posicao = i;
        }
    }


    if (posicao+1 == hospedesCadastrados) { // Se for o último do vetor

        vetorHospedeController(2);
        resultado = 1;
    } else { // Se não for o último do vetor

        //1º Jogar o último na posição do hospede que irá ser deletado
        vetorHospede[posicao] = vetorHospede[hospedesCadastrados-1];


        //2º Diminuir o vetor
        vetorHospedeController(2);
        resultado = 1;
    }

    return resultado;
}

/*----------------------------------------------------------------------------*/
/*                                   EXPORTAÇÃO BINÁRIO                       */
/*----------------------------------------------------------------------------*/
void exportarHospedeBinarioController() {
    hospede *vetorHospedeTemp;
    int contadorHospede = quantidadeHospedeCadastradoController(0);
    vetorHospedeTemp = vetorHospedeController(0);

    FILE *arquivoHospede;
    arquivoHospede = fopen("arquivoHospede.bin","wb");
    if (!arquivoHospede) {
        erroHospedeExportarView();
        exit(1);
    }


    fwrite(&contadorHospede, sizeof(int), 1, arquivoHospede);
    fwrite(vetorHospedeTemp, sizeof(hospede), contadorHospede, arquivoHospede);
    int fflush(FILE *arquivoHospede);
    fclose(arquivoHospede);
}

/*----------------------------------------------------------------------------*/
/*                                   IMPORTAÇÃO BINÁRIO                       */
/*----------------------------------------------------------------------------*/

void importarHospedeBinarioController() {

    //Código para realizar a importacação
    vetorHospedeController(88);
    tamanhoVetorHospedeController(88);
    quantidadeHospedeCadastradoController(88);
    menuHospedeView(88);
    codigoHospedeController(88);


}

void importaContadorBinarioHospedeController(int *pContador) {
    *pContador = quantidadeHospedeCadastradoController(0);
}

void importarHospedeBin(int *pContador) {

    *pContador = quantidadeHospedeCadastradoController(0);
}



/*Adicionar valores na conta do hospede*/
void receberContasHospedeController(float pValor, int pCodigoHospede) {
    hospede* vetorTemp;
    int i, hospedesCadastrados;
    hospedesCadastrados = quantidadeHospedeCadastradoController(0);

    vetorTemp = vetorHospedeController(0);

    for  (i = 0; i < hospedesCadastrados; i++) {

        if (vetorTemp[i].codigo == pCodigoHospede) {
            vetorTemp[i].contaHospede += pValor;
        }

    }

}
