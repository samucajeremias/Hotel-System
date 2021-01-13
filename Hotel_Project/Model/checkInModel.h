#ifndef CHECKIN_H
#define CHECKIN_H

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
        int codigoReserva;
        float valorPago;
        int opcaoDePagamento; //0->pagamento check-out 1-> pagamento no check-in
        int diaCheckin;
        int mesCheckin;
        int anoCheckin;
        int diarias;
        int hora;
        int minuto;
        int situacao;
        int formaDePagamento; // 0-> Cartao 1-> Dinheiro
    } checkin;



/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/
checkin cadastrarCheckinView();
void menuCheckinView();
int excluirCheckinView();
void listarCheckinView();
void buscarCheckinPorCodigoView();





/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/
void buscarPagamentoChekin(checkin *pCheckin);
int recebeCheckinController(checkin checkinTemp);
checkin *listarCheckinControll();
int excluirCheckinController(int pCodigo);
checkin buscarCheckinPorCodigoController(int pCodigoCheckin);
int verificarSituacaoCheckinController(int pCodigoReserva);
checkin retornaCheckinPorCodigoReservaController(int pCodigoReserva);


/*----------------------------------------------------------------------------*/
/*                                 Exportar Binario                           */
/*----------------------------------------------------------------------------*/

void exportarCheckinController();
void erroExportarCheckin();



/*----------------------------------------------------------------------------*/
/*                                 IMPORTAR BINARIO                                */
/*----------------------------------------------------------------------------*/
void erroImportarCheckin();
void importarCheckinController();
void inicializarContadorCheckin(int pContador);




#ifdef __cplusplus
}
#endif

#endif /* CHECKIN_H */
