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


// Dados dois vértices, determina se existe caminho eles ou não;
bool GrafoL::tem_caminho(int u, int v) {
    // Criamos um vetor para marcar que todos os vértices ainda não 
    // foram visitados;
    bool * visitado = new bool[V + 2];
    for(int i = 0; i < V; i++) visitado[i] = false;

    // Rodamos uma dfs patindo de u, se chegamos em v, então visitado[v]
    // é true, se não chegamos é false;

    dfsR(u, visitado);
    return visitado[v];
}


void GrafoL::imprime_caminho(int u, int v) {
    bool * visitado = new bool[V + 2];
    int * pred = new int[V + 2];

    for(int i =0; i < V; i++) {
        visitado[i] = false;
        pred[i] = -1;
    }

    pred[u] = u;
    acha_caminho_r(u, visitado, pred);

    if(pred[v] == -1) {
        cout << "Não tem caminho!\n";
    }
    else { 
        for(int w = v; w != u; w = pred[w]) {
            printf("%d - ", w);
        }
        cout << u << '\n';
    }

}

void GrafoL::acha_caminho_r(int v, bool * visitado, int * pred) {
    // É uma dfs com a diferença que estamos marcando o predecessor;
    visitado[v] = true;

    for(int w: adj[v]) {
        if(!visitado[w]) {
            // Salva no pred qual foi o vértice que foi visto anteriormente;
            pred[w] = v;
            acha_caminho_r(w, visitado, pred);
        }
    }
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

    int ok = 1;


    // PROBLEMA 1 // 

    // Tem caminho de u a v? Como resolver esse problema?
    // --> Roda a dfs recursiva partindo de u, se o visitado de u marcar
    //     falso após a dfsR, então não existe caminho;

    /*while(ok) { 
        cout << "Digite dois vértices: ";
        int u, v; cin >> u >> v;

        if(GG.tem_caminho(u, v)) printf("Tem caminho entre %d e %d\n", u, v);
        else printf("Não tem caminho entre %d e %d\n", u, v);
        cin >> ok;
    }*/


    // PROBLEMA 2 //

    // Se tem caminho, como imprimir esse caminho?
    // --> Roda uma dfs e salva num vetor de predecessores qual foi o vértice
    //     que foi visitado antes do vértice de valor do índice. Exemplo: se
    //     pred[i] = y, então o vértice visitado antes do y foi o i;

    /*while(ok) { 
        cout << "Digite dois vértices: ";
        int u, v; cin >> u >> v;

        GG.imprime_caminho(u, v);
        cout << "Continuar? "; cin >> ok;
    }*/

    return 0;
}