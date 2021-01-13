#ifndef CHECKOUT_MODEL_H
#define CHECKOUT_MODEL_H

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
    int codigoCheckOut;
    float total;
    int reserva;
    int codigoHospede;
    int diaChegada;
    int diaSaida;
    int mesChegada;
    int mesSaida;
    int anoChegada;
    int anoSaida;    

}checkOut;


/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/

void menuCheckOutView();
void registrarCheckOutView();
void listarCheckOutView();
void calcularDiariaView(int pReserva, float *pTotalDiarias);
void erroExportarCheckOut();
void erroImportarCheckOut();
void inicializarContadorCheckOutView(int pContador);
void buscarCheckoutView();

/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/
int salvarCheckOutController(checkOut salvaCheckOut);
checkOut *retornaCheckOutController();
checkOut retornaCheckOutPorCodigo(int pCodigo);
void exportarCheckOutController();
void importarCheckOutController();
int verificarCheckOutController(int pCodigoReserva);


#ifdef __cplusplus
}
#endif

#endif /* CHECKOUT_MODEL_H */

/*----------------------------------------------------------------------------*/
/*                                 EXPORTAÇÃO BINÁRIO                         */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*                                 IMPORTAÇÃO BINÁRIO                         */
/*----------------------------------------------------------------------------*/
