#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "grafo.h"
#include "operacoes.h"
using namespace std;


// Devolve o índice da primeira aparição da sequência aux
// no vetor v;
int pri(const vector<node>& v, const string aux) {
    int start = 0, end = v.size(), meio;
    int resp = end;

    while(start < end) {
        meio = (start + end)/2;
        //cout << meio << ": " << v[meio].info << endl;

        int ind = v[meio].info.find(aux);
        //cout << " índice: " << ind << endl;
        
        if(ind == 0) {
            resp = min(meio, resp);
            //cout << "ind\n";
            end = meio;
        }
        else if(aux == v[meio].info) {
            //cout << "==\n";
            end = meio;
            // Não sei o que fazer se forem iguais...
        } 
        else if(aux > v[meio].info) {
            //cout << ">\n";
            start = meio + 1;
        }
        else {
            //cout << "<\n";
            end = meio;
        }
    }
    return resp;
}

// Devolve o índice da última aparição da sequência aux
// no vetor v;
int ult(const vector<node>& v, const string aux) {
    int start = 0, end = v.size(), meio;
    int resp = 0;

    while(start < end) {
        meio = (start + end)/2;
        //cout << meio << ": " << v[meio].info << endl;


        int ind = v[meio].info.find(aux);
        //cout << " >> índice: " << ind << endl;
        
        if(ind == 0) {
            resp = max(meio, resp);
            //cout << "ind\n";
            start = meio + 1;
        }
        else if(aux == v[meio].info) {
            start = meio + 1;
            //cout << "==\n";
            // Não sei o que fazer se forem iguais...
        } 
        else if(aux > v[meio].info) {
            //cout << ">\n";
            start = meio + 1;
        }
        else {
            //cout << "<\n";
            end = meio;
        }
    }

    return resp;
}


int main() {
    cout << " \n-----------/// BEM VINDX AO EP3 - Od4ir ///-----------\n\n";


    cout << "\nOlá biologx, digite o nome do arquivo com os pedaços de DNA:\n >> ";
    string file_name;
    cin >> file_name;

    ifstream arquivo(file_name);

    if(arquivo.is_open()) {
        string dna, aux;
        getline(arquivo, dna);
        int copy, V;
        getline(arquivo, aux);
        copy = stoi(aux);
        getline(arquivo, aux);
        V = stoi(aux);

        string linha;
        vertices verts;
        int i = 0;
        while(getline(arquivo, linha)) {
            // Em linha está a substring;
            node no(linha, i++);
            verts.push_back(no);
        }

        cout << "\n Deseja imprimir os dados? S/N: \n >> ";
        char op; cin >> op;

        if(op == 'S') {
            cout << "\n DNA Original: " << dna << endl;
            cout << " Número de cópias.............." << copy << endl;
            cout << " Número de substrings.........." << V << endl;
            cout << " Substrings: " << endl;
            for(node no: verts) { 
                cout << "  " << no.id << ": " << no.info << endl;
            }
        }

        cout << "\n\n---------/// PARTE 2 - MONTAGEM DOS ARCOS ///----------\n\n";

        cout << "Escolha o parâmetro V: (Valor mínimo " << V << ") \n >> ";
        int K; cin >> K;
        vector<int> vis(V + 1, 0);

        arestas adj = vector<vector<aresta>>(V);

        for(node no: verts) {
            ll k_max = no.info.size();
            fill(vis.begin(), vis.end(), 0);

            ll tam = no.info.size();

            while(k_max >= K) {
                string aux = no.info.substr(tam - k_max, k_max);
                ll p = pri(verts, aux);
                ll u = ult(verts, aux);
                for(ll i = p; i <= u; i++) {
                    if(vis[i] == 0) { 
                        add_aresta(adj, verts[no.id], verts[i], k_max);
                        vis[i] = 1;
                    }
                }
                k_max--;
            }
        }
        cout << "\n Deseja imprimir as arestas e seus pesos? S/N: \n >> ";
        cin >> op;

        if(op == 'S') { 
            for(int i = 0; i < V; i++) {
                cout << i << ": " << verts[i].info << endl;
                cout << "Grau de saída: " << adj[i].size() << " " << verts[i].g_out << endl;
                cout << "Grau de entrada: " << verts[i].g_in << endl;
                for(aresta a: adj[i]) {
                    cout << "  >" << a.vertice << ": " << verts[a.vertice].info << "(" << a.peso << ")\n";
                }
            }
        }


        if(tem_circuito(V, adj)) {
            cout << "Grafo tem circuito!\n";
        }
        else {
            cout << "Grafo não tem circuitos!\n";
            cout << "Ordenação Topológica: \n";
            vector<ll> order = ordenacao_topologica(V, adj);

            for(ll i = 0; i < (ll)order.size(); i++) {
                cout << order[i] << " - ";
            }

            ll dest;

            for(ll i = 0; i < V; i++) {
                if(verts[i].g_in == 0) {
                    cout << "Caminho máximo saindo de " << i << ": " << verts[i].info << endl;
                    vector<ll> pred = caminho_maximo(adj, i, V, dest);
                    vector<ll> big = o_caminho_maximo(pred, dest);
                    //printa_caminho_maximo(pred, dest);
                    printa_biggest_way(big, verts, adj);

                }
            }
        }

    }
    else {
        cout << "Não foi possível abrir o arquivo, tente novamente!\n";
    }
    return 0;
    
}