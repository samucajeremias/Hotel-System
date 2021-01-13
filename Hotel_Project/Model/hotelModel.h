/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   hotelModel.h
 * Author: yuri2

#ifndef HOTELMODEL_H
 *
 * Created on 20 de Setembro de 2019, 17:50
 */
#ifndef HOTELMODEL_H
#define HOTELMODEL_H

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

    typedef struct{

       char nomeFantasia[40];
       char razaoSocial[40];
       char inscricaoEstadual[40];
       char cnpj[40];
       char enderecoCompleto[40];
       char telefone[40];
       char email[40];
       char nomeResponsavel[40];
       char telefoneResponsavel[40];
       int horarioCheckIn;
       int horarioCheckOut;
       float lucro;
       int situacao;

    }cadastrarHotel;

    int opcao;




    /*----------------------------------------------------------------------------*/
    /*                                    VIEW                                    */
    /*----------------------------------------------------------------------------*/
void menuHotelView();
cadastrarHotel cadastrarHotelView();
void mostrarHotelView();
cadastrarHotel atualizarHotelView();
cadastrarHotel excluirHotelView();

/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/

void receberHotel(cadastrarHotel recebeHotel);
cadastrarHotel retornarHotel();




#ifdef __cplusplus
}
#endif

#endif /* HOTELMODEL_H */
/*----------------------------------------------------------------------------*/
/*                                    Exportar Binario                        */
/*----------------------------------------------------------------------------*/

void exportarHotelController();
void erroExportarHotel();



/*----------------------------------------------------------------------------*/
/*                                    Importar Binario                        */
/*----------------------------------------------------------------------------*/
void importarHotelController();
void erroImportarHotel();
void inicializarContadorHotel(int contHotel);
