#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ======================== ESTRUTURAS ========================

struct Produto {
    int codigo;
    string nome;
    double preco;
    int estoque;
    Produto* proximo;
};

struct NoArvore {
    int codigo;
    NoArvore* esquerda;
    NoArvore* direita;
};

struct NoFila {
    string nome;
    NoFila* proximo;
};

struct NoPilha {
    string descricao;
    NoPilha* proximo;
};

// ======================== VARIAVEIS ========================

Produto* inicioProdutos = nullptr;
NoArvore* raiz = nullptr;
NoFila* inicioFila = nullptr;
NoFila* fimFila = nullptr;
NoPilha* topoHistorico = nullptr;
int proximoCodigo = 1;

// ======================== PROTOTIPOS ========================

NoArvore* inserirArvore(NoArvore* no, int codigo);
NoArvore* removerArvore(NoArvore* no, int codigo);
NoArvore* menorNo(NoArvore* no);

// ======================== PRODUTOS ========================

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

    raiz = inserirArvore(raiz, novo->codigo);
    cout << "Produto cadastrado! Codigo: " << novo->codigo << "\n";
}

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