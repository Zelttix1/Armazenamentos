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
    }

    delete atual;
    raiz = removerArvore(raiz, codigo);
    cout << "Produto removido.\n";
}

// Lista todos os produtos cadastrados.
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

// Insere um codigo na arvore binaria.
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

// Busca um codigo na arvore binaria.
bool buscarArvore(NoArvore* no, int codigo) {
    if (no == nullptr) return false;
    if (no->codigo == codigo) return true;
    if (codigo < no->codigo) return buscarArvore(no->esquerda, codigo);
    return buscarArvore(no->direita, codigo);
}

// Percorre a arvore em ordem crescente.
void listarArvore(NoArvore* no) {
    if (no == nullptr) return;
    listarArvore(no->esquerda);
    cout << no->codigo << " ";
    listarArvore(no->direita);
}

// Encontra o menor codigo da arvore.
NoArvore* menorNo(NoArvore* no) {
    while (no != nullptr && no->esquerda != nullptr) {
        no = no->esquerda;
    }
    return no;
}

// Remove um codigo da arvore binaria.
NoArvore* removerArvore(NoArvore* no, int codigo) {
    if (no == nullptr) return nullptr;

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
        no->direita = removerArvore(no->direita, sucessor->codigo);
    }
    return no;
}

// ======================== BUSCA E ORDENACAO ========================

// Cria um vetor com os produtos da lista.
vector<Produto*> criarVetor() {
    vector<Produto*> produtos;
    Produto* atual = inicioProdutos;
    while (atual != nullptr) {
        produtos.push_back(atual);
        atual = atual->proximo;
    }
    return produtos;
}

