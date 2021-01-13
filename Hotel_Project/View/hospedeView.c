#include "../Model/hospedeModel.h"



/*----------------------------------------------------------------------------*/
/*                                    MENU                                    */
/*----------------------------------------------------------------------------*/
/*
 * Nome: menuHospedeView()
 * Parâmetro¹: void.
 * Return: void
 * Author: João Geraldo
 * Função: Mostra as opções do menu e chama a função selecionada.
 */
void menuHospedeView(int pOpcao) {
    hospede temp;

    static int contadorCadastroHospede = 0;
    int *p = &contadorCadastroHospede;
    int resultado = 0;

    if (pOpcao == 88) {
        importaContadorBinarioHospedeController(&contadorCadastroHospede);
        opcao = 0;
        goto parametro_88_Hospede;
    }

    do {

        printf(
                "------------------------------------------------------------------\n"
                "\t\t\t\tMENU \n"
                "------------------------------------------------------------------\n"
                "1 -> CADASTRAR HOSPEDE \n"
                "2 -> LISTAR HOSPEDES CADASTRADOS\n"
                "3 -> BUSCAR HOSPEDE \n"
                "4 -> BUSCAR HOSPEDE POR NOME \n"
                "5 -> ATUALIZAR REGISTRO DE HOSPEDE \n"
                "6 -> DELETAR REGISTRO DE HOSPEDE \n"

                "0 -> [Sair] \n\n\n"
                );

        scanf("%d*c", &opcao);
        parametro_88_Hospede:


        switch (opcao) {

            case 0:
                //Sair do programa
                break;

            case 1:
                temp = cadastrarHospedeView();

                if (temp.situacao == 1) {

                    //Cadastrou certo contadorCadastro começa em 0
                    resultado = salvarHospedeController(temp, contadorCadastroHospede);

                    if (resultado == 1) {

                        printf("Hospede Cadastrado com sucesso!!\n");
                        contadorCadastroHospede++;
                    }


                } else {
                    //Deu erro no cadastro
                    printf("Erro ao cadastrar\n\n");
                }

                break;

            case 2:

                if (contadorCadastroHospede == 0) {

                    printf("Cadastre um hospede primeiro \n");

                } else {

                    //Mostrar hospedes
                    listarHospedesView(contadorCadastroHospede);
                }

                break;

            case 3:

                buscarHospedeView();
                break;

            case 4:

                buscarHospedeNomeView();


                break;

            case 5:

                // Mandar para a função de atualizar hospede
                temp = atualizarHospedeView();

                //Condição para seguir com update
                if (temp.situacao == 1) {

                    resultado = atualizarHospedeController(temp);

                    //Condição para ter atualizado certo
                    if (resultado == 1) {

                        mostrarHospedeAtualizadoView(temp.codigo);
                    }

                } else {
                    printf("Hospede não encontrado");
                }
                break;

            case 6:
                resultado = deletarHospedeView();

                if (resultado == 3) {
                    printf("Hospede não existente \n");
                } else if(resultado == 2){
                    printf("Hospede deletado com sucesso!! \n");
                    contadorCadastroHospede --;
                } else {
                    printf("Hospede não foi deletado \n");
                }

                break;
            default:
                //system("clear");
                printf("Valor invalido!\n");

        }

    } while (opcao != 0);

}

/*----------------------------------------------------------------------------*/
/*                                  FUNÇÕES                                   */
/*----------------------------------------------------------------------------*/

/*
 * Nome: cadastrarHospedeView()
 * Parâmetro¹: void.
 * Return: hospede cadastro
 * Author: João Geraldo
 * Função: Armazena os dados do hospede temporariamente e
 * retorna os mesmos para quem o chamou
 */
