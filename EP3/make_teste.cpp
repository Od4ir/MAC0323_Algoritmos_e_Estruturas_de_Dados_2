#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "grafo.h"
#include "operacoes.h"
using namespace std;


int main() {
    ll n;
    cout << " \n-----------/// GERADOR DE TESTES EP3 - Od4ir ///-----------\n\n";
    cout << "Digite o tamanho da string que deseja gerar: \n >> ";
    cin >> n;

    string dna = gera_string(n);

    cout << "\n Deseja imprimir? S/N\n >> ";
    char op; cin >> op;
    if(op == 'S')
        cout << dna << endl;

    ll MIN, MAX, K;

    cout << "\nDigite alguns parâmetros para produção da substring: \n";
    cout << " Tam. MIN >> ";
    cin >> MIN;
    cout << " Tam. MAX >> ";
    cin >> MAX;


    cout << "\nDigite o número de cópias que deseja gerar a partir da string DNA: \n >> ";

    ll copy; cin >> copy;

    vector<string> v;


    int cp = 0;
    while(cp < copy) { 
        int tam_total = dna.size();
        int tam = (rand() % (MAX - MIN + 1)) + MIN;
        int c = tam_total / tam;

        if(tam_total - tam * c < MIN && c > 1 && tam_total % tam != 0) {
            for(int i = c; i > 0; i--) {
                if(tam_total - tam * c >= MIN) {
                    c = i;
                    break;
                }
            }
        }

        if(c != 0 && (tam_total - tam * c >= MIN || tam_total % tam == 0)) {
            int ind = 0;
            for(int i = c; i > 0; i--) {
                v.push_back(dna.substr(ind, tam));
                ind = ind + tam;
            }
            int aux = tam_total - tam * c;
            if(aux != 0) {
                v.push_back(dna.substr(ind, aux));
            }
            cp++;
        }
    }

    cout << "\n Deseja imprimir? S/N\n >> ";
    cin >> op;

    if(op == 'S') { 
        for(int i = 0; i < v.size(); i++) {
            cout << i + 1 << ": " << v[i] << endl;
        }
    }

    cout << "\nVamos ordenar as substrings geradas para facilitar processos posteriores. \n";

    sort(v.begin(), v.end(), compara_string);

    cout << " Deseja imprimir a versão ordenada? S/N\n >> ";
    cin >> op;

    if(op == 'S') {
        for(string x: v) {
            cout << x << endl;
        }
    }

    cout << "\nDigite o nome do arquivo em que deseja salvar o teste: \n >> ";
    string file_name; cin >> file_name;

    ofstream arquivo(file_name);

    if(arquivo.is_open()) {
        arquivo << dna << endl;
        arquivo << copy << endl;
        arquivo << v.size() << endl;
        for(string x: v) {
            arquivo << x << endl;
        }
        arquivo.close();
        cout << "Arquivo " << file_name << " gerado!\n";
    }
    else {
        cout << "Não foi possível gerar o arquivo!\n";
    }
    return 0;
}

