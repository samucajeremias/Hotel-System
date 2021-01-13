/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   categoriaAcomodacaoModel.h
 * Author: igorj
 *
 * Created on 20 de Setembro de 2019, 14:21
 */

#ifndef CATEGORIAACOMODACAOMODEL_H
#define CATEGORIAACOMODACAOMODEL_H

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
    char descricao[256];
    float precoDiaria;
    int adultos;
    int criancas;
}categoria;

/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/
int menuCategoriaAcomodacaoView(int pOpcao);
categoria cadastrar_acomodacao();
void mostrarCategoriasView(int contador);
void informacaoCategoriaView(int pCodigo);
int atualizarCategoriaView();
int removerCategoriaView();

/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/
int salvarCategoriaAcomodacaoController(categoria registro, int contador);
categoria* retornarListaController();
categoria informacaoCategoriaController(int codigo, int *achou);
int atualizarCategoriaAcomodacaoController(categoria registro, int cod);
int removerCategoriaController(int cod);
int retornaQuantidadeCategoria();
categoria buscarCatAcomodacaoCodigoController(int pCodigoReserva);

#ifdef __cplusplus
}
#endif

#endif /* CATEGORIAACOMODACAOMODEL_H */

/*----------------------------------------------------------------------------*/
/*                                 EXPORTAÇÃO BINÁRIO                         */
/*----------------------------------------------------------------------------*/
void exportarCategoriaAcomodacaoController();
void erroExportarCategoriaAcomodacao();
/*----------------------------------------------------------------------------*/
/*                                 IMPORTAÇÃO BINÁRIO                         */
/*----------------------------------------------------------------------------*/
void importarCategoriaAcomodacaoController();
void erroImportarCategoriaAcomodacao();
void inicializarContadorCatAcomodacao(int contadorCatAcomodacao);