// Ordena os produtos pelo codigo usando Bubble Sort.
void ordenarBubble(vector<Produto*>& produtos) {
    // Bubble Sort: complexidade O(n²) no pior caso.
    for (int i = 0; i < (int)produtos.size() - 1; i++) {
        for (int j = 0; j < (int)produtos.size() - i - 1; j++) {
            if (produtos[j]->codigo > produtos[j + 1]->codigo) {
                Produto* temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
}

// Realiza a busca sequencial.
int buscaSequencial(vector<Produto*>& produtos, int codigo, int& comparacoes) {
    comparacoes = 0;
    for (int i = 0; i < (int)produtos.size(); i++) {
        comparacoes++;
        if (produtos[i]->codigo == codigo) return i;
    }
    return -1;
}

// Realiza a busca binaria em um vetor ordenado.
int buscaBinaria(vector<Produto*>& produtos, int codigo, int& comparacoes) {
    int inicio = 0;
    int fim = (int)produtos.size() - 1;
    comparacoes = 0;

    while (inicio <= fim) {
        comparacoes++;
        int meio = inicio + (fim - inicio) / 2;
        if (produtos[meio]->codigo == codigo) return meio;
        if (produtos[meio]->codigo < codigo) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// Pesquisa um produto e compara os dois metodos de busca.
void pesquisarProduto() {
    if (inicioProdutos == nullptr) {
        cout << "Nenhum produto cadastrado.\n";
        return;
    }

    int codigo, compSeq, compBin;
    cout << "Digite o codigo do produto: ";
    cin >> codigo;

    vector<Produto*> produtos = criarVetor();
    int resultadoSeq = buscaSequencial(produtos, codigo, compSeq);
    ordenarBubble(produtos);
    int resultadoBin = buscaBinaria(produtos, codigo, compBin);

    cout << "\n===== RESULTADO DAS BUSCAS =====\n";
    cout << "Busca sequencial: " << compSeq << " comparacoes\n";
    cout << "Busca binaria: " << compBin << " comparacoes\n";

    if (resultadoSeq != -1) {
        cout << "Produto encontrado: " << produtos[resultadoBin]->nome << "\n";
        cout << "Preco: R$ " << produtos[resultadoBin]->preco << "\n";
    } else {
        cout << "Produto nao encontrado.\n";
    }
}

// ======================== FILA DE CLIENTES ========================

// Adiciona um cliente ao final da fila (FIFO).
void adicionarCliente() {
    NoFila* novo = new NoFila;
    cout << "Nome do cliente: ";
    getline(cin >> ws, novo->nome);
    novo->proximo = nullptr;

    if (fimFila == nullptr) {
        inicioFila = novo;
        fimFila = novo;
    } else {
        fimFila->proximo = novo;
        fimFila = novo;
    }
    cout << "Cliente adicionado a fila.\n";
}

// Atende o primeiro cliente que entrou na fila.
void atenderCliente() {
    if (inicioFila == nullptr) {
        cout << "A fila esta vazia.\n";
        return;
    }

    NoFila* removido = inicioFila;
    cout << "Atendendo cliente: " << removido->nome << "\n";
    inicioFila = inicioFila->proximo;

    if (inicioFila == nullptr) {
        fimFila = nullptr;
    }
    delete removido;
}

// ======================== PILHA DE HISTORICO DE VENDAS ========================

// Registra uma venda e reduz o estoque do produto.
void registrarVenda() {
    int codigo;
    cout << "Codigo do produto vendido: ";
    cin >> codigo;

    Produto* atual = inicioProdutos;
    while (atual != nullptr && atual->codigo != codigo) {
        atual = atual->proximo;
    }

    if (atual == nullptr) {
        cout << "Produto nao encontrado.\n";
        return;
    }
    if (atual->estoque <= 0) {
        cout << "Produto sem estoque.\n";
        return;
    }

    atual->estoque--;
    NoPilha* novaVenda = new NoPilha;
    novaVenda->descricao = "Venda: " + atual->nome +
        " (codigo " + to_string(atual->codigo) + ")";
    novaVenda->proximo = topoHistorico;
    topoHistorico = novaVenda;

    cout << "Venda registrada! Estoque atualizado.\n";
}

// Mostra primeiro a venda mais recente (LIFO).
void mostrarHistorico() {
    if (topoHistorico == nullptr) {
        cout << "Nenhuma venda registrada.\n";
        return;
    }

    cout << "\n===== HISTORICO DE VENDAS =====\n";
    NoPilha* atual = topoHistorico;
    while (atual != nullptr) {
        cout << atual->descricao << "\n";
        atual = atual->proximo;
    }
}

// ======================== LIBERACAO DE MEMORIA ========================

// Libera todos os produtos da lista encadeada.
void liberarProdutos() {
    while (inicioProdutos != nullptr) {
        Produto* removido = inicioProdutos;
        inicioProdutos = inicioProdutos->proximo;
        delete removido;
    }
    inicioProdutos = nullptr;
}

// Libera recursivamente todos os nos da arvore binaria.
void liberarArvore(NoArvore* no) {
    if (no == nullptr) return;
    liberarArvore(no->esquerda);
    liberarArvore(no->direita);
    delete no;
}

// Libera os clientes que ainda estiverem aguardando na fila.
void liberarFila() {
    while (inicioFila != nullptr) {
        NoFila* removido = inicioFila;
        inicioFila = inicioFila->proximo;
        delete removido;
    }
    inicioFila = nullptr;
    fimFila = nullptr;
}

// Libera todos os registros armazenados na pilha de vendas.
void liberarHistorico() {
    while (topoHistorico != nullptr) {
        NoPilha* removido = topoHistorico;
        topoHistorico = topoHistorico->proximo;
        delete removido;
    }
    topoHistorico = nullptr;
}

// Centraliza a liberacao de todas as estruturas dinamicas do sistema.
void liberarMemoria() {
    liberarProdutos();
    liberarArvore(raiz);
    raiz = nullptr;
    liberarFila();
    liberarHistorico();
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
        cout << "6 - Adicionar cliente na fila\n";
        cout << "7 - Atender proximo cliente\n";
        cout << "8 - Registrar venda\n";
        cout << "9 - Mostrar historico de vendas\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarProduto(); break;
            case 2: removerProduto(); break;
            case 3: listarProdutos(); break;
            case 4: pesquisarProduto(); break;
            case 5:
                if (raiz == nullptr) cout << "Arvore vazia.\n";
                else {
                    cout << "Codigos em ordem crescente: ";
                    listarArvore(raiz);
                    cout << "\n";
                }
                break;
            case 6: adicionarCliente(); break;
            case 7: atenderCliente(); break;
            case 8: registrarVenda(); break;
            case 9: mostrarHistorico(); break;
            case 0: cout << "Encerrando sistema...\n"; break;
            default: cout << "Opcao invalida.\n";
        }
    } while (opcao != 0);

    liberarMemoria();
    cout << "Memoria liberada. Sistema finalizado com seguranca.\n";
    return 0;
}