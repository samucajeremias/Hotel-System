#include "../Model/basicoModel.h"
static int gCodigoCheckin = 1;
static int gContadorCadastroCheckin = 0;

/*----------------------------------------------------------------------------*/
/*                                    MENU                                    */
/*----------------------------------------------------------------------------*/
/*
 * Nome: menuHospedeView()
 * Parâmetro¹: void.
 * Return: void
 * Author: João Geraldo
 * Função: Mostra as opções do menu e chama a função selecionada.
 */

void menuCheckinView() {
  checkin temp;

  int resultado = 0;

  do {

    printf(
        "------------------------------------------------------------------\n"
        "\t\t\t\tMENU \n"
        "------------------------------------------------------------------\n"
        "1 -> CADASTRAR CHECK-IN \n"
        "2 -> LISTAR CHECK-IN CADASTRADOS\n"
        "3 -> BUSCAR CHECK-IN \n"
        "4 -> DELETAR REGISTRO DE CHECK-IN \n"

        "0 -> [Sair] \n\n\n");

    scanf("%d*c", &opcao);

    switch (opcao) {

    case 0:
      // Sair do programa
      break;

    case 1:
      temp = cadastrarCheckinView();

      // Realizou o cadastro, pode seguir para salvar no controller
      if (temp.situacao == 1) {
        resultado = recebeCheckinController(temp);

        if (resultado == 1) { // Salvou no controller

          printf("Check-in cadastrado com sucesso!!\n");
          gContadorCadastroCheckin++;

        } else {
          printf("Erro ao realizar Check-in \n");
        }
      }

      break;

    case 2:

      if (gContadorCadastroCheckin == 0) {
        printf("Cadastre um check-in primeiro \n");

      } else {
        listarCheckinView();
      }
      break;

    case 3:

      if (gContadorCadastroCheckin == 0) {
        printf("Cadastre um check-in primeiro \n");

      } else {

        buscarCheckinPorCodigoView();
      }

      break;

    case 4:

      if (gContadorCadastroCheckin == 0) {
        printf("Cadastre um check-in primeiro \n");

      } else {

        resultado = excluirCheckinView();

        if (resultado == 1) {

          printf("Código não encontrado\n");

        } else {

          gContadorCadastroCheckin--;
          printf("Excluido!\n");
        }
      }

      break;

    default:
      // system("clear");
      printf("Valor invalido!\n");
    }

  } while (opcao != 0);
}

