#include "../Model/OperadoresDoSistemaModel.h"
#include "../Model/basicoModel.h"

/*----------------------------------------------------------------------------*/
/*                                FUNÇÕES DO VETOR                            */
/*----------------------------------------------------------------------------*/

/*
 * Nome: vetorFuncionarioController()
 * Parâmetro: int pEscolha
 * Return: *vetorFuncionario
 * Author: João Geraldo
 * Função: Criar vetor static, retornar endereço de memoria do mesmo e realloc
 * o vetor se preciso
*/
funcionario* vetorFuncionarioController(int pEscolha) {

    funcionario static *vetorFuncionario;
    int quantidadeCadastros = quantidadeOperadoresCadastradoController(0);
    int tamanhoVetor;


    if (quantidadeCadastros == 0) {

        vetorFuncionario = (funcionario*) malloc(TAMANHO * sizeof(funcionario));
    }


    if (pEscolha == 1) { //Realloc + 1 Posição

        tamanhoVetor = tamanhoVetorOperadorController(1);

        vetorFuncionario = realloc(vetorFuncionario, tamanhoVetor * sizeof(funcionario));

    } else if (pEscolha == 2) { //Realloc - 1 Posição

        if (quantidadeCadastros == 1) {
            free(vetorFuncionario);
            quantidadeOperadoresCadastradoController(2);
        } else {

            tamanhoVetor = tamanhoVetorOperadorController(2);
            quantidadeOperadoresCadastradoController(2);

            vetorFuncionario = realloc(vetorFuncionario, tamanhoVetor * sizeof(funcionario));
        }

    } else if (pEscolha == 88) {
        int contadorOperadores = 0;

        FILE *arquivoOperadores;
        arquivoOperadores = fopen("arquivoOperadores.bin", "rb");

        if (!arquivoOperadores) {
            erroOperadoresDoSistemaImportarView();
            exit(1);
        }

        fread(&contadorOperadores, sizeof(int), 1, arquivoOperadores);

        vetorFuncionario = (funcionario*) malloc(contadorOperadores * sizeof(funcionario));

        if (vetorFuncionario == NULL) {

            //MALLOC NAO FUNCIONOU
            errorView(19);

        }

        fread(vetorFuncionario, sizeof(funcionario), contadorOperadores, arquivoOperadores);

        fclose(arquivoOperadores);
    }

    return vetorFuncionario;
}


/*
 * Nome: tamanhoVetorOperadorController()
 * Parâmetro: int pEscolha
 * Return: tamanhoVetor
 * Author: João Geraldo
 * Função: Retorna o tamanho atual do vetor, e acrescenta ou subtrai o mesmo
*/
int tamanhoVetorOperadorController(int pEscolha) {

    int static tamanhoVetor = TAMANHO;

    if (pEscolha == 1) { //Acrescenta 1

        tamanhoVetor ++;

    } else if (pEscolha == 2) { // Subtraí 1
        tamanhoVetor --;
    } else if(pEscolha == 88) {
        int contadorOperadores = 0;

        FILE *arquivoOperadores;
        arquivoOperadores = fopen("arquivoOperadores.bin", "rb");

        if (!arquivoOperadores) {
            erroOperadoresDoSistemaImportarView();
            exit(1);
        }

        fread(&contadorOperadores, sizeof(int), 1, arquivoOperadores);
        fclose(arquivoOperadores);
        tamanhoVetor = contadorOperadores;
    }

    return tamanhoVetor;
}

/*
 * Nome: quantidadeOperadoresCadastradoController()
 * Parâmetro: int pEscolha
 * Return: funcionariosCadastrados
 * Author: João Geraldo
 * Função: Retorna a quantidade de funcionarios cadastrados no sistema e também
 * pode acrescentar ou diminuir essa quantidade de acordo com o parâmetro
*/
int quantidadeOperadoresCadastradoController(int pEscolha) {

    int static funcionariosCadastrados = 0; //Embora Static já começar em zero

    if (pEscolha == 1) { //Acrescenta 1

        funcionariosCadastrados ++;

    } else if (pEscolha == 2) { // Subtraí 1
        funcionariosCadastrados --;

    } else if(pEscolha == 88) {

        int contadorOperadores = 0;

        FILE *arquivoOperadores;
        arquivoOperadores = fopen("arquivoOperadores.bin", "rb");

        if (!arquivoOperadores) {
            erroOperadoresDoSistemaImportarView();
            exit(1);
        }

        fread(&contadorOperadores, sizeof(int), 1, arquivoOperadores);

        fclose(arquivoOperadores);
        funcionariosCadastrados = contadorOperadores;
    }

    return funcionariosCadastrados;
}

