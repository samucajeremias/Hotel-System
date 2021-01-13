/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   acomodacoesModel.h
 * Author: yuri2
 *
 * Created on 1 de Outubro de 2019, 13:46
 */

#ifndef ACOMODACOESMODEL_H
#define ACOMODACOESMODEL_H

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
    char descricao[100];
    char facilidades[100];
    int categoria;
    int situacao;
    int numero;

}acomodacoes ;

int opcao;


/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/

void menuAcomodacoesView(int pCodigo);
acomodacoes cadastrarAcomodacaoView(int cont);
void verAcomodacoesView(int cont);
int excluirAcomodacoesView(int cont);
void mostrarTodasAcomodacoesView(int cont);
acomodacoes alterarAcomodacaoView(int cont);

/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/

void recebeAcomodacaoController(acomodacoes acomodacaoTemporaria, int cont);
void excluirAcomodacoesController(int pCodigo);
acomodacoes* retornarTodasAcomodacoesController();
void atualizarAcomodacoesController(acomodacoes temp);
acomodacoes retornaAcomodacaoPorCodigoController(int pCodigo);
int retornaQuantidadeAcomodacao();

#ifdef __cplusplus
}
#endif

#endif /* ACOMODACOESMODEL_H */

/*----------------------------------------------------------------------------*/
/*                                 EXPORTAÇÃO BINÁRIO                         */
/*----------------------------------------------------------------------------*/
void exportarAcomodacaoController();
void erroExportarAcomodacao();


/*----------------------------------------------------------------------------*/
/*                                 IMPORTAÇÃO BINÁRIO                         */
/*----------------------------------------------------------------------------*/
void importarAcomodacaoController();
void erroImportarAcomodacao();
void inicializarContadorAcomodacao(int contador);
