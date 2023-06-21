#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;
using ll = long long int;


// ---------------------- /// ESTRUTURAS /// ---------------------- // 

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
    aresta() {}
    // Eu considero que arestas são diferentes de elas tem mesmo id de 
    // vértice e mesmo peso;
    // Como eu só chamo essa função 
    bool operator==(const aresta& a) const {
        return (vertice == a.vertice);
    }
    void operator=(const aresta& aux) {
        vertice = aux.vertice;
        peso = aux.peso;
    }
};

// Vetor de arestas;
// arestas[i][j].vertice =  node ao qual o node de id i está conectado;
// arestas[i][j].peso = um valor inteiro que indica o peso da aresta;
typedef struct vector<vector<aresta>> arestas;

// Estrutura auxiliar de arcos;
struct arco {
    aresta a;
    ll v;
    arco(aresta aux,  ll vertice) {
        a = aux;
        v = vertice;
    }
    bool operator==(const arco& arc) const {
        return (a == arc.a && v == arc.v);
    }
};

// Vetor de arcos;
typedef struct vector<arco> arcos;



// ---------------------- ///  FUNÇÕES   /// ---------------------- // 

// Função que compara dois arcos - serve para ordenação do vetor de 
// arcos. 
bool compara_arco(const arco& arc1, const arco& arc2) {
    return arc1.a.peso < arc2.a.peso;
}


// Recebe o vetor de arcos, o de arestas, dois nodes u e v, e o peso re-
// sentado por k e adiciona uma aresta entre u e v com peso k caso não 
// já exista uma aresta entre v e u com peso maior que k. 
// Se está aresta for criada, coloca ela nos vetores arc e are;
void add_aresta_simples(arcos& arc, arestas &are, node &u, node &v, ll k) {
    // Vamos adicionar uma aresta que sai de u para v;
    v.g_in++;
    are[u.id].push_back(aresta(v.id, k));
    arco aux(are[u.id][are[u.id].size() - 1], u.id);

    arc.push_back(aux);
    u.g_out = (ll)are[u.id].size();
}

