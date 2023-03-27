#include "EP1.h"
#include <cstdlib> 

Avioes * Avioes::insere_aviao(Avioes *lista, char *id_code, int comb, int dec, int voo, int tipo) {
    if(lista == nullptr) {
        lista = (Avioes *) malloc(sizeof(Avioes));
        lista->time_combustivel = comb;
        lista->time_decolagem = dec;
        lista->time_voo = voo;
        lista->type = tipo;
        lista->id_pista = -1;
        for(int i = 0; i < 5; i++) {
            lista->id[i] = id_code[i];
        }
        lista->ant == nullptr;
        lista->prox == nullptr;
        return lista;
    }
    else if(comb > lista->time_combustivel) {
        lista->prox = lista->insere_aviao(lista->prox, id_code, comb, dec, voo, tipo);
    }
    else {
        lista->ant = lista->insere_aviao(lista->prox, id_code, comb, dec, voo, tipo);
    }
    return lista;
}

Avioes * Avioes::minimo(Avioes *lista) {
    if(lista == nullptr || lista->ant == nullptr) {
        return lista;
    }
    else {
        return minimo(lista->ant);
    }
}

void Avioes::pass_time() {
    time_combustivel--;
    if(time_combustivel == 0) 
        type = 1;  // Torna-se um voo de emergência;
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
    Avioes *lista;
    lista = nullptr;
    char id[5];
    int comb, dec, voo, tipo; // Teste
    //pistas[0].cria_pista(1);
    //pistas[1].cria_pista(2);
    //pistas[2].cria_pista(3);
    //pistas[0].info_pista();

    for(int i = 0; i < 4; i++) {
        printf("Aviao %d!\n", i + 1);
        cin >> id;
        cin >> comb;
        cin >> dec;
        cin >> voo;
        cin >> tipo;
        lista = lista->insere_aviao(lista, id, comb, dec, voo, tipo);
    }
    lista = lista->minimo(lista);
    printf("%s\n", lista->id);

    return 0;
}

