#include "../Model/OperadoresDoSistemaModel.h"

/*----------------------------------------------------------------------------*/
/*                                    MENU                                    */
/*----------------------------------------------------------------------------*/
/*
 * Nome: menuFuncionarioView()
 * Parâmetro¹: void.
 * Return: void
 * Author: João Geraldo
 * Função: Mostra as opções do menu e chama a função selecionada.
 */
void menuFuncionarioView(int pOpcao) {
    funcionario temp;

    static int contadorCadastroOperadores = 0;

    int resultado = 0;

    if (pOpcao == 88) {
        importaContadorBinarioOperadorController(&contadorCadastroOperadores);
        opcao = 0;
        goto parametro_88_Operadores;
    }
    do {

        printf(
                "------------------------------------------------------------------\n"
                "\t\t\t\tMENU \n"
                "------------------------------------------------------------------\n"
                "1 -> CADASTRAR FUNCIONÁRIO \n"
                "2 -> LISTAR FUNCIONÁRIOS CADASTRADOS\n"
                "3 -> BUSCAR FUNCIONÁRIO POR CÓDIGO\n"
                "4 -> BUSCAR FUNCIONÁRIO POR NOME \n"
                "5 -> ATUALIZAR REGISTRO DE FUNCIONÁRIO \n"
                "6 -> DELETAR REGISTRO DE FUNCIONÁRIO \n"

                "0 -> [Sair] \n\n\n"
                );

        scanf("%d*c", &opcao);
        parametro_88_Operadores:


        switch (opcao) {

            case 0:
                //Sair do programa
                break;

            case 1:
                system("clear");
                temp = cadastrarFuncionarioView();

                if (temp.situacao == 1) {

                    //Cadastrou certo contadorCadastroOperadores começa em 0
                    resultado = salvarFuncionarioController(temp, contadorCadastroOperadores);

                    if (resultado == 1) {

                        printf("Funcionario Cadastrado com Sucesso!!\n");
                        contadorCadastroOperadores++;
                    } else {
                        printf("Erro ao salvar na base de dados \n");
                    }


                } else {
                    //Deu erro no cadastro
                    printf("Erro ao receber os dados\n");
                }

                break;

            case 2:
                system("clear");
                if (contadorCadastroOperadores == 0) {

                    printf("Cadastre um Funcionario primeiro \n");

                } else {

                    //Mostrar Funcionarios
                    listarFuncionariosView(contadorCadastroOperadores);
                }

                break;

            case 3:
                system("clear");
                if (contadorCadastroOperadores == 0) {

                    printf("Cadastre um Funcionario primeiro \n");

                } else {

                    buscarFuncionarioCodigoView();
                }
                break;

            case 4:
                system("clear");

                if (contadorCadastroOperadores == 0) {

                    printf("Cadastre um Funcionario primeiro \n");

                } else {

                    buscarFuncionarioNomeView();
                }
                break;

            case 5:

                if (contadorCadastroOperadores == 0) {

                    printf("Cadastre um Funcionario primeiro \n");

                } else {

                    // Mandar para a função de atualizar funcionario
                    temp = atualizarFuncionarioView();

                    if (temp.situacao == 1) { //Atualizou os dados de forma certa

                        resultado = atualizarFuncionarioController(temp);

                        if (resultado == 0) {
                            printf("Erro ao atualizar funcionario \n" );
                        } else {

                            printf("Funcionario atualizado com Sucesso!! \n" );
                        }

                    }
                }

                break;


            case 6:
                system("clear");
                resultado = deletarFuncionarioView();

                if (resultado == 3) {
                    printf("Funcionario não existente \n");
                } else if(resultado == 2){
                    printf("O Funcionario foi deletado com sucesso!! \n");
                    contadorCadastroOperadores --;
                } else if (resultado == 10){ //Erro no controller
                    printf("Erro ao deletar Funcionario \n");
                }else {
                    printf("Operação cancelada \n");
                }
                break;

            default:


                system("clear");
                printf("Valor invalido!\n");

        }

    } while (opcao != 0);

}

/*----------------------------------------------------------------------------*/
/*                                  FUNÇÕES                                   */
/*----------------------------------------------------------------------------*/


/*
 * Nome: cadastrarFuncionarioView()
 * Parâmetro¹: void.
 * Return: funcionario cadastro
 * Author: João Geraldo
 * Função: Armazena os dados do funcionario temporariamente e retorna os mesmos
 * para quem o chamou
 */
