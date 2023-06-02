#include <bits/stdc++.h>
#include "grafo.h"
using namespace std;

// Funções de Grafo Implementado como Vetor:

// Criação do grafo:
GrafoL::GrafoL(int N) {
    E = 0;
    V = N;
    adj = (vector<int> *) malloc(sizeof(vector<int>) * (N + 2));
}

// Adicão de nova aresta com direção;
void GrafoL::add_d(int v, int u) {
    adj[v].push_back(u);
    E++;
}

// Adição de nova aresta sem direção;
void GrafoL::add(int v, int u) {
    add_d(v, u);
    add_d(u, v);
    E--; 
}

// Printa para cada vértice seus adjacentes;
void GrafoL::print() {
    for(int i = 1; i <= V; i++) {
        cout << "Vértice: " << i << ": ";
        for(int j = 0; j < adj[i].size(); j++) {
            cout << adj[i][j] << " - ";
        }
        cout << endl;
    }
}

// BUsca em largura;
// --> Vai visitando todos os vértices (Modelo Geral);
void GrafoL::dfs() {
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
// --> É melhor que o modelo de matriz na maioria dos casos pois a iteração
//     ocorre somente nos vértices com adjacência, já salvos no vetor;
void GrafoL::dfsR(int u, bool * visitado) {
    // Marcamos que acabamos de visitar o vértice:
    visitado[u] = true;
    // Para todos os vértices conectados ao vértice u que ainda não
    // foram visitados, chamaos o dfs recursivo para marcá-los e marcar
    // seus adjacentes;
    for(int v: adj[u]) {
        if(!visitado[v]) {
            dfsR(v, visitado);
        }
    }
    // No final de apenas uma iteração, se o grafo não apresentar mais
    // de um componente conexo, todos os vértices estarão marcados;
}

bool GrafoL::tem_caminho(int u, int v) {
    bool * visitado = new bool[V + 2];
    for(int i = 0; i < V; i++) visitado[i] = false;

    dfsR(u, visitado);
    return visitado[v];
}



int main() {
    // Adição das arestas e vértices;
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


    // Tem caminho de u a v? Como resolver esse problema?
    // --> Roda a dfs recursiva partindo de u, se o visitado de u marcar
    //     falso após a dfsR, então não existe caminho;

    cout << "Digite dois vértices: ";
    int u, v; cin >> u >> v;

    if(GG.tem_caminho(u, v)) printf("Tem caminho entre %d e %d\n", u, v);
    else printf("Não tem caminho entre %d e %d\n", u, v);


    // Se tem caminho, como imprimir esse caminho?
    // --> 


    return 0;
}