#include "item.h"
#include "vo.h"
#include <cstdlib>
#include <cstring>
#include <iostream> // Remover dps;

VO::VO(int n) {
    size = 2;
    fim = -1;
    vetor = (Item *) malloc(sizeof(Item) * (n + 1));
}

void VO::resize() {
    Item * novo;
    size = size * 2;
    novo = (Item *) malloc(sizeof(Item) * size);
    for(int i = 0; i < fim; i++) {
        novo[i] = vetor[i];
    }
    free(vetor);
    vetor = novo;
}
/* FUnção strcmp(a, b):
    Devolve  0 - Se a == b;
    Devolve <0 - Se a < b;
    Devolve >0 - Se a > b;
*/

void VO::copy(int i, int j) {
    vetor[i].repet = vetor[j].repet;
    vetor[i].tam = vetor[j].tam;
    vetor[i].vog = vetor[j].vog;
    strcpy(vetor[i].key, vetor[j].key);
}

void VO::add(Item item) {
    cout << "Colocando " << item.key << endl;
    int start = 0, end = fim + 1, meio;
    bool colocado;

    while(start < end) {
        meio = (start + end)/2;
        cout << item.key << " é ";
        int comp = strcmp(item.key, vetor[meio].key);
        if(comp == 0) {
            vetor[meio].repet++;
            colocado = true;
            
        }
        else if(comp > 0) {
            cout << "maior que ";
            // Palavra do item é menor que a palavra do meio;
            start = meio + 1;
        }
        else {
            cout << "menor que ";
            // Palavra do item é maior do que a palavra do meio;
            end = meio;
        }
        cout << vetor[meio].key << endl;

    }

    cout << "---------------\n";

    if(start != fim) { 
        for(int i = fim; i >= start; i--) {
            cout << "Empurrando " << i << ": " << vetor[i].key << endl;
        } 
    }
    fim++;
    vetor[fim] = item;
    cout << "---------------\n";
    cout << "Deveria ter ficado na posição " << start << endl;
    cout << "Item colocado no vetor na posição: " << fim << endl;

}

/*void VO::add(Item item){
    cout << "Colocando " << item.key << endl;
    cout << fim << endl << endl;
    int start = 0, end = fim + 1; 
    int meio;
    bool colocado =  false;

    // Busca Binária para inserir o número na posição correta;
    while(start < end && !colocado) {
        meio = (start + end)/2;
        int comp = strcmp(item.key, vetor[meio].key);
        if(comp == 0) {
            vetor[meio].repet++;
            colocado = true;
            
        }
        else if(comp > 0) {
            // Palavra do item é menor que a palavra do meio;
            end = meio;
        }
        else {
            // Palavra do item é maior do que a palavra do meio;
            start = meio + 1;
        }
    } 

    cout << "Colocando na posição: " << meio << endl;

    if(!colocado) {
        fim++;
        for(int i = fim - 1; i >= meio; i--) { 
            copy(i + 1, i);
        }
        vetor[meio] = item;

        for(int i = 0; i <= fim; i++) {
            cout << i << ": " << vetor[i].key << endl;
        }
        cout << "Na posição " << meio << " está " << vetor[meio].key << endl;
    }
}*/

