// Teste de uso de class:

#include <iostream>
using namespace std;

class Pessoa {
    public:
        int idade;
        char nome[20];
        int aniversariar(Pessoa x);
        void mudar_nome(Pessoa x);
};

int Pessoa::aniversariar(Pessoa x) {
    cout << "Feliz aniversario! Voce tem agora ";
    x.idade = x.idade + 1;
    cout << x.idade << " anos! \n";
    return x.idade;
};

void Pessoa::mudar_nome(Pessoa x) {
    cout << "Digite um novo nome: \n";
    cin >> x.nome;
};

int main() {
    Pessoa odair;
    cout << "Qual seu nome?\n";
    cin >> odair.nome;
    cout << "Qual sua idade?\n";
    cin >> odair.idade;
    odair.aniversariar(odair);
    cout << odair.idade;
    odair.mudar_nome(odair);
    cout << odair.nome;

    return 0;

}

