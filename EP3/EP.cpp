#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
    // Tenho que determinar o índice de ínicio sem que passe do tamanho
    // da string dna e que dê o tamanho que desejo;

    int ind = rand() % (tam_dna - tam);
    return dna.substr(ind, tam);
}

// Função auxiliar para verificar as substrings geradas;
void gera_k_strings(int k, int MIN, int MAX, string& dna) {
    int aux = MAX - MIN + 1;
    for(int i = 0; i < k; i++) {
        int tam = (rand() % (aux)) + MIN;
        string a = gera_substring(tam, dna);
        cout << i << ": " << a << " | tam: " << tam << " | tam_real: " << a.size() << endl;
    }
}

node::node(string chave, int i) {
    key.assign(chave);
    id = i;
}



int main() {
    int n; 
    vertices v;

    cout << " \n-----------/// BEM VINDX AO EP3 - Od4ir ///-----------\n\n";

    cout << "Vamos começar!\n";

    cout << " \n---------/// PARTE 1 - GERAÇÃO DOS DADOS ///----------\n\n";

    cout << "1.1) Começaremos gerando os dados para o teste!\n";
    cout << "Vamos gerar uma grande string para começar. \n\n Digite o tamanho deseja da string: \n >> ";
    cin >> n;
    
    string dna = gera_string(n);

    cout << "\n Deseja imprimir? S/N\n >> ";
    char op; cin >> op;
    if(op == 'S')
        cout << dna << endl;
    
    cout << "\n1.2) Vamos gerar substrings a partir dessa gerada.\n\n Digite o número de substrings que deseja gerar: \n >> ";
    int k; cin >> k;

    cout << "\n Digite o tamanho máximo e mínimo dessas strings: \n";
    int MIN, MAX; cout << " MIN >> "; cin >> MIN;
    cout << " MAX >> "; cin >> MAX;

    cout << "\n1.3) Vamos gerar as substrings, guardá-las em um vetor.\n";

    // Gerando as substrings e guardando elas;

    int tam_aux = MAX - MIN + 1;
    for(int i = 0; i < k; i++) {
        int tam = (rand() % tam_aux) + MIN;
        node no(gera_substring(tam, dna), i + 1);
        //cout << no.key << " guardado!" << endl;
        v.push_back(no);
    }

    cout << "\n Deseja imprimir? S/N\n >> ";
    cin >> op;

    if(op == 'S') { 
        for(int i = 0; i < v.size(); i++) {
            cout << v[i].id << ": " << v[i].key << endl;
        }
    }

    cout << "\nDados gerados, agora vamos organizar e estruturar esses dados!\n\n";

    cout << " \n-------/// PARTE 2 - ESTRUTURAÇÃO DOS DADOS ///-------\n\n";

    cout << "2.1) Vamos criar um grafo de nós nessa parte, em que cada vértice tem\ncomo id uma substring. Para isso, vamos organizar tudo primeiro.\n";
    cout << "Vamos ordenar o vetor de substrings por ordem alfabética. Isso vai faci-\nlitar a criação do grafo. \n\n";

    cout << " Deseja imprimir a versão ordenada? S/N\n >> ";
    cin >> op;

    sort(v.begin(), v.end(), compara_nodes);

    // Corrigindo os ids de cada node:
    for(int i = 0; i < v.size(); i++) {
        v[i].id = i;
    }

    if(op == 'S') {
        for(node x: v) {
            cout << x.id << ": " << x.key << endl;
        }
    }

    return 0;
}




