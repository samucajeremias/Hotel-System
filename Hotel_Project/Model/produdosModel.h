/*
 * File:   produdosModel.h
 * Author: yuri
 *
 * Created on 16 de Outubro de 2019, 19:25
 */

#ifndef PRODUDOSMODEL_H
#define PRODUDOSMODEL_H

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
        char descricao[50];
        int estoque;
        int estoqueMinimo;
        float precoDeCusto;
        float precoDeVenda;

    }produtos;

    int opcao;


/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/
    void menuProdutosView();
    produtos cadastrarProdutosView();
    void mostrarProdutosView(int contCadastro);
    void buscarPorCodigo(int contCadastro);
    void alterarProdutosView(int contCadastro);
    int excluirProdutosView(int contCadastro);
    void importarProdutoBinarioView(int pContador);

/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/
    void cadastrarProdutosController(produtos temp, int contCadastro);
    produtos* retornarProdutoController();
    produtos retornarPorCodigoController(int codigo, int contCadastro);
    void alterarProdutosController(produtos auxTemp, int contCadastro);
    int excluirProdutosController(int codigo, int contCadastro);
    int retornaQuantidadeProdutos();
    produtos retornaPorCodigo(int pCodigo);
    void atualizarEstoqueController();


#ifdef __cplusplus
}
#endif

#endif /* PRODUDOSMODEL_H */
/*----------------------------------------------------------------------------*/
/*                                 Importar Binário                           */
/*----------------------------------------------------------------------------*/
void importarProdutoController();
void erroImportarProdutos();


/*----------------------------------------------------------------------------*/
/*                                 Exportar Binário                           */
/*----------------------------------------------------------------------------*/
void exportarProdutoController();
void erroExportarProdutos();
