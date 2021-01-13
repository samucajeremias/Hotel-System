#ifndef CONTROLE_CAIXA_H
#define CONTROLE_CAIXA_H

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
        int codigoPagamento;
        float valorPagamento;
        char origem[100];
    } lancamento;


    typedef struct {
        float totalEmCaixa;
    }caixa;

    typedef struct {
        int codigoRetirada;
        float valorRetirada;
        char origem[100];
    }retirada;



/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/
void verLancamentosView();
void consultaSaldoView();
void verRetiradaView();
void erroImportarLancamentoView();
void erroExportarLancamentoView();
void erroExportarRetiradaView();
void erroImportarRetiradaView();
void erroExportarCaixaView();
void erroImportarCaixaView();

/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/
void registrarLancamentoController(char *pOrigem, float pValor);
lancamento* retornaListaLancamentosController();
int retornarQuantidadeLancamentos();
void importarLancamentoBinController();
void exportarLancamentoBinController();

int retornaQuantidadeRetirada();
void registrarRetiradaController(char *pOrigem, float pValor);
retirada* retornaListaRetiradaController();
void exportarRetiradaController();
void importarRetiradaController();



caixa retornaCaixaController();
void importarCaixaController();
void exportarCaixaController();



#ifdef __cplusplus
}
#endif

#endif /* CONTROLE_CAIXA_H */
