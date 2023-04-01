#include <iostream>
#include "pistas.h"
using namespace std;

void Avioes::cria_aviao(Avioes aviao, char id, int time_voo, int time_comb, int type) {
    aviao.id = id;
    aviao.time_voo = time_voo;
    aviao.time_comb = time_comb;
    aviao.type = type;
    aviao.prox = aviao.ant = nullptr;
}

void Pistas::copia_aviao(Pistas pista, Avioes aviao) {
    pista.
}

Pistas Pistas::insere_aviao(Pistas pista, Avioes aviao) {
    if(pista.lista == nullptr) {
        pista.lista = (Avioes *) malloc(sizeof(Avioes));
        pista.lista->copia_aviao(aviao);

        

    }
}