#include "../Model/basicoModel.h"
/*
 * Nome: toUpperCase()
 * Parâmetro¹: char *pString.
 * Return: Void.
 * Author: João Geraldo
 * Função: Recebe o enderco de memoria da string e a transforma em string com letras
 * maiusculas
 */
void toUpperCase(char *pString) {
    int i;

    for (i = 0; i < strlen(pString); i++) {

        pString[i] = toupper(pString[i]);

    }
}
