#include <bits/stdc++.h>
using namespace std;

// Implementação em Matriz:

class GrafoM {
    public:
        int **adj;                    // Matriz de adjacência;
        int E;                        // Número de arestas;
        int V;                        // Número de vértices;
        GrafoM(int N);                // Cria um grafo a partir do parâmetro n;
        void add(int u, int v);       // Adiciona uma aresta no grafo (sem direção);
        void add_d(int u, int v);     // Adiciona uma aresta no grafo (com direção);
        void print();                 // Printa a matriz de adjacência do grafo;
        void dfs();                   // Busca em profundidade;
        void dfsR(int u, bool * vis);
        bool tem_caminho(int u, int v);
        void acha_caminho_r(int v, bool * visitado, int * pred);
        void imprime_caminho(int u, int v);
};

class GrafoL {
    public:
        GrafoL(int V);
        int E;
        int V;                          // Número de vértices;
        vector<int> * adj;              // Lista de adjacências;
        void add(int u, int v);         // Adiciona uma aresta entre u e v sem direção;
        void add_d(int u, int v);       // Adiciona uma aresta com direção de u a v;
        void print();                   // Printa para cada vértice os vértices conectados;
        void dfs();                     // Busca em profundidade;
        void dfsR(int u, bool * vis);
        bool tem_caminho(int u, int v);
        void acha_caminho_r(int v, bool * visitado, int * pred);
        void imprime_caminho(int u, int v);
};