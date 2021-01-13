#ifndef BASICOMODEL_H
#define BASICOMODEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/*                                 CONSTANTES                                 */
/*----------------------------------------------------------------------------*/

#define ACRESCIMO 1
#define TAMANHO 1

/*----------------------------------------------------------------------------*/
/*                                 BIBLIOTECAS                                */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#include "acomodacoesModel.h"
#include "categoriaAcomodacaoModel.h"
#include "fornecedoresModel.h"
#include "hospedeModel.h"
#include "hotelModel.h"
#include "reservaModel.h"
#include "OperadoresDoSistemaModel.h"
#include "produdosModel.h"
#include "checkInModel.h"
#include "controleDeCaixaModel.h"
#include "saidaProdutosModel.h"
#include "checkOutModel.h"

void toUpperCase(char *pString);

/*----------------------------------------------------------------------------*/
/*                                 VIEW                                       */
/*----------------------------------------------------------------------------*/
void menuImportacaoExportacaoView();
void menuTransacaoView();
void controleDeCaixaView();

#ifdef __cplusplus
}
#endif

#endif /* BASICOMODEL_H */
