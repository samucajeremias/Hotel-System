#ifndef RESERVAMODEL_H
#define RESERVAMODEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/*                                 BIBLIOTECAS                                */
/*----------------------------------------------------------------------------*/
#include "basicoModel.h"
#include "categoriaAcomodacaoModel.h"
/*----------------------------------------------------------------------------*/
/*                                   STRUCT                                   */
/*----------------------------------------------------------------------------*/

int opcao;

typedef struct {

  int diaChegada;
  int diaSaida;
  int mesChegada;
  int mesSaida;
  int codigoAcomodacao;
  int codigoReserva;
  int codigoHospede;
  int anoSaida;
  int anoChegada;

} reserva;

typedef struct {
    int categoriaAcomodacao;
    int quantidadeAdultos;
    int quantidadeCriancas;
    char facilidade[256];

} filtro;

typedef struct {
    char facilidadeQuebrada[150];
} filtroFacilidade;

/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/
void menuReservaView();
void cadastrarReservaView();
int *filtrarAcomodacaoView(filtro pDados);
int filtroDataView(reserva pReservaTemp, int pAcomodacaoAprovada);
void mostrarReservasView();
void excluirReservaView();
void importarReservaBinariaView(int pContador);
/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/
void salvaReservaController(reserva reservaView, int contReserva);
reserva *retornarReservasController();
void excluirReservaController(int posicao);
int verificaReservaCodigoController(int pCodigoReserva);
reserva buscarReservaCodigoController(int pCodigoReserva);

#ifdef __cplusplus
}
#endif

#endif /* RESERVAMODEL_H */

/*----------------------------------------------------------------------------*/
/*                                 Importar Binário                           */
/*----------------------------------------------------------------------------*/

void importarReservaController();
void erroImportarReserva();

/*----------------------------------------------------------------------------*/
/*                                 Exportar Binário                           */
/*----------------------------------------------------------------------------*/
void exportarReservaController();
void erroExportarReserva();
