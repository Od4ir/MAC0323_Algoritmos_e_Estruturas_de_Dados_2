// Estudando como escrever funções em C++;
#include <iostream>
using namespace std;

/* O protótipo de uma função é semelhante ao prótipo das funções em C:

tipo nome(lista de parâmetros) {
    Código da Função;
    Return algo; (Ou não, se for uma void);
}

*/
int eh_par(int x) {
    return(x % 2 == 0);
}

int main() {
    int num;
    cin >> num;
    if(eh_par(num)) cout << "Eh par!\n";
    else cout << "Nao eh par!\n";
    return 0;
}
