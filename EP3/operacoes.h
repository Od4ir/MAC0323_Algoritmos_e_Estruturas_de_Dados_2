#include <iostream>
#include <vector>
#include <string>
#include "grafo.h"
using namespace std;

// Devolve o índice da primeira aparição da sequência aux
// no vetor v;
ll pri(const vector<node>& v, const string aux) {
    ll start = 0, end = v.size(), meio;
    ll resp = end;

    while(start < end) {
        meio = (start + end)/2;
        //cout << meio << ": " << v[meio].info << endl;

        ll ind = v[meio].info.find(aux);
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
ll ult(const vector<node>& v, const string aux) {
    ll start = 0, end = v.size(), meio;
    ll resp = 0;

    while(start < end) {
        meio = (start + end)/2;
        //cout << meio << ": " << v[meio].info << endl;


        ll ind = v[meio].info.find(aux);
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
// Compara dois nodes a partir de suas chaves (strings);
// Gera uma string com as letras A, C, G e T de tamanho k;
string gera_string(int k);
// Gera uma substring de tamanho tam a partir da string dna;
string gera_substring(int tam, const string& dna);
// Função que guarda os nodes em um vetor;


bool compara_string(string& a, string& b) {
    return a < b;
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