/*
 * Nome: codigoFuncionarioController()
 * Parâmetro: Void
 * Return: int codigoFuncionario
 * Author: João Geraldo
 * Função: Gera o código de cada funcionario e retorna esse número
*/
int codigoFuncionarioController(int pOpcao) {
    int static codigoFuncionario = 0;

    codigoFuncionario ++;

    if (pOpcao == 88) {
        importarOperadorBin(&codigoFuncionario);
    }



    return codigoFuncionario;
}
/*----------------------------------------------------------------------------*/
/*                                   CREATE                                   */
/*----------------------------------------------------------------------------*/

/*
 * Nome: salvarFuncionarioController()
 * Parâmetro: funcionario pRegistro, int pContador
 * Return: int situacao
 * Author: João Geraldo
 * Função: Realiza o cadastro do funcionario no vetor
*/
int salvarFuncionarioController(funcionario pRegistro, int pContador) {

    int situacao = 0;
    funcionario static *vetorFuncionario;

    //Passando zero apenas para saber valor atual
    int tamanhoVetor = tamanhoVetorOperadorController(0);
    int funcionariosCadastrados = quantidadeOperadoresCadastradoController(0);


    if (pContador == 0) { // Primeiro cadastro, precisa de malloc

        //Passando zero para dar malloc e pegar endereço do vetor
        vetorFuncionario = vetorFuncionarioController(0);

    } else if (tamanhoVetor == funcionariosCadastrados) {

        //Espaço esgotado, precisa de realloc (1) para dar realloc de +1
        vetorFuncionario = vetorFuncionarioController(1);
    }

    vetorFuncionario[funcionariosCadastrados] = pRegistro;
    vetorFuncionario[funcionariosCadastrados].codigo = codigoFuncionarioController(0);

    // Passando 1 para acrescentar 1 funcionario cadastrado
    quantidadeOperadoresCadastradoController(1);

    situacao = 1;
    return situacao;
}
/*----------------------------------------------------------------------------*/
/*                                    READ                                    */
/*----------------------------------------------------------------------------*/

/*
 * Nome: listarFuncionariosController()
 * Parâmetro: Void
 * Return: Funcionario*
 * Author: João Geraldo
 * Função: Retorna uma lista dos funcionários cadastrados
 */

 funcionario* listarFuncionariosController() {
     funcionario *temp;

     temp = vetorFuncionarioController(0);

     return temp;
 }

/*
* Nome: ()
* Parâmetro: Void
* Return: Void
* Author: João Geraldo
* Função:
*/

funcionario buscarFuncionarioCodigoController(int pCodigoFuncionario){

    int i, funcionariosCadastrados = quantidadeOperadoresCadastradoController(0);

    funcionario *vetorFuncionario;
    vetorFuncionario = vetorFuncionarioController(0);

    for (size_t i = 0; i < funcionariosCadastrados; i++) {

        vetorFuncionario[i].situacao = 0; //Não encontrado ainda

        if (pCodigoFuncionario == vetorFuncionario[i].codigo) {

            vetorFuncionario[i].situacao = 1;

            return vetorFuncionario[i];
        }
    }

    //Estará retornando situacao = 0, ou seja, funcionario não encontrado
    return vetorFuncionario[i];
}


/*
* Nome: buscarFuncionarioNomeController()
* Parâmetro: char pNome[40]
* Return: funcionario* temp
* Author: João Geraldo
* Função: Retorna uma lista com os funcionarios qu e possuem o nome passado como
* parâmetro
*/

funcionario* buscarFuncionarioNomeController(char pNome[40]) {

   int i, contadorTemp = 1, funcionarioEncontrado = 0 ;
   int funcionariosCadastrados = quantidadeOperadoresCadastradoController(0);

   funcionario *temp, *vetorFuncionario;

   vetorFuncionario = vetorFuncionarioController(0);

   temp = malloc(contadorTemp * sizeof (funcionario));

   for (i = 0; i < funcionariosCadastrados; i++) {

       //Verificar se o vetor temporário está cheio
       if (contadorTemp == funcionarioEncontrado) {

           contadorTemp++;
           temp = (funcionario*) realloc(temp, contadorTemp * sizeof (funcionario));
       }

       if (strstr(vetorFuncionario[i].nome, pNome)) {

           //Guarda informações no vetor caso tenha o nome que foi buscado
           temp[funcionarioEncontrado] = vetorFuncionario[i];

           funcionarioEncontrado++;

       }

   }

   //armazenando a quantidade de funcionarios com o nome buscado
   temp[0].contador = funcionarioEncontrado;

   return temp;
}

