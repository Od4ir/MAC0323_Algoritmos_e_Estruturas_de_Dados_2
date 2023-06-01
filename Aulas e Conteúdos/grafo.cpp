#include <bits/stdc++.h>
#include "grafo.h"
using namespace std;

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

void GrafoM::add2(int u, int v) {
    u = u - 1;
    v = v - 1;
    // Adicionando uma aresta de u para v (com direção);
    adj[u][v] = 1;
    E++;
}

void GrafoM::add(int u, int v) {
    // Adicionando uma aresta sem direção:
    add2(u, v);
    add2(v, u);
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

GrafoL::GrafoL(int N) {
    E = 0;
    V = N;
}

void GrafoL::add(int v, int u);

int main() {
    cout << "Digite o número de vértices: \n";
    int N; cin >> N;
    GrafoM G(N);

    cout << "Digite o número de arestas: \n";
    int A; cin >> A;

    cout << "Digite as arestas: \n";

    for(int i = 0; i < A; i++) {
        int a, b;
        cin >> a >> b;
        G.add(a, b);
    }
    G.print();
    return 0;
}



