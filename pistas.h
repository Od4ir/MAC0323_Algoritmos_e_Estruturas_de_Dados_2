#include <iostream>
using namespace std;

class Avioes;
class Fila;
class Pistas;
class Historico;

class Avioes {
    public:
        char id[5];
        char id_voo[3];
        int time_comb;
        int time_voo;
        int type;
        int inst;

        // Função que cria um Avião:
        Avioes(char * id_aviao, char * info_voo, int comb, int voo, int tipo, int t);
        // Função que gera um avião aleatório: 
        Avioes gera_aviao(int C, int V, int pp, int pe, int t); 
        int testando_com_pos(int pos, int t, int time_interditada);
};

class Fila {
    public:
        Avioes aviao;
        int pos;
        Fila * prox;
        Fila * ant;
        Fila * insere_na_fila(Fila * fila, Avioes aviao, int pos, Fila * ant);
        Fila * insere_na_fila_posicao(Fila * fila, Avioes aviao, int pos, Fila * ant);
        Avioes primeiro_fila(Fila * fila);
        Avioes aviao_na_pos(Fila * fila, int pos);
        int simulacao(Pistas pista, Avioes A, int t);
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
        void aumenta_quantidade(int t);
};

class Historico {
    public:
        Avioes aviao;
        Historico * dir;
        Historico * esq;
        Historico * insere_na_arvore(Historico * hist, Avioes A, int * v);
        void in_order(Historico * hist);
};