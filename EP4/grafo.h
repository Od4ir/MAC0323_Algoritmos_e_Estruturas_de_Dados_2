#include <vector>
#include <iostream>

using namespace std;

class Grafo {
    public:

    int V, E;                      // Número de vértices e arestas;
    vector<vector<int>> adj;       // Lista de adjagências;

    Grafo(int verts) {
        V = verts;
        E = 0;
        adj = vector<vector<int>>(V);
    }

    void add_aresta(int u, int v) {   // Adiciona uma aresta de u -> v;
        cout << "Adicionando entre " << u << " e " << v << endl;
        adj[u].push_back(v);
        E++;
    }

    void dfsR(int u, bool * vis) {     // Executa uma dfs de forma recursiva;
        vis[u] = true;

        for(int v: adj[u]) {
            if(!vis[v]) {
                dfsR(v, vis);
            }
        }
    }
};