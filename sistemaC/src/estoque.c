#include <stdio.h>
#include <string.h>

#define ARQUIVO "estoques.txt"
#define produtos_limite 100

struct Produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
};

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarProduto(struct Produto produtos[], int *quantidadeCadastrada) {
    if (*quantidadeCadastrada >= produtos_limite) {
        printf("\nLimite de produtos atingido!\n");
        return;
    }

    int idx = *quantidadeCadastrada;
    int codigo_temp, duplicado;
    char entradaCod[50];

    printf("\n--- CADASTRO DO PRODUTO %d ---\n", idx + 1);

    while (1) {
        printf("Digite o codigo do produto (apenas numeros): ");
        scanf("%49s", entradaCod);
        limparBuffer();

        int apenasNumeros = 1;
        for (int i = 0; entradaCod[i] != '\0'; i++) {
            if (entradaCod[i] < '0' || entradaCod[i] > '9') {
                apenasNumeros = 0;
                break;
            }
        }

        if (!apenasNumeros) {
            printf("Codigo invalido! Digite apenas numeros.\n");
            continue;
        }

        codigo_temp = 0;
        for (int i = 0; entradaCod[i] != '\0'; i++) {
            codigo_temp = codigo_temp * 10 + (entradaCod[i] - '0');
        }

        duplicado = 0;
        for (int j = 0; j < idx; j++) {
            if (produtos[j].codigo == codigo_temp) {
                duplicado = 1;
                break;
            }
        }

        if (duplicado) {
            printf("Este codigo ja existe! Tente outro.\n");
        } else {
            produtos[idx].codigo = codigo_temp;
            break;
        }
    }

    printf("Digite o nome do produto: ");
    fgets(produtos[idx].nome, sizeof(produtos[idx].nome), stdin);
    produtos[idx].nome[strcspn(produtos[idx].nome, "\n")] = '\0';

    printf("Digite o preco do produto: R$ ");
    while (scanf("%f", &produtos[idx].preco) != 1 || produtos[idx].preco < 0) {
        printf("Preco invalido. Digite novamente: R$ ");
        limparBuffer();
    }
    limparBuffer();

    printf("Digite a quantidade em estoque: ");
    while (scanf("%d", &produtos[idx].quantidade) != 1 || produtos[idx].quantidade < 0) {
        printf("Quantidade invalida. Digite novamente: ");
        limparBuffer();
    }
    limparBuffer();

    (*quantidadeCadastrada)++;
    printf("\nProduto cadastrado com sucesso!\n");
}

