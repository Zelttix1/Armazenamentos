#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

// ESTRUTURAS
struct Produto {
    int codigo;
    string nome;
    double preco;
    int estoque;
    Produto* prox;
};

struct NoArvore {
    int codigo;
    NoArvore *esq, *dir;
};

struct NoFila {
    string nome;
    NoFila* prox;
};

struct NoPilha {
    string venda;
    NoPilha* prox;
};

// INICIO DAS ESTRUTURAS
Produto* produtos = nullptr;
NoArvore* raiz = nullptr;
NoFila *inicioFila = nullptr, *fimFila = nullptr;
NoPilha* topo = nullptr;
int proximoCodigo = 1;

// ÁRVORE BINÁRIA
// Insere um código na árvore usando recursividade.
NoArvore* inserirArvore(NoArvore* no, int codigo) {
    if (no == nullptr) {
        NoArvore* novo = new NoArvore{codigo, nullptr, nullptr};
        return novo;
    }
    if (codigo < no->codigo) no->esq = inserirArvore(no->esq, codigo);
    else if (codigo > no->codigo) no->dir = inserirArvore(no->dir, codigo);
    return no;
}

// Procura um código na árvore de forma recursiva.
bool buscarArvore(NoArvore* no, int codigo) {
    if (no == nullptr) return false;
    if (no->codigo == codigo) return true;
    if (codigo < no->codigo) return buscarArvore(no->esq, codigo);
    return buscarArvore(no->dir, codigo);
}

// Exibe os códigos em ordem crescente.
void listarArvore(NoArvore* no) {
    if (no == nullptr) return;
    listarArvore(no->esq);
    cout << no->codigo << " ";
    listarArvore(no->dir);
}

// Encontra o menor nó de uma parte da árvore.
NoArvore* menorNo(NoArvore* no) {
    while (no->esq != nullptr) no = no->esq;
    return no;
}

// Remove um código da árvore.
NoArvore* removerArvore(NoArvore* no, int codigo) {
    if (no == nullptr) return nullptr;
    if (codigo < no->codigo) no->esq = removerArvore(no->esq, codigo);
    else if (codigo > no->codigo) no->dir = removerArvore(no->dir, codigo);
    else {
        if (no->esq == nullptr) {
            NoArvore* temp = no->dir;
            delete no;
            return temp;
        }
        if (no->dir == nullptr) {
            NoArvore* temp = no->esq;
            delete no;
            return temp;
        }
        NoArvore* temp = menorNo(no->dir);
        no->codigo = temp->codigo;
        no->dir = removerArvore(no->dir, temp->codigo);
    }
    return no;
}

// PRODUTOS
// Cadastra um produto na lista e seu código na árvore.
void cadastrarProduto() {
    Produto* novo = new Produto;
    novo->codigo = proximoCodigo++;
    cout << "Nome: ";
    getline(cin >> ws, novo->nome);
    cout << "Preço: ";
    cin >> novo->preco;
    cout << "Estoque: ";
    cin >> novo->estoque;
    novo->prox = nullptr;

    if (produtos == nullptr) produtos = novo;
    else {
        Produto* atual = produtos;
        while (atual->prox != nullptr) atual = atual->prox;
        atual->prox = novo;
    }
    raiz = inserirArvore(raiz, novo->codigo);
    cout << "Produto cadastrado. Código: " << novo->codigo << "\n";
}

// Remove um produto da lista e da árvore.
void removerProduto() {
    int codigo;
    cout << "Código: ";
    cin >> codigo;
    Produto *atual = produtos, *anterior = nullptr;

    while (atual != nullptr && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == nullptr) {
        cout << "Produto não encontrado.\n";
        return;
    }
    if (anterior == nullptr) produtos = atual->prox;
    else anterior->prox = atual->prox;

    delete atual;
    raiz = removerArvore(raiz, codigo);
    cout << "Produto removido.\n";
}

// Lista os produtos. O parâmetro possui valor padrão.
void listarProdutos(bool detalhes = true) {
    if (produtos == nullptr) {
        cout << "Nenhum produto cadastrado.\n";
        return;
    }
    for (Produto* p = produtos; p != nullptr; p = p->prox) {
        cout << p->codigo << " - " << p->nome;
        if (detalhes) cout << " | R$ " << p->preco << " | Estoque: " << p->estoque;
        cout << "\n";
    }
}

// BUSCA E ORDENAÇÃO
// Copia os ponteiros dos produtos para um vetor.
vector<Produto*> criarVetor() {
    vector<Produto*> v;
    for (Produto* p = produtos; p != nullptr; p = p->prox) v.push_back(p);
    return v;
}

// Ordena os produtos pelo código usando Bubble Sort. Complexidade: O(n²).
void bubbleSort(vector<Produto*>& v) {
    for (int i = 0; i < (int)v.size() - 1; i++)
        for (int j = 0; j < (int)v.size() - i - 1; j++)
            if (v[j]->codigo > v[j + 1]->codigo)
                swap(v[j], v[j + 1]);
}

// Busca item por item e conta as comparações.
int buscaSequencial(vector<Produto*>& v, int codigo, int& comparacoes) {
    comparacoes = 0;
    for (int i = 0; i < (int)v.size(); i++) {
        comparacoes++;
        if (v[i]->codigo == codigo) return i;
    }
    return -1;
}

