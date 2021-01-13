#include "../Model/categoriaAcomodacaoModel.h"

/*
 * Nome: menuCategoriaAcomodacaoView
 * Parâmetro: int pOpcao serve para pular para a linha de listar categorias de acomodações
 * Return: int contadorCadastrados quantidade de categorias registradas
 * Author: Igor Jeremias
 * Função: Menu de opções
 */
int static contador = 0;


int menuCategoriaAcomodacaoView(int pOpcao){

    int op;
    categoria temp;
    int condicao;
    int codigo;

    if (pOpcao == 3) {
        goto parametro_3_CatAcomodacao;
    }

    do {
        printf(
            "O que deseja fazer?\n"
            "1- Cadastrar categoria\n"
            "2- Informação sobre a categoria\n"
            "3- Lista de categorias\n"
            "4- Atualizar definição da categoria\n"
            "5- Apagar categoria\n"
            "6- Sair\n"
            " Escolha sua opção: "
        );
        scanf("%d", &op);

        switch (op) {
            case 1:
                temp = cadastrar_acomodacao();
                condicao = salvarCategoriaAcomodacaoController(temp, contador);
                if (condicao == 0){
                    printf("\nCategoria de acomodação cadastrada com sucesso."
                            "\n\n");
                    contador++;
                } else
                    printf("\nFalha ao cadastrar categoria de acomodação.\n\n");
                break;
            case 2:
                //Passando 0 para nao entrar na condição do goto
                informacaoCategoriaView(0);
                break;
            case 3:
                parametro_3_CatAcomodacao:
                if (contador == 0){
                    printf("\nNão há nenhuma categoria registrada\n\n");

                    if (pOpcao == 3) {
                        op = 6;
                    }
                } else {

                    mostrarCategoriasView(contador);
                    if (pOpcao == 3) {
                        op = 6;
                    }
                }
                break;
            case 4:
                condicao = atualizarCategoriaView();
                if (condicao == 0){
                    printf("\nCategoria de acomodação atualizada com sucesso."
                            "\n\n");
                } else
                    printf("\nFalha ao atualizar categoria de acomodação.\n\n");
                break;
            case 5:
                condicao = removerCategoriaView();
                if (condicao == 0){
                    printf("\nCategoria de acomodação removida com sucesso."
                            "\n\n");
                    contador--;
                } else
                    printf("\nFalha ao remover categoria de acomodação.\n\n");
                break;
            case 6:
                printf("\nAté logo\n");
                break;
            default:
                printf("\nOpção inválida\n");
                break;
        }
    } while (op != 6);

    return contador;

}

/*
 * Nome: cadastrar_acomodacao
 * Parâmetro: -
 * Return: categoria
 * Author: Igor Jeremias
 * Função: Realiza o cadastro de acomodações
 */

categoria cadastrar_acomodacao(){

    categoria cadastro;

    getchar();

    printf("Escreva uma descrição para a categoria: ");
    fgets(cadastro.descricao, sizeof(cadastro.descricao), stdin);
    toUpperCase(cadastro.descricao);

    printf("Digite o valor da diária (R$): ");
    scanf("%f", &cadastro.precoDiaria);

    printf("Quantos adultos ela comporta?: ");
    scanf("%d", &cadastro.adultos);

    printf("Quantas crianças ela comporta?: ");
    scanf("%d", &cadastro.criancas);

    getchar();

    return cadastro;
}

/*
 * Nome: mostrarCategoriasView
 * Parâmetro: int contador
 * Return: void
 * Author: Igor Jeremias
 * Função: Mostrar as categorias cadastradas
 */

void mostrarCategoriasView(int contador){

    int i;
    categoria *mostrar;

    if (contador > 0) {
        printf("----------------------------------------------------\n");
        printf("\t\t\t            LISTA DE ACOMODAÇÕES              \n");
        printf("----------------------------------------------------\n");
    }
    mostrar = retornarListaController();
    for (i = 0; i < contador; i++){
        printf("\nCategoria %d\nDescrição: %sPreço da diária: R$%.2f\n"
                "Comporta %d adultos e %d crianças\n\n", mostrar[i].codigo,
                mostrar[i].descricao, mostrar[i].precoDiaria, mostrar[i].adultos,
                mostrar[i].criancas);
    }

}

/*
 * Nome: informacaoCategoriaView
 * Parâmetro: -
 * Return: void
 * Author: Igor Jeremias
 * Função: Visualiza determinada categoria pelo código digitado pelo usuário
 */

void informacaoCategoriaView(int pCodigo){

    int codigo, achou = 0;
    categoria temp;

    if (pCodigo != 0) {
        codigo = pCodigo;
        goto parametro_codigo_CatAcomodacao;
    }

    printf("Digite o código da categoria: ");
    scanf("%d", &codigo);

    parametro_codigo_CatAcomodacao:
    temp = informacaoCategoriaController(codigo, &achou);

    if (achou == 0){
        printf("\nCategoria não encontrada\n\n");
    } else {

        printf("\nDescrição: %sPreço da diária: R$%.2f\n"
        "Comporta %d adultos e %d crianças\n\n", temp.descricao,
         temp.precoDiaria, temp.adultos, temp.criancas);
    }

}

/*
 * Nome: atualizarCategoriaView
 * Parâmetro: -
 * Return: int
 * Author: Igor Jeremias
 * Função: Modificar categoria de acomodação
 */

int atualizarCategoriaView(){

    int codigo, achou = 0;
    categoria temp;

    printf("Digite o código da categoria: ");
    scanf("%d", &codigo);

    temp = informacaoCategoriaController(codigo, &achou);

    if (achou == 0){
        printf("\nCategoria não encontrada\n\n");
    } else {
        getchar();

        printf("Escreva uma descrição para a categoria: ");
        fgets(temp.descricao, sizeof (temp.descricao), stdin);
        toUpperCase(temp.descricao);

        printf("Digite o valor da diária (R$): ");
        scanf("%f", &temp.precoDiaria);

        printf("Quantos adultos ela comporta?: ");
        scanf("%d", &temp.adultos);

        printf("Quantas crianças ela comporta?: ");
        scanf("%d", &temp.criancas);

        getchar();

        return atualizarCategoriaAcomodacaoController(temp, codigo);
    }
}

/*
 * Nome: removerCategoriaView
 * Parâmetro: -
 * Return: int
 * Author: Igor Jeremias
 * Função: Remover categoria de acomodação
 */

int removerCategoriaView(){

    int codigo, achou = 0;
    categoria temp;

    printf("Digite o código da categoria que deseja remover: ");
    scanf("%d", &codigo);

    temp = informacaoCategoriaController(codigo, &achou);

    if (achou == 0){
        printf("\nCategoria não encontrada\n\n");
    } else {
        return removerCategoriaController(codigo);
    }

}
void erroExportarCategoriaAcomodacao() {

  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");

}
void erroImportarCategoriaAcomodacao() {

  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");

}

void inicializarContadorCatAcomodacao(int contadorCatAcomodacao) {

  contador = contadorCatAcomodacao;


}
