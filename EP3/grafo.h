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


// Adiciona uma aresta entre os nodes u e v;
void add_aresta_simples(arestas &are, node &u, node &v, ll k) {
    // Vamos adicionar uma aresta que sai de u para v;
    v.g_in++;
    are[u.id].push_back(aresta(v.id, k));
    u.g_out = (ll)are[u.id].size();
}

// Adiciona uma aresta entre os nodes u e v se já não existe uma aresta entre eles;
// Se existir, verifica se o peso da nova é maior do que a da antiga;
// Se for, substitui, se não, não adiciona a nova aresta;
void add_aresta(arestas& are, node& u, node& v, ll k) {

    // Primeiro vamos ver se já existe uma aresta entre v e u;
    // Se já existir, vamos ver se o k dela é menor que o k da atual;
    //  Se for menor, destruimos ela e colocamos a nova;
    //  Se for maior, não adicionamos a nova;

    for(aresta a: are[v.id]) {
        if(a.vertice == u.id) {
            // Já tem uma aresta entre os dois e o peso é menor;
            if(a.peso < k) {
                are[v.id].erase(remove(are[v.id].begin(), are[v.id].end(), a), are[v.id].end());
                // Vamos remover a aresta que sai de v para u:
                v.g_out = are[v.id].size();
                u.g_in--;
                add_aresta_simples(are, u, v, k);
                return;
            }
            // Se for maior, não adiciona;
            return;
        }
    }
    // Se sair do loop sem dar return, significa que ainda não há uma 
    // aresta entre eles;

    // Adiciona uma aresta entre u e v se forem nodes diferentes;
    if(!(u == v)) add_aresta_simples(are, u, v, k);
}

// Avalia se existem circuitos na aresta ou não;
bool circ_r(ll u, ll * pre, ll * pos, ll& tempo, const arestas& adj) {
    pre[u] = tempo++;

    for(aresta w: adj[u]) {
        if(pre[w.vertice] == -1) {
            if(circ_r(w.vertice, pre, pos, tempo, adj)) return true;
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


// Retorna se o grafo tem circuitos ou não;
bool tem_circuito(ll V, const arestas& are) {
    ll * pre = new ll[V + 1];
    ll * pos = new ll[V + 1];
    ll tempo = 0;

    for(ll i = 0; i < V; i++) {
        pre[i] = pos[i] = -1;
    }

    for(ll i = 0; i < V; i++) { // A gnt itera por todas os vértices pois
        // não tem certeza se o grafo tem mais de uma comp. conexa;
        if(pre[i] == -1) {
            if(circ_r(i, pre, pos, tempo, are)) {
                delete[] pre;
                delete[] pos;
                return true;
            }
        }
    }
    delete[] pre;
    delete[] pos;
    return false;
}

void dfs(ll u, const arestas& are, bool * vis) {
    vis[u] = true;

    for(aresta a: are[u]) {
        if(!vis[a.vertice]) {
            dfs(a.vertice, are, vis);
        }
    }
}

// Dado dois nós, retorna se a aresta entre eles está em um circuito ou não;
// É garantido que só chamarei essa função caso exista uma aresta u -> v;
bool aresta_em_circuito(ll V, const arestas& are, const node &u, const node &v) {
    bool * vis = new bool[V + 1];
    for(int i = 0; i < V; i++) vis[i] = false;

    dfs(v.id, are, vis);
    if(vis[u.id]) {
        delete[] vis;
        return true; 
    }

    delete[] vis;
    return false;
}



