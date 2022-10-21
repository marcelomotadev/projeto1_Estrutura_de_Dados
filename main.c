#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char cliente[20];
    float preco;
    int codigo_pedido;
    void *prox;
} Pedido;

typedef struct {
    char nome[20];
    float preco;
} Item;

typedef struct{
    int var;
    void *prox;
} Num;
Pedido *inicio, *fim = NULL, *aux;
Num *ini, *ff = NULL, *ax;

typedef struct{
    int cod_cliente;
    int cod_pedido;
    int qtd;
    void *prox;

} ListaPedidos;

ListaPedidos *inicio2, *fim2 = NULL, *aux2; 

Item cardapio[10] = {
    {"Hamburger de Carne", 12.75},
    {"Hamburger de Bacon", 12.75},
    {"Kibe", 2.90},
    {"Esfirra", 5.00},
    {"Batata Frita", 9.90},
    {"Batata Frita Grande", 15.90},
    {"Refrigerante Laranja", 6.00},
    {"Refrigerante de Cola", 6.00},
    {"Sorvete Napolitano", 15.30},
    {"Milkshake", 10.20}
    };

char nome_cliente[40];
int codigo_geral = 0;
int total_itens = 0;


Pedido* insere(Pedido *pedido){
    pedido->prox = NULL;
    if(inicio == NULL && fim == NULL){
        inicio = pedido;
        fim = pedido;
    } else {
        fim->prox = pedido;
        fim = pedido;
    }
}

Num* insere_num(Num *num){
    num->prox = NULL;
    if(ini == NULL && ff == NULL){
        ini = num;
        ff = num;
    } else {
        ff->prox = num;
        ff = num;
    }
}

ListaPedidos* insere_Lp(ListaPedidos *lista_pedidos){
    lista_pedidos->prox = NULL;
    if(inicio2 == NULL && fim2 == NULL){
        inicio2 = lista_pedidos;
        fim2 = lista_pedidos;
    } else {
        fim2->prox = lista_pedidos;
        fim2 = lista_pedidos;
    }
}


void add(){
    aux = inicio;
    int cod = inicio->codigo_pedido;
    ax = (Num *) malloc(sizeof(Num));
    ax->var = cod;
    ax->prox = NULL;
    insere_num(ax);
    
    

    while(aux != NULL){
        if(aux->codigo_pedido != cod){
            cod = aux->codigo_pedido;
            ax = (Num *) malloc(sizeof(Num));
            ax->var = cod;
            ax->prox = NULL;
            insere_num(ax);

    }
    aux = aux->prox;
  }
}  

void imprimir_num(){
    system("cls");
    ax = ini;
    while(ax != NULL){
        printf("%d\n", ax->var);
        ax = ax->prox;
    }
    system("pause");
}

void imprimir_fila(){
    system("cls");
    aux = inicio;
    while(aux != NULL){
        printf("Cliente: %s\nPreco: %f\nCod: %d\n", aux->cliente, aux->preco, aux->codigo_pedido);
        aux = aux->prox;
    }
    system("pause");
}

int length(char str[20]){
    int i = 0;
    while(str[i] != '\0'){
        i = i +1;
    }
    return i;
}
void imprime_pontos(int tam){
    for(int i = 0; i <  20 - tam; ++i){
        printf(".");
    }
}
void imprime_cardapio(){
    for(int i = 0; i < 10; ++i){
        printf("%d - %s", i, cardapio[i].nome);
        imprime_pontos(length(cardapio->nome));
        printf("\n");
    }
}

void realizar_pedido(){
    char r = 'S';
    int quant;
    int codigo_item;
    
    printf("Nome do cliente: ");
    scanf(" %s", nome_cliente);
    imprime_cardapio();
    while(r == 'S'){
        aux2 = (ListaPedidos *) malloc(sizeof(ListaPedidos));
        aux = (Pedido *) malloc(sizeof(Pedido));
        printf("Digite o codigo do item: ");
        scanf("%d", &codigo_item);
        if(codigo_item > 9){
            printf("Codigo invalido!\n");
        } else {
            printf("Digite a quantidade: ");
            scanf("%d", &quant);
            total_itens = total_itens + quant;
            strcpy(aux->cliente, nome_cliente);
            aux->preco = cardapio[codigo_item].preco * quant;
            aux->codigo_pedido = codigo_geral;
            aux->prox = NULL;
            insere(aux);
            aux2->cod_cliente = codigo_geral;
            aux2->cod_pedido = codigo_item;
            aux2->qtd = quant;
            aux2->prox = NULL;
            insere_Lp(aux2);
            printf("Deseja comprar outro item? S | N: ");
            scanf(" %c", &r);
            r = toupper(r);
        }
    }
    system("cls");
    aux2 = inicio2;
    float total1 = 0;
    float total2 = 0;
    while(aux2 != NULL){
        printf("Item: %s \n", cardapio[aux2->cod_pedido].nome);
        printf("Quantidade: %d\n", aux2->qtd);
        total1 = cardapio[aux2->cod_pedido].preco * quant;
        printf("Valor: %f\n", total1);
        printf(".....................................\n");
        total2 = total1 + total2;
        aux2 = aux2->prox;
    }
    printf("Total do pedido: %f\n", total2);
    codigo_geral = codigo_geral + 1;
    system("pause");

}

void imprimir_codigo(){
    aux = inicio;
    int cod = aux->codigo_pedido;
    char str[40];
    strcpy(str, aux->cliente);
    while(aux != NULL){
        if(aux->codigo_pedido != cod){
            printf("Pedido: #%d\n", cod);
        }
        
        printf("Cliente: %s\n", str);
        printf("Total: %f\n", aux->preco);
        aux = aux->prox;
        
    }
    

}
void fechar_caixa(){
    system("cls");
    aux = inicio;
    ax = ini;
    int cod = aux->codigo_pedido;
    float balanco = 0;
    while(ax != NULL){
        printf("Pedido: #%d\n", ax->var);
        float total = 0;
        while(aux != NULL){
            if(ax->var == aux->codigo_pedido){
                printf("*%f\n", aux->preco);
                fflush(stdout);
                total = total + aux->preco;
            }
            aux = aux->prox;

        }
        printf("Total: %f\n", total);
        balanco = balanco + total;
        printf("...........................................\n");
        total = 0;
        ax = ax->prox;
        aux = inicio;
    }
    printf("Balanco do dia\n\n");
    printf("Total de itens vendidos: %d\n", total_itens);
    printf("Saldo: R$ %f\n", balanco);
    system("pause");
}


int main()
{
    int resp;
    char str[20];
    float valor;

    while(resp != 4){
        printf("1 - Realizar pedido\n");
        printf("2 - Imprimir\n");
        printf("3 - Fechar Caixa\n");
        printf("4 - Sair\n");
        printf("Digite uma opcao: ");
        scanf(" %d", &resp);
        switch(resp){
            case 1:
            realizar_pedido(); break;
            case 2: 
            imprimir_fila(); break;
            case 3: 
            add(); fechar_caixa(); break;



        }

    }
    

    return 0;
}
