#include <iostream>
#include "pistas.h"
using namespace std;

// Função para fabricar aviões: 
// Sobre o tipo: ]
//      - 0 e 1 (Pouso normal e pouso especial);
//      - 2 e 3 (Decolagem normal e decolagem especial);

Avioes::Avioes(char id_aviao, char info_voo, int comb, int voo, int tipo) {
    /* for(int i = 0; i < 5; i++) {
        id[i] = id_aviao[i];
    } 
    for(int i = 0; i < 3; i++) {
        id_voo[i] = id_voo[i];
    } */
    id = id_aviao;
    id_voo = info_voo;
    type = tipo;
    if(tipo < 2) {
        time_comb = comb;
        time_voo = 0;
    }
    else {
        time_comb = 0;
        time_voo = voo/10;
    }
}

void Fila::insere_na_fila(Fila * fila, Avioes aviao) {
    if(fila == nullptr) {
        fila = (Fila *) malloc(sizeof(Fila));
        fila->aviao = aviao;
        fila->ant = nullptr;
        fila->prox = nullptr;
    }
    else  {
        insere_na_fila(fila->prox, aviao);
    }
}

Pistas::Pistas(int id, int quant, int time, int stat) {
    id_pista = id;
    quantidade = quant;
    time_interditada = time;
    fila = (Fila *) malloc(sizeof(Fila));
    status = stat;
}

int main() { 
    Pistas p1(1, 0, 0, 0), p2(2, 0, 0, 0), p3(3, 0, 0, 0);
    
    for(int i = 0; i < 10; i++) {
        Avioes aux((char)(i + 65), (char)(i + 97), i + 10, 0, 0);
        if(i % 3 == 1) {
            p1.fila->insere_na_fila(p1.fila, aux);
        }
        else if(i % 3 == 2) {
            p2.fila->insere_na_fila(p2.fila, aux);
        }
        else {
            p3.fila->insere_na_fila(p3.fila, aux);
        }
    }

    Pistas aux = p1;
    for(int i = 0; i < 3; i++) {
        cout << "Aviões na Pista " << i + 1 << ":\n";
        for(Fila *f = aux.fila; f != nullptr; f = f->prox) {
            cout << "Avião: " << f->aviao.id << endl;
            cout << "Combustível: " << f->aviao.time_comb << endl;
            cout << "Tipo " << f->aviao.type << endl;
        }
        cout << endl;
        if(i == 0) aux = p2;
        if(i == 1) aux = p3;
    }


    return 0;
}
