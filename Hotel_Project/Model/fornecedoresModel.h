/*
 * File:   fornecedoresModel.h
 * Author: igorj
 *
 * Created on 18 de Outubro de 2019, 14:11
 */

#ifndef FORNECEDORESMODEL_H
#define FORNECEDORESMODEL_H

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
        char nome[20];
        char razao[100];
        char inscricao[20];
        char cnpj[20];
        char endereco[140];
        char telefone[20];
        char email[30];
    } fornecedores;

/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/
void fornecedoresView();
fornecedores adicionarFornecedorView ();
int removerFornecedorView();
int atualizarFornecedorView();
void mostrarFornecedoresView(int contador);
int informacaoFornecedorView();

/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/
int salvarFornecedorController(fornecedores registro, int contador);
int removerFornecedorController(int cod);
fornecedores* retornarListaFornecedoresController();
int atualizarFornecedorController(fornecedores registro, int cod);
fornecedores informacaoFornecedorController(int codigo, int *achou);
#ifdef __cplusplus
}
#endif

#endif /* FORNECEDORESMODEL_H */
/*----------------------------------------------------------------------------*/
/*                                 EXPORTAÇÃO BINÁRIO                         */
/*----------------------------------------------------------------------------*/

void exportarFornecedoresController();
void erroExportarFornecedor();/*----------------------------------------------------------------------------*/
/*                                 IMPORTAÇÃO BINÁRIO                         */
/*----------------------------------------------------------------------------*/
void importarFornecedoresController();
void erroImportarFornecedor();
void inicializarContadorFornecedor(int contFornecedor);