/*
 * Nome: listarCheckinControll()
 * Parâmetro: Void
 * Return: checkin gVetorCheckin
 * Author: João Geraldo e Yuri
 * Função: Retorna todos os checkins já registrados no sistema para o View e posteriormente
 * exibi-los em tela
*/
checkin cadastrarCheckinView() {


  checkin tempCheckin;
  tempCheckin.situacao = 0;
  int resposta, pagamento, verificacao;
  time_t mytime;
  mytime = time(NULL);
  struct tm tm = *localtime(&mytime);

  tempCheckin.diaCheckin = tm.tm_mday;
  tempCheckin.mesCheckin =
      tm.tm_mon + 1; // Vai de 0-11 nessa funcao por isso '+1'
  tempCheckin.anoCheckin = tm.tm_year + 1900;
  tempCheckin.hora = tm.tm_hour;
  tempCheckin.minuto = tm.tm_min;

  printf("Informe o código de reseva: ");
  scanf("%d%*c", &tempCheckin.codigoReserva);

  // Verificar antes se a reserva existe

  resposta = verificaReservaCodigoController(tempCheckin.codigoReserva);

  if (resposta == 0) { // Não existe Reserva
    printf("Não existe reserva cadastrada com esse código \n");

  } else {

    verificacao = verificarSituacaoCheckinController(tempCheckin.codigoReserva);


    if(verificacao == 1){

      printf("Reserva ja Cadastrado no Check-In\n");
      tempCheckin.situacao = 0;

    } else {

      printf("Pagamento da diária: \n1-> Check-in\n2-> Check-out\n");
      scanf("%d%*c", &pagamento);

      printf("Forma de pagamento: \n0->\n1-> Dinheiro\n");
      scanf("%d%*c", &tempCheckin.formaDePagamento);


      // Buscar valor da diaria
      buscarPagamentoChekin(&tempCheckin);

      if (pagamento == 1) { // Pagamento no check-in
        tempCheckin.opcaoDePagamento = 1;

        printf("--------------------------------------------------\n");
        printf("\t\t\tDADOS DO CHECKIN\n");
        printf("--------------------------------------------------\n");
        printf("Total Diarias: %d Total R$ %.2f\n", tempCheckin.diarias, tempCheckin.valorPago);

        tempCheckin.codigo = gCodigoCheckin;

        printf("Código do checkin: %d\n"
               "Código da reserva: %d\n"
               "Opção de pagamento: Entrada\n"
               "Valor pago R$: %.2f\n"
               "Data do checkin: %d/%d/%d\n"
               "Hora: %d:%d\n",
               tempCheckin.codigo, tempCheckin.codigoReserva,
               tempCheckin.valorPago, tempCheckin.diaCheckin,
               tempCheckin.mesCheckin, tempCheckin.anoCheckin, tempCheckin.hora,
               tempCheckin.minuto);
      } else { //Pagamento Check-Out
        tempCheckin.opcaoDePagamento = 0;

        printf("--------------------------------------------------\n");
        printf("\t\t\tDADOS DO CHECKIN\n");
        printf("--------------------------------------------------\n");
        printf("Total Diarias: %d\n", tempCheckin.diarias);
        tempCheckin.codigo = gCodigoCheckin;
        printf("Código do checkin: %d\n"
               "Código da reserva: %d\n"
               "Opção de pagamento: SAÍDA\n"
               "Valor A pagar(DIÁRIAS)  R$: %.2f\n"
               "Data do checkin: %d/%d/%d\n"
               "Hora: %d:%d\n\n\n\n",
               tempCheckin.codigo, tempCheckin.codigoReserva,
               tempCheckin.valorPago, tempCheckin.diaCheckin,
               tempCheckin.mesCheckin, tempCheckin.anoCheckin, tempCheckin.hora,
               tempCheckin.minuto);

      }

      gCodigoCheckin++;
      tempCheckin.situacao = 1;
    }


  }



  return tempCheckin;
}

/*
 * Nome: pagamentoCheckin()
 * Parâmetro: int pCodigoReserva
 * Return: int diasTotal
 * Author: João Geraldo
 * Função: Calcula quantos dias o hospede ficará no hotel. Levando em conta a
 * data atual do check-in e a data de saída, programada na reserva. Essa função
 * deve ser usada somente para opção de pagamento no check-in.
 */
/*int pagamentoCheckin(int pCodigoReserva) {

  int anoComum[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int anoBissexto[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int diasEntrada = 0, diasSaida = 0, diasTotal = 0;
  // Função que manipula datas
  time_t mytime;
  mytime = time(NULL);
  struct tm tm = *localtime(&mytime);

  int mesEntrada = tm.tm_mon + 1; // Vai de 0-11 nessa funcao por o '+1'

  // Pegar informação da reserva
  int diaCheckout, mesCheckout, anoCheckout;
  diaCheckout = pegarDataController(1, pCodigoReserva);
  mesCheckout = pegarDataController(2, pCodigoReserva);
  anoCheckout = pegarDataController(3, pCodigoReserva);

  // Pegando dias decorridos no ano [Data Atual do checkin] [Entrada]
  if ((tm.tm_year + 1900) % 4 == 0) { // Ano bissexto
    for (size_t i = 0; i < mesEntrada - 1; i++) {

      diasEntrada += anoBissexto[i];
    }

  } else { // Ano comum

    for (size_t i = 0; i < mesEntrada - 1; i++) {

      diasEntrada += anoComum[i];
    }
  }

  diasEntrada += tm.tm_mday;

  // Pegando dias decorridos no ano [Saída] prevista pela reserva
  if (anoCheckout % 4 == 0) { // Ano bissexto

    for (size_t i = 0; i < mesCheckout; i++) {

      diasSaida += anoBissexto[i];
    }

  } else { // Ano Comum

    for (size_t i = 0; i < mesCheckout; i++) {

      diasSaida += anoComum[i];
    }
  }
  diasSaida += diaCheckout;

  diasTotal = diasSaida - diasEntrada;

  return diasTotal;
}*/

