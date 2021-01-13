#include "../Model/basicoModel.h"
static checkin *gVetorCheckin;
static int gTamVetorCheckin = 0, gContadorCheckinRegistrado = 0;

/*----------------------------------------------------------------------------*/
/*                                FUNÇÕES DO VETOR                            */
/*----------------------------------------------------------------------------*/

/*
 * Nome: ()
 * Parâmetro:
 * Return:
 * Author: João Geraldo
 * Função:
*/

/*----------------------------------------------------------------------------*/
/*                                    CREATE                                  */
/*----------------------------------------------------------------------------*/

/*
 * Nome: ()
 * Parâmetro:
 * Return:
 * Author: João Geraldo
 * Função:
*/


int recebeCheckinController(checkin pCheckinTemp){

    int verificador;

    verificador = 0;

    if (gContadorCheckinRegistrado == 0) {

      gVetorCheckin = malloc(TAMANHO * sizeof(checkin));

      gTamVetorCheckin = TAMANHO;

    } else if (gContadorCheckinRegistrado == gTamVetorCheckin) {

        gTamVetorCheckin = gTamVetorCheckin + TAMANHO;

        gVetorCheckin =
          realloc(gVetorCheckin, gTamVetorCheckin * sizeof(checkin));
    }

    gVetorCheckin[gContadorCheckinRegistrado] = pCheckinTemp;
    if (pCheckinTemp.opcaoDePagamento == 1 && pCheckinTemp.formaDePagamento == 1) {
        registrarLancamentoController("DIÁRIAS CHECK-IN" , pCheckinTemp.valorPago);

    } else if (pCheckinTemp.opcaoDePagamento == 1 && pCheckinTemp.formaDePagamento == 0) {
        /* mandar para contas a receber */
    }

    gContadorCheckinRegistrado ++;

    verificador = 1;

    return verificador;

}

/*----------------------------------------------------------------------------*/
/*                                    READ                                    */
/*----------------------------------------------------------------------------*/

/*
 * Nome: listarCheckinControll()
 * Parâmetro: Void
 * Return: checkin gVetorCheckin
 * Author: João Geraldo
 * Função: Retorna todos os checkins já registrados no sistema para o View e posteriormente
 * exibi-los em tela
*/

checkin *listarCheckinControll() {
    return gVetorCheckin;
}

checkin buscarCheckinPorCodigoController(int pCodigoCheckin) {
    int i, posicao = 0;

    for (i = 0; i < gContadorCheckinRegistrado; i++) {

        if (gVetorCheckin[i].codigo == pCodigoCheckin) {
            posicao = i;

        }
    }

    return gVetorCheckin[posicao];
}

/*----------------------------------------------------------------------------*/
/*                                    UPDATE                                  */
/*----------------------------------------------------------------------------*/

/*
 * Nome: ()
 * Parâmetro:
 * Return:
 * Author: João Geraldo
 * Função:
*/

/*----------------------------------------------------------------------------*/
/*                                    DELETE                                  */
/*----------------------------------------------------------------------------*/

/*
 * Nome: ()
 * Parâmetro:
 * Return:
 * Author: João Geraldo
 * Função:
*/
int excluirCheckinController(int pCodigo) {

  int i, posicao;

  posicao = -1;

  for(i = 0; i < gTamVetorCheckin; i++){

    if(gVetorCheckin[i].codigo == pCodigo) {

      posicao = i;

    }

  }

  if (posicao != -1) {

    gVetorCheckin[posicao] = gVetorCheckin[gTamVetorCheckin-1];

    gTamVetorCheckin = gTamVetorCheckin - TAMANHO;

    gContadorCheckinRegistrado --;

    gVetorCheckin = realloc(gVetorCheckin, gTamVetorCheckin * sizeof(checkin));

    return 0;

  } else {


    return 1;

  }

}


/*
 * Nome: verificarSituacaoCheckinController()
 * Parâmetro: int pCodigoReserva
 * Return: int situacao
 * Author: João Geraldo
 * Função: Recebe um codigo de reserva e verifica se esse codigo já foi utilizado
 * em algum checkin, retornando 1 caso ja tenha sido usado e 0 caso ainda nao tenha
 * sido registrado um checkin com esse codigo de reserva
*/
int verificarSituacaoCheckinController(int pCodigoReserva) {

    int situacao, i;

    for ( i = 0; i < gContadorCheckinRegistrado; i++) {
        if (pCodigoReserva == gVetorCheckin[i].codigoReserva) {
            situacao = 1;
        }
    }

    return situacao;
}



void buscarPagamentoChekin(checkin *pCheckin) {

  categoria categoriaTemp;
  acomodacoes acomodacaoTemp;
  reserva reservaTemp;
  float precoAPagar;



    //Buscar na reserva o codigo da categoria de acomodação
    reservaTemp = buscarReservaCodigoController((pCheckin)->codigoReserva);

    //Buscar na acomodacao o codigo da categoria
    acomodacaoTemp = retornaAcomodacaoPorCodigoController(reservaTemp.codigoAcomodacao);

    // Buscar na categoria de acomodacao o valor da diária

    categoriaTemp = buscarCatAcomodacaoCodigoController(acomodacaoTemp.categoria);
    (pCheckin)->diarias = (((reservaTemp.diaSaida +(reservaTemp.mesSaida*30)+ (reservaTemp.anoSaida * 365))-(reservaTemp.diaChegada +(reservaTemp.mesChegada*30)+ (reservaTemp.anoChegada * 365))));
    //*pCheckin->diarias = (((reservaTemp.diaSaida +(reservaTemp.mesSaida*30)+ (reservaTemp.anoSaida * 365))-(reservaTemp.diaChegada +(reservaTemp.mesChegada*30)+ (reservaTemp.anoChegada * 365))));
    //*pCheckin->valorPago = categoriaTemp.precoDiaria * (*pCheckin->diarias);
    (pCheckin)->valorPago = categoriaTemp.precoDiaria * (pCheckin)->diarias;

}


void exportarCheckinController(){

  FILE *arquivoCheckin;

  arquivoCheckin = fopen("arquivoCheckin.bin", "wb");

    if (!arquivoCheckin) {
        erroExportarCheckin();
        exit(1);
    }

  fwrite(&gContadorCheckinRegistrado, sizeof(int), 1, arquivoCheckin);


  fwrite(gVetorCheckin, sizeof(checkin), gContadorCheckinRegistrado, arquivoCheckin);


  int fflush(FILE *arquivoCheckin);
  fclose(arquivoCheckin);

}

void importarCheckinController() {
    FILE *arquivoCheckin;
    arquivoCheckin = fopen("arquivoCheckin.bin", "rb");

    if (!arquivoCheckin) {
        erroImportarCheckin();
        exit(1);
    }

    fread(&gContadorCheckinRegistrado, sizeof(int), 1, arquivoCheckin);

    gVetorCheckin = malloc(gContadorCheckinRegistrado * sizeof(checkin));

    fread(gVetorCheckin, sizeof(checkin), gContadorCheckinRegistrado, arquivoCheckin);

    inicializarContadorCheckin(gContadorCheckinRegistrado);

    gTamVetorCheckin = gContadorCheckinRegistrado;

    fclose(arquivoCheckin);

}

checkin retornaCheckinPorCodigoReservaController(int pCodigoReserva){
	
	int i, posicao = 0;
	for ( i = 0; i < gContadorCheckinRegistrado; i++)
	{
		if (gVetorCheckin[i].codigo == pCodigoReserva)
		{
			posicao = i;
		}
		
	}
	return gVetorCheckin[posicao];
	
}