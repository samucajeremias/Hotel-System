#ifndef SAIDA_PRODUTO_H
#define SAIDA_PRODUTO_H

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

  int codigoProduto[100];
  int quantidade[100];
  int contadorItem; //Quantos itens foram vendidos


} carrinhoSaidaProdutos;

typedef struct {

  int codigoSaidaProduto;
  int codigoHospede;
  float total;
  int formaDePagamento; //0-> anotar 1 -> a vista
  carrinhoSaidaProdutos carrinho;

} saidaProdutos;


/*----------------------------------------------------------------------------*/
/*                                    VIEW                                    */
/*----------------------------------------------------------------------------*/
void listarVendas();
void menuSaidaProdutosView();
void cadastrarVendaView();
void erroImportarVendasView();
void erroExportarVendasView();
void inicializarContadoresView(int pContador);
void erroExportarNotaFiscal();
void buscarVendasView();
/*----------------------------------------------------------------------------*/
/*                                 CONTROLLER                                 */
/*----------------------------------------------------------------------------*/
int salvaVendasController(saidaProdutos pVendas);
void importarVendasController();
void exportarVendasController();
void notaFiscalController(saidaProdutos pVendas);
saidaProdutos *retornaTodasVendasController();
int retornaVendasRegistradas();
saidaProdutos retornaVendaPorCodigo(int pCodigo);


#ifdef __cplusplus
}
#endif

#endif /* SAIDA_PRODUTO_H */
