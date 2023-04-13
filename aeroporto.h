class Pista;
class Fila;
class FilaP;
class Avioes;
class Historico;

int conta_posicoes(Fila * fila);
Fila * insere_em_pos(Fila * fila, int pos, Avioes A, int quantidade);

class Pista {
    public:
        int id;
        int quantidade;
        int tempo_interditada;
        Fila * fila;
        Pista(int id_pista, int quant, int time, Fila * f); 
        void remove_primeiro();
        void pousa_decola_primeiro_aviao(int * mcpp, int * mtep, int * med, int * quant_dec, int * quant_pou, int * q_emerg, int t);
        Avioes remove_na_pos(int pos);
};

class Avioes {
    public:
        char id[5];
        char id_voo[3];
        int time_comb;
        int time_voo;
        int type;
        int inst;
        Avioes(char * id_aviao, char * info_voo, int comb, int voo, int tipo, int t);
        int simula_na_pos(int pos, int t, int time_interditada);
};

class Fila {
    public:
        Avioes aviao;
        Fila * prox;
        Fila * ant;
        //Fila * insere_no_comeco(Fila * inicio, Avioes aviao); 
};

class FilaP {
    public:
        Pista pista;
        FilaP * prox;
};

class Historico {
    public:
        Avioes aviao;
        Historico * dir;
        Historico * esq;
};
