#include "../Model/basicoModel.h"

static int gContadorCheckOut;


void menuCheckOutView() {


    int resultado = 0;

    do {

      printf(
          "------------------------------------------------------------------\n"
          "\t\t\t\tMENU \n"
          "------------------------------------------------------------------\n"
          "1 -> REALIZAR CHECK-OUT\n"
          "2 -> LISTAR CHECK-OUT \n"
          "3 -> BUSCAR CHECK-OUT \n"

          "0 -> [Sair] \n\n\n");

      scanf("%d*c", &opcao);

      switch (opcao) {

      case 0:
        // Sair do programa
        break;

      case 1:

            registrarCheckOutView();
            

        break;

      case 2:

            listarCheckOutView();

        break;

      case 3:

            buscarCheckoutView();

        break;

      case 4:



        break;

      default:
        // system("clear");
        printf("Valor invalido!\n");
      }

    } while (opcao != 0);


}

void registrarCheckOutView() {
    int codigoReserva, resposta = 0, confirmarCheckout = 0;
    reserva reservaTemp;
    float totalDiaria = 0;
    checkOut checkOutTemp;
    checkin checkinTemp;
    hospede hospedeTemp;
    int verificador = 0;

    printf("INFORME SUA RESERVA: ");
    scanf("%d%*c", &codigoReserva);

    printf("antes da funcao\n\n");
    resposta = verificarCheckOutController(codigoReserva);
    printf("depois da funcao\n\n");

     if (resposta == 1)
     {
       printf("CHECK-OUT JÁ REALIZADO\n ");

     } else {

       //Buscando dados do check-in
      checkinTemp = retornaCheckinPorCodigoReservaController(codigoReserva);


    if (checkinTemp.formaDePagamento == 0)
    {
        /*Calculando o valor das diarias já que não foi pago no check-in*/
        calcularDiariaView(codigoReserva, &totalDiaria);

        checkOutTemp.total = totalDiaria;
    }

    //Buscando informações da reserva
    reservaTemp = buscarReservaCodigoController(codigoReserva);

    //Buscando dados do hospede
    hospedeTemp = buscarHospedeController(reservaTemp.codigoHospede);

    //Recebendo datas de entrada
    checkOutTemp.diaChegada = checkinTemp.diaCheckin;
    checkOutTemp.mesChegada = checkinTemp.mesCheckin;
    checkOutTemp.anoChegada = checkinTemp.anoCheckin;

    //Recebendo datas de saida
    checkOutTemp.diaSaida = reservaTemp.diaSaida;
    checkOutTemp.mesSaida = reservaTemp.mesSaida;
    checkOutTemp.anoSaida = reservaTemp.anoSaida;
    checkOutTemp.reserva = codigoReserva;
    //Somando as diárias com o consumo do hospede
    checkOutTemp.total = checkOutTemp.total + hospedeTemp.contaHospede;

    printf("CHECK-OUT:\n");
    printf("HOSPEDE: %s");
    printf("CÓDIGO HOSPEDE: %d \n", hospedeTemp.codigo);            
    printf("Total: %.2f\n\n", checkOutTemp.total);

    printf("CONFIRMAR CHECK-OUT?\n1->SIM\n2->NÃO\n\n");
    scanf("%d%*c", &confirmarCheckout);
    
    if (confirmarCheckout == 1)
    {

      verificador = salvarCheckOutController(checkOutTemp);
    if (verificador == 1)
      {
          printf("CHECK-OUT REALIZADO COM SUCESSO!!\n\n");
          gContadorCheckOut++;
      }

     } else {
      printf("CHECK-OUT CANCELADO\n");
    
    }

  }
}

void calcularDiariaView(int pReserva, float *pTotalDiarias) {
    categoria categoriaTemp;
    acomodacoes acomodacaoTemp;
    reserva reservaTemp;


    //Buscar na reserva o codigo da categoria de acomodação
    reservaTemp = buscarReservaCodigoController(pReserva);

    //Buscar na acomodacao o codigo da categoria
    acomodacaoTemp = retornaAcomodacaoPorCodigoController(reservaTemp.codigoAcomodacao);

    // Buscar na categoria de acomodacao o valor da diária
    categoriaTemp = buscarCatAcomodacaoCodigoController(acomodacaoTemp.categoria);
    *pTotalDiarias = (((reservaTemp.diaSaida +(reservaTemp.mesSaida*30)+ (reservaTemp.anoSaida * 365))-(reservaTemp.diaChegada +(reservaTemp.mesChegada*30)+ (reservaTemp.anoChegada * 365))));

}



void listarCheckOutView() {

    checkOut *tempCheckOut;
    int i;
    hospede hospedeTemp;    
  
    tempCheckOut = retornaCheckOutController();

    for(i = 0; i < gContadorCheckOut; i++) {
        
      hospedeTemp = buscarHospedeController(tempCheckOut[i].codigoHospede);

      printf("CÓDIGO HOSPEDE: %d \n", hospedeTemp.codigo);
      printf("HOSPEDE: %s", hospedeTemp.nome);
      printf("Código Check-Out: %d\n", tempCheckOut[i].codigoCheckOut);
      printf("Total: %.2f\n\n", tempCheckOut[i].total);


    }



}

void buscarCheckoutView() {

    checkOut tempCheckOut;
    int i, codigoCheckout;
    hospede hospedeTemp;


    printf("INFORME O CÓDIGO DO CHECK-OUT: ");
    scanf("%d%*c", &codigoCheckout);

    hospedeTemp = buscarHospedeController(tempCheckOut.codigoHospede);

    tempCheckOut = retornaCheckOutPorCodigo(codigoCheckout);

    printf("Código Check-Out: %d\n", tempCheckOut.codigoCheckOut);
    printf("CÓDIGO HOSPEDE: %d \n", hospedeTemp.codigo);
    printf("HOSPEDE: %s", hospedeTemp.nome);
    printf("Total: %.2f\n", tempCheckOut.total);

}


void erroExportarCheckOut() {


  printf("ERRO AO CRIAR ARQUIVO\n");

}

void erroImportarCheckOut() {

  printf("ERRO AO LER ARQUIVO\n");

}

void inicializarContadorCheckOutView(int pContador) {

  gContadorCheckOut = pContador;

}
