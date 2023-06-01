#include <bits/stdc++.h>
#include "grafo.h"
using namespace std;

// Funções de Grafo Implementado como Matriz:

GrafoM::GrafoM(int N) {
    // Número de vértices:
    V = N;
    // Alocação da matriz:
    *adj = (int *) malloc(sizeof(int) * N);
    for(int i = 0; i < N; i++) {
        adj[i] = (int *) malloc(sizeof(int) * N);
    }
    // Iniciando a matriz toda com zeros:
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }
    // Número de arestas iniciais:
    E = 0;
}

void GrafoM::add_d(int u, int v) {
    u = u - 1;
    v = v - 1;
    // Adicionando uma aresta de u para v (com direção);
    adj[u][v] = 1;
    E++;
}

void GrafoM::add(int u, int v) {
    // Adicionando uma aresta sem direção:
    add_d(u, v);
    add_d(v, u);
    E--; // Retira a aresta que foi contada duplamente;
}

void GrafoM::print() { 
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            cout << adj[i][j] << ' ';
        }
        cout << '\n';
    }
}

// Funções de Grafo Implementado como Vetor:

GrafoL::GrafoL(int N) {
    E = 0;
    V = N;
    adj = (vector<int> *) malloc(sizeof(vector<int>) * (N + 2));
}

void GrafoL::add_d(int v, int u) {
    adj[v].push_back(u);
    E++;
}

void GrafoL::add(int v, int u) {
    add_d(v, u);
    add_d(u, v);
    E--; 
}

void GrafoL::print() {
    for(int i = 1; i <= V; i++) {
        cout << "Vértice: " << i << ": ";
        for(int j = 0; j < adj[i].size(); j++) {
            cout << adj[i][j] << " - ";
        }
        cout << endl;
    }
}



int main() {
    cout << "Digite o número de vértices: \n";
    int N; cin >> N;
    GrafoL GG(N);

    cout << "Digite o número de arestas: \n";
    int A; cin >> A;

    cout << "Digite as arestas: \n";

    for(int i = 0; i < A; i++) {
        int a, b;
        cin >> a >> b;
        GG.add_d(a, b);
    }
    GG.print();
    return 0;
}