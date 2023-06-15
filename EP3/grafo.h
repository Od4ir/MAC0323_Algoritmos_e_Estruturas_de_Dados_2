#include <iostream>
#include <vector>
#include <string>
using namespace std;
using ll = long long int;

// Estrutura de cada vértice/nó:
struct node {
    string info;
    ll id;
    node(string informacao, ll i) {
        info.assign(informacao);
        id = i;
    }
    node() { }

    bool operator==(const node& b) const {
        return (id == b.id);
    }

};

// Vetor de vértices, nós:
typedef struct vector<node> vertices;

// Estrutura de uma aresta:
struct aresta {
    node vertice;
    ll peso;
    aresta(node no, ll p) {
        peso = p;
        vertice = no;
    }
    bool operator==(const aresta& a) const {
        return (vertice.id == a.vertice.id && peso == a.peso);
    }
};

// Vetor de arestas:
typedef struct vector<vector<aresta>> arestas;

// arestas[i][j].vertice =  node ao qual o node de id i está conectado;
// arestas[i][j].peso = um valor inteiro que indica o peso da aresta;