hospede cadastrarHospedeView() {
    hospede cadastro;
    getchar();

    cadastro.situacao = 0;

    printf("Nome: ");
    //scanf("%s", &cadastro.nome);
    fgets(cadastro.nome, sizeof (cadastro.nome), stdin);
    toUpperCase(cadastro.nome);

    printf("Email: ");
    fgets(cadastro.email, sizeof (cadastro.email), stdin);
    toUpperCase(cadastro.email);

    printf("Endereço: ");
    fgets(cadastro.endereco, sizeof (cadastro.endereco), stdin);
    toUpperCase(cadastro.endereco);

    printf("CPF: ");
    fgets(cadastro.cpf, sizeof (cadastro.cpf), stdin);

    printf("Sexo[M/F]: ");
    fgets(cadastro.sexo, sizeof (cadastro.sexo), stdin);
    getchar(); // Limpar buffer teclado
    toUpperCase(cadastro.sexo);

    printf("Telefone: ");
    fgets(cadastro.telefone, sizeof (cadastro.telefone), stdin);

    printf("Aniversario: ");
    fgets(cadastro.data, sizeof (cadastro.data), stdin);

    printf("Estado civil: ");
    fgets(cadastro.estadoCivil, sizeof (cadastro.estadoCivil), stdin);
    toUpperCase(cadastro.estadoCivil);

    cadastro.contaHospede = 0;

    cadastro.situacao = 1;

    return cadastro;
}

/*
 * Nome: listarHospedesView()
 * Parâmetro¹: int pQuantidadeRegistros.
 * Return: void
 * Author: João Geraldo
 * Função: Mostra todos os hospedes registrados pelo controller
 */
void listarHospedesView(int pQuantidadeRegistros) {
    hospede *temp;

    temp = listarHospedesController();

    for (int i = 0; i < pQuantidadeRegistros; i++) {

        printf( " %dº Hospede \n"
                "Codigo: %d "
                "Nome: %s "
                "Email: %s "
                "Endereço: %s "
                "Sexo %s "
                "CPF %s "
                "Telefone %s "
                "Estado civil %s "
                "Data de aniversário %s\n"
                "Contas a pagar R$ %.2f\n\n",
                i + 1,
                temp[i].codigo,
                temp[i].nome,
                temp[i].email,
                temp[i].endereco,
                temp[i].sexo,
                temp[i].cpf,
                temp[i].telefone,
                temp[i].estadoCivil,
                temp[i].data,
                temp[i].contaHospede
        );

        if (pQuantidadeRegistros > 1) {
            printf("-------------------------------------------------------\n");
        }

    }
}

/*
 * Nome: buscarHospedeView()
 * Parâmetro¹: void.
 * Return: codigo. Retorna o codigo do hospede.
 * Author: João Geraldo
 * Função: Faz a busca de um hospede por código, mostra os dados do mesmo caso
 * esteja cadastrado no sistema e retorna o código do hospede ou zero caso não
 * esteja cadastrado
 */
int buscarHospedeView() {
    int codigo = 0;
    hospede temp;

    printf("Código do hospede: ");
    scanf("%d*c", &codigo);

    //Buscando os dados no controller
    temp = buscarHospedeController(codigo);

    system("clear");

    if ((codigo == temp.codigo) && temp.situacao != 0) {

        printf("Codigo: %d \n"
                "Nome: %s "
                "Email: %s "
                "Endereço: %s "
                "Sexo: %s "
                "CPF: %s "
                "Telefone: %s "
                "Estado civil: %s "
                "Data de aniversário: %s "
                "Contas as pagar R$ %.2f\n",
                temp.codigo,
                temp.nome,
                temp.email,
                temp.endereco,
                temp.sexo,
                temp.cpf,
                temp.telefone,
                temp.estadoCivil,
                temp.data,
                temp.contaHospede
        );

    } else {

        printf("Esse hospede não existe na base de dados\n");
        return 0; //Hospede nao encontrado ou nao existe
    }

    return codigo;
}

/*
 * Nome: atualizarHospedeView()
 * Parâmetro¹: void.
 * Return: temp. Retorna os dados atualizados.
 * Author: João Geraldo
 * Função: Atualiza os dados dos hospedes e os retorna para o lugar que chamou
 */