// Adiciona uma aresta entre os nodes u e v se já não existe uma aresta entre eles;
// Se existir, verifica se o peso da nova é maior do que a da antiga;
// Se for, substitui, se não, não adiciona a nova aresta;
void add_aresta(arcos& arc, arestas& are, node& u, node& v, ll k) {

    // Primeiro vamos ver se já existe uma aresta entre v e u;
    // Se já existir, vamos ver se o k dela é menor que o k da atual;
    //  Se for menor, destruimos ela e colocamos a nova;
    //  Se for maior, não adicionamos a nova;

    for(aresta a: are[v.id]) {
        if(a.vertice == u.id) {
            // Já tem uma aresta entre os dois e o peso é menor;
            if(a.peso < k) {
                are[v.id].erase(remove(are[v.id].begin(), are[v.id].end(), a), are[v.id].end());
                arco aux(a, v.id);
                arc.erase(remove(arc.begin(), arc.end(), aux), arc.end());
                // Vamos remover a aresta que sai de v para u:
                v.g_out = are[v.id].size();
                u.g_in--;
                add_aresta_simples(arc, are, u, v, k);
                return;
            }
            // Se for maior, não adiciona;
            return;
        }
    }
    // Se sair do loop sem dar return, significa que ainda não há uma 
    // aresta entre eles;

    // Adiciona uma aresta entre u e v se forem nodes diferentes;
    if(!(u == v)) add_aresta_simples(arc, are, u, v, k);
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

// Realiza uma dfs no grafo;
void dfs(ll u, const arestas& are, bool * vis) {
    vis[u] = true;

    for(aresta a: are[u]) {
        if(!vis[a.vertice]) {
            dfs(a.vertice, are, vis);
        }
    }
}

// É uma dfs alterada para verificar se uma aresta está em ciclo ou não. 
// Retorna true se o vértice v for acessado em algum momento e false se
// v nunca for acessado. 
bool dfs_ciclo(ll u, ll v, const arestas& are, bool * vis) {
    vis[u] = true;

    for(aresta a: are[u]) {
        if(a.vertice == v) return true;
        if(!vis[a.vertice]) {
            return dfs_ciclo(a.vertice, v, are, vis);
        }
    }

    return false;
}

// Dado dois nós, retorna se a aresta entre eles está em um circuito ou não;
// É garantido que só chamarei essa função caso exista uma aresta u -> v;
bool aresta_em_circuito(ll V, const arestas& are, const node &u, const node &v) {
    bool * vis = new bool[V + 1];
    for(int i = 0; i < V; i++) vis[i] = false;

    //return dfs_ciclo(v.id, u.id, are, vis);
    dfs(v.id, are, vis);
    if(vis[u.id]) return true;
    return false;
}

// Utilizando as funções de remoação do vector, remove a aresta entre u e v;
void remove_aresta(arestas& are, node &u, node&v) {
    // Remove aresta entre u -> v e atualiza os valores de g_in e g_out;
    aresta aux(v.id, 0);
    are[u.id].erase(remove(are[u.id].begin(), are[u.id].end(), aux), are[u.id].end());
    u.g_out--;
    v.g_in--;
}

// DFS alterada para gerar uma ordenação topológica dos vértices do grafo, colo-
// cando-os na pilha order;
void dfs_ordem_topologica(ll u, bool * vis, stack<ll>& order, const arestas& adj) {
    vis[u] = true;

    for(aresta v: adj[u]) {
        if(!vis[v.vertice]) {
            dfs_ordem_topologica(v.vertice, vis, order, adj);
        }
    }

    order.push(u);
}

// FUnção que devolve um vetor com a ordenação topológica;
vector<ll> ordenacao_topologica(ll V, const arestas& adj) {
    bool * vis = new bool[V + 1];
    for(ll i = 0; i < V; i++) vis[i] = false;

    stack<ll> order;
    vector<ll> ordem_topologica;

    for(ll i = 0; i < V; i++) {
        if(!vis[i]) {
            dfs_ordem_topologica(i, vis, order, adj);
        }
    }

    while(!order.empty()) {
        ordem_topologica.push_back(order.top());
        order.pop();
    }

    return ordem_topologica;
}

// Função que devolve um vetor com predecessores dos vértices e salva em 
// dest o vértice para o qual percorremos a maior distância;
vector<ll> caminho_maximo(const arestas& adj, ll source, ll V, ll& dest) {
    vector<ll> dist(V, -1);
    vector<ll> pred(V, -1);
    dist[source] = 0;
    pred[source] = source;
    ll MAX = -1;

    vector<ll> order = ordenacao_topologica(V, adj);

    for(ll i = 0; i < V; i++) {
        ll u = order[i];

        if(dist[u] != -1) {
            for(aresta a: adj[u]) {
                if(dist[a.vertice] < dist[u] + a.peso) {
                    dist[a.vertice] = dist[u] + a.peso;
                    pred[a.vertice] = u;
                    MAX = max(MAX, dist[a.vertice]);
                    if(MAX == dist[a.vertice]) {
                        dest = a.vertice;
                    }

                }
            }
        }
    }

    return pred;
}

// Devolve um vetor com os vértices em ordem do caminho máximo;
vector<ll> o_caminho_maximo(vector<ll>& pred, ll dest) {
    stack<ll> caminho;

    while(dest != -1 && pred[dest] != dest) {
        caminho.push(dest);
        dest = pred[dest];
    }
    caminho.push(dest);
    vector<ll> biggest_way;

    cout << "Caminho máximo: \n";

    while(!caminho.empty()) {
        biggest_way.push_back(caminho.top());
        caminho.pop();
    }
    return biggest_way;
}

// Printa o caminho máximo:
void printa_biggest_way(vector<ll>& big, vertices& verts, arestas& adj) {
    ll fim = (ll)big.size();
    if(big[0] != -1) { 
        cout << verts[big[0]].info;

        for(ll i = 1; i < fim; i++) {
            for(aresta a: adj[big[i - 1]]) {
                if(a.vertice == big[i]) {
                    ll tam = verts[a.vertice].info.size();
                    if(tam != a.peso) {
                        cout << verts[a.vertice].info.substr(a.peso, tam - a.peso);
                    }
                    break;
                }
            }
        }
    }
    cout << endl;
}

// Gera a string final de resposta:
string resp_final(vector<ll>& big, vertices& verts, arestas& adj) {
    ll fim = (ll)big.size();
    string dna_resp;
    if(big[0] != -1) { 
        dna_resp.append(verts[big[0]].info);
        
        for(ll i = 1; i < fim; i++) {
            for(aresta a: adj[big[i - 1]]) {
                if(a.vertice == big[i]) {
                    ll tam = verts[a.vertice].info.size();
                    if(tam != a.peso) {
                        dna_resp.append(verts[a.vertice].info.substr(a.peso, tam - a.peso));
                    }
                    break;
                }
            }
        }
    }
    return dna_resp;
}

// Printa o caminho máximo em número de vértices; 
void printa_caminho_maximo(vector<ll>& pred, ll dest) {
    stack<ll> caminho;

    while(pred[dest] != dest) {
        caminho.push(dest);
        dest = pred[dest];
    }
    caminho.push(dest);

    cout << "Caminho máximo: \n";

    while(!caminho.empty()) {
        cout << caminho.top() << " ";
        caminho.pop();
    }
    cout << endl;
}