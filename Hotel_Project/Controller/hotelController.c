#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../Model/hotelModel.h"

// Vetor Global
cadastrarHotel hotelPrincipal;



/*
 * Nome: receberHotel
 * Parâmetro¹: struct cadastrarHotel recebeHotel.
 * Return: void
 * Author: Yuri
 * Função: recebe o hotel do view e o salva.
 */
void receberHotel(cadastrarHotel recebeHotel) {

    strcpy(hotelPrincipal.nomeFantasia, recebeHotel.nomeFantasia);
    strcpy(hotelPrincipal.razaoSocial, recebeHotel.razaoSocial);
    strcpy(hotelPrincipal.inscricaoEstadual, recebeHotel.inscricaoEstadual);
    strcpy(hotelPrincipal.cnpj, recebeHotel.cnpj);
    strcpy(hotelPrincipal.enderecoCompleto, recebeHotel.enderecoCompleto);
    strcpy(hotelPrincipal.telefone, recebeHotel.telefone);
    strcpy(hotelPrincipal.email, recebeHotel.email);
    strcpy(hotelPrincipal.nomeResponsavel, recebeHotel.nomeResponsavel);
    strcpy(hotelPrincipal.telefoneResponsavel, recebeHotel.telefoneResponsavel);
    hotelPrincipal.horarioCheckIn = recebeHotel.horarioCheckIn;
    hotelPrincipal.horarioCheckOut = recebeHotel.horarioCheckOut;
    hotelPrincipal.lucro = recebeHotel.lucro;

}

/*
 * Nome: retornarHotel
 * Parâmetro¹: struct cadastrarHotel retornarHotel.
 * Return: struct
 * Author: Yuri
 * Função: retorna hotel para ser exibido no view.
 */

cadastrarHotel retornarHotel() {


    return hotelPrincipal;
}

/*void tipoSave(cadastrarHotel pDados) {

    pForma = tipoSalvamento();

    if (pForma == 1) { //Salvar na memoria ram

        receberHotel(pDados);

    } else if (pForma == 2) { //Salvar em arquivo binario

    } else { //Salvar arquivo de texto

    }
}
*/
void exportarHotelController() {
  FILE *arquivoHotel;

  arquivoHotel = fopen("arquivoHotel.bin", "wb");

  if(!arquivoHotel) {
    erroExportarHotel();
    exit(1);
  }

  fwrite(&hotelPrincipal, sizeof(cadastrarHotel), 1, arquivoHotel);

  int fflush(FILE *arquivoHotel);

  fclose(arquivoHotel);
}
void importarHotelController(){

    FILE *arquivoHotel;
    arquivoHotel = fopen("arquivoHotel.bin", "rb");

    if (!arquivoHotel) {

        erroImportarHotel();
        exit(1);
    }

inicializarContadorHotel(1);

    fread(&hotelPrincipal, sizeof(cadastrarHotel), 1, arquivoHotel);

    fclose(arquivoHotel);
}
