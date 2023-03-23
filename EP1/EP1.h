#include <iostream>
using namespace std;

class Avioes {
    char id[5];               // ID identificando o avião 12ABC;
    int time_combustivel;     // Tempo de combustível (Pouso);
    int time_decolagem;       // Tempo de decolagem;
    int time_voo;             // Tempo da viagem/voo;
    int type;                 // Tipo do voo (Emergência ou Normal)
    int id_pista;             // id da pista em que está o avião;
    public:
        // Criação do avião;
        void cria_aviao(char *id_code, int comb, int dec, int voo, int tipo);  
        // Passagem do tempo;
        void pass_time();  
};            

class Pista {
    int id;                   // 1, 2 ou 3;
    int status;               // 0 - Livre, 1 - Ocupada;
    int timer;                // Para marcar o tempo de interdição;
    char id_aviao[5];         // Avião que está na pista;
    public:
        void cria_pista(int id_number);
        void pass_time();
        void pouso_ou_decolagem(int tempo, char *id_airplane);
        void info_pista();
};

