<!-- omit in toc -->
# 🔤 EP4 - Grafo e Expressões Regulares;

<!-- omit in toc -->
## 📑 índice:

- [📄 Descrição:](#-descrição)
- [🔗 Dependências:](#-dependências)
- [▶️ Executando o código:](#️-executando-o-código)
- [🧪 Como Testar:](#-como-testar)
  - [⬅️ Exemplos de Entradas e Sáidas:](#️-exemplos-de-entradas-e-sáidas)



## 📄 Descrição:

O objetivo do EP4 foi implementar um programa que recebe uma expressão regular contendo diferentes símbolos diferentes (Veja mais no [Enunciado do EP4](#)) e um conjunto de palavras e verifica se a expressão é reconhecida ou não pela expressão passada. Para isso, a implementação contou com o uso da estrutura de um grafo para representar um autômato finito não determinístico para verificar se, dada uma palavra, existe nesse grafo um caminho que leva a aceitação da palavra. 


Para entender o melhor o projeto, considere ler:
- [Enunciado do EP4](#link);



## 🔗 Dependências:
Todos os testes foram feitos em um computador com **arquitetura x86_64** com sistema operacional **Linux Ubuntu - 22.04.3 LTS**.
- **g++ (GNU C++ Compiler):** g++ (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0;


## ▶️ Executando o código:
Para compilar o código, basta digitar no terminal:
```bash
g++ EP4.cpp -o EP4
```
Para executar:
```bash
./EP4
```

## 🧪 Como Testar:
Para testar o código (EP4.cpp), basta compilá-lo e executá-lo como descrito anteriormente, e após isso preencher as informações solicitadas. As informações solicitadas serão:
- A expressão regular no formato aceito;
- O número de palavras que você deseja testar;
- As palavras que serão testadas;

Veja um exemplo abaixo de algumas expressões regulares:

### ⬅️ Exemplos de Entradas e Sáidas:
```
Expressão Regular: ((A*B)|C)* 

Palavras:
-> ABC (S);
-> AC (N);
-> BCAB (S);
```

```
Expressão Regular: (.)*A(.)*

Palavras: 
-> ABA (S);
-> Cachorro (N);
-> CAchorro (N);
```
```
Expressão Regular: R[AEIOU]T[AEIOU]

Palavras:
-> RATO (S);
-> RTTA (N);
-> TORA (N);
-> RUTU (S);
```