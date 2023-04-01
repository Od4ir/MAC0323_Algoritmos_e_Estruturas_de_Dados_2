#include <iostream>
using namespace std;

/* typedef struct Avioes {
    int time_combustivel;     // Tempo de combustível (Pouso);
    int time_decolagem;       // Tempo de decolagem;
    int time_voo;             // Tempo da viagem/voo;
    int type;                 // Tipo do voo (Emergência ou Normal) - 0 (normal) 1(emergência)
    int id_pista;             // id da pista em que está o avião - n (número da pista) ou -1 (no ar)
    char id_aviao[5];
    struct Avioes * ant;
    struct Avioes * prox;
} lista_avioes; */

class Avioes {
    int time_combustivel;     // Tempo de combustível (Pouso);
    int time_voo;             // Tempo da viagem/voo (10% do valor de entrada);
    int type;                 // Tipo do voo (Emergência ou Normal) - 0 (normal) 1(emergência)
    // int id_pista;             // id da pista em que está o avião - n (número da pista) ou -1 (no ar)
    public:
        char id[5];               // ID identificando o avião 12ABC;
        Avioes * ant;
        Avioes * prox;
        // Criação do avião;
        Avioes * insere_aviao(Avioes *lista, char *id_code, int comb, int voo, int tipo);  
        // Retorna o avião que está em 1º na fila;
        Avioes * minimo(Avioes *lista);
        // Remove um avião, dado seu id;
        Avioes * remove(Avioes *lista, char *id);
        
        // Passagem do tempo;
        void pass_time();  
        // Avioes remove_aviao(char *id_aviao);

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