/*----------------------------------------------------------------------------*/
/*                                    UPDATE                                  */
/*----------------------------------------------------------------------------*/

/*
* Nome: atualizarFuncionarioController()
* Parâmetro: funcionario pRegistroAtualizado
* Return: int situacao
* Author: João Geraldo
* Função: Atualiza as informações de um funcionário específico
*/
int atualizarFuncionarioController(funcionario pRegistroAtualizado) {

   int situacao = 0;
   funcionario *vetorFuncionario;
   vetorFuncionario = vetorFuncionarioController(0);

   int funcionariosCadastrados = quantidadeOperadoresCadastradoController(0);

   //Procurar a posição do funcionario no vetor
   for (size_t i = 0; i < funcionariosCadastrados; i++) {

       if (pRegistroAtualizado.codigo == vetorFuncionario[i].codigo) {
           //Atualizar dados
           vetorFuncionario[i] = pRegistroAtualizado;
           situacao = 1;
           break;
       }
   }

   return situacao;
}

/*----------------------------------------------------------------------------*/
/*                                    DELETE                                  */
/*----------------------------------------------------------------------------*/

/*
* Nome: deletarFuncionarioControlller()
* Parâmetro: int pCodigoFuncionario
* Return: int situacao
* Author: João Geraldo
* Função: Delete o funcionario da base de dados usando o código de identificação
*/
int deletarFuncionarioControlller(int pCodigoFuncionario){

    int posicao, situacao = 0;
    funcionario *vetorFuncionario;
    vetorFuncionario = vetorFuncionarioController(0);

    int funcionariosCadastrados = quantidadeOperadoresCadastradoController(0);

    //Buscar posição do funcionário a ser deletado
    for (size_t i = 0; i < funcionariosCadastrados; i++) {
        if (pCodigoFuncionario == vetorFuncionario[i].codigo) {
            posicao = i;
        }
    }

    //Última posição, então apenas dar realloc
    if (posicao+1 == funcionariosCadastrados) {
        vetorFuncionarioController(2);
        situacao = 1;


    } else { //Nao ser a ultima posicao
        /*Mover o último funcionario para a posição que será deletada */

        vetorFuncionario[posicao] = vetorFuncionario[funcionariosCadastrados-1];
        //Dar realloc
        vetorFuncionarioController(2);
        situacao = 1;

    }
    return situacao;

}
/*----------------------------------------------------------------------------*/
/*                                   EXPORTAÇÃO BINÁRIO                       */
/*----------------------------------------------------------------------------*/
void exportarOperadoresBinarioController() {

    funcionario *vetorFuncionarioTemp;
    int contadorOperadores = quantidadeOperadoresCadastradoController(0);
    vetorFuncionarioTemp = vetorFuncionarioController(0);

    FILE *arquivoOperadores;
    arquivoOperadores = fopen("arquivoOperadores.bin","wb");

    if (!arquivoOperadores) {
        erroOperadoresDoSistemaExportarView();
        exit(1);
    }


    fwrite(&contadorOperadores, sizeof(int), 1, arquivoOperadores);
    fwrite(vetorFuncionarioTemp, sizeof(funcionario), contadorOperadores, arquivoOperadores);
    int fflush(FILE *arquivoOperadores);
    fclose(arquivoOperadores);
}

/*----------------------------------------------------------------------------*/
/*                                   IMPORTAÇÃO BINÁRIO                       */
/*----------------------------------------------------------------------------*/

void importarOperadoresBinarioController() {

    //Código para realizar a importacação
    vetorFuncionarioController(88);
    tamanhoVetorOperadorController(88);
    quantidadeOperadoresCadastradoController(88);
    menuFuncionarioView(88);
    codigoFuncionarioController(88);
}



//Atualizar o contador do View
void importaContadorBinarioOperadorController(int *pContador) {
    *pContador = quantidadeOperadoresCadastradoController(0);
}

//Atualizando o contador do código de operadores
void importarOperadorBin(int *pContador) {
    *pContador = quantidadeOperadoresCadastradoController(0);
}