funcionario cadastrarFuncionarioView() {
    funcionario cadastro;
    int permissao = 0;
    getchar();

    /*Inicializando as permissões*/
    cadastro.permissaoGestaoHospede = 0;
    cadastro.permissaoReservas = 0;
    cadastro.permissaoTransacoes = 0;
    cadastro.permissaoFeedback = 0;
    cadastro.permissaoControleDeDados = 0;
    /*Fim Inicialização de permissões*/

    cadastro.situacao = 0;

    printf("Nome: ");
    fgets(cadastro.nome, sizeof (cadastro.nome), stdin);
    toUpperCase(cadastro.nome);

    printf("Usuário: ");
    fgets(cadastro.usuario, sizeof (cadastro.usuario), stdin);

    printf("Senha: ");
    fgets(cadastro.senha, sizeof (cadastro.senha), stdin);

    printf("Permissão de acesso \n");

    do{

        printf(
            "1 -> Módulo de Cadastro e gestão de hospedes \n"
            "2 -> Módulo de reservas \n"
            "3 -> Módulo de transações \n"
            "4 -> Módulo de feedback \n"
            "5 -> Módulo de controle de dados \n"
            "0 -> [Salvar Permissões] \n"
        );
        scanf(" %d", &permissao );

        system("clear");

        if (permissao == 1) {

            cadastro.permissaoGestaoHospede = 1;

        } else if (permissao == 2) {

            cadastro.permissaoReservas = 1;

        } else if (permissao == 3) {

            cadastro.permissaoTransacoes = 1;

        }  else if (permissao == 4) {

            cadastro.permissaoFeedback = 1;

        } else if (permissao == 5) {

            cadastro.permissaoControleDeDados = 1;

        } else if (permissao == 0) {

            break; //Finaliza o cadastro

        } else {

            printf("Permissão não identificada, escolha entre 1 a 5 ou 0 para finalizar \n");

        }

    } while (permissao != 0);

    cadastro.situacao = 1;

    return cadastro;
}


/*
 * Nome: listarFuncionariosView()
 * Parâmetro: int int pFuncionariosCadastrados.
 * return: Void
 * Author: João Geraldo
 * Função: Recebe a quantidade de funcionarios já registrados como parâmetro
 * e mostra todos os funcionarios registrados, depois de solicitar esses registros
 * para o controller
*/
void listarFuncionariosView(int pFuncionariosCadastrados) {
    funcionario *temp;

    //Receber a lista do controller
    //temp = vetorFuncionarioController(0);
    temp = listarFuncionariosController();

    // Mostrar no View
    printf("FUNCIONARIOS CADASTRADOS \n" );
    for (size_t i = 0; i < pFuncionariosCadastrados; i++) {
        printf("%dº Registro",i+1);
        printf(

            "Código: %d \n"
            "Nome: %s"
            "Usuário %s"
            "Senha: %s",
            temp[i].codigo,
            temp[i].nome,
            temp[i].usuario,
            temp[i].senha
        );


        if (temp[i].permissaoGestaoHospede == 0) {
            printf("Permissão de Gestão de Hospedes? NÃO\n" );
        } else {
            printf("Permissão de Gestão de Hospedes? SIM\n" );
        }

        if (temp[i].permissaoReservas == 0) {
            printf("Permissão de Reservas? NÃO\n" );
        } else {
            printf("Permissão de Reservas? SIM\n" );
        }

        if (temp[i].permissaoTransacoes == 0) {
            printf("Permissão de Transações? NÃO\n" );
        } else {
            printf("Permissão de Transações? SIM\n" );
        }

        if (temp[i].permissaoFeedback == 0) {
            printf("Permissão de Feedback? NÃO\n" );
        } else {
            printf("Permissão de Feedback? SIM\n" );
        }

        if (temp[i].permissaoControleDeDados == 0) {
            printf("Permissão de Controle de dados? NÃO\n" );
        } else {
            printf("Permissão de Controle de dados? SIM\n" );
        }

    }
}

/*
 * Nome: ()
 * Parâmetro: Void
 * Return: Void
 * Author: João Geraldo
 * Função:
 */
void buscarFuncionarioCodigoView() {
    funcionario temp;
    int codigo;

    printf("Digite o código do funcionário: " );
    scanf("%d%*c", &codigo);

    temp = buscarFuncionarioCodigoController(codigo);

    if (temp.situacao  == 1) {

        printf(

            "Código: %d \n"
            "Nome: %s"
            "Usuário %s"
            "Senha: %s",
            temp.codigo,
            temp.nome,
            temp.usuario,
            temp.senha
        );


        if (temp.permissaoGestaoHospede == 0) {
            printf("Permissão de Gestão de Hospedes? NÃO\n" );
        } else {
            printf("Permissão de Gestão de Hospedes? SIM\n" );
        }

        if (temp.permissaoReservas == 0) {
            printf("Permissão de Reservas? NÃO\n" );
        } else {
            printf("Permissão de Reservas? SIM\n" );
        }

        if (temp.permissaoTransacoes == 0) {
            printf("Permissão de Transações? NÃO\n" );
        } else {
            printf("Permissão de Transações? SIM\n" );
        }

        if (temp.permissaoFeedback == 0) {
            printf("Permissão de Feedback? NÃO\n" );
        } else {
            printf("Permissão de Feedback? SIM\n" );
        }

        if (temp.permissaoControleDeDados == 0) {
            printf("Permissão de Controle de dados? NÃO\n" );
        } else {
            printf("Permissão de Controle de dados? SIM\n" );
        }


    } else {
        printf("Não existe funcionário cadastrado com esse código \n" );
    }
}

