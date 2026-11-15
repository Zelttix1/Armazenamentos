
#include <iostream>
#include <string>
using namespace std;

// Estrutura dos produtos
struct Produto {
    int codigo;
    string nome;
    double preco;
    int estoque;
    Produto* proximo;
};

// Inicio da lista de produtos
Produto* inicioProdutos = nullptr;
int proximoCodigo = 1;

// Cadastra um novo produto
void cadastrarProduto() {
    Produto* novo = new Produto;

    novo->codigo = proximoCodigo++;

    cout << "Nome do produto: ";
    getline(cin >> ws, novo->nome);

    cout << "Preco: ";
    cin >> novo->preco;

    cout << "Quantidade em estoque: ";
    cin >> novo->estoque;

    novo->proximo = nullptr;

    if (inicioProdutos == nullptr) {
        inicioProdutos = novo;
    } else {
        Produto* atual = inicioProdutos;

        while (atual->proximo != nullptr) {
            atual = atual->proximo;
        }

        atual->proximo = novo;
    }

    cout << "Produto cadastrado com sucesso!\n";
    cout << "Codigo: " << novo->codigo << "\n";
}

// Remove um produto pelo codigo
void removerProduto() {
    int codigo;

    cout << "Codigo do produto: ";
    cin >> codigo;

    Produto* atual = inicioProdutos;
    Produto* anterior = nullptr;

    while (atual != nullptr && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << "Produto nao encontrado.\n";
        return;
    }

    if (anterior == nullptr) {
        inicioProdutos = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    delete atual;

    cout << "Produto removido com sucesso!\n";
}

// Lista todos os produtos
void listarProdutos() {
    Produto* atual = inicioProdutos;

    if (atual == nullptr) {
        cout << "Nenhum produto cadastrado.\n";
        return;
    }

    cout << "\n===== PRODUTOS CADASTRADOS =====\n";

    while (atual != nullptr) {
        cout << "Codigo: " << atual->codigo << "\n";
        cout << "Nome: " << atual->nome << "\n";
        cout << "Preco: R$ " << atual->preco << "\n";
        cout << "Estoque: " << atual->estoque << "\n";
        cout << "--------------------------\n";

        atual = atual->proximo;
    }
}

// Menu inicial
int main() {
    int opcao;

    do {
        cout << "\n===== GERENCIADOR DE ESTABELECIMENTO =====\n";
        cout << "1 - Cadastrar produto\n";
        cout << "2 - Remover produto\n";
        cout << "3 - Listar produtos\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";

        cin >> opcao;

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;

            case 2:
                removerProduto();
                break;

            case 3:
                listarProdutos();
                break;

            case 0:
                cout << "Encerrando sistema...\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);

    return 0;
}