int excluirCheckinView() {

  int codigo, verificacao = 1;

  printf("Digite o código de Check-In que deseja excluir: ");
  scanf("%d", &codigo);

  verificacao = excluirCheckinController(codigo);

  if (verificacao == 1) {

    return verificacao;

  } else {

    return verificacao;
  }
}

/*
 * Nome: listarCheckinView()
 * Parâmetro: Void
 * Return: void
 * Author: João Geraldo
 * Função: Busca do controlle todos os checkins registrados e s exibe aqui no
 * view
 */
void listarCheckinView() {
  checkin *temp;
  int i;
  temp = listarCheckinControll();

  if (gContadorCadastroCheckin != 0) {

    printf("--------------------------------------------------\n");
    printf("\t\t\tLISTA DE CHECKIN\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < gContadorCadastroCheckin; i++) {
      printf("%dº: ", i + 1);

      if (temp[i].opcaoDePagamento == 1) {
          printf("Código do checkin: %d\n"
                 "Código da reserva: %d\n"
                 "Valor pago R$: %.2f\n"
                 "Data do checkin: %d/%d/%d %d:%d\n",
                 temp[i].codigo, temp[i].codigoReserva, temp[i].valorPago,
                 temp[i].diaCheckin, temp[i].mesCheckin, temp[i].anoCheckin,
                 temp[i].hora, temp[i].minuto

          );
        printf("Opção de pagamento: ENTRADA\n\n\n");


      } else {

          printf("Código do checkin: %d\n"
                 "Código da reserva: %d\n"
                 "Valor A pagar(DIÁRIAS) R$: %.2f\n"
                 "Data do checkin: %d/%d/%d\n\n\n",
                 temp[i].codigo, temp[i].codigoReserva, temp[i].valorPago,
                 temp[i].diaCheckin, temp[i].mesCheckin, temp[i].anoCheckin,
                 temp[i].hora, temp[i].minuto

          );
        printf("Opção de pagamento: SAÍDA\n");
      }
    }

  } else {
    printf("Não existe checkin registrado ainda\n");
  }
}

/*
 * Nome: buscarCheckinPorCodigoView()
 * Parâmetro: Void
 * Return: void
 * Author: João Geraldo
 * Função: Busca do controlle um checkin de acordo com o codigo passado e o
 * exibe
 */
void buscarCheckinPorCodigoView() {

  int codigoCheckin = 0;
  checkin tempCheckin;
  printf("Codigo da reserva: ");
  scanf("%d%*c", &codigoCheckin);

  tempCheckin = buscarCheckinPorCodigoController(codigoCheckin);

  if (tempCheckin.codigo == codigoCheckin) {
    printf("--------------------------------------------------\n");
    printf("\t\t\tDADOS DO CHECKIN\n");
    printf("--------------------------------------------------\n");

    printf("Código do checkin: %d\n"
           "Código da reserva: %d\n"
           "Valor pago R$: %f"
           "Data do checkin: %d/%d/%d\n",
           tempCheckin.codigo, tempCheckin.codigoReserva, tempCheckin.valorPago,
           tempCheckin.diaCheckin, tempCheckin.mesCheckin,
           tempCheckin.anoCheckin);
    if (tempCheckin.opcaoDePagamento == 1) {
      printf("Opção de pagamento: Entrada\n");

    } else {
      printf("Opção de pagamento: EntradaK-OUT\n");
    }
  }
}

void erroExportarCheckin() {

  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");
}

void erroImportarCheckin() {

  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");
}

void inicializarContadorCheckin(int pContador) {

  gCodigoCheckin = pContador + 1;
  gContadorCadastroCheckin = pContador;
}
