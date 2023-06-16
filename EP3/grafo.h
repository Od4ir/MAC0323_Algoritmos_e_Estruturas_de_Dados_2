#include <iostream>
#include <vector>
#include <string>
using namespace std;
using ll = long long int;

// Estrutura de cada vértice/nó:
struct node {
    string info;
    ll id;
    ll g_in;
    ll g_out;
    node(string informacao, ll i) {
        info.assign(informacao);
        id = i;
        g_in = 0;
        g_out = 0;
    }
    node() { }

    void atualiza_g_out(int op) {
        if(op == 1) g_out++;
        else g_out--;
    }
    void atualiza_g_in(int op) {
    if(op == 1) g_in++;
    else g_in--;      
    }

    bool operator==(const node& b) const {
        return (id == b.id);
    }

};

// Vetor de vértices, nós:
typedef struct vector<node> vertices;

// Estrutura de uma aresta:
struct aresta {
    ll vertice;
    ll peso;
    aresta(ll no, ll p) {
        peso = p;
        vertice = no;
    }
    // Eu considero que arestas são diferentes de elas tem mesmo id de 
    // vértice e mesmo peso;
    // Como eu só chamo essa função 
    bool operator==(const aresta& a) const {
        return (vertice == a.vertice && peso == a.peso);
    }
};

// Vetor de arestas:
typedef struct vector<vector<aresta>> arestas;

// arestas[i][j].vertice =  node ao qual o node de id i está conectado;
// arestas[i][j].peso = um valor inteiro que indica o peso da aresta;

bool circ_r(ll u, ll * pre, ll * pos, ll * pred, ll& tempo, const arestas& adj) {
    pre[u] = tempo++;

    for(aresta w: adj[u]) {
        if(pre[w.vertice] == -1) {
            pred[w.vertice] = u;
            if(circ_r(w.vertice, pre, pos, pred, tempo, adj)) return true;
        }
        if(pos[w.vertice] == -1) {
            // Se em algum mommento a gente retornar para algum vértice
            // que já teve sua visita iniciada, mas não foi concluída, sa-
            // bemos que esse grafo tem ciclos. 
            return true;
        }
    }
    pos[u] = tempo++;
    return false;
}


bool tem_circuito(ll V, const arestas& are) {
    ll * pre = new ll[V + 1];
    ll * pos = new ll[V + 1];
    ll * pred = new ll[V + 1];
    ll tempo = 0;

    for(ll i = 0; i < V; i++) {
        pre[i] = pos[i] = pred[i] = -1;
    }

    for(ll i = 0; i < V; i++) { // A gnt itera por todas os vértices pois
        // não tem certeza se o grafo tem mais de uma comp. conexa;
        if(pred[i] == -1) {
            pred[i] = -1;
            if(circ_r(i, pre, pos, pred, tempo, are)) return true;
        }
    }
    return false;
}


