#include "../Model/basicoModel.h"
static int gQuantidadeAcomodacaoAprovada = 0;
static int gQuantidadeReservas = 0;
static int contadorReserva = 0;
static int contCodigotReserva = 1;


void menuReservaView() {

  int opcao, resposta;

  do {

    printf("!!!!!!Menu De Reservas!!!!!\n\n"
           "1. Reservar\n"
           "2. Ver Reservas\n"
           "3. Cancelar Reserva\n"
           "0. Sair\n");
    scanf("%d", &opcao);

    switch (opcao) {

    case 0:

      break;

    case 1:

      cadastrarReservaView();

      break;

    case 2:

      mostrarReservasView();

      break;

    case 3:

      excluirReservaView();

      break;

    }

  } while (opcao != 0);
}

/*
 * Nome: cadastrarReservaView()
 * Parâmetro¹: Void
 * Return: Void
 * Author: Yuri e João Geraldo
 * Função: Recebe as especificações que o hospede quer no quarto e as datas,
 * busca as acomodações que possuem essas características e verifica a disponibilidade
 * de reserva de acordo com as datas desejadas pelo hospede
 */
void cadastrarReservaView() {

  int codigoHospedeReservaTemp, *vetorAcomodacoesAprovadas, i, w;
  int quantidadeAcomodacaoCadastrado = 0, situacao = 0;
  reserva reservaTemp;
  filtro dadosFiltragem;
  int resposta;

  // Verificar se existe acomodacao cadastrada
  quantidadeAcomodacaoCadastrado = retornaQuantidadeAcomodacao();

  if (quantidadeAcomodacaoCadastrado == 0) {
    printf("CADASTRE UMA ACOMODAÇÃO PRIMEIRO\n");
  } else {

    printf("Já é Cadastrado ?\n1 ->[SIM]\n2->[NÃO]\n");
    scanf("%d", &resposta);

    if (resposta == 2) {

      menuHospedeView(0);
    }

    /*Pegando id do hospede*/
    do {

         codigoHospedeReservaTemp = buscarHospedeView();

        if (codigoHospedeReservaTemp == 0) {
            menuHospedeView(0);
        }


    } while (codigoHospedeReservaTemp == 0);

    reservaTemp.codigoHospede = codigoHospedeReservaTemp;

    reservaTemp.codigoReserva = contCodigotReserva; // Código único da reserva

    menuCategoriaAcomodacaoView(3); // Mostra as categorias
    /*Receber os dados do filtro*/
    printf("Digite o código da categoria desejada: ");
    scanf("%d%*c", &dadosFiltragem.categoriaAcomodacao);

    printf("Quantidade de adultos: ");
    scanf("%d", &dadosFiltragem.quantidadeAdultos);

    printf("Quantidade de crianças: ");
    scanf("%d%*c", &dadosFiltragem.quantidadeCriancas);
    getchar();

    printf("Informe as facilidades que necessita no quarto separando por 1 "
           "ESPAÇO\n");
    printf("Exemplo: tv ventilador hidromassagem \n");
    fgets(dadosFiltragem.facilidade, sizeof(dadosFiltragem.facilidade), stdin);
    // fgets(cadastro.nome, sizeof (cadastro.nome), stdin);
    toUpperCase(dadosFiltragem.facilidade);
    // strcat(dadosFiltragem.facilidade, " ");
    // printf("%s.", dadosFiltragem.facilidade);

    // Filtrar até encontar o quarto certo
    vetorAcomodacoesAprovadas = filtrarAcomodacaoView(dadosFiltragem);

    /*Segunda parte do filtro, após receber as acomodações que atendem as
    especificações do hospede, falta verificar se existe data disponivel, só irá
    fazer essa verificação se a quantidade de acomodações aprovadas for maior
    que 0, ou seja, existir alguma acomodação que passou no primeiro filtro*/

    if (gQuantidadeAcomodacaoAprovada > 0) {

      printf("Digite o dia de chegada: ");
      scanf("%d", &reservaTemp.diaChegada);

      printf("Digite o dia de saída: ");
      scanf("%d", &reservaTemp.diaSaida);

      printf("Digite o mês desejado para reservar: ");
      scanf("%d", &reservaTemp.mesChegada);

      printf("Digite o mês desejado para Sair: ");
      scanf("%d", &reservaTemp.mesSaida);

      printf("Digite o ano desejado para reservar: ");
      scanf("%d", &reservaTemp.anoChegada);

      printf("Digite o ano que deseja Sair: ");
      scanf("%d", &reservaTemp.anoSaida);

      /**/

      if (gQuantidadeReservas == 0) {

        /*Preenchendo a reserva*/
        reservaTemp.codigoAcomodacao = vetorAcomodacoesAprovadas[0];

        salvaReservaController(reservaTemp, gQuantidadeReservas);

        gQuantidadeReservas++;
        contCodigotReserva++;

        printf("RESERVA REALIZADA COM SUCESSO!!\n");

      } else {

        for (w = 0; w < gQuantidadeAcomodacaoAprovada; w++) {

          situacao = 0;

          situacao = filtroDataView(reservaTemp, vetorAcomodacoesAprovadas[w]);


          if (situacao == 1) {

            reservaTemp.codigoAcomodacao = vetorAcomodacoesAprovadas[w];

            salvaReservaController(reservaTemp, gQuantidadeReservas);

            contCodigotReserva++;
            gQuantidadeReservas++;
            printf("RESERVA REALIZADA COM SUCESSO!!\n");
            break;
          }

          if (w == gQuantidadeAcomodacaoAprovada - 1) {

            printf("JÁ EXISTE UMA RESERVA COM ESSA DATA\n");

          }
        }
      }
    } else {
      printf("NAO LOCALIZAMOS UMA ACOMODAÇÃO COM ESSAS ESPECIFICAÇÕES\n");
    }

    printf("Acomodações com estas especificações:  \n");
    for (i = 0; i < gQuantidadeAcomodacaoAprovada; i++) {
      printf("%d \n", vetorAcomodacoesAprovadas[i]);
    }
} /*FIM else que siginifica que existe pelo menos 1 acomodacao registrada*/

} /*FIM cadastrarReservaView()*/

