#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ESTRUTURAS
struct Produto { int codigo; string nome; double preco; int estoque; Produto* prox; };
struct NoArvore { int codigo; NoArvore *esq, *dir; };
struct Cliente { string nome; Cliente* prox; };
struct Venda { string descricao; Venda* prox; };

// INICIO DAS ESTRUTURAS
Produto* produtos = nullptr;
NoArvore* raiz = nullptr;
Cliente *inicio = nullptr, *fim = nullptr;
Venda* topo = nullptr;
int proximoCodigo = 1;

// ARVORE BINARIA: insercao recursiva.
NoArvore* inserirArvore(NoArvore* no, int codigo) {
    if (!no) return new NoArvore{codigo, nullptr, nullptr};
    if (codigo < no->codigo) no->esq = inserirArvore(no->esq, codigo);
    else if (codigo > no->codigo) no->dir = inserirArvore(no->dir, codigo);
    return no;
}

// Busca recursiva na arvore.
bool buscarArvore(NoArvore* no, int codigo) {
    if (!no) return false;
    if (no->codigo == codigo) return true;
    return codigo < no->codigo ? buscarArvore(no->esq, codigo)
                               : buscarArvore(no->dir, codigo);
}

// Percurso in-ordem: exibe os codigos em ordem crescente.
void listarArvore(NoArvore* no) {
    if (!no) return;
    listarArvore(no->esq);
    cout << no->codigo << " ";
    listarArvore(no->dir);
}

// Cadastro: insere o produto na lista e o codigo na arvore.
void cadastrar() {
    Produto* novo = new Produto;
    novo->codigo = proximoCodigo++;
    cout << "Nome: "; getline(cin >> ws, novo->nome);
    cout << "Preco: "; cin >> novo->preco;
    cout << "Estoque: "; cin >> novo->estoque;
    novo->prox = nullptr;
    if (!produtos) produtos = novo;
    else {
        Produto* p = produtos;
        while (p->prox) p = p->prox;
        p->prox = novo;
    }
    raiz = inserirArvore(raiz, novo->codigo);
    cout << "Cadastrado! Codigo: " << novo->codigo << "\n";
}

// Remove um codigo da arvore, tratando os tres casos de filhos.
NoArvore* removerArvore(NoArvore* no, int codigo) {
    if (!no) return nullptr;
    if (codigo < no->codigo) no->esq = removerArvore(no->esq, codigo);
    else if (codigo > no->codigo) no->dir = removerArvore(no->dir, codigo);
    else {
        if (!no->esq || !no->dir) {
            NoArvore* filho = no->esq ? no->esq : no->dir;
            delete no; return filho;
        }
        NoArvore* menor = no->dir;
        while (menor->esq) menor = menor->esq;
        no->codigo = menor->codigo;
        no->dir = removerArvore(no->dir, menor->codigo);
    }
    return no;
}

// Remove produto da lista e da arvore.
void removerProduto() {
    int codigo;
    cout << "Codigo: "; cin >> codigo;
    Produto *p = produtos, *ant = nullptr;
    while (p && p->codigo != codigo) { ant = p; p = p->prox; }
    if (!p) { cout << "Produto nao encontrado.\n"; return; }
    if (!ant) produtos = p->prox;
    else ant->prox = p->prox;
    delete p;
    raiz = removerArvore(raiz, codigo);
    cout << "Produto removido.\n";
}

// Lista produtos. O parametro detalhes tem valor padrao true.
void listarProdutos(bool detalhes = true) {
    if (!produtos) { cout << "Lista vazia.\n"; return; }
    for (Produto* p = produtos; p; p = p->prox) {
        cout << p->codigo << " - " << p->nome;
        if (detalhes) cout << " | R$ " << p->preco << " | Estoque: " << p->estoque;
        cout << "\n";
    }
}

// Copia os ponteiros da lista para um vetor auxiliar.
vector<Produto*> criarVetor() {
    vector<Produto*> v;
    for (Produto* p = produtos; p; p = p->prox) v.push_back(p);
    return v;
}

// Bubble Sort: ordena codigos. Complexidade O(n²).
void bubbleSort(vector<Produto*>& v) {
    for (int i = 0; i < (int)v.size()-1; i++)
        for (int j = 0; j < (int)v.size()-i-1; j++)
            if (v[j]->codigo > v[j+1]->codigo) swap(v[j], v[j+1]);
}

// Busca sequencial: verifica um elemento por vez.
int buscaSequencial(vector<Produto*>& v, int codigo, int& comp) {
    comp = 0;
    for (int i = 0; i < (int)v.size(); i++) {
        comp++;
        if (v[i]->codigo == codigo) return i;
    }
    return -1;
}

