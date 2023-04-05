#include <iostream>
#include <cstdlib>
#include "pistas.h"
using namespace std;

// Função para fabricar aviões: 
// Sobre o tipo: ]
//      - 0 e 1 (Normal e Especial)
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

    Pistas p1(1, 0, 0, 0), p2(2, 0, 0, 0), p3(3, 0, 0, 0);
    Fila * fila = nullptr;


    for(int i = 0; i < T; i++) {
        quant_avioes = rand()%K;
        cout << "INSTANTE ATUAL: " << i + 1 << endl << endl;
        printf("%d Aviões entraram em contato!\n", quant_avioes);

        for(int j = 0; j < quant_avioes; j++) {
            Avioes aux = aux.gera_aviao(C, V, pp, pe);
             if(i % 3 == 1) {
                p1.fila = p1.fila->insere_na_fila(p1.fila, aux);
                p1.quantidade++;
                p1.time_interditada+= 3;
            }
            else if(i % 3 == 2) {
                p2.fila = p2.fila->insere_na_fila(p2.fila, aux);
                p2.quantidade++;
                p2.time_interditada+= 3;
            }
            else {
                p3.fila = p3.fila->insere_na_fila(p3.fila, aux);
                p3.quantidade++;
                p3.time_interditada+= 3;
            } 

        }
        cout << endl;
    }


    Pistas aux = p1;
    
    for(int i = 0; i < 3; i++) { 
        cout << "Na Pista " << i + 1 << ": \n"; 
        cout << "Há " << aux.quantidade << " aviões!\n";
        cout << "Interdição: " << aux.time_interditada << "!\n";
        for(Fila *f = aux.fila; f != nullptr; f = f->prox) {
            cout << "Avião : " << f->aviao.id << endl;
        }
        if(i == 0) aux = p2;
        if(i == 1) aux = p3;
    } 

    return 0;
}
