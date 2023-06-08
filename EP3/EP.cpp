#include <iostream>
#include <vector>
#include <string>
#include "EP.h"
using namespace std;

bool compara_nodes(node& a, node& b) {
    return a.key < b.key;
}

string gera_string(int k) {  
    string base, dna;

    for(int i = 0; i < k; i++) { 
        int aux = rand() % 4;
        if(aux == 0) base = "A";
        else if(aux == 1) base = "C";
        else if(aux == 2) base = "G";
        else base = "T";
        dna.append(base);
    }
    return dna;
}

string gera_substring(int tam, const string& dna) {
    int tam_dna = dna.size();
    cout << "Size: " << tam_dna << endl;

    // Tenho que determinar o índice de ínicio sem que passe do tamanho
    // da string dna e que dê o tamanho que desejo;

    int ind = rand() % (tam_dna - tam);
    cout << "índice inicial: " << ind << endl;
    cout << "Final: " << tam + ind - 1 << endl;

    return dna.substr(ind, tam);
}

void gera_k_strings(int k, int MIN, int MAX, string& dna) {
    int aux = MAX - MIN + 1;
    for(int i = 0; i < k; i++) {
        int tam = (rand() % (aux)) + MIN;
        string a = gera_substring(tam, dna);
        cout << i << ": " << a << " | tam: " << tam << " | tam_real: " << a.size() << endl;
    }
}


int main() {
    int n; 
    cout << "Digite o tamanho da string: ";
    cin >> n;

    string dna = gera_string(n);
    cout << dna << endl;

    cout << "Digite quantas strings deseja gerar: ";
    int k; cin >> k;
    cout << "Digite o tamanho mínimo e máximo das strings: ";
    int MIN, MAX; cin >> MIN >> MAX;

    gera_k_strings(k, MIN, MAX, dna);
    return 0;
}




