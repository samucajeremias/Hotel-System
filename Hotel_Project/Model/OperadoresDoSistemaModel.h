#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

/*----------------------------------------------------------------------------*/
/*                                 BIBLIOTECAS                                */
/*----------------------------------------------------------------------------*/
#include "basicoModel.h"


/*----------------------------------------------------------------------------*/
/*                                   STRUCT                                   */
/*----------------------------------------------------------------------------*/
    typedef struct {
        int codigo;
        char nome[40];
        char usuario[40];
        char senha[40];
        int permissaoGestaoHospede;
        int permissaoReservas;
        int permissaoTransacoes;
        int permissaoFeedback;
        int permissaoControleDeDados;
        int situacao;
        int contador;
    } funcionario; //Struct OperadoresDoSistemaModel.h

    int opcao;

/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/
funcionario cadastrarFuncionarioView();
void listarFuncionariosView(int pFuncionariosCadastrados);
funcionario atualizarFuncionarioView();
int deletarFuncionarioView();
void buscarFuncionarioCodigoView();
void buscarFuncionarioNomeView();
funcionario atualizarFuncionarioView();
void menuFuncionarioView(int pOpcao);
int deletarFuncionarioView();
void erroOperadoresDoSistemaImportarView();
void erroOperadoresDoSistemaExportarView();


/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/
funcionario* vetorFuncionarioController(int pEscolha);
int salvarFuncionarioController(funcionario pRegistro, int pContador);
funcionario* listarFuncionarioController();
void exportarOperadoresBinarioController();
int quantidadeOperadoresCadastradoController(int pEscolha);
int tamanhoVetorOperadorController(int pEscolha);
int codigoFuncionarioController(int pOpcao);
funcionario* listarFuncionariosController();
funcionario buscarFuncionarioCodigoController(int pCodigoFuncionario);
funcionario* buscarFuncionarioNomeController(char pNome[40]);
int atualizarFuncionarioController(funcionario pRegistroAtualizado);
int deletarFuncionarioControlller(int pCodigoFuncionario);
void importaContadorBinarioOperadorController(int *pContador);
void importarOperadoresBinarioController();
void importarOperadorBin(int *pContador);

#endif /* FUNCIONARIO_H */
