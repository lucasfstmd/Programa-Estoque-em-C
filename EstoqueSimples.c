
#include <stdio.h>

#define true 1
#define false 0

int pararPrograma = false;

struct produtosDat{
  int registro;
  char nome[ 50 ];
  int quantidade;
  double custo;
};

void listaProdutos();
int interface();
int parar();
void atualizacao();
void atualizacao_qnt();
void atualizacao_custo();
void novoProduto();
void deletaProduto();
void deletaProdutoQnt(int registro);

int main(){
  while (!pararPrograma) {
    interface();
  }
  printf("\nPrograma fechado.\n");
  return false;
}

int interface(){


  FILE *abPtr;
    int escolha;

    if ((abPtr = fopen("hardware.dat", "rb+")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
    }

    else{

  printf(
    "\nDigite [1] para excluir um registro.\n"
    "Digite [2] para atualizar.\n"
    "Digite [3] para adicionar uma nova ferramenta.\n"
    "Digite [4] para exibir a lista.\n"
    "Digite [5] para sair.\n");

    printf("\nSua escolha: ");
    scanf("%d", &escolha);

    switch(escolha){
          case 1:
            deletaProduto(abPtr);
            break;
          case 2:
            atualizacao(abPtr);
            break;
          case 3:
            novoProduto(abPtr);
            break;
          case 4:
            listaProdutos();
            break;
          case 5:
              pararPrograma = true;
              break;
          default:
            printf("Escolha nao disponivel.\n");
            break;
        }
      }



  return 0;

}

void listaProdutos(){

    FILE *abPtr;

    struct produtosDat produtos = { 0, "", 0, 0.0 };

    if ((abPtr = fopen("hardware.dat", "rb")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
    }
    else{
        printf("\n%-11s%-28s%-15s%10s\n", "Registro", "Nome", "Quantidade", "Custo");

        while(!feof(abPtr)){
            fread(&produtos, sizeof(struct produtosDat), 1, abPtr);

            if (produtos.registro != 0){
                printf("%-11d%-28s%-15d%10.2f\n", produtos.registro, produtos.nome, produtos.quantidade, produtos.custo);
            }
        }
        
        fclose(abPtr);
    }

    return 0;

}

void atualizacao(){

  int escolha;

    printf(
      "\nDigite [1] para atualizar a quantidade\n"
      "Digite [2] para atualizar o custo\n"
      "Digite [3] para voltar ao menu\n");

    scanf("%d", &escolha);

      switch (escolha){
        case 1:
          atualizacao_qnt();
          break;
        case 2:
          atualizacao_custo();
          break;
        case 3:
          interface();
          break;
        default:
          printf("Escolha invalida.\n");
          atualizacao();
          break;
      }

}

void atualizacao_qnt(){

  FILE *abPtr;
    int registro;
    int quantidade;
    int escolha;

    struct produtosDat produtos = { 0, "", 0, 0.0 };

    if ((abPtr = fopen("hardware.dat", "rb+")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
    }
    else{
        printf("\nDigite o registro: ");
        scanf("%d", &registro);

        fseek(abPtr, (registro - 1) * sizeof(struct produtosDat), SEEK_SET);
        fread(&produtos, sizeof(struct produtosDat), 1, abPtr);

        if (produtos.registro == 0){
            printf("Registro nao existe.\n");
        }
        else {

        struct produtosDat produtos = { 0, "", 0, 0.0 };

        fseek(abPtr, (registro - 1) * sizeof(struct produtosDat), SEEK_SET);
        fread(&produtos, sizeof(struct produtosDat), 1, abPtr);

        printf("\n%-11s%-28s%-15s%10s\n", "Registro", "Nome", "Quantidade", "Custo");
        printf("%-11d%-28s%-15d%10.2f\n\n", produtos.registro, produtos.nome, produtos.quantidade, produtos.custo);

        printf("\nUtiliza [+] para adicionar ou [-] para subtrair da quantidade: ");
        scanf("%d", &quantidade);

        if (quantidade <= 0){
            printf("O produto nao pode ser alterado pois o valor ja esta zerado.\n");
            deletaProdutoQnt(registro);
        }
        else{

        produtos.quantidade += quantidade;

        printf("\n%-11s%-28s%-15s%10s\n", "Registro", "Nome", "Quantidade", "Custo");
        printf("%-11d%-28s%-15d%10.2f\n\n", produtos.registro, produtos.nome, produtos.quantidade, produtos.custo);

        fseek(abPtr, (registro - 1) * sizeof(struct produtosDat), SEEK_SET);
        fwrite(&produtos, sizeof(struct produtosDat), 1, abPtr);
        }
           fclose(abPtr);
      }
    }

return 0;
}

void atualizacao_custo(){

  FILE *abPtr;
    int registro;
    double custo;

    struct produtosDat produtos = { 0, "", 0, 0.0 };

    if ((abPtr = fopen("hardware.dat", "rb+")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
    }
    else{
        printf("\nDigite o registro: ");
        scanf("%d", &registro);

        fseek(abPtr, (registro - 1) * sizeof(struct produtosDat), SEEK_SET);
        fread(&produtos, sizeof(struct produtosDat), 1, abPtr);

        if (produtos.registro == 0){
            printf("Registro nao existe.\n");
        }
        else {

        fseek(abPtr, (registro - 1) * sizeof(struct produtosDat), SEEK_SET);

        fread(&produtos, sizeof(struct produtosDat), 1, abPtr);

        printf("\n%-11s%-28s%-15s%10s\n", "Registro", "Nome", "Quantidade", "Custo");
        printf("%-11d%-28s%-15d%10.2f\n\n", produtos.registro, produtos.nome, produtos.quantidade, produtos.custo);

        printf("\nUtiliza [+] para adicionar ou [-] para subtrair do custo: ");
        scanf("%lf", &custo);

        produtos.custo += custo;

        printf("\n%-11s%-28s%-15s%10s\n", "Registro", "Nome", "Quantidade", "Custo");
        printf("%-11d%-28s%-15d%10.2f\n\n", produtos.registro, produtos.nome, produtos.quantidade, produtos.custo);

        fseek(abPtr, (registro - 1) * sizeof(struct produtosDat), SEEK_SET);
        fwrite(&produtos, sizeof(struct produtosDat), 1, abPtr);
        }
    

    fclose(abPtr);

    }

return 0;

}

void deletaProduto(){

  FILE *abPtr;
  int registro;
  int escolha;

    struct produtosDat produtos;
    struct produtosDat produtosNulo = { 0, "", 0, 0.0 };

    if ((abPtr = fopen("hardware.dat", "rb+")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
    }
    else{

        printf("\nDigite registro para excluir: ");
        scanf("%d", &registro);

        fseek(abPtr, (registro - 1) * sizeof(struct produtosDat), SEEK_SET);
        fread(&produtos, sizeof(struct produtosDat), 1, abPtr);

        if (produtos.registro == 0){
            printf("Registro nao existe.\n");
        }
        else {

            printf(
              "\nProduto ainda existente no estoque, deseja realmente apaga-lo?.\n"
              "[1] nao.\n"
              "[2] sim.\n");
            scanf("%d", &escolha);
            switch (escolha){
              case 1:
                interface();
                break;
            }

            printf("\n%-11s%-28s%-15s%10s\n", "Registro", "Nome", "Quantidade", "Custo");
            printf("%-11d%-28s%-15d%10.2f\n\n", produtos.registro, produtos.nome, produtos.quantidade, produtos.custo);

            fseek(abPtr, (registro -1 ) * sizeof(struct produtosDat), SEEK_SET);
            fwrite(&produtosNulo, sizeof(struct produtosDat), 1, abPtr);

            printf("\nProduto excluido com sucesso.\n");

        }

        fclose(abPtr);

    }

  return 0;

}

void novoProduto(){

  FILE *abPtr;
    int registro;

    struct produtosDat produtos = { 0, "", 0, 0.0 };

    if ((abPtr = fopen("hardware.dat", "rb+")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
    }
    else{

        printf("\nDigite o Registro: ");
        scanf("%d", &registro);

        while (registro > 100 || registro < 1){
          printf("\nDigite um registro entre 1 e 100: ");
          scanf("%d", &registro);
        }
        
        fseek(abPtr, (registro - 1) * sizeof(struct produtosDat), SEEK_SET);
        fread(&produtos, sizeof(struct produtosDat), 1, abPtr);

        if (produtos.registro != 0){
            printf("\nA ferramenta de registro %d ja existe.\n", produtos.registro);
            printf("\n%-11s%-28s%-15s%10s\n", "Registro", "Nome", "Quantidade", "Custo");
            printf("%-11d%-28s%-15d%10.2f\n\n", produtos.registro, produtos.nome, produtos.quantidade, produtos.custo);
        }
        else{

            printf("\nDigite o nome do produto, quantidade e o custo: ");
            scanf(" %[^\n] %d %lf", produtos.nome, &produtos.quantidade, &produtos.custo);
            produtos.registro = registro;

            printf("\n%-11s%-28s%-15s%10s\n", "Registro", "Nome", "Quantidade", "Custo");
            printf("%-11d%-28s%-15d%10.2f\n\n", produtos.registro, produtos.nome, produtos.quantidade, produtos.custo);

            fseek(abPtr, (produtos.registro - 1) * sizeof(struct produtosDat), SEEK_SET);
            fwrite(&produtos, sizeof(struct produtosDat), 1, abPtr);

        }
       
        fclose(abPtr);
    }

   return 0;

}

void deletaProdutoQnt(int registro){

  FILE *abPtr;


    struct produtosDat produtos;
    struct produtosDat produtosNulo = { 0, "", 0, 0.0 };

    if ((abPtr = fopen("hardware.dat", "rb+")) == NULL){
        printf("Erro ao abrir o arquivo.\n");
    }
    else{

        fseek(abPtr, (registro - 1) * sizeof(struct produtosDat), SEEK_SET);
        fread(&produtos, sizeof(struct produtosDat), 1, abPtr);

        if (produtos.registro == 0){
            printf("\nRegistro nao existe.\n");
        }
        else {
            printf("\nProduto deletado, pois nao tem estoque.\n");
            
            printf("\n%-11s%-28s%-15s%10s\n", "Registro", "Nome", "Quantidade", "Custo");
            printf("%-11d%-28s%-15d%10.2f\n\n", produtos.registro, produtos.nome, produtos.quantidade, produtos.custo);

            fseek(abPtr, (registro -1 ) * sizeof(struct produtosDat), SEEK_SET);

            fwrite(&produtosNulo, sizeof(struct produtosDat), 1, abPtr);
        }

        fclose(abPtr);

    }

    return 0;
}
