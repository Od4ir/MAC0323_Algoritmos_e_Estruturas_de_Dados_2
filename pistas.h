#include <iostream>
using namespace std;

class Avioes {
    public:
        char id[5];
        char id_voo[3];
        int time_comb;
        int time_voo;
        int type;

        // Função que cria um Avião:
        Avioes(char * id_aviao, char * info_voo, int comb, int voo, int tipo);
        // Função que gera um avião aleatório: 
        Avioes gera_aviao(int C, int V, int pp, int pe); 
};

class Fila {
    public:
        Avioes aviao;
        Fila * prox;
        Fila * ant;
        Fila * insere_na_fila(Fila * fila, Avioes aviao);
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