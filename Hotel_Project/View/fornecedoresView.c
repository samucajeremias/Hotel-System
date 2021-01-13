#include "../Model/fornecedoresModel.h"

/*
 * Nome: fornecedoresView
 * Parâmetro: -
 * Return: void
 * Author: Igor Jeremias
 * Função: Menu de opções
 */

static int contadorFornecedores = 0;

void fornecedoresView(){

    int op;
    fornecedores temp;
    int condicao;
    int codigo;

    while (op != 6){
        printf("1- Adicionar fornecedor\n2- Remover fornecedor\n3- Atualizar "
                "fornecedor\n4- Informações sobre o fornecedor\n5- Lista de "
                "fornecedores\n6- Sair\nEscolha sua opção: ");
        scanf("%d", &op);

        switch (op){
            case 1:
                temp = adicionarFornecedorView(temp, contadorFornecedores);
                condicao = salvarFornecedorController(temp, contadorFornecedores);
                if (condicao == 0){
                    printf("\nCadastro bem-sucedido\n\n");
                    contadorFornecedores++;
                } else
                    printf("\nFalha ao cadastrar fornecedor\n\n");
                break;
            case 2:
                condicao = removerFornecedorView();
                if (condicao == 0){
                    printf("\nRemoção bem-sucedida\n\n");
                    contadorFornecedores--;
                } else
                    printf("\nFalha ao remover fornecedor\n\n");
                break;
            case 3:
                condicao = atualizarFornecedorView();
                if (condicao == 0){
                    printf("\nFornecedor atualizado com sucesso\n\n");
                } else
                    printf("\nFalha ao atualizar fornecedor\n\n");
                break;
            case 4:
                informacaoFornecedorView();
                break;
            case 5:
                if (contadorFornecedores == 0){
                    printf("\nNão há nenhum fornecedor cadastrado\n\n");
                } else
                    mostrarFornecedoresView(contadorFornecedores);
                break;
            case 6:
                printf("\nAté logo\n\n");
                break;
            default:
                printf("\nOpção inválida\n\n");
                break;
        }
    }

}

/*
 * Nome: adicionarFornecedorView
 * Parâmetro: -
 * Return: int
 * Author: Igor Jeremias
 * Função: Cadastrar fornecedor
 */

fornecedores adicionarFornecedorView (){

    fornecedores cadastro;

    getchar();

    printf("Digite o nome fantasia do fornecedor: ");
    fgets(cadastro.nome, sizeof (cadastro.nome), stdin);
    toUpperCase(cadastro.nome);

    printf("Digite a razão social do fornecedor: ");
    fgets(cadastro.razao, sizeof (cadastro.razao), stdin);

    printf("Digite a inscrição estadual do fornecedor: ");
    fgets(cadastro.inscricao, sizeof (cadastro.inscricao), stdin);

    printf("Digite o CNPJ do fornecedor: ");
    fgets(cadastro.cnpj, sizeof (cadastro.cnpj), stdin);

    printf("Digite o endereço completo do fornecedor: ");
    fgets(cadastro.endereco, sizeof (cadastro.endereco), stdin);
    toUpperCase(cadastro.endereco);

    printf("Digite o telefone do fornecedor: ");
    fgets(cadastro.telefone, sizeof (cadastro.telefone), stdin);

    printf("Digite o e-mail do fornecedor: ");
    fgets(cadastro.email, sizeof (cadastro.email), stdin);
    toUpperCase(cadastro.email);

    //cadastro bem-sucedido;
    return cadastro;
}

/*
 * Nome: removerFornecedorView
 * Parâmetro: -
 * Return: int
 * Author: Igor Jeremias
 * Função: Remover fornecedor
 */

int removerFornecedorView() {
    int codigo, achou = 0;
    fornecedores temp;

    printf("Digite o código do fornecedor que deseja remover: ");
    scanf("%d", &codigo);

    temp = informacaoFornecedorController(codigo, &achou);

    if (achou == 0) {
        printf("\nFornecedor não encontrado\n\n");
    } else {
        return removerFornecedorController(codigo);
    }
}

