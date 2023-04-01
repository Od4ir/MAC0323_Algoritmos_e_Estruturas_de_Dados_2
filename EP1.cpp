#include <iostream>
#include <cstdlib>
#include "pistas.h"
using namespace std;

// Função para fabricar aviões: 
// Sobre o tipo: ]
//      - 0 e 1 (Pouso normal e pouso especial);
//      - 2 e 3 (Decolagem normal e decolagem especial);

Avioes::Avioes(char * id_aviao, char * info_voo, int comb, int voo, int tipo) {
    for(int i = 0; i < 5; i++) {
        id[i] = id_aviao[i];
    } 
    for(int i = 0; i < 3; i++) {
        id_voo[i] = id_voo[i];
    } 
    type = tipo;
    time_comb = comb;
    time_voo = voo;
}

// int C - Indica a quantidade máxima de Combustível;
// int V - Indica a quantidade máxima de Tempo de Voo;
// int pp - Um valor de 0 a 100 que indica a probabilidade de ser um pouso;
//     pd - É igual a 100 - pd;
// int pe - Um valor de 0 a 100 que indica a probabilidade de ser uma emergência;
Avioes Avioes::gera_aviao(int C, int V, int pp, int pe) {
    char id_aviao[5], id_voo[3];
    int comb, voo, tipo, type;

    for(int i = 0; i < 2; i++) {
        id_aviao[i] = (char)(rand()%26 + 'A');
    }
    for(int i = 2; i < 5; i++) {
        id_aviao[i] = (char)(rand()%10 + 48);
    }

    for(int i = 0; i < 3; i++) {
        id_voo[i] = (char(rand()%26 + 'A'));
    }

    tipo = rand()%100;

    if(tipo <= pp) {        // Significa que é um Pouso;
        comb = rand()%C;
        voo = 0;
    }
    else {                  // Significa que é uma Decolagem;
        voo = rand()%V;
        voo = voo/10;
        comb = 0;
    }

    type = rand()%100;
    if(type <= pe) {        // Vai ser de Emergência;
        type = 1;
    }
    else {                  // Vai ser normal;
        type = 0;
    }

    Avioes aviao_novo(id_aviao, id_voo, comb, voo, type);
    return aviao_novo;
}

Fila * Fila::insere_na_fila(Fila * fila, Avioes aviao) {
    if(fila == nullptr) {
        fila = (Fila *) malloc(sizeof(Fila));
        fila->aviao = aviao;
        fila->ant = nullptr;
        fila->prox = nullptr;
        return fila;
    }
    else  {
        fila->prox = insere_na_fila(fila->prox, aviao);
        return fila;
    }
}

Pistas::Pistas(int id, int quant, int time, int stat) {
    id_pista = id;
    quantidade = quant;
    time_interditada = time;
    fila = nullptr;
    status = stat;
}

int main() { 
    int T, K, quant_avioes;
    int C, V, pp, pe;
    cout << "Tempo de Execução da Simulação: \n >>>  ";
    cin >> T;  
    cout << endl;

    cout << "Número Máximo de Aviões por unidade de tempo: \n >>>  ";
    cin >> K;
    cout << endl;

    cin >> C;
    cin >> V;
    cin >> pp;
    cin >> pe;

    for(int i = 0; i < T; i++) {
        quant_avioes = rand()%K;
        cout << "INSTANTE ATUAL: " << i + 1 << endl << endl;
        printf("%d Aviões entraram em contato!\n", quant_avioes);

        for(int j = 0; j < quant_avioes; j++) {
            Avioes aux = aux.gera_aviao(C, V, pp, pe);
            printf("Avião %d: ", i + j);
            cout << " >> id: " << aux.id << endl;
            cout << " >> id_voo: " << aux.id_voo << endl;
            cout << " >> comb: " << aux.time_comb << endl;
            cout << " >> voo: " << aux.time_voo << endl;
            cout << " >> type: " << aux.type << endl;
        }
        cout << endl;
    }

    /*Pistas p1(1, 0, 0, 0), p2(2, 0, 0, 0), p3(3, 0, 0, 0);
    Fila * fila = nullptr;
    
    for(int i = 0; i < 20; i++) {
        Avioes aux((char)(i + 65), (char)(i + 97), i + 10, 0, 0);

        if(i % 3 == 1) {
            p1.fila = p1.fila->insere_na_fila(p1.fila, aux);
        }
        else if(i % 3 == 2) {
            p2.fila = p2.fila->insere_na_fila(p2.fila, aux);
        }
        else {
            p3.fila = p3.fila->insere_na_fila(p3.fila, aux);
        } 
    }

    Pistas aux = p1;
    
    for(int i = 0; i < 3; i++) { 
        cout << "Na Pista " << i + 1 << ": \n"; 
        for(Fila *f = aux.fila; f != nullptr; f = f->prox) {
            cout << "Avião : " << f->aviao.id << endl;
        }
        if(i == 0) aux = p2;
        if(i == 1) aux = p3;
    } */

    return 0;
}
