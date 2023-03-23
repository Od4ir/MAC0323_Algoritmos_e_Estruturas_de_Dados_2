#include "EP1.h"

void Avioes::cria_aviao(char *id_code, int comb, int dec, int voo, int tipo) {
    for(int i = 0; i < 5; i++) {
        id[i] = id_code[i];
    }
    time_combustivel = comb;
    time_decolagem = dec;
    time_voo = voo;
    type = tipo;
    id_pista = -1;   //Por padrão o avião sempre estará no ar;
}

void Avioes::pass_time() {
    time_combustivel--;
}

void Pista::cria_pista(int id_number) { // Criação da pista;
    id = id_number;
    status = 0;
    timer = 0;
}

void Pista::pass_time() { // Passagem de tempo;
    timer = timer - 1;
    if(timer == 0) {
        status = 0;
    }
}

void Pista::pouso_ou_decolagem(int tempo, char *id_airplane) { // Utilização da pista;
    timer = tempo;
    status = 1;
    for(int i = 0; i < 5; i++) {
        id_aviao[i] = id_airplane[i];
    }
}

void Pista::info_pista() { // Imprimir as informações da pista;
    cout << "ID Pista: " << id << endl;
    cout << "Status: ";
    if(status == 0) cout << "Livre\n";
    else {
        cout << "Interditada/Ocupada\n"; 
        cout << "Durante: " << timer << endl;
    }
} 

int main() {
    Pista pistas[3];
    Avioes aviao;
    //aviao.cria_aviao(1);
    pistas[0].cria_pista(1);
    pistas[1].cria_pista(2);
    pistas[2].cria_pista(3);

    pistas[0].info_pista();
    return 0;
}