/*
 * Nome: filtrarAcomodacaoView()
 * Parâmetro¹: filtro pDados
 * Return: acomodacoesAprovadas
 * Author: Yuri e João Geraldo
 * Função: Recebe os itens que o hospede quer no quarto, e realiza uma busca em
 * todas as acomodações para ver quais possuem tais requistos e retorna o codigo
 * das acomodações aprovadas em forma de vetor
 */
int *filtrarAcomodacaoView(filtro pDados) {
  int trigger, contadorEspaco = 0, i, j, p, contadorFacilidade = 0;
  gQuantidadeAcomodacaoAprovada = 0;
  int quantidadeCategoriaRegistrada = retornaQuantidadeCategoria();

  // Receber acomodações cadastradas
  acomodacoes *acomodacaoTemp;
  acomodacaoTemp = retornarTodasAcomodacoesController();

  // Recebe as categorias de acomodações que estão cadastradas
  categoria *categoriaTemporaria;
  categoriaTemporaria = retornarListaController();

  // Receber quantidade de acomodações registradas
  int quantidadeAcomodacaoCadastrado = retornaQuantidadeAcomodacao();

  // verificadorFacilidade serve para contar quantos itens a acomodação tem
  // requisitada
  int verificadorFacilidade = 0;
  int *acomodacoesAprovadas;
  /*ESSE VETOR CARREGARÁ TODOS OS REQUISITOS PARA A ACOMODAÇÃO SER APROVADA,
   SEPARADA POR POSIÇÃO NO VETOR*/
  filtroFacilidade *vetorFacilidade;
  // Alocando espaço de acordo com a quantidade de facilidades
  vetorFacilidade = malloc(1 * sizeof(filtroFacilidade));

  /*Vetor para guardar as acomodações que serão aprovadas*/
  acomodacoesAprovadas = malloc(1 * sizeof(int));

  /*Quebrando string de facilidades */
  char *token = strtok(pDados.facilidade, " ");

  while (token != NULL) {
    /*Armazenando as facilidades no vetor*/
    contadorEspaco++;
    strcpy(vetorFacilidade[contadorFacilidade].facilidadeQuebrada, token);
    token = strtok(NULL, " ");
    contadorFacilidade++;
    vetorFacilidade = realloc(vetorFacilidade, (contadorFacilidade + 1) *
                                                   sizeof(filtroFacilidade));
  }

  /* 1º laço de repetição serve para percorrer todas as acomodações registradas
   */
  for (i = 0; i < quantidadeAcomodacaoCadastrado; i++) {

    // Controlador das especificações
    trigger = 0;
    verificadorFacilidade = 0;

    /*Condição para entrar somente se bater a mesma cateria estabelecida pelo
     * cliente*/
    if (acomodacaoTemp[i].categoria == pDados.categoriaAcomodacao) {
      /*2º Laço serve para percorrer todas as facilidades descritas*/
      for (j = 0; j < contadorEspaco; j++) {

        if (strstr(acomodacaoTemp[i].facilidades,
                   vetorFacilidade[j].facilidadeQuebrada)) {
          verificadorFacilidade++;
        }

        if (verificadorFacilidade == contadorEspaco) {

          for (p = 0; p < quantidadeCategoriaRegistrada; p++) {

            if (categoriaTemporaria[p].codigo == acomodacaoTemp[i].categoria) {
              /*Comparando a quantidade de adultos suportados*/
              if (categoriaTemporaria[p].adultos >= pDados.quantidadeAdultos) {

                if (categoriaTemporaria[p].criancas >=
                    pDados.quantidadeCriancas) {
                  trigger = 1;
                }
              }
            }
          }
        }
      }
    }

    /*Possui todas as especificações do cliente*/
    if (trigger == 1) {

      acomodacoesAprovadas[gQuantidadeAcomodacaoAprovada] =
          acomodacaoTemp[i].codigo;
      gQuantidadeAcomodacaoAprovada++;
      acomodacoesAprovadas = realloc(
          acomodacoesAprovadas, sizeof(int) * gQuantidadeAcomodacaoAprovada);
    }
  }

  return acomodacoesAprovadas;
}

