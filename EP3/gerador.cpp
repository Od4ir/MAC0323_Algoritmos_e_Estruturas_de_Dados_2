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

int main() {
    int k; cin >> k;
    string dna = gera(k);

    cout << dna << endl;
}