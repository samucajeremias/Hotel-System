#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Model/hotelModel.h"

/*
 * Nome: menuHotel()
 * Parâmetro¹: void.
 * Return: void
 * Author: Yuri
 * Função: Mostra as opções do menu e chama a função selecionada.
 */


static int cont = 0;

void menuHotelView() {

  cadastrarHotel temp;



  do {

    if (cont == 0) {

      printf("\\\\\\MENU\\\\\\\\ \n");

      printf("1. Cadastrar Hotel\n"
             "2. Excluir dados do Hotel\n"
             "3. Ver dados do Hotel\n"
             "0. Sair\n");

      scanf("%d*c", &opcao);

      switch (opcao) {

      case 0:

        break;

      case 1:

        temp = cadastrarHotelView();

        if (temp.situacao == 0) {

          receberHotel(temp);

          cont++;
        }

        printf("Hotel Cadastrado!\n\n");

        break;

      case 2:

        temp = excluirHotelView();

        if (temp.situacao == 0) {

          receberHotel(temp);
        }

        printf("Os dados do Hotel foram excluidos!\n\n");

        break;

      case 3:

        mostrarHotelView();

        break;
      }

    } else {

      printf("\n\n \\\\\\MENU\\\\\\\\ \n\n");

      printf("1. Alterar dados do Hotel\n"
             "2. Excluir dados do Hotel\n"
             "3. Ver dados do Hotel\n"
             "0. Sair\n");

      scanf("%d*c", &opcao);

      switch (opcao) {

      case 0:

        break;

      case 1:

        temp = atualizarHotelView();

        if (temp.situacao == 0) {

          receberHotel(temp);
        }

        printf("Os dados foram alterados com secesso!\n\n");

        break;

      case 2:

        temp = excluirHotelView();

        if (temp.situacao == 0) {

          receberHotel(temp);

          cont--;
        }

        printf("Os dados do Hotel foram excluidos!\n\n");

        break;

      case 3:

        mostrarHotelView();

        break;
      }
    }

  } while (opcao != 0);
}

/*
 * Nome: cadastrarHotelView
 * Parâmetro¹: void.
 * Return: struct
 * Author: Yuri
 * Função: Recebe os dados digitados pelo usuario e manda para posteriormente
  salvar no controller.
 */

cadastrarHotel cadastrarHotelView() {

  cadastrarHotel dadosHotel;

  dadosHotel.situacao = 1;

  getchar();

  printf("--------CADASTRO-------\n\n");
  printf("Nome fantasia: ");
  fgets(dadosHotel.nomeFantasia, sizeof(dadosHotel.nomeFantasia), stdin);
  toUpperCase(dadosHotel.nomeFantasia);

  printf("Razão Social: ");
  fgets(dadosHotel.razaoSocial, sizeof(dadosHotel.razaoSocial), stdin);

  printf("Inscrição Estadual: ");
  fgets(dadosHotel.inscricaoEstadual, sizeof(dadosHotel.inscricaoEstadual),
        stdin);
  printf("CNPJ: ");
  fgets(dadosHotel.cnpj, sizeof(dadosHotel.cnpj), stdin);
  printf("Endereço Completo: ");
  fgets(dadosHotel.enderecoCompleto, sizeof(dadosHotel.enderecoCompleto),
        stdin);
        toUpperCase(dadosHotel.enderecoCompleto);

  printf("Telefone: ");
  fgets(dadosHotel.telefone, sizeof(dadosHotel.telefone), stdin);

  printf("E-mail: ");
  fgets(dadosHotel.email, sizeof(dadosHotel.email), stdin);
  toUpperCase(dadosHotel.email);

  printf("Nome do Responsável: ");
  fgets(dadosHotel.nomeResponsavel, sizeof(dadosHotel.nomeResponsavel), stdin);
  toUpperCase(dadosHotel.nomeResponsavel);

  printf("Telefone do Responsável: ");
  fgets(dadosHotel.telefoneResponsavel, sizeof(dadosHotel.telefoneResponsavel),
        stdin);

  printf("Horário de check In: ");
  scanf("%d", &dadosHotel.horarioCheckIn);

  printf("Horário de check Out: ");
  scanf("%d", &dadosHotel.horarioCheckOut);

  printf("Lucro do Hotel: ");
  scanf("%f", &dadosHotel.lucro);

  dadosHotel.lucro = 0;

  getchar();

  dadosHotel.situacao = 0;

  return dadosHotel;
}

/*
 * Nome: mostrarHotelView
 * Parâmetro¹: void.
 * Return: struct
 * Author: Yuri
 * Função: Retorna struct do controller e exibe os dados do hotel.
 */

void mostrarHotelView() {

  cadastrarHotel temp;

  temp = retornarHotel();

  printf("Nome Fantasia: %s\n", temp.nomeFantasia);
  printf("Razão Social: %s\n", temp.razaoSocial);
  printf("Inscrição Estadual: %s\n", temp.inscricaoEstadual);
  printf("CNPJ: %s\n", temp.cnpj);
  printf("Endereço Completo: %s\n", temp.enderecoCompleto);
  printf("Telefone: %s\n", temp.telefone);
  printf("E-mail: %s\n", temp.email);
  printf("Nome do Responsável: %s\n", temp.nomeResponsavel);
  printf("Telefone do Responsável: %s\n", temp.telefoneResponsavel);
  printf("Horário de check In: %d\n\n", temp.horarioCheckIn);
  printf("Horário do check Out: %d\n\n", temp.horarioCheckOut);
  printf("Lucro: %.2f\n\n", temp.lucro);
}