/*
 * Nome: buscarFuncionarioNomeView()
 * Parâmetro: Void
 * Return: Void
 * Author: João Geraldo
 * Função:Faz uma busca e lista todos os funcionários com o mesmo nome digitado
 */
 void buscarFuncionarioNomeView() {
     char nome[40];

     funcionario *temp;
     getchar();
     printf("Digite o nome que deseja buscar: ");
     scanf("%[^\n]%*c", nome);
     toUpperCase(nome);

     //não estava funcionando a funcao strstr no controller com fgets
     //fgets(nome, sizeof(nome), stdin);
     setbuf(stdin, NULL);

     temp = buscarFuncionarioNomeController(nome);

     //Mostra todos os funcionarios com o nome digitado
     for (size_t i = 0; i < temp[0].contador; i++) {

         printf("%dº Registro",i+1);
         printf(

             "Código: %d \n"
             "Nome: %s"
             "Usuário %s"
             "Senha: %s",
             temp[i].codigo,
             temp[i].nome,
             temp[i].usuario,
             temp[i].senha
         );

         if (temp[i].permissaoGestaoHospede == 0) {
             printf("Permissão de Gestão de Hospedes? NÃO\n" );
         } else {
             printf("Permissão de Gestão de Hospedes? SIM\n" );
         }

         if (temp[i].permissaoReservas == 0) {
             printf("Permissão de Reservas? NÃO\n" );
         } else {
             printf("Permissão de Reservas? SIM\n" );
         }

         if (temp[i].permissaoTransacoes == 0) {
             printf("Permissão de Transações? NÃO\n" );
         } else {
             printf("Permissão de Transações? SIM\n" );
         }

         if (temp[i].permissaoFeedback == 0) {
             printf("Permissão de Feedback? NÃO\n" );
         } else {
             printf("Permissão de Feedback? SIM\n" );
         }

         if (temp[i].permissaoControleDeDados == 0) {
             printf("Permissão de Controle de dados? NÃO\n" );
         } else {
             printf("Permissão de Controle de dados? SIM\n" );
         }

     }

 }

 /*
  * Nome: atualizarFuncionarioView()
  * Parâmetro: Void.
  * return: struct funcionario
  * Author: João Geraldo
  * Função:
 */
