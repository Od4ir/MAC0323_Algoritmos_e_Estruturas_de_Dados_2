class Pista;
class Fila;
class FilaP;
class Avioes;
class Historico;

Fila * insere2(Fila * f, Avioes A);
Fila * insere_em_pos(Fila * fila, int pos, Avioes A, int quantidade);
Fila * remove2(Fila * f, Avioes A);
void calcula_media_mcpe(FilaP * p, int t, int * mcpe);
int conta_posicoes(Fila * fila);
Avioes gera_aviao(int C, int V, int pp, int pe, int t);
Fila * insere_em_pos(Fila * fila, int pos, Avioes A, int quantidade);
FilaP * insere(FilaP * fila, Pista px);

class Pista {
    public:
        int id;
        int quantidade;
        int tempo_interditada;
        Fila * fila;
        Pista(int id_pista, int quant, int time, Fila * f); 
        void pousa_decola_primeiro_aviao(int * mcrp, int * mtep, int * med, int * quant_dec, int * quant_pou, int t);
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
