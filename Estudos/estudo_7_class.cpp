#include <iostream>
using namespace std;

class aviao {
    int id;
    int status;
    int pista;
    public:
        void cria_aviao(int id);
        void info_aviao();
        void muda_status(int novo_status);
};

class Pista {
    int id;
    int tam;
    int passageiro;
    aviao pousado;
    public:
        void cria_pista(int id, int tam, int passageiro, aviao pousado);
        void info_pista();
        void troca_aviao();
        int muda_passageiro(int quant);
};

void Pista::info_pista() {
    cout << "ID da Pista: " << id << endl;
    cout << "Tamanho da Pista: " << tam << endl;
    cout << "Passageiros atuais: " << passageiro << endl;
}