funcionario atualizarFuncionarioView() {
    int codigo = 0, item, permissao;
    funcionario temp;

    //Buscar dados no CONTROLLER
    printf("Digite o codigo do funcionario que deseja atualizar: " );
    scanf(" %d", &codigo );

    temp = buscarFuncionarioCodigoController(codigo);

    //Mostrar os dados antes
    if (temp.situacao == 0) {
        printf("Funcionario não cadastrado \n" );
    } else {

        temp.situacao = 0;

        //Ler qual deseja motificar
        printf("ITEM QUE DESEJA ATUALIZAR: \n" );
        do {

            printf(
                "1-> Nome: \n"
                "2-> Usuario: \n"
                "3-> Senha \n"
                "4-> Permissão de Gestão de Hospedes \n"
                "5-> Permissão de Reservas \n"
                "6-> Permissão de Transações \n"
                "7-> Permissão de Feedback \n"
                "8-> Permissão de Controle de Dados \n"
                "0 -> [SALVAR DADOS]\n"
            );

            scanf("%d%*c", &item);

            switch (item) {
                case 0:
                    //Salva
                    break;
                case 1:
                    printf("Nome atual: %s ", temp.nome );
                    printf("Nome Novo: ");
                    fgets(temp.nome, sizeof(temp.nome), stdin);
                    toUpperCase(temp.nome);

                    break;

                case 2:
                    printf("Usuário atual: %s ", temp.usuario );
                    printf("Usuário Novo: ");
                    fgets(temp.usuario, sizeof(temp.usuario), stdin);

                    break;

                case 3:
                    printf("Senha atual: %s ", temp.senha );
                    printf("Senha Novo: ");
                    fgets(temp.senha, sizeof(temp.senha), stdin);

                    break;

                case 4: //Gestao de hospedes

                    printf("Permissao Gestão de Hospedes Atual: " );
                    if (temp.permissaoGestaoHospede == 0) {

                        printf("NEGADA \n");

                    } else {

                        printf("PERMITIDO \n");
                    }

                    printf(
                        "Permissao Gestão de Hospedes Novo: \n"
                        "1-> PERMITIR \n "
                        "2 -> NEGAR \n"
                    );

                    scanf("%d%*c", &permissao);

                    if (permissao == 2) {
                        temp.permissaoGestaoHospede = 0;

                    } else if (permissao == 1) {

                        temp.permissaoGestaoHospede = 1;

                    } else {

                        printf("Digite um número válido \n" );
                    }

                    break;

                case 5: //Reservas

                    printf("Permissao Gerenciamento de Reservas Atual: " );
                    if (temp.permissaoReservas == 0) {

                        printf("NEGADA \n");

                    } else {

                        printf("PERMITIDO \n");

                    }

                    printf(
                        "Permissao Gerenciamento de Reservas Novo: \n"
                        "1-> PERMITIR \n "
                        "2 -> NEGAR \n"
                    );

                    scanf("%d%*c", &permissao);

                    if (permissao == 2) {
                        temp.permissaoReservas = 0;

                    } else if (permissao == 1) {

                        temp.permissaoReservas = 1;

                    } else {

                        printf("Digite um número válido \n" );
                    }

                    break;

                case 6: //Transações
                    printf("Permissao Gerenciamento de Transações Atual: " );
                    if (temp.permissaoTransacoes == 0) {

                        printf("NEGADA \n");

                    } else {

                        printf("PERMITIDO \n");

                    }

                    printf(
                        "Permissao Gerenciamento de Transações Novo: \n"
                        "1-> PERMITIR \n "
                        "2 -> NEGAR \n"
                    );

                    scanf("%d%*c", &permissao);

                    if (permissao == 2) {
                        temp.permissaoTransacoes = 0;

                    } else if (permissao == 1) {

                        temp.permissaoTransacoes = 1;

                    } else {

                        printf("Digite um número válido \n" );
                    }


                    break;

                case 7: //Feedback
                    printf("Permissao Gerenciamento de Feedback Atual: " );
                    if (temp.permissaoFeedback == 0) {

                        printf("NEGADA \n");

                    } else {

                        printf("PERMITIDO \n");

                    }

                    printf(
                        "Permissao Gerenciamento de Feedback Novo: \n"
                        "1-> PERMITIR \n "
                        "2 -> NEGAR \n"
                    );

                    scanf("%d%*c", &permissao);

                    if (permissao == 2) {
                        temp.permissaoFeedback = 0;

                    } else if (permissao == 1) {

                        temp.permissaoFeedback = 1;

                    } else {

                        printf("Digite um número válido \n" );
                    }


                    break;

                case 8: //Controle de Dados
                    printf("Permissao Controle de dados Atual: " );
                    if (temp.permissaoControleDeDados == 0) {

                        printf("NEGADA \n");

                    } else {

                        printf("PERMITIDO \n");

                    }

                    printf(
                        "Permissao Controle de dados Novo: \n"
                        "1 -> PERMITIR \n "
                        "2 -> NEGAR \n"
                    );

                    scanf("%d%*c", &permissao);

                    if (permissao == 2) {
                        temp.permissaoControleDeDados = 0;

                    } else if (permissao == 1) {

                        temp.permissaoControleDeDados = 1;

                    } else {

                        printf("Digite um número válido \n" );
                    }


                    break;

            }


        } while (item != 0);

        temp.situacao = 1;
    }


    return temp;
}

int deletarFuncionarioView() {
    int codigo, resposta, resultado;
    funcionario temp;

    printf("Código do funcionário que deseja deletar: " );
    scanf("%d%*c", &codigo);

    temp = buscarFuncionarioCodigoController(codigo);

    if (temp.situacao == 0) {
        printf("Funcionario não existe \n" );
        return 3;

    } else {

        printf("Tem certeza que deseja deletar o funcionario: %s ?\n1-> SIM\n2-> NÃO", temp.nome);
        scanf("%d%*c", &resposta);

        if (resposta == 1) { //Deleta

            resultado = deletarFuncionarioControlller(temp.codigo);

            if (resultado == 1) { //Operação relizada com sucesso no controller
                return 2;

            } else { //Não deletou

                return 10; //erro no controller
            }
        } else { //Nao deleta

            return 0; //Número qualquer para não deletar
        }
    }
}

void erroOperadoresDoSistemaImportarView() {
    printf("PROBLEMA AO LER O ARQUIVO BINÁRIO Operadores do sistema");
}

void erroOperadoresDoSistemaExportarView() {
    printf("PROBLEMA AO SALVAR O ARQUIVO BINÁRIO Operadores do sistema");

}
