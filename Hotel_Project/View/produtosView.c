#include "../Model/produdosModel.h"


/*
 * Nome: menuProdutosView()
 * Parâmetro¹: Void.
 * Return: Void
 * Author: Yuri
 * Função: Menu de opções para produtos
 */

static int contCadastroProduto = 0;
static int contCodigo = 1;

void menuProdutosView() {

    produtos temp;
    int retorno;

    do{

        printf("********MENU********\n\n\n"
               "1. Cadastrar\n"
               "2. Mostrar Produtos Cadastrados\n"
               "3. Busca por Código\n"
               "4. Alterar Produto\n"
               "5. Excluir Produto\n"
               "0. Sair\n");
        scanf("%d", &opcao);
        printf("%d\n", contCadastroProduto);
        switch (opcao) {

            case 0:

                break;

            case 1:

                temp = cadastrarProdutosView();

                cadastrarProdutosController(temp, contCadastroProduto);

                contCadastroProduto++;

                break;

            case 2:

                mostrarProdutosView(contCadastroProduto);

                break;

            case 3:

                buscarPorCodigo(contCadastroProduto);

                break;

            case 4:

                alterarProdutosView(contCadastroProduto);

                break;

            case 5:

                retorno = excluirProdutosView(contCadastroProduto);

                if (retorno == 1) {

                    contCadastroProduto--;

                }



                break;
        }


    } while(opcao != 0);




}

/*
 * Nome: cadastrarProdutosView
 * Parâmetro¹: Void.
 * Return: struct produtos
 * Author: Yuri
 * Função: cadastra um novo produto
 */

produtos cadastrarProdutosView(){

    produtos temp;

    temp.codigo = contCodigo;
    printf("Estoque do Produto: ");
    scanf("%d", &temp.estoque);
    printf("Estoque Mínimo: ");
    scanf("%d", &temp.estoqueMinimo);
    printf("Preço de Custo: ");
    scanf("%f", &temp.precoDeCusto);
    printf("Preço de Venda: ");
    scanf("%f", &temp.precoDeVenda);

    getchar();

    printf("Descrição: ");
    fgets(temp.descricao, sizeof(temp.descricao), stdin);
    toUpperCase(temp.descricao);

    contCodigo++;

    return temp;

}

/*
 * Nome: mostrarProdutosView()
 * Parâmetro¹: int contCadastroProduto.
 * Return: Void
 * Author: Yuri
 * Função: Mostra todos os produtos cadastrados.
 */
void mostrarProdutosView(int contCadastroProduto){

    produtos *temp;
    int i;


    temp = retornarProdutoController();

    if(contCadastroProduto > 0) {

        printf("*--*-*-*-*PRODUTOS CADASTRADOS-*-*-*-*-*\n\n\n");

        for(i = 0; i < contCadastroProduto; i++) {

            printf("%d. \n\n"
                   "Código: %d\n"
                   "Descrição: %s\n"
                   "Estoque: %d\n"
                   "Estoque Mínimo: %d\n"
                   "Preço de Custo: %f\n"
                   "Preço de Venda: %f\n\n", i+1, temp[i].codigo, temp[i].descricao, temp[i].estoque, temp[i].estoqueMinimo, temp[i].precoDeCusto, temp[i].precoDeVenda);

         }
    } else {

        printf("Não existem Produtos Cadastradas\n");

    }




}

/*
 * Nome: buscararPorCodigo
 * Parâmetro¹: int contCadastroProduto.
 * Return: Void
 * Author: Yuri
 * Função: Mostra o produto cadastrado de acordo com o código.
 */

void buscarPorCodigo(int contCadastroProduto) {

    int codigo;
    produtos temp;

    printf("Digite o código: ");
    scanf("%d", &codigo);



        temp = retornarPorCodigoController(codigo, contCadastroProduto);

        if(temp.codigo != -1) {

            printf("Código: %d\n"
                   "Descrição: %s\n"
                   "Estoque: %d\n"
                   "Estoque Mínimo: %d\n"
                   "Preço de Custo: %f\n"
                   "Preço de Venda: %f\n\n", temp.codigo, temp.descricao, temp.estoque, temp.estoqueMinimo, temp.precoDeCusto, temp.precoDeVenda);


        } else {

            printf("Código não encontrado!\n");

        }




}

/*
 * Nome: alterarProdutosView()
 * Parâmetro¹: int contCadastroProduto.
 * Return: Void
 * Author: Yuri
 * Função: Recebe a quantidade de produtos registrados por parâmetro, recebe os
 * novos dados e envia para o controller atualizar
 */

void alterarProdutosView(int contCadastroProduto){

    int codigo, opc = 1, i, j = 0 ;
    produtos *temp;
    produtos auxTemp;

    temp = retornarProdutoController();

    printf("Digite o código: ");
    scanf("%d", &codigo);

    for(i = 0; i < contCadastroProduto; i++) {

        if (temp[i].codigo == codigo) {

            auxTemp = temp[i];

            i = contCadastroProduto + 1;

        } else {

            auxTemp.codigo = -1;

        }
    }

    if (auxTemp.codigo != -1) {

        while (opc != 0) {

            printf("####MENU DE ALTERAÇÃO####\n\n\n"
                   "1. Descrição\n"
                   "2. Estoque\n"
                   "3. Estoque Minimo\n"
                   "4. Preço de Custo\n"
                   "5. Preço de Venda\n"
                   "0. Salvar\n");

            scanf("%d", &opc);

            if (opc == 1) {

                getchar();
                printf("Digite a nova Descrição: ");
                fgets(auxTemp.descricao, sizeof(auxTemp.descricao), stdin);
                toUpperCase(auxTemp.descricao);

            } else if (opc == 2) {

                getchar();

                printf("Digite a nova quantidade em estoque: ");
                scanf("%d", &auxTemp.estoque);

            }  else if (opc == 3) {

                printf("Digite a nova quantidade de estoqui mínimo: ");
                scanf("%d", &auxTemp.estoqueMinimo);

            } else if (opc == 4) {

                printf("Digite o novo preço de custo: ");
                scanf("%f", &auxTemp.precoDeCusto);

            } else if (opc == 5) {

                printf("Digite o novo preço de venda: ");
                scanf("%f", &auxTemp.precoDeVenda);

            }


        }

        alterarProdutosController(auxTemp, contCadastroProduto);

    } else {

        printf("Código não encontrado!\n");

    }


}

/*
 * Nome: excluirProdutosView()
 * Parâmetro¹: int contCadastroProduto.
 * Return: Void
 * Author: Yuri
 * Função: Recebe o código do produto que será excluido, se ele existir, será
 * deletado
 */
int excluirProdutosView(int contCadastroProduto){

    int codigo, condicao, retorno;

    printf("Qual o código do produto que deseja excluir: ");
    scanf("%d", &codigo);

    condicao = excluirProdutosController(codigo, contCadastroProduto);

    if (condicao != 0) {

        printf("Excluido!\n");

        retorno = 1;

    } else {

        printf("Código não encontrado!\n");

        retorno = 0;

    }

    return retorno;

}
void erroImportarProdutos() {


  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");

}

void erroExportarProdutos() {


  printf("PROBLEMA NA CRIACAO DO ARQUIVO BINÁRIO\n");

}

void importarProdutoBinarioView(int pContador) {
    contCadastroProduto = pContador;
    contCodigo = pContador + 1;
}
