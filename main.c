#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do pedido
typedef struct Pedido {
    int id;
    char cliente[50];
    char itens[200];
    float valor;
    char status[30];
    struct Pedido* proximo;    
} Pedido;

// Função para criar lista vazia (retorna NULL)
Pedido* criarListaVazia() {
    return NULL;
}

// Função para criar um novo pedido
Pedido* criarNovoPedido(int id, char*cliente, char* itens, float valor) {
    // Aloca memória para o novo pedido
    Pedido* novoPedido = (Pedido*)malloc(sizeof(Pedido));

    if (novoPedido == NULL) {
        printf("Erro: Não foi possivel alocar memória!\n");
        return NULL;
    }

    // Preenche os dados do pedido
    novoPedido->id = id;
    strcpy(novoPedido->cliente, cliente);
    strcpy(novoPedido->itens, itens);
    novoPedido->valor = valor;
    strcpy(novoPedido->status, "Aguardando Preparação");
    novoPedido->proximo = NULL;

    return novoPedido;
}

// Função para inserir pedido na lista
Pedido* inserirPedido(Pedido* lista, int id, char* cliente, char* itens, float valor) {
    Pedido* novoPedido = criarNovoPedido(id, cliente, itens, valor);

    if (novoPedido == NULL) {
        return lista; // Retorna lista inaltera se erro
    }

    // Se lista está vazia, o novo pedido vira o primeiro
    if (lista == NULL) {
        return novoPedido;
    }

    // Caso contrário, insere no final da lista
    Pedido* atual = lista;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = novoPedido;

    return lista;
}

// Função para exibir um pedido
void exibirPedido(Pedido* pedido) {
    printf("\n--- Pedido #%d --- \n", pedido->id);
    printf("Cliente: %s\n, pedido->cliente");
    printf("Itens: %sn\n", pedido->itens);
    printf("Valor: R$ %.2f\n", pedido->valor);
    printf("Status: %s\n", pedido->status);
}

// Função para buscar pedido por ID
Pedido* buscarPedidoPorId(Pedido* lista, int id) {
    Pedido* atual = lista;

    while (atual != NULL) {
        if (atual->id == id) {
            return atual; // Encontrou Pedido
        }
        atual = atual->proximo;
        }

        return = NULL; // Não encontrou
}

// Função para atualizar status do pedido
int atualizarStatus(Pedido* lista, int id, char* novoStatus) {
    Pedido* pedido = buscarPedidoPorId(lista, id);

    if (pedido == NULL) {
        printf("Erro: Pedido #%d não encontrado!\n", id);
        return 0; // Falso - não atualizou
    }

    printf("Status do Pedido #%d alterado de '%s' para '%s'\n", id, pedido->status, novoStatus);

    strcpy(pedido->status, novoStatus);
    return 1; // Verdadeiro - atualizou com sucesso
    }

    //Função para listar todos os pedidos
    void listarTodosPedidos(Pedido* lista) {
        if (lista == NULL) {
            printf("Nenhum pedido na lista.\n");
            return;
        }
       
        printf("\n==== Lista de todos os pedidos ===\n");
        Pedido* atual = lista;
        while (atual != NULL) {
            exibirPedido(atual);
            atual = atual->proximo;
        }
    }

// Função para testar recebimento de pedidos
void testarAtualizacaoStatus() {
    Pedido* lista = criarListaVazia();

    printf("Testando Atualização de Status...\n");

    //Receber pedidos
    printf("1. Recebendo pedidos...\n");
    lista = inserirPedido(lista, 1, "João Silva", "2x Hamburguer, 1x Batata", 25.50);
    lista = inserirPedido(lista, 2, "Maria Santos", "1x Pizza, 1X Refrigerante", 32.00);
    lista = inserirPedido(lista, 3, "Pedro Costa", "1x Sanduiche, 1X suco", 18.75);

    //Listar pedidos inciais
    listarTodosPedidos(lista);

    printf("\n2. Atualizando status dos pedidos...\n");

    //Atualizar status do pedido 1
    atualizarStatus(lista, 1, "Em preparação");

    //Atualizar status do pedido 2
    atualizarStatus(lista, 2, "Pronto para entrega");

    //Tentar atualizar pedido que não existe
    atualizarStatus(lista, 99, "Em preparação");

    //Atualizar status do pedido 3
    atualizarStatus(lista, 3, "Entregue");

    //Listar pedidos após atualizações
    printf("\n3. Lista após atualizações:\n");
    listarTodosPedidos(lista);
}

int main() {
    printf("=== Sistemas de Restaurante ===\n");
    testarAtualizacaoStatus();
    return 0;
}