hospede atualizarHospedeView() {

    hospede temp;

    int op = 0;
    temp = buscarDadosView();


    //Recebeu os dados de forma certa. Pode seguir com a atualização
    if (temp.situacao == 1) {

        system("clear");

        do {
            printf("Digite o item que deseja atualizar: \n");
            printf(
                    "1 -> Nome \n"
                    "2 -> Email\n"
                    "3 -> Telefone\n"
                    "4 -> CPF\n"
                    "5 -> Endereço\n"
                    "6 -> Estado Civil\n"
                    "7 -> Sexo\n"
                    "8 -> Data de aniversário\n"
                    "0 -> [FINALIZAR]\n"
            );

            scanf("%d%*c", &op);
            //getchar();

            switch(op) {
                case 1:

                    printf("Nome atual: %s ", temp.nome);
                    printf("Nome novo: ");
                    fgets(temp.nome, sizeof(temp.nome), stdin);
                    toUpperCase(temp.nome);

                    break;

                case 2:

                    printf("Email atual: %s ", temp.email);
                    printf("Email novo: ");
                    fgets(temp.email, sizeof(temp.email), stdin);
                    toUpperCase(temp.email);

                    break;

                case 3:

                    printf("Telefone atual: %s ", temp.telefone);
                    printf("Telefone novo: ");
                    fgets(temp.telefone, sizeof(temp.telefone), stdin);

                    break;

                case 4:

                    printf("CPF atual: %s ", temp.cpf);
                    printf("CPF novo: ");
                    fgets(temp.cpf, sizeof(temp.cpf), stdin);

                    break;

                case 5:

                    printf("Endereço atual: %s ", temp.endereco);
                    printf("Endereço novo: ");
                    fgets(temp.endereco, sizeof(temp.endereco), stdin);
                    toUpperCase(temp.endereco);

                    break;

                case 6:

                    printf("Estado Civil atual: %s ", temp.estadoCivil);
                    printf("Estado Civil novo: ");
                    fgets(temp.estadoCivil, sizeof(temp.estadoCivil), stdin);
                    toUpperCase(temp.estadoCivil);

                    break;

                case 7:

                    printf("Sexo atual: %s ", temp.sexo);
                    printf("Sexo novo: [M/F] ");
                    fgets(temp.sexo, sizeof(temp.sexo), stdin);
                    toUpperCase(temp.sexo);

                    break;

                case 8:

                    printf("Data de aniversario atual: %s ", temp.data);
                    printf("Data de aniversario novo: ");
                    fgets(temp.data, sizeof(temp.data), stdin);

                    break;
            }


        } while(op != 0);

        temp.situacao = 1;
    }


    return temp;
}

/*
 * Nome: buscarHospedeNomeView()
 * Parâmetro¹: void.
 * Return: void.
 * Author: João Geraldo
 * Função: Faz a busca dos hospedes por nome e retorna uma lista de todos que
 * possuem o mesmo nome
 */

void buscarHospedeNomeView() {
    char nome[40];

    hospede *temp;
    getchar();
    printf("Digite o nome que deseja buscar:");
    scanf("%[^\n]%*c", nome);
    toUpperCase(nome);

    //não estava funcionando a funcao strstr no controller com fgets
    //fgets(nome, sizeof(nome), stdin);
    setbuf(stdin, NULL);

    temp = buscarHospedeNomeController(nome);

    //Mostra todos os hospedes com o nome digitado
    for (size_t i = 0; i < temp[0].contador; i++) {

        printf("Codigo: %d "
                "Nome: %s "
                "Email: %s "
                "Endereço: %s "
                "Sexo %s "
                "CPF %s "
                "Telefone %s "
                "Estado civil %s "
                "Data de aniversário %s "
                "Contas a pagar R$ %.2f\n",
                temp[i].codigo,
                temp[i].nome,
                temp[i].email,
                temp[i].endereco,
                temp[i].sexo,
                temp[i].cpf,
                temp[i].telefone,
                temp[i].estadoCivil,
                temp[i].data,
                temp[i].contaHospede
        );
    }

    if (temp[0].contador == 0) {
        printf("Não existe hospede registrado com esse nome\n" );
    }

}

