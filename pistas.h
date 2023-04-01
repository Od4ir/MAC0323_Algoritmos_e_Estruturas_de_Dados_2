#include <iostream>
using namespace std;

class Avioes {
    public:
        char id;
        int time_voo;
        int time_comb;
        int type;
        Avioes * prox;
        Avioes * ant;
        void cria_aviao(Avioes aviao, char id, int time_voo, int time_comb, int type);
};

class Pistas {
    private:
        int id_pista;
    public:
        int tempo_de_interdicao;
        Avioes * lista;
        Pistas insere_aviao(Avioes * lista, Avioes aviao);
        void copia_aviao(Pistas pista, Avioes aviao);
};