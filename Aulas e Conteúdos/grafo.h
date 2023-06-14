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
        bool tem_caminho(int u, int v); // Devolve se existe caminho entre u e v;
        void acha_caminho_r(int v, bool * visitado, int * pred);   // Encontra o caminho entre u e v;
        void imprime_caminho(int u, int v);                        // Imprime o caminho entre u e v (Ao contrário);
        int comp_conexa();                     // Devolve quantas componentes conexas o grafo tem;
        vector<int> vetor_comp_conexas();      // Devolve um vetor marcando qual a componente conexa de cada vértice;
        bool eh_bipartido();                                  // Devolve se o grafo é bipartido ou não;
        bool bipartidoR(int v, vector<int>& cores, int cor);
        vector<int> caminho_mais_curto(int u); // Devolve os comprimentos do caminho mais curto de u a qualquer outro vértice;
        void acha_caminho_curtos(int u, vector<int>& dist, vector<int>& pred);
        void imprime_caminho_curto(int u, int v);
        void dfs2();
        void dfsR2(int u, int * pre, int * pos, int * pred, int& tempo);
        bool tem_circuito();
        bool circ_r(int u, int * pre, int * pos, int * pred, int& tempo);
        int * comp_fortemente_conexas();
        void dfsCFCR(int v, int * pre, int * sc, int * low, int& cont, int& k, stack<int>& pilha);
        // CFCR - Componentes Fortemente Conexos Recursivo;
};