void listarProdutos(struct Produto produtos[], int quantidadeCadastrada) {
    if (quantidadeCadastrada == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    printf("\n--- LISTA DE PRODUTOS ---\n");
    for (int i = 0; i < quantidadeCadastrada; i++) {
        printf("Codigo: %d | Nome: %s | Preco: R$ %.2f | Qtd: %d\n",
               produtos[i].codigo,
               produtos[i].nome,
               produtos[i].preco,
               produtos[i].quantidade);
    }
}

void consultarProduto(struct Produto produtos[], int quantidadeCadastrada) {
    if (quantidadeCadastrada == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    int codBusca, achou = 0;

    printf("\n--- CONSULTAR PRODUTO ---\n");
    printf("Digite o codigo do produto: ");
    if (scanf("%d", &codBusca) != 1) {
        printf("Codigo invalido.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    for (int i = 0; i < quantidadeCadastrada; i++) {
        if (produtos[i].codigo == codBusca) {
            printf("\nEncontrado -> Codigo: %d | Nome: %s | Preco: R$ %.2f | Qtd: %d\n",
                   produtos[i].codigo,
                   produtos[i].nome,
                   produtos[i].preco,
                   produtos[i].quantidade);
            achou = 1;
            break;
        }
    }

    if (!achou) {
        printf("\nProduto nao encontrado!\n");
    }
}

void alterarProduto(struct Produto produtos[], int quantidadeCadastrada) {
    if (quantidadeCadastrada == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    int codBusca, achou = 0;

    printf("\n--- ALTERAR PRODUTO ---\n");
    printf("Digite o codigo do produto: ");
    if (scanf("%d", &codBusca) != 1) {
        printf("Codigo invalido.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    for (int i = 0; i < quantidadeCadastrada; i++) {
        if (produtos[i].codigo == codBusca) {
            printf("Digite o novo nome: ");
            fgets(produtos[i].nome, sizeof(produtos[i].nome), stdin);
            produtos[i].nome[strcspn(produtos[i].nome, "\n")] = '\0';

            printf("Digite o novo preco: R$ ");
            while (scanf("%f", &produtos[i].preco) != 1 || produtos[i].preco < 0) {
                printf("Preco invalido. Digite novamente: R$ ");
                limparBuffer();
            }
            limparBuffer();

            printf("Digite a nova quantidade: ");
            while (scanf("%d", &produtos[i].quantidade) != 1 || produtos[i].quantidade < 0)
            {
                printf("Quantidade invalida. Digite novamente: ");
                limparBuffer();
            }
            limparBuffer();

            printf("\nProduto alterado com sucesso!\n");
            achou = 1;
            break;
        }
    }

    if (!achou) {
        printf("\nProduto nao encontrado!\n");
    }
}

void excluirProduto(struct Produto produtos[], int *quantidadeCadastrada) {
    if (*quantidadeCadastrada == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    int codBusca, achou = 0;

    printf("\n--- EXCLUIR PRODUTO ---\n");
    printf("Digite o codigo do produto: ");
    if (scanf("%d", &codBusca) != 1) {
        printf("Codigo invalido.\n");
        limparBuffer();
        return;
    }
    limparBuffer();

    for (int i = 0; i < *quantidadeCadastrada; i++) {
        if (produtos[i].codigo == codBusca) {
            for (int j = i; j < *quantidadeCadastrada - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            (*quantidadeCadastrada)--;
            achou = 1;
            printf("\nProduto excluido com sucesso!\n");
            break;
        }
    }

    if (!achou) {
        printf("\nProduto nao encontrado!\n");
    }
}

void verificarEstoque(struct Produto produtos[], int quantidadeCadastrada) {
    if (quantidadeCadastrada == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    printf("\n--- SITUACAO DO ESTOQUE ---\n");
    for (int i = 0; i < quantidadeCadastrada; i++) {
        printf("\nCodigo: %d | Nome: %s | Quantidade: %d | ",
               produtos[i].codigo,
               produtos[i].nome,
               produtos[i].quantidade);

        if (produtos[i].quantidade == 0) {
            printf("ESTOQUE ESGOTADO\n");
        } else if (produtos[i].quantidade <= 5) {
            printf("ESTOQUE BAIXO\n");
        } else {
            printf("ESTOQUE NORMAL\n");
        }
    }
}

void calcularTotalEstoque(struct Produto produtos[], int quantidadeCadastrada) {
    if (quantidadeCadastrada == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    float total = 0;
    for (int i = 0; i < quantidadeCadastrada; i++) {
        total += produtos[i].preco * produtos[i].quantidade;
    }

    printf("\n--- VALOR TOTAL DO ESTOQUE ---\n");
    printf("Valor total: R$ %.2f\n", total);
}

void maiorValorEstoque(struct Produto produtos[], int quantidadeCadastrada) {
    if (quantidadeCadastrada == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    int maior = 0;
    for (int i = 1; i < quantidadeCadastrada; i++) {
        if (produtos[i].preco * produtos[i].quantidade >
            produtos[maior].preco * produtos[maior].quantidade) {
            maior = i;
        }
    }

    printf("\nProduto com maior valor em estoque: %s (R$ %.2f)\n",
           produtos[maior].nome,
           produtos[maior].preco * produtos[maior].quantidade);
}

void menorValorEstoque(struct Produto produtos[], int quantidadeCadastrada) {
    if (quantidadeCadastrada == 0) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    int menor = 0;
    for (int i = 1; i < quantidadeCadastrada; i++) {
        if (produtos[i].preco * produtos[i].quantidade <
            produtos[menor].preco * produtos[menor].quantidade) {
            menor = i;
        }
    }

    printf("\nProduto com menor valor em estoque: %s (R$ %.2f)\n",
           produtos[menor].nome,
           produtos[menor].preco * produtos[menor].quantidade);
}

void ordenarProdutos(struct Produto produtos[], int quantidadeCadastrada) {
    struct Produto temp;

    for (int i = 0; i < quantidadeCadastrada - 1; i++) {
        for (int j = 0; j < quantidadeCadastrada - 1 - i; j++) {
            if (produtos[j].codigo > produtos[j + 1].codigo) {
                temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
}

void salvarDados(struct Produto produtos[], int quantidadeCadastrada) {
    FILE *arqSalvar = fopen(ARQUIVO, "w");

    if (arqSalvar == NULL) {
        printf("\nErro ao abrir arquivo para salvar!\n");
        return;
    }

    for (int i = 0; i < quantidadeCadastrada; i++) {
        fprintf(arqSalvar, "%d,%s,%.2f,%d\n",
                produtos[i].codigo,
                produtos[i].nome,
                produtos[i].preco,
                produtos[i].quantidade);
    }

    fclose(arqSalvar);
    printf("\nDados salvos com sucesso!\n");
}

void carregarDados(struct Produto produtos[], int *quantidadeCadastrada) {
    FILE *arqCarregar = fopen(ARQUIVO, "r");

    if (arqCarregar == NULL) {
        return;
    }

    *quantidadeCadastrada = 0;

    while (*quantidadeCadastrada < produtos_limite &&
           fscanf(arqCarregar, "%d,%49[^,],%f,%d\n",
                  &produtos[*quantidadeCadastrada].codigo,
                  produtos[*quantidadeCadastrada].nome,
                  &produtos[*quantidadeCadastrada].preco,
                  &produtos[*quantidadeCadastrada].quantidade) == 4) {
        (*quantidadeCadastrada)++;
    }

    fclose(arqCarregar);
    printf("\nDados carregados com sucesso! (%d produtos)\n",
           *quantidadeCadastrada);
}

int main() {
    struct Produto produtos[produtos_limite];
    int quantidadeCadastrada = 0;
    int opcao = 0;

    carregarDados(produtos, &quantidadeCadastrada);

    do {
        printf("\n=================================================\n");
        printf("         SISTEMA DE CONTROLE DE ESTOQUE          \n");
        printf("=================================================\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Consultar produto\n");
        printf("4 - Alterar produto\n");
        printf("5 - Excluir produto\n");
        printf("6 - Verificar estoque\n");
        printf("7 - Calcular valor total do estoque\n");
        printf("8 - Mostrar produto de maior valor\n");
        printf("9 - Mostrar produto de menor valor\n");
        printf("10 - Ordenar produtos\n");
        printf("11 - Salvar dados\n");
        printf("12 - Carregar dados\n");
        printf("13 - Sair\n");
        printf("=================================================\n");
        printf("Digite uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida! Digite apenas numeros de 1 a 13.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        if (opcao < 1 || opcao > 13) {
            printf("\nOpcao invalida! Escolha um numero entre 1 e 13.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &quantidadeCadastrada);
                break;
            case 2:
                listarProdutos(produtos, quantidadeCadastrada);
                break;
            case 3:
                consultarProduto(produtos, quantidadeCadastrada);
                break;
            case 4:
                alterarProduto(produtos, quantidadeCadastrada);
                break;
            case 5:
                excluirProduto(produtos, &quantidadeCadastrada);
                break;
            case 6:
                verificarEstoque(produtos, quantidadeCadastrada);
                break;
            case 7:
                calcularTotalEstoque(produtos, quantidadeCadastrada);
                break;
            case 8:
                maiorValorEstoque(produtos, quantidadeCadastrada);
                break;
            case 9:
                menorValorEstoque(produtos, quantidadeCadastrada);
                break;
            case 10:
                if (quantidadeCadastrada == 0) {
                    printf("\nNenhum produto cadastrado!\n");
                    break;
                }
                ordenarProdutos(produtos, quantidadeCadastrada);
                printf("\nProdutos ordenados por codigo com sucesso!\n");
                break;
            case 11:
                salvarDados(produtos, quantidadeCadastrada);
                break;
            case 12:
                carregarDados(produtos, &quantidadeCadastrada);
                break;
            case 13:
                salvarDados(produtos, quantidadeCadastrada);
                printf("\nSaindo do sistema. Ate logo!\n");
                break;
        }
    } while (opcao != 13);

    return 0;
}