// Busca binaria: divide o intervalo pela metade. Complexidade O(log n).
int buscaBinaria(vector<Produto*>& v, int codigo, int& comp) {
    int ini = 0, fim = (int)v.size()-1;
    comp = 0;
    while (ini <= fim) {
        comp++;
        int meio = (ini + fim)/2;
        if (v[meio]->codigo == codigo) return meio;
        if (v[meio]->codigo < codigo) ini = meio+1;
        else fim = meio-1;
    }
    return -1;
}

// Compara as buscas e consulta tambem a arvore.
void pesquisar() {
    if (!produtos) { cout << "Cadastre um produto primeiro.\n"; return; }
    int codigo, c1, c2;
    cout << "Codigo para pesquisar: "; cin >> codigo;
    vector<Produto*> v = criarVetor();
    int pos1 = buscaSequencial(v, codigo, c1);
    bubbleSort(v);
    int pos2 = buscaBinaria(v, codigo, c2);
    cout << "Sequencial: " << c1 << " comparacoes\n";
    cout << "Binaria: " << c2 << " comparacoes\n";
    cout << "Arvore: " << (buscarArvore(raiz,codigo) ? "encontrado" : "nao encontrado") << "\n";
    if (pos1 != -1) cout << "Produto: " << v[pos2]->nome << " | R$ " << v[pos2]->preco << "\n";
    else cout << "Produto nao encontrado.\n";
}

// FILA FIFO: adiciona cliente no final.
void adicionarCliente() {
    Cliente* novo = new Cliente;
    cout << "Nome do cliente: "; getline(cin >> ws, novo->nome);
    novo->prox = nullptr;
    if (!fim) inicio = fim = novo;
    else { fim->prox = novo; fim = novo; }
    cout << "Cliente entrou na fila.\n";
}

// FILA FIFO: atende e remove o primeiro cliente.
void atenderCliente() {
    if (!inicio) { cout << "Fila vazia.\n"; return; }
    Cliente* temp = inicio;
    cout << "Atendendo: " << temp->nome << "\n";
    inicio = inicio->prox;
    if (!inicio) fim = nullptr;
    delete temp;
}

// PILHA LIFO: registra venda e reduz o estoque.
void registrarVenda() {
    int codigo;
    cout << "Codigo do produto vendido: "; cin >> codigo;
    Produto* p = produtos;
    while (p && p->codigo != codigo) p = p->prox;
    if (!p) { cout << "Produto nao encontrado.\n"; return; }
    if (p->estoque <= 0) { cout << "Sem estoque.\n"; return; }
    p->estoque--;
    Venda* nova = new Venda;
    nova->descricao = "Venda: " + p->nome + " (codigo " + to_string(codigo) + ")";
    nova->prox = topo; topo = nova;
    cout << "Venda registrada.\n";
}

// Exibe historico da venda mais recente para a mais antiga.
void historico() {
    if (!topo) { cout << "Historico vazio.\n"; return; }
    for (Venda* p = topo; p; p = p->prox) cout << p->descricao << "\n";
}

// LIBERACAO DE MEMORIA: arvore recursiva.
void liberarArvore(NoArvore* no) {
    if (!no) return;
    liberarArvore(no->esq); liberarArvore(no->dir);
    delete no;
}

// Libera todos os nos da lista de produtos.
void liberarProdutos() {
    while (produtos) {
        Produto* temp = produtos; produtos = produtos->prox;
        delete temp;
    }
}

// Libera todos os nos da fila.
void liberarFila() {
    while (inicio) {
        Cliente* temp = inicio; inicio = inicio->prox;
        delete temp;
    }
    fim = nullptr;
}

// Libera todos os nos da pilha.
void liberarPilha() {
    while (topo) {
        Venda* temp = topo; topo = topo->prox;
        delete temp;
    }
}

// Libera todas as estruturas antes de encerrar.
void liberarMemoria() {
    liberarProdutos(); liberarArvore(raiz); raiz = nullptr;
    liberarFila(); liberarPilha();
}

// MENU PRINCIPAL.
int main() {
    int opcao;
    do {
        cout << "\n=== GERENCIADOR DE ESTABELECIMENTO ===\n";
        cout << "1-Cadastrar  2-Remover  3-Listar  4-Pesquisar\n";
        cout << "5-Mostrar arvore  6-Adicionar cliente  7-Atender\n";
        cout << "8-Registrar venda  9-Historico  0-Sair\nOpcao: ";
        cin >> opcao;
        switch (opcao) {
            case 1: cadastrar(); break;
            case 2: removerProduto(); break;
            case 3: listarProdutos(); break;
            case 4: pesquisar(); break;
            case 5: listarArvore(raiz); cout << "\n"; break;
            case 6: adicionarCliente(); break;
            case 7: atenderCliente(); break;
            case 8: registrarVenda(); break;
            case 9: historico(); break;
            case 0: cout << "Encerrando...\n"; break;
            default: cout << "Opcao invalida.\n";
        }
    } while (opcao != 0);
    liberarMemoria();
    cout << "Memoria liberada.\n";
    return 0;
}
