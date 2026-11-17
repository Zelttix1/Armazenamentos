# Sistema de Gerenciamento de Estabelecimento

## 1. Sobre o projeto

O **Sistema de Gerenciamento de Estabelecimento** é um projeto desenvolvido em C++ com o objetivo de facilitar o gerenciamento de uma pequena loja por meio de um sistema executado no terminal.

O programa permite cadastrar, remover, consultar e organizar produtos, além de controlar o atendimento de clientes e manter um histórico de vendas.

O projeto foi desenvolvido com foco na aplicação prática de conceitos de programação e estruturas de dados estudados durante o curso de Engenharia de Software.

## 2. Funcionalidades

O sistema possui as seguintes funcionalidades:

- **Cadastro de produtos:** permite adicionar novos produtos ao estabelecimento.
- **Remoção de produtos:** permite excluir produtos cadastrados.
- **Listagem de produtos:** apresenta os produtos disponíveis.
- **Busca de produtos:** permite localizar produtos por seu código.
- **Ordenação:** organiza os produtos utilizando o algoritmo Bubble Sort.
- **Árvore binária de busca:** organiza os produtos por código, facilitando as consultas.
- **Fila de atendimento:** organiza os clientes conforme a ordem de chegada.
- **Pilha de vendas:** armazena o histórico das vendas realizadas.
- **Menu interativo:** permite acessar as funcionalidades do programa.

## 3. Tecnologias utilizadas

- Linguagem de programação: C++.
- Biblioteca iostream: entrada e saída de dados.
- Biblioteca string: manipulação de textos.
- Estruturas de dados: listas encadeadas, árvores binárias, filas e pilhas.
- Algoritmos: busca, recursividade e Bubble Sort.

## 4. Estrutura do projeto

```text
Sistema-Gerenciamento-Estabelecimento/
│
├── main.cpp
├── README.md
└── Relatorio_Tecnico.md
```

**main.cpp:** contém a implementação do sistema e suas funcionalidades.

**README.md:** apresenta informações gerais, funcionalidades e instruções de execução.

**Relatorio_Tecnico.md:** apresenta os aspectos técnicos e as estruturas de dados utilizadas.

## 5. Como executar

É necessário possuir um compilador C++ instalado, como o GCC.

No terminal, acesse a pasta do projeto e execute:

```bash
g++ -std=c++17 -Wall main.cpp -o estabelecimento
```

Depois, execute o programa:

**Windows:**
```bash
estabelecimento.exe
```

**Linux:**
```bash
./estabelecimento
```

## 6. Objetivo acadêmico

O projeto tem como finalidade demonstrar a utilização de diferentes estruturas de dados e algoritmos na resolução de um problema prático.

Além disso, busca desenvolver conhecimentos sobre organização de código, lógica de programação, manipulação de dados e integração de funcionalidades.

## 7. Considerações finais

O Sistema de Gerenciamento de Estabelecimento reúne diferentes conceitos de programação em uma aplicação simples e funcional, simulando operações básicas de uma pequena loja.
