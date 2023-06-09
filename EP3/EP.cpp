#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "testes.h"
using namespace std;

// Devolve o índice da primeira aparição da sequência aux
// no vetor v;
int pri(const vector<node>& v, const string aux) {

}

// Devolve o índice da última aparição da sequência aux
// no vetor v;
int ult(const vector<node>& v, const string aux) {

}

void add_arco(int u, int ini, int ult) {
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

    }
    else {
        cout << "Não foi possível abrir o arquivo. Tente novamente. \n";
    }

    return 0;
}