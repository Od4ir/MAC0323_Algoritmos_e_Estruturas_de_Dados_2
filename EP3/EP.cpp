#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "testes.h"
#include "grafo.h"
using namespace std;


// Devolve o índice da primeira aparição da sequência aux
// no vetor v;
int pri(const vector<node>& v, const string aux) {
    int start = 0, end = v.size() + 1, meio;
    int resp = end;

    while(start < end) {
        meio = (start + end)/2;
        //cout << meio << ": " << v[meio].key << endl;

        int ind = v[meio].key.find(aux);
        //cout << " índice: " << ind << endl;
        
        if(ind == 0) {
            resp = min(meio, resp);
            //cout << "ind\n";
            end = meio;
        }
        else if(aux == v[meio].key) {
            //cout << "==\n";
            end = meio;
            // Não sei o que fazer se forem iguais...
        } 
        else if(aux > v[meio].key) {
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
        //cout << meio << ": " << v[meio].key << endl;


        int ind = v[meio].key.find(aux);
        //cout << " >> índice: " << ind << endl;
        
        if(ind == 0) {
            resp = max(meio, resp);
            //cout << "ind\n";
            start = meio + 1;
        }
        else if(aux == v[meio].key) {
            start = meio + 1;
            //cout << "==\n";
            // Não sei o que fazer se forem iguais...
        } 
        else if(aux > v[meio].key) {
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


void add_arco(int u, int v, int peso) {
    // Vou precisar de um vetor de adjacências;
}



int main() {
    cout << " \n-----------/// BEM VINDX AO EP3 - Od4ir ///-----------\n\n";

    cout << " \n---------/// PARTE 1 - OBTENÇÃO DOS DADOS ///----------\n\n";

    cout << " Vamos pegar um arquivo de teste para realizar as operações.\n \n Digite o nome do arquivo: \n >> ";
    string file_name;
    cin >> file_name;

    ifstream arquivo(file_name);
    vertices v;

    if(arquivo.is_open()) {
        string dna, aux;
        getline(arquivo, dna);
        int copy, k;
        getline(arquivo, aux);
        copy = stoi(aux);
        getline(arquivo, aux);
        k = stoi(aux);

        string linha;
        int i = 0;
        while(getline(arquivo, linha)) {
            // Em linha está a substring;
            node no(linha, i++);
            v.push_back(no);
        }

        cout << "\n Deseja imprimir os dados? S/N: \n >> ";
        char op; cin >> op;

        if(op == 'S') {
            cout << "\n DNA Original: " << dna << endl;
            cout << " Número de cópias.............." << copy << endl;
            cout << " Número de substrings.........." << k << endl;
            cout << " Substrings: " << endl;
            for(node n: v)
                cout << "  " << n.id << ": " << n.key << endl;
        }

        cout << "\n\n---------/// PARTE 2 - MONTAGEM DOS ARCOS ///----------\n\n";

        cout << "Escolha o parâmetro k: (Valor mínimo " << k << ") \n >> ";
        int K; cin >> K;
        for(node no: v) {
            // Em um loop para cada nó, iremos achar aqueles que irão ter aresta;
            int tam = no.key.size();
            cout << "Nó atual: " << no.key << endl;
            string aux = no.key.substr(tam - K, K);
            cout << "Sub final: " << aux << endl;
            int p = pri(v, aux);
            int u = ult(v, aux);

            for(int i = p; i <= u; i++) {
                cout << "  " << i << ": " << v[i].key << endl;
            }
        }
    }
    else {
        cout << "Não foi possível abrir o arquivo. Tente novamente. \n";
    }

    return 0;
}