#include "../Model/basicoModel.h"

static int gQtdCheckOut = 0, gCodigoCheckOut = 1, gTamVetorCheckOut;
checkOut *gVetorCheckOut;

int salvarCheckOutController(checkOut salvaCheckOut) {

    int verificador;

    verificador = 0;
    if(gQtdCheckOut == 0) {

        
        gVetorCheckOut = malloc(TAMANHO * sizeof(checkOut));        

        gTamVetorCheckOut = TAMANHO;

    } else if(gTamVetorCheckOut == gQtdCheckOut) {

        gTamVetorCheckOut++;        
        gVetorCheckOut = realloc(gVetorCheckOut, gTamVetorCheckOut*sizeof(checkOut));        

    }


    salvaCheckOut.codigoCheckOut = gCodigoCheckOut;

    gVetorCheckOut[gQtdCheckOut] = salvaCheckOut;
    gCodigoCheckOut++;
    gQtdCheckOut++;

    verificador = 1;

    return verificador;

 }

 checkOut *retornaCheckOutController() {


     return gVetorCheckOut;

 }


 checkOut retornaCheckOutPorCodigo(int pCodigo) {

     int i, posicao;


     for(i = 0 ;i < gQtdCheckOut; i++) {

         if(pCodigo == gVetorCheckOut[i].codigoCheckOut) {

             posicao = i;

         }


     }

    return gVetorCheckOut[posicao];
 }

 void exportarCheckOutController() {

     FILE *arquivoCheckOut;

     arquivoCheckOut = fopen("arquivoCheckOut.bin", "wb");

     if(!arquivoCheckOut) {
         erroExportarCheckOut();
         exit(1);
     }

     fwrite(&gQtdCheckOut, sizeof(int), 1, arquivoCheckOut);
     fwrite(gVetorCheckOut, sizeof(checkOut), gTamVetorCheckOut, arquivoCheckOut);

     int fflush(FILE *arquivoCheckOut);

     fclose(arquivoCheckOut);



 }


 void importarCheckOutController() {

    FILE *arquivoCheckOut;

    arquivoCheckOut = fopen("arquivoCheckOut.bin", "rb");

    if(!arquivoCheckOut) {
         erroImportarCheckOut();
         exit(1);
     }

     fread(&gQtdCheckOut, sizeof(int), 1, arquivoCheckOut);

     gVetorCheckOut = malloc(gQtdCheckOut*sizeof(checkOut));

     fread(gVetorCheckOut, sizeof(checkOut), gQtdCheckOut, arquivoCheckOut);

     gTamVetorCheckOut = gQtdCheckOut;

     gCodigoCheckOut = gQtdCheckOut + 1;

     inicializarContadorCheckOutView(gQtdCheckOut);


     fclose(arquivoCheckOut);


 }

int verificarCheckOutController(int pCodigoReserva){
    int i, situacao = 0;
    
    for (i = 0; i < gQtdCheckOut; i++)
    {
        if (pCodigoReserva == gVetorCheckOut[i].reserva) 
        {
            situacao = 1;
        }
        
    }
    
    return situacao;
}