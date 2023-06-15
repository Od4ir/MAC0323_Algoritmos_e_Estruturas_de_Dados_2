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
    int start = 0, end = v.size() + 1, meio;
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
    int start = 0, end = v.size() + 1, meio;
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

void add_aresta(arestas& are, node u, node v, int k) {

    // Primeiro vamos ver se já existe uma aresta entre v e u;
    // Se já existir, vamos ver se o k dela é menor que o k da atual;
    //  Se for menor, destruimos ela e colocamos a nova;
    //  Se for maior, não adicionamos a nova;

    for(aresta a: are[v.id]) {
        if(a.vertice.info == u.info) {
            // Já tem uma aresta entre os dois;
            if(a.peso < k) {
                are[v.id].erase(remove(are[v.id].begin(), are[v.id].end(), a), are[v.id].end());
                are[u.id].push_back(aresta(v, k));
                return;
            }
            // Se for maior, não adiciona;
            return;
        }
    }
    // Se sair do loop sem dar return, significa que ainda não há uma 
    // aresta entre eles;

    // Adiciona uma aresta entre u e v se forem nodes diferentes;
    if(!(u == v)) are[u.id].push_back(aresta(v, k));
}


int main() {
    cout << " \n-----------/// BEM VINDX AO EP3 - Od4ir ///-----------\n\n";


    cout << "\nOlá biologx, digite o nome do arquivo com os pedaços de DNA: >> \n";
    string file_name;
    cin >> file_name;

    ifstream arquivo(file_name);

    if(arquivo.is_open()) {
        string dna, aux;
        getline(arquivo, dna);
        int copy, k;
        getline(arquivo, aux);
        copy = stoi(aux);
        getline(arquivo, aux);
        k = stoi(aux);

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
            cout << " Número de substrings.........." << k << endl;
            cout << " Substrings: " << endl;
            for(node no: verts) { 
                cout << "  " << no.id << ": " << no.info << endl;
            }
        }

        cout << "\n\n---------/// PARTE 2 - MONTAGEM DOS ARCOS ///----------\n\n";

        cout << "Escolha o parâmetro k: (Valor mínimo " << k << ") \n >> ";
        int K; cin >> K;
        vector<int> vis(k + 1, 0);

        arestas adj = vector<vector<aresta>>(k);

        for(node no: verts) {
            ll k_max = no.info.size();
            fill(vis.begin(), vis.end(), 0);

            for(ll i = 0; i < k; i++) {
                cout << i + 1 << ": " << vis[i] << endl;
            }

            cout << "Nó atual " << no.id << ": " << no.info << endl;
            ll tam = no.info.size();

            while(k_max >= K) {
                string aux = no.info.substr(tam - k_max, k_max);

                cout << " Sub Final: " << aux <<  " k atual: " << k_max <<endl;
                ll p = pri(verts, aux);
                ll u = ult(verts, aux);

                for(ll i = p; i <= u; i++) {
                    if(vis[i] == 0) { 
                        cout << " " << i << ": " << verts[i].info << endl;

                        add_aresta(adj, no, verts[i], k_max);
                        vis[i] = 1;
                    }
                }
                k_max--;
            }
        }

        for(int i = 0; i < k; i++) {
            cout << verts[i].info << endl;
            for(aresta a: adj[i]) {
                cout << "  >" << a.vertice.id << ": " << a.vertice.info << "(" << a.peso << ")\n";
            }
        }
    }

    
}