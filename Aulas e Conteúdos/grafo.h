#include <bits/stdc++.h>
using namespace std;

// Implementação em Matriz:

class GrafoM {
    public:
        int **adj;                 // Matriz de adjacência;
        int E;                     // Número de arestas;
        int V;                     // Númeor de vértices;
        GrafoM(int N);              // Cria um grafo a partir do parâmetro n;
        void add(int u, int v);    // Adiciona uma aresta no grafo (sem direção);
        void add2(int u, int v);   // Adiciona uma aresta no grafo (com direção);
        void print();              // Printa a matriz de adjacência do grafo;

};

class GrafoL {
    public:
        GrafoL(int V);
        int E;
        int V;                         // Número de vértices;
        vector<vector<int>> adj;       // Lista de adjacências;
        void add(int u, int v);        // Adiciona uma aresta entre u e v sem direção;
        void add2(int u, int v);       // Adiciona uma aresta com direção de u a v;
};