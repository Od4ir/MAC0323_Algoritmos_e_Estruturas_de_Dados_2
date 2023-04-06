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
        int pos;
        Fila * prox;
        Fila * ant;
        Fila * insere_na_fila(Fila * fila, Avioes aviao, int pos, Fila * ant);
        Fila * insere_na_fila_posicao(Fila * fila, Avioes aviao, int pos);
        Avioes primeiro_fila(Fila * fila);
};

class Pistas {
    public:
        int id_pista;
        int quantidade;
        int time_interditada;
        Fila * fila;
        int status;
        Pistas(int id, int quant, int time, int stat);    // Criação de Pistas;
        Avioes primeiro_pista(Pistas pista);              // Retorna o primeiro avião da pista;
        Fila * remove_o_primeiro(Pistas pista);
};

class Historico {
    public:
        Avioes aviao;
        Historico * dir;
        Historico * esq;
        Historico * insere_na_arvore(Historico * hist, Avioes A, int * v);
};