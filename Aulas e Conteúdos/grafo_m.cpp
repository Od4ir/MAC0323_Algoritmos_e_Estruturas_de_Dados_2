#include <bits/stdc++.h>
#include "grafo.h"
using namespace std;

// Funções de Grafo Implementado como Matriz:

// Criação do grafo:
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

// Adicão de nova aresta com direção;
void GrafoM::add_d(int u, int v) {
    // Adicionando uma aresta de u para v (com direção);
    adj[u][v] = 1;
    E++;
}

// Adição de nova aresta sem direção;
void GrafoM::add(int u, int v) {
    // Adicionando uma aresta sem direção:
    add_d(u, v);
    add_d(v, u);
    E--; // Retira a aresta que foi contada duplamente;
}

// Printar a matriz de adjacências;
void GrafoM::print() { 
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            cout << adj[i][j] << ' ';
        }
        cout << '\n';
    }
}

// BUsca em largura;
// --> Vai visitando todos os vértices (Modelo Geral);
void GrafoM::dfs() {
    // Vetor para marcar os vértices visitados;
    bool * visitado = new bool[V + 2];
    // Marcamos todos os vértices como não visitado;
    for(int i = 0; i < V; i++) visitado[i] = false;
    // Percorremos os vértices e se ele não foi visitado, chamamamos
    // a dfs recursiva nele que irá marcar os vértices conectados;
    for(int i = 0; i < V; i++) {
        if(!visitado[i]) {
            dfsR(i, visitado);
        }
    }
    delete[] visitado;
}

// A partir de um vértice, visita todos seus adjacentes e assim 
// vai recursivamente;
// --> É pior que o modelo de vetor pois precisa iterar por todos os vértices
//     e verificar se existe aresta entre o atual e o iterado; 
void GrafoM::dfsR(int u, bool * visitado) {
    visitado[u] = true;
    for(int v = 0; v < V; v++) {
        if(adj[u][v] == 1 && !visitado[v]) {
            dfsR(v, visitado);
        }
    }
}

bool GrafoM::tem_caminho(int u, int v) {
    bool * visitado = new bool[V + 2];

    for(int i = 0; i < V; i++) visitado[i] = false;

    dfsR(u, visitado);
    return visitado[v];
}

void GrafoM::imprime_caminho(int u, int v) {
    bool * visitado = new bool[V + 2];
    int * pred = new int[V + 2];

    for(int i =0; i < V; i++) {
        visitado[i] = false;
        pred[i] = -1;
    }

    pred[u] = u;
    acha_caminho_r(u, visitado, pred);

    if(pred[v] == -1) {
        cout << "Não tem caminho\n";
    }
    else {
        for(int w = v; w != u; w = pred[w]) {
            printf("%d - ", w);
        }
        cout << u << endl;
    }
}

void GrafoM::acha_caminho_r(int v, bool * visitado, int * pred) {
    visitado[v] = true;

    for(int i = 0; i < V; i++) {
        if(adj[v][i] != 0 && !visitado[i]) {
            pred[i] = v;
            acha_caminho_r(i, visitado, pred);
        }
    }
}
int main() {
    cout << "Digite o número de vértices: \n";
    int N; cin >> N;
    GrafoM GG(N);

    cout << "Digite o número de arestas: \n";
    int A; cin >> A;

    cout << "Digite as arestas: \n";

    for(int i = 0; i < A; i++) {
        int a, b;
        cin >> a >> b;
        GG.add_d(a, b);
    }
    int ok = 1;

    // PROBLEMA 1 //

    /*while(ok) { 
        cout << "Digite dois vértices: ";
        int u, v; cin >> u >> v;

        GG.imprime_caminho(u, v);
        cout << "Continuar? "; cin >> ok;
    }
    return 0;*/

    


}
 