int filtroDataView(reserva pReservaTemp, int pAcomodacaoAprovadas) {

  int i, p, j, dataChegada, dataSaida, comparaDataChegada, comparaDataSaida,
      verificador = 0;

  reserva *reservasCadastradas;

  reservasCadastradas = retornarReservasController();

  dataChegada = pReservaTemp.diaChegada + (pReservaTemp.mesChegada * 30) +
                (pReservaTemp.anoChegada * 365);
  dataSaida = pReservaTemp.diaSaida + (pReservaTemp.mesSaida * 30) +
              (pReservaTemp.anoSaida * 365);

  verificador = 0;

  for (int i = 0; i < gQuantidadeReservas; i++) {

    comparaDataChegada = reservasCadastradas[i].diaChegada +
                         (reservasCadastradas[i].mesChegada * 30) +
                         (reservasCadastradas[i].anoChegada * 365);

    comparaDataSaida = reservasCadastradas[i].diaSaida +
                       (reservasCadastradas[i].mesSaida * 30) +
                       (reservasCadastradas[i].anoSaida * 365);

    for (p = comparaDataChegada; p <= comparaDataSaida; p++) {

      for (j = dataChegada; j <= dataSaida; j++) {

        if (p == j) {

          if (pAcomodacaoAprovadas == reservasCadastradas[i].codigoAcomodacao) {

            verificador++;

            p = comparaDataSaida + 1;
          }
        }
      }
    }
  }

  if (verificador == 0) {

    return 1;

  } else {

    return 0;
  }
}
void mostrarReservasView() {

  reserva *mostrarReservas;
  int i;


  mostrarReservas = retornarReservasController();

  for(i = 0; i < gQuantidadeReservas;i++){

    //Mostra as reservas cadastradas
    printf("RESERVAS CADASTRADAS\n\n");
    printf("%dº: \n", i+1);
    printf("ENTRADA: %d/%d/%d\n", mostrarReservas[i].diaChegada, mostrarReservas[i].mesChegada, mostrarReservas[i].anoChegada);
    printf("SAIDA: %d/%d/%d\n", mostrarReservas[i].diaSaida, mostrarReservas[i].mesSaida, mostrarReservas[i].anoSaida);
    printf("Código da Acomodação: %d\n", mostrarReservas[i].codigoAcomodacao);
    printf("Código da Reserva: %d\n", mostrarReservas[i].codigoReserva);
    printf("Código do Hóspede: %d\n", mostrarReservas[i].codigoHospede);

  }

}
void excluirReservaView() {

  int codigoDaReserva, i, excluir, posicao;
  reserva *comparador;

  comparador = retornarReservasController();

  printf("Digite o código da reserva que deseja cancelar: ");
  scanf("%d", &codigoDaReserva);

  excluir = 0;

  for(i = 0; i < gQuantidadeReservas; i++) {

    if(comparador[i].codigoReserva == codigoDaReserva){

      posicao = i;

      excluirReservaController(posicao);

      excluir = 1;

      gQuantidadeReservas --;

      printf("Excluido!\n");
    }

  }

  if (excluir != 1) {
    printf("Código não encontrado\n");
  }

}

void erroImportarReserva() {



  printf("PROBLEMA NA LEITURA DO ARQUIVO BINÁRIO\n");

}
void erroExportarReserva() {


  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");

}

void importarReservaBinariaView(int pContador) {
    contCodigotReserva = pContador+1;
    gQuantidadeReservas = pContador;
}
