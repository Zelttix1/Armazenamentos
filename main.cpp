
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

// ======================== VARIAVEIS ========================

Produto* inicioProdutos = nullptr;
NoArvore* raiz = nullptr;
int proximoCodigo = 1;

// ======================== PROTOTIPOS ========================

NoArvore* inserirArvore(NoArvore* no, int codigo);
NoArvore* removerArvore(NoArvore* no, int codigo);
NoArvore* menorNo(NoArvore* no);

// ======================== CADASTRO ========================

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

    cout << "Produto cadastrado com sucesso!\n";
    cout << "Codigo: " << novo->codigo << "\n";
}

// ======================== REMOCAO ========================

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
    raiz = removerArvore(raiz, codigo);

    cout << "Produto removido com sucesso!\n";
}

// ======================== LISTAGEM ========================

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

// ======================== ARVORE BINARIA ========================

NoArvore* inserirArvore(NoArvore* no, int codigo) {
    if (no == nullptr) {
        NoArvore* novo = new NoArvore;
        novo->codigo = codigo;
        novo->esquerda = nullptr;
        novo->direita = nullptr;
        return novo;
    }

    if (codigo < no->codigo) {
        no->esquerda = inserirArvore(no->esquerda, codigo);
    } else if (codigo > no->codigo) {
        no->direita = inserirArvore(no->direita, codigo);
    }

    return no;
}

bool buscarArvore(NoArvore* no, int codigo) {
    if (no == nullptr) {
        return false;
    }

    if (no->codigo == codigo) {
        return true;
    }

    if (codigo < no->codigo) {
        return buscarArvore(no->esquerda, codigo);
    }

    return buscarArvore(no->direita, codigo);
}

void listarArvore(NoArvore* no) {
    if (no == nullptr) {
        return;
    }

    listarArvore(no->esquerda);
    cout << no->codigo << " ";
    listarArvore(no->direita);
}

NoArvore* menorNo(NoArvore* no) {
    while (no != nullptr && no->esquerda != nullptr) {
        no = no->esquerda;
    }

    return no;
}

NoArvore* removerArvore(NoArvore* no, int codigo) {
    if (no == nullptr) {
        return nullptr;
    }

    if (codigo < no->codigo) {
        no->esquerda = removerArvore(no->esquerda, codigo);
    } else if (codigo > no->codigo) {
        no->direita = removerArvore(no->direita, codigo);
    } else {
        if (no->esquerda == nullptr) {
            NoArvore* direita = no->direita;
            delete no;
            return direita;
        }

        if (no->direita == nullptr) {
            NoArvore* esquerda = no->esquerda;
            delete no;
            return esquerda;
        }

        NoArvore* sucessor = menorNo(no->direita);

        no->codigo = sucessor->codigo;

        no->direita = removerArvore(
            no->direita, sucessor->codigo
        );
    }

    return no;
}

// ======================== BUSCAS E ORDENACAO ========================

vector<Produto*> criarVetor() {
    vector<Produto*> produtos;

    Produto* atual = inicioProdutos;

    while (atual != nullptr) {
        produtos.push_back(atual);
        atual = atual->proximo;
    }

    return produtos;
}

void ordenarBubble(vector<Produto*>& produtos) {

    // Bubble Sort: complexidade O(n²) no pior caso.
    for (int i = 0; i < (int)produtos.size() - 1; i++) {

        for (int j = 0; j < (int)produtos.size() - i - 1; j++) {

            if (produtos[j]->codigo > produtos[j + 1]->codigo) {

                Produto* temporario = produtos[j];

                produtos[j] = produtos[j + 1];

                produtos[j + 1] = temporario;
            }
        }
    }
}

int buscaSequencial(
    vector<Produto*>& produtos,
    int codigo,
    int& comparacoes
) {
    comparacoes = 0;

    for (int i = 0; i < (int)produtos.size(); i++) {

        comparacoes++;

        if (produtos[i]->codigo == codigo) {
            return i;
        }
    }

    return -1;
}

int buscaBinaria(
    vector<Produto*>& produtos,
    int codigo,
    int& comparacoes
) {
    int inicio = 0;
    int fim = (int)produtos.size() - 1;

    comparacoes = 0;

    while (inicio <= fim) {

        comparacoes++;

        int meio = inicio + (fim - inicio) / 2;

        if (produtos[meio]->codigo == codigo) {
            return meio;
        }

        if (produtos[meio]->codigo < codigo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

void pesquisarProduto() {

    if (inicioProdutos == nullptr) {
        cout << "Nenhum produto cadastrado.\n";
        return;
    }

    int codigo;
    int comparacoesSeq;
    int comparacoesBin;

    cout << "Digite o codigo do produto: ";
    cin >> codigo;

    vector<Produto*> produtos = criarVetor();

    int resultadoSeq = buscaSequencial(
        produtos, codigo, comparacoesSeq
    );

    ordenarBubble(produtos);

    int resultadoBin = buscaBinaria(
        produtos, codigo, comparacoesBin
    );

    cout << "\n===== RESULTADO DAS BUSCAS =====\n";

    cout << "Busca sequencial: "
         << comparacoesSeq << " comparacoes\n";

    cout << "Busca binaria: "
         << comparacoesBin << " comparacoes\n";

    if (resultadoSeq != -1) {
        cout << "Produto encontrado: "
             << produtos[resultadoBin]->nome << "\n";

        cout << "Preco: R$ "
             << produtos[resultadoBin]->preco << "\n";
    } else {
        cout << "Produto nao encontrado.\n";
    }
}

// ======================== MENU PRINCIPAL ========================

int main() {
    int opcao;

    do {
        cout << "\n===== GERENCIADOR DE ESTABELECIMENTO =====\n";
        cout << "1 - Cadastrar produto\n";
        cout << "2 - Remover produto\n";
        cout << "3 - Listar produtos\n";
        cout << "4 - Pesquisar produto\n";
        cout << "5 - Mostrar arvore binaria\n";
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

            case 4:
                pesquisarProduto();
                break;

            case 5:
                if (raiz == nullptr) {
                    cout << "Arvore vazia.\n";
                } else {
                    cout << "Codigos em ordem crescente: ";
                    listarArvore(raiz);
                    cout << "\n";
                }
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
