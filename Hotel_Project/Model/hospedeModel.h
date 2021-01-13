#ifndef HOSPEDE_H
#define HOSPEDE_H

#ifdef __cplusplus
extern "C" {
#endif
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
        char sexo[10];
        char cpf[40];
        char email[40];
        char telefone[40];
        char endereco[40];
        char estadoCivil[40];
        char data[11];
        int situacao;
        int contador;
        float contaHospede; //
    } hospede; //Struct hospedeModel.h

    int opcao;

/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/
    void menuHospedeView(int pOpcao);
    hospede cadastrarHospedeView();
    void listarHospedesView(int pQuantidadeRegistros);
    int buscarHospedeView();
    hospede atualizarHospedeView();
    void mostrarHospedeAtualizadoView(int pCodigo);
    hospede buscarDadosView();
    void buscarHospedeNomeView();
    void errorView(int pCodigoError);
    int deletarHospedeView();
    void retornaCodigoCadastradoView(hospede pRegistro);
    void erroHospedeImportarView();
    void erroHospedeExportarView();
    void importaContadorBinarioHospedeController();

/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/
    void aumentarVetorController(int pOpcao);
    int salvarHospedeController(hospede pRegistro, int pSetMalloc);
    hospede* listarHospedesController();
    hospede buscarHospedeController(int pCodigoHospede);
    int atualizarHospedeController(hospede pRegistro);
    hospede* buscarHospedeNomeController(char pNome[40]);
    int diminuirVetorController();
    int deletarHospedeController(int pCodigo);
    int tamanhoVetorHospedeController(int pEscolha);
    int quantidadeHospedeCadastradoController(int pEscolha);
    int codigoHospedeController(int pOpcao);
    void importarHospedeBinarioController();
    void exportarHospedeBinarioController();
    void importarHospedeBin(int *pContador);
    void receberContasHospedeController(float pValor, int pCodigoHospede);

#ifdef __cplusplus
}
#endif

#endif /* HOSPEDE_H */