// Busca pela metade do vetor. O vetor precisa estar ordenado.
int buscaBinaria(vector<Produto*>& v, int codigo, int& comparacoes) {
    int ini = 0, fim = (int)v.size() - 1;
    comparacoes = 0;
    while (ini <= fim) {
        comparacoes++;
        int meio = (ini + fim) / 2;
        if (v[meio]->codigo == codigo) return meio;
        if (v[meio]->codigo < codigo) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// Compara a busca sequencial com a binária.
void pesquisarProduto() {
    if (produtos == nullptr) {
        cout << "Cadastre um produto primeiro.\n";
        return;
    }
    int codigo, compSeq, compBin;
    cout << "Código para pesquisar: ";
    cin >> codigo;

    vector<Produto*> v = criarVetor();
    int posSeq = buscaSequencial(v, codigo, compSeq);
    bubbleSort(v);
    int posBin = buscaBinaria(v, codigo, compBin);

    cout << "Busca sequencial: " << compSeq << " comparações\n";
    cout << "Busca binária: " << compBin << " comparações\n";
    cout << "Código na árvore: " << (buscarArvore(raiz, codigo) ? "encontrado" : "não encontrado") << "\n";
    if (posSeq != -1 && posBin != -1)
        cout << "Encontrado: " << v[posBin]->nome << " | R$ " << v[posBin]->preco << "\n";
    else cout << "Produto não encontrado.\n";
}

// FILA DE CLIENTES (FIFO)
// Adiciona um cliente no final da fila.
void adicionarCliente() {
    NoFila* novo = new NoFila;
    cout << "Nome do cliente: ";
    getline(cin >> ws, novo->nome);
    novo->prox = nullptr;

    if (fimFila == nullptr) inicioFila = fimFila = novo;
    else {
        fimFila->prox = novo;
        fimFila = novo;
    }
    cout << "Cliente entrou na fila.\n";
}

// Atende e remove o primeiro cliente da fila.
void atenderCliente() {
    if (inicioFila == nullptr) {
        cout << "Fila vazia.\n";
        return;
    }
    NoFila* removido = inicioFila;
    cout << "Atendendo: " << removido->nome << "\n";
    inicioFila = inicioFila->prox;
    if (inicioFila == nullptr) fimFila = nullptr;
    delete removido;
}

// PILHA DE VENDAS (LIFO)
// Registra uma venda e diminui uma unidade do estoque.
void registrarVenda() {
    int codigo;
    cout << "Código do produto vendido: ";
    cin >> codigo;

    Produto* p = produtos;
    while (p != nullptr && p->codigo != codigo) p = p->prox;
    if (p == nullptr) {
        cout << "Produto não encontrado.\n";
        return;
    }
    if (p->estoque <= 0) {
        cout << "Sem estoque.\n";
        return;
    }

    p->estoque--;
    NoPilha* nova = new NoPilha;
    nova->venda = "Venda: " + p->nome + " (código " + to_string(p->codigo) + ")";
    nova->prox = topo;
    topo = nova;
    cout << "Venda registrada.\n";
}

// Mostra a venda mais recente primeiro.
void mostrarHistorico() {
    if (topo == nullptr) {
        cout << "Histórico vazio.\n";
        return;
    }
    for (NoPilha* p = topo; p != nullptr; p = p->prox)
        cout << p->venda << "\n";
}

// LIBERAÇÃO DE MEMÓRIA
// Libera todos os nós da árvore recursivamente.
void liberarArvore(NoArvore* no) {
    if (no == nullptr) return;
    liberarArvore(no->esq);
    liberarArvore(no->dir);
    delete no;
}

// Libera a lista de produtos.
void liberarProdutos() {
    while (produtos != nullptr) {
        Produto* temp = produtos;
        produtos = produtos->prox;
        delete temp;
    }
}

// Libera a fila de clientes.
void liberarFila() {
    while (inicioFila != nullptr) {
        NoFila* temp = inicioFila;
        inicioFila = inicioFila->prox;
        delete temp;
    }
    fimFila = nullptr;
}

// Libera o histórico de vendas.
void liberarPilha() {
    while (topo != nullptr) {
        NoPilha* temp = topo;
        topo = topo->prox;
        delete temp;
    }
}

// Libera todas as estruturas antes de encerrar.
void liberarMemoria() {
    liberarProdutos();
    liberarArvore(raiz);
    raiz = nullptr;
    liberarFila();
    liberarPilha();
}

// MENU PRINCIPAL
int main() {
    int opcao;
    do {
        cout << "\n=== GERENCIADOR DE ESTABELECIMENTO ===\n";
        cout << "1-Cadastrar  2-Remover  3-Listar  4-Pesquisar\n";
        cout << "5-Mostrar árvore  6-Adicionar cliente  7-Atender\n";
        cout << "8-Registrar venda  9-Histórico  0-Sair\n";
        cout << "Opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarProduto(); break;
            case 2: removerProduto(); break;
            case 3: listarProdutos(); break;
            case 4: pesquisarProduto(); break;
            case 5:
                if (raiz == nullptr) cout << "Árvore vazia.\n";
                else { listarArvore(raiz); cout << "\n"; }
                break;
            case 6: adicionarCliente(); break;
            case 7: atenderCliente(); break;
            case 8: registrarVenda(); break;
            case 9: mostrarHistorico(); break;
            case 0: cout << "Encerrando...\n"; break;
            default: cout << "Opção inválida.\n";
        }
    } while (opcao != 0);

    liberarMemoria();
    cout << "Memória liberada.\n";
    return 0;
}
