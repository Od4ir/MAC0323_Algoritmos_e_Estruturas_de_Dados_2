#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "testes.h"
using namespace std;


int main() {
    cout << " \n-----------/// BEM VINDX AO EP3 - Od4ir ///-----------\n\n";

    cout << " \n---------/// PARTE 1 - OBTENÇÃO DOS DADOS ///----------\n\n";

    cout << " Vamos pegar um arquivo de teste para realizar as operações.\n Digite o nome do arquivo: \n >> ";
    string file_name;
    cin >> file_name;

    ifstream arquivo(file_name);
    vertices v;

    if(arquivo.is_open()) {
        string dna, aux;
        getline(arquivo, dna);
        cout << dna << endl;
        int copy, k;
        getline(arquivo, aux);
        copy = stoi(aux);
        cout << copy << endl;
        getline(arquivo, aux);
        k = stoi(aux);
        cout << k << endl;

        string linha;
        int i = 0;
        while(getline(arquivo, linha)) {
            // Em linha está a substring;
            node no(linha, i++);
            v.push_back(no);
        }
    }

    for(node n: v) {
        cout << n.id << ": " << n.key << endl;
    }

    return 0;
}