/*
 * Nome: atualizarFornecedorView
 * Parâmetro: -
 * Return: int
 * Author: Igor Jeremias
 * Função: Atualizar fornecedor
 */

int atualizarFornecedorView(){

    int codigo, achou = 0;
    fornecedores temp;

    printf("Digite o código do fornecedor: ");
    scanf("%d", &codigo);

    temp = informacaoFornecedorController(codigo, &achou);

    if (achou == 0){
        printf("\nFornecedor não encontrado\n\n");
    } else {
        getchar();

        printf("Digite o nome fantasia do fornecedor: ");
        fgets(temp.nome, sizeof (temp.nome), stdin);
        toUpperCase(temp.nome);

        printf("Digite a razão social do fornecedor: ");
        fgets(temp.razao, sizeof (temp.razao), stdin);

        printf("Digite a inscrição estadual do fornecedor: ");
        fgets(temp.inscricao, sizeof (temp.inscricao), stdin);

        printf("Digite o CNPJ do fornecedor: ");
        fgets(temp.cnpj, sizeof (temp.cnpj), stdin);

        printf("Digite o endereço completo do fornecedor: ");
        fgets(temp.endereco, sizeof (temp.endereco), stdin);
        toUpperCase(temp.endereco);

        printf("Digite o telefone do fornecedor: ");
        fgets(temp.telefone, sizeof (temp.telefone), stdin);

        printf("Digite o e-mail do fornecedor: ");
        fgets(temp.email, sizeof (temp.email), stdin);
        toUpperCase(temp.email);
    }

    return atualizarFornecedorController(temp, codigo);
}

/*
 * Nome: mostrararFornecedoresView
 * Parâmetro: int contadorFornecedores
 * Return: int
 * Author: Igor Jeremias
 * Função: Mostrar lista de fornecedores
 */

void mostrarFornecedoresView(int contadorFornecedores){

    int i;
    fornecedores *mostrar;

    mostrar = retornarListaFornecedoresController();
    for (i = 0; i < contadorFornecedores; i++){
        printf("\nFornecedor %d\nNome fantasia: %sRazão Social: %sInscrição "
                "estadual: %sCNPJ: %sEndereço: %sTelefone: %sE-mail: %s"
                "\n", mostrar[i].codigo, mostrar[i].nome, mostrar[i].razao,
                mostrar[i].inscricao, mostrar[i].cnpj, mostrar[i].endereco,
                mostrar[i].telefone, mostrar[i].email);
    }

}

/*
 * Nome: informacaoFornecedoresView
 * Parâmetro: -
 * Return: int
 * Author: Igor Jeremias
 * Função: Obter informação sobre um fornecedor
 */

int informacaoFornecedorView(){

    int codigo, achou = 0;
    fornecedores temp;

    printf("Digite o código do fornecedor: ");
    scanf("%d", &codigo);

    temp = informacaoFornecedorController(codigo, &achou);

    if (achou == 1){
        printf("\nFornecedor %d\nNome fantasia: %sRazão Social: %sInscrição "
                "estadual: %sCNPJ: %sEndereço: %sTelefone: %sE-mail: %s"
                "\n", temp.codigo, temp.nome, temp.razao,
                temp.inscricao, temp.cnpj, temp.endereco,
                temp.telefone, temp.email);
    } else
        printf("\nFornecedor não encontrado\n\n");

    return 0;
}

void erroImportarFornecedor(){

  printf("PROBLEMAS NA CRIAÇÃO DO ARQUIVO\n");

}

void erroExportarFornecedor(){

  printf("PROBLEMAS NA CRIAÇÃO DO ARQUIVO\n");

}

void inicializarContadorFornecedor(int contFornecedor) {

  contadorFornecedores = contFornecedor;

}
