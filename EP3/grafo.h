#include <iostream>
#include <vector>
#include <string>
using namespace std;
using ll = long long int;

typedef string Info;

// Estrutura de cada vértice/nó:
struct node {
    Info info;
    ll id;
    node(Info info, int i) {
        info.assign(info);
        id = i;
    }
};

// Vetor de vértices, nós:
typedef struct vector<node> vertices;

// Estrutura de uma aresta:
struct aresta {
    node vertice;
    ll peso;
};

// Vetor de arestas:
typedef struct vector<vector<aresta>> arestas;

// arestas[i][j].vertice =  node ao qual o node de id i está conectado;
// arestas[i][j].peso = um valor inteiro que indica o peso da aresta;