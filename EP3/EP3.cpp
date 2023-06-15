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

        for(node no: verts) {
            int k_max = no.info.size();

            cout << "Nó atual " << no.id << ": " << no.info << endl;
            int tam = no.info.size();

            while(k_max <= K) {
                string aux = no.info.substr(tam - k_max, k_max);

                cout << " Sub FInal: " << aux << endl;
                ll p = pri(verts, aux);
                ll u = ult(verts, aux);

                for(int i = p; i <= u; i++) {
                    cout << " " << i << ": " << verts[i].info << endl;
                }



            }
        }

        /*for(string x: v) {
            // Em um loop para cada nó, iremos achar aqueles que irão ter aresta;
            int tam = x.size();
            cout << "Nó atual: " << no.info << endl;
            string aux = no.info.substr(tam - K, K);
            cout << "Sub final: " << aux << endl;
            int p = pri(v, aux);
            int u = ult(v, aux);

            for(int i = p; i <= u; i++) {
                cout << "  " << i << ": " << v[i].info << endl;
            }
        }*/
    }

    
}