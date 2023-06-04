#include <iostream>
#include <string>
using namespace std;

string gera(int k) {
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

void corta_dna(int k, int t_min, int t_max, string &dna) {
    int tam = dna.size();
    int t_aux = t_max - t_min + 1;

    for(int i = 0; i < k; i++) {
        int t_sub = rand() % t_aux + t_min;
        cout << "Tamanho: " << t_sub << endl;
        // t_sub reprensenta o tamanho da substring que irei pegar;
        int ind = rand() % (tam - t_sub);
        cout << "índice inicial: " << ind << endl;
        cout << i << ": " << dna.substr(ind, t_sub - ind) << endl;

    }
}

int main() {
    int k; cin >> k;
    string dna = gera(k);
    cout << dna << endl;
    cin >> k;
    int tmax, tmin; cin >> tmax >> tmin;
    corta_dna(k, tmin, tmax, dna);

}