/*
 * Nome: AtualizarHotelView
 * Parâmetro¹: void.
 * Return: struct
 * Author: Yuri
 * Função: Altera os dados já cadastrados do hotel.
 */

cadastrarHotel atualizarHotelView() {

  int opc = 20;

  cadastrarHotel alterarDadosHotel;

  alterarDadosHotel = retornarHotel();

  alterarDadosHotel.situacao = 1;

  while (opc != 0) {

    printf("\n\nALTERAÇÃO DE DADOS\n\n");

    printf("1. Nome Fantasia \n"
           "2. Razão Social\n"
           "3. Inscrição Estadual\n"
           "4. CNPJ\n"
           "5. Endereço Completo\n"
           "6. Telefone\n"
           "7. E-Mail\n"
           "8. Nome do Responsável\n"
           "9. Telefone do Responsável\n"
           "10. Horário de Check-in\n"
           "11. Horário de Check-out\n"
           "12. Lucro\n"
           "0. Voltar\n\n");

    scanf("%d", &opc);

    getchar();

    if (opc == 1) {

      printf("Digite o novo Nome Fantasia: ");
      fgets(alterarDadosHotel.nomeFantasia,
            sizeof(alterarDadosHotel.nomeFantasia), stdin);
            toUpperCase(alterarDadosHotel.nomeFantasia);

    } else if (opc == 2) {

      printf("Digite a nova Razão Social: ");
      fgets(alterarDadosHotel.razaoSocial,
            sizeof(alterarDadosHotel.razaoSocial), stdin);

    } else if (opc == 3) {

      printf("Digite a nova Inscrição Estadual: ");
      fgets(alterarDadosHotel.inscricaoEstadual,
            sizeof(alterarDadosHotel.inscricaoEstadual), stdin);

    } else if (opc == 4) {

      printf("Digite o novo CNPJ: ");
      fgets(alterarDadosHotel.cnpj, sizeof(alterarDadosHotel.cnpj), stdin);

    } else if (opc == 5) {

      printf("Digite o novo Endereço: ");
      fgets(alterarDadosHotel.enderecoCompleto,
            sizeof(alterarDadosHotel.enderecoCompleto), stdin);
            toUpperCase(alterarDadosHotel.enderecoCompleto);
    } else if (opc == 6) {

      printf("Digite o novo Telefone: ");
      fgets(alterarDadosHotel.telefone, sizeof(alterarDadosHotel.telefone),
            stdin);

    } else if (opc == 7) {

      printf("Digite o novo E-mail: ");
      fgets(alterarDadosHotel.email, sizeof(alterarDadosHotel.email), stdin);
      toUpperCase(alterarDadosHotel.email);
    } else if (opc == 8) {

      printf("Digite o novo Nome do Responsável: ");
      fgets(alterarDadosHotel.nomeResponsavel,
            sizeof(alterarDadosHotel.nomeResponsavel), stdin);
            toUpperCase(alterarDadosHotel.nomeResponsavel);

    } else if (opc == 9) {

      printf("Digite o novo Telefone do Responsável: ");
      fgets(alterarDadosHotel.telefoneResponsavel,
            sizeof(alterarDadosHotel.telefoneResponsavel), stdin);

    } else if (opc == 10) {

      printf("Digite o novo Horário de check In: ");
      scanf("%d", &alterarDadosHotel.horarioCheckIn);

    } else if (opc == 11) {

      printf("Digite o novo Horário de check Out: ");
      scanf("%d", &alterarDadosHotel.horarioCheckOut);
    }
     else if (opc == 12) {

      printf("Digite a nova porcentagem de lucro: ");
      scanf("%f", &alterarDadosHotel.lucro);
    }

    getchar();
  }

  alterarDadosHotel.situacao = 0;

  return alterarDadosHotel;
}

/*
 * Nome: cadastrarHotelView
 * Parâmetro¹: void.
 * Return: struct
 * Author: Yuri
 * Função: exclui os dados cadastrados do hotel.
 */

cadastrarHotel excluirHotelView() {

  int excluirDados;
  char naoCadastrado[40] = "Não cadastrado";
  cadastrarHotel excluirHotel;

  printf("/-/-/-/-/-/-/EXCLUIR/-/-/-/-/-/-/\n\n");
  printf("Tem certeza que deseja excluir todos os dados ?\n"
         "1. Sim\n"
         "2. Não\n");

  scanf("%d", &excluirDados);

  excluirHotel.situacao = 1;

  if (excluirDados == 1) {

    strcpy(excluirHotel.cnpj, naoCadastrado);
    strcpy(excluirHotel.email, naoCadastrado);
    strcpy(excluirHotel.enderecoCompleto, naoCadastrado);
    strcpy(excluirHotel.inscricaoEstadual, naoCadastrado);
    strcpy(excluirHotel.nomeFantasia, naoCadastrado);
    strcpy(excluirHotel.nomeResponsavel, naoCadastrado);
    strcpy(excluirHotel.razaoSocial, naoCadastrado);
    strcpy(excluirHotel.telefone, naoCadastrado);
    strcpy(excluirHotel.telefoneResponsavel, naoCadastrado);
    excluirHotel.horarioCheckIn = 0;
    excluirHotel.horarioCheckOut = 0;
    excluirHotel.lucro = 0;

  }

  excluirHotel.situacao = 0;

  return excluirHotel;
}

void erroImportarHotel() {

  printf("PROBLEMAS NA CRIAÇÃO DO ARQUIVO\n");

}
void erroExportarHotel() {

  printf("PROBLEMAS NA CRIAÇÃO DO ARQUIVO\n");
}
void inicializarContadorHotel(int contHotel) {

  cont=contHotel;

}
