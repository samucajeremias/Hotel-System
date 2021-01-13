#include "../Model/basicoModel.h"
reserva *gVetorReservas;
int gTamVetorReservas = 0;

void salvaReservaController(reserva reservaView, int contReserva) {

    if (contReserva == 0) {

        gVetorReservas = malloc(TAMANHO * sizeof (reserva));

        gTamVetorReservas = TAMANHO;

    } else if (gTamVetorReservas == contReserva) {

        gTamVetorReservas = gTamVetorReservas + TAMANHO;

        gVetorReservas =
                realloc(gVetorReservas, gTamVetorReservas * sizeof (reserva));
    }

    gVetorReservas[contReserva] = reservaView;
}

reserva *retornarReservasController() {
    return gVetorReservas;
}

void excluirReservaController(int posicao) {

    if (gTamVetorReservas == 1) {

        gTamVetorReservas--;
        free(gVetorReservas);

    } else {

        gVetorReservas[posicao] = gVetorReservas[gTamVetorReservas - 1];
        gTamVetorReservas = gTamVetorReservas - 1;
        gVetorReservas =
                realloc(gVetorReservas, gTamVetorReservas * sizeof (reserva));
    }
}

void importarReservaController() {

    FILE *arquivoReserva;

    arquivoReserva = fopen("arquivoReserva.bin", "rb");

    if (!arquivoReserva) {

        erroImportarReserva();
        exit(1);
    }

    fread(&gTamVetorReservas, sizeof (int), 1, arquivoReserva);

    importarReservaBinariaView(gTamVetorReservas);
    gVetorReservas = malloc(gTamVetorReservas * sizeof (reserva));

    fread(gVetorReservas, sizeof (reserva), gTamVetorReservas, arquivoReserva);
    int fflush(FILE * arquivoReserva);
    fclose(arquivoReserva);
}

void exportarReservaController() {

    FILE *arquivoReserva;

    arquivoReserva = fopen("arquivoReserva.bin", "wb");

    if (!arquivoReserva) {

        erroExportarReserva();
        exit(1);
    }

    fwrite(&gTamVetorReservas, sizeof (int), 1, arquivoReserva);

    fwrite(gVetorReservas, sizeof (reserva), gTamVetorReservas, arquivoReserva);
    int fflush(FILE * arquivoReserva);
    fclose(arquivoReserva);
}

// Verifica se a reserva informada existe mesmo

int verificaReservaCodigoController(int pCodigoReserva) {
    int i;

    for (i = 0; i < gTamVetorReservas; i++) {

        if (pCodigoReserva == gVetorReservas[i].codigoReserva) {

            return 1;
        }
    }

    return 0;
}

reserva buscarReservaCodigoController(int pCodigoReserva) {
    int i, posicao;

    for (i = 0; i < gTamVetorReservas; i++) {

        if (pCodigoReserva == gVetorReservas[i].codigoReserva) {
            posicao = i;
        }
    }

    return gVetorReservas[posicao];
}
