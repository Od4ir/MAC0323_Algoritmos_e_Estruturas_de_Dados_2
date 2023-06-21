#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "grafo.h"
#include "operacoes.h"
using namespace std;

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
        ll i = 0;
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

        cout << "Escolha o parâmetro K: \n";//(Valor mínimo " <<  << ") \n >> ";
        int K; cin >> K;
        vector<int> vis(V + 1, 0);

        arestas adj = vector<vector<aresta>>(V);
        arcos arc;

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
                        add_aresta(arc, adj, verts[no.id], verts[i], k_max);
                        vis[i] = 1;
                    }
                }
                k_max--;
            }
        }
        cout << "\nDeseja imprimir as arestas e seus pesos? S/N: \n >> ";
        cin >> op;


        sort(arc.begin(), arc.end(), compara_arco);

        if(op == 'S') { 
            cout << " [1] - Por vértice; \n [2] - Ordenadas por peso\n >> ";
            int opt;
            cin >> opt;

            cout << "\n\n------------------/// IMPRESSÃO ///-------------------\n\n";

            if(opt == 1) { 
                for(int i = 0; i < V; i++) {
                    cout << " " << i << ": " << verts[i].info << endl;
                    cout << "  Grau de saída: " << verts[i].g_out << endl;
                    cout << "  Grau de entrada: " << verts[i].g_in << endl;
                    for(aresta a: adj[i]) {
                        cout << "  >" << a.vertice << ": " << verts[a.vertice].info << "(" << a.peso << ")\n";
                    }
                }
            }
            else { 
                for(int i = 0; i < arc.size(); i++) {
                    cout << arc[i].a.peso << ": (" << arc[i].v << " -> " << arc[i].a.vertice << ")\n";
                }
            }
        }

        cout << "\n---------------/// FIM IMPRESSÃO /// -----------------\n\n";


        if(tem_circuito(V, adj)) {
            cout << "\nGrafo tem circuito...\n";
            cout << "Vamos eliminar os arcos de menor peso até não mais ciclo!\n\n";
            ll minimo = 0;

            while(tem_circuito(V, adj)) { 
                for(ll i = minimo; i < arc.size(); i++) {
                    if(aresta_em_circuito(V, adj, verts[arc[i].v], verts[arc[i].a.vertice])) {
                        printf("(%lld)", arc[i].a.peso);
                        cout << "  Removendo (" << verts[arc[i].v].id << " -> " << verts[arc[i].a.vertice].id << ")!\n";
                        remove_aresta(adj, verts[arc[i].v], verts[arc[i].a.vertice]);
                        minimo = i + 1;
                        break;
                    }
                }
            }
            cout << "\nGrafo não (mais) tem circuitos!\n\n";
        }


        cout << "\n\n-------------/// PARTE 3 - RESPOSTAS ///---------------\n\n";
        cout << "Ordenação Topológica: \n";
        vector<ll> order = ordenacao_topologica(V, adj);

        for(ll i = 0; i < (ll)order.size(); i++) {
            cout << order[i] << " - ";
        }

        ll dest;
        ll tam_max = 0;
        string resp;
        string auxx;


        cout << "\n\nAre you ready for the answer? \n";
        cin >> resp;

        for(ll i = 0; i < V; i++) {
            if(verts[i].g_in == 0) {
                cout << "\n\nCaminho máximo saindo de " << i << ": " << verts[i].info << endl;
                dest = i;
                vector<ll> pred = caminho_maximo(adj, i, V, dest);
                vector<ll> big = o_caminho_maximo(pred, dest);
                //printa_caminho_maximo(pred, dest);
                auxx = resp_final(big, verts, adj);
                if((ll)auxx.size() > tam_max) {
                    tam_max = auxx.size();
                    resp.resize(auxx.size());
                    auxx.copy(&resp[0], auxx.size());
                }
                printa_biggest_way(big, verts, adj);
            }
        }

        cout << "\n---------------/// RESPOSTA FINAL /// ----------------\n\n";
        i = 0;

        for(ll k = resp.size(); k > 0; k--) {
            ll ind = dna.find(resp.substr(i, k));

            if(ind == 0 && k == dna.size()) {
                cout << "100% IGUAL\n";
                break;
            }
            else if(ind != dna.npos) {
                double aux = (double)k / (double)dna.size();
                cout << aux * 100 << "% IGUAL, mas faltou uma parte\n";
                break;
            }
        }

        cout << "\nOriginal  --> " << dna << endl;
        cout << "Resposta  --> " << resp << endl;

        cout << "Tamanho final..................." << resp.size() << endl;
        cout << "Tamanho original................" << dna.size() << endl << endl;

    }
    else {
        cout << "Não foi possível abrir o arquivo, tente novamente!\n";
    }
    return 0;
    
}