/*
 * Nome: buscarHospedeView()
 * Parâmetro¹: void.
 * Return: temp
 * Author: João Geraldo
 * Função: Faz a busca de um hospede por código e retorna essas informações
 */

hospede buscarDadosView() {

    hospede temp;

    int codigo = 0;

    printf("Digite o código do usuário: ");
    scanf("%d%*c", &codigo);

    temp = buscarHospedeController(codigo);

    return temp;
}


/*
 * Nome: mostrarHospedeAtualizadoView()
 * Parâmetro¹: int pCodigo.
 * Return: void.
 * Author: João Geraldo
 * Função: Mostra os dados de um hospede de acordo com o seu id e avisa se não
 * está cadastrado
 */
void mostrarHospedeAtualizadoView(int pCodigo) {

    hospede temp;

    temp = buscarHospedeController(pCodigo);

    if (pCodigo == temp.codigo) {

        printf("Codigo: %d \n"
                "Nome: %s \n"
                "Email: %s \n"
                "Endereço: %s \n"
                "Sexo %s \n"
                "CPF %s \n"
                "Telefone %s \n"
                "Estado civil %s \n"
                "Data de aniversário %s \n"
                "Contas a pagar R$ %.2f\n",
                temp.codigo,
                temp.nome,
                temp.email,
                temp.endereco,
                temp.sexo,
                temp.cpf,
                temp.telefone,
                temp.estadoCivil,
                temp.data,
                temp.contaHospede
        );

    } else {

        printf("Hospede não encontrado ou não existe\n");
        //return 0; //Hospede nao encontrado ou nao existe
    }
}

/*
 * Nome: deletarHospedeView()
 * Parâmetro¹: void.
 * Return: int resultado.
 * Author: João Geraldo
 * Função: Verifica se o hospede digitado esta cadastrado e se estiver manda para
 * o controle esse código para deletar da base de dados
 */
int deletarHospedeView() {

    int codigoHospede = 0, resultado = 0, resposta = 0;
    hospede temp;

    //Receber codigo de usuário
    codigoHospede = buscarHospedeView();

    //Verificar se hospede existe

    if (codigoHospede == 0) {

        return 3; // Significa que não existe na base de dados

    } else {


        printf("\n\n[ALERTA!!] --> Tem certeza que deseja deletar este cadastro? <-- [ALERTA!!]\n" );
        printf(
            "1 -> SIM, TENHO CERTEZA\n"
            "2 -> NÃO, QUERO MANTER O CADASTRO \n"
        );
        scanf("%d*c", &resposta );

        if (resposta == 1) {
            resultado = deletarHospedeController(codigoHospede);
            return 2;
        } else {

            return 1;
        }
    }

}

void retornaCodigoCadastradoView(hospede pRegistro) {
    printf("Hospede: %s \n", pRegistro.nome );
    printf("Código: %d\n", pRegistro.codigo);
}
/*
--------------------------------------------------------------------------------
                                     ERROS
--------------------------------------------------------------------------------

ERROR 19 -> MALLOC NÃO FUNCIONOU
ERROR 20 -> REALLOC NÃO FUNCIONOU
*/

/*
 * Nome: errorView()
 * Parâmetro¹: int pCodigoError.
 * Return: void.
 * Author: João Geraldo
 * Função: Mostra um código de erro
 */
void errorView(int pCodigoError) {

    system("clear");
    printf("ALERTA!!\n" );
    printf("Error %d \n", pCodigoError);
}

void erroHospedeImportarView() {
    printf("PROBLEMA AO LER O ARQUIVO BINÁRIO Hospede");
}

void erroHospedeExportarView() {
    printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO");

}
