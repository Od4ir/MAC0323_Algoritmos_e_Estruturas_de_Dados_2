#include <iostream>
using namespace std;

class Avioes {
    public:
        char id_voo;
        int time_comb;
        int time_voo;
        int type;
        char id;

        Avioes(char id_aviao, char info_voo, int comb, int voo, int tipo);
};

class Fila {
    public:
        Avioes aviao;
        int total_time;
        Fila * prox;
        Fila * ant;

        void insere_na_fila(Fila * fila, Avioes aviao);
};

class Pistas {
    public:
        int id_pista;
        int quantidade;
        int time_interditada;
        Fila * fila;
        int status;
        Pistas(int id, int quant, int time, int stat);
};