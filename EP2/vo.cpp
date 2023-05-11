#include "item.h"
#include "vo.h"
#include <cstdlib>
#include <cstring>

VO::VO() {
    size = 2;
    fim = 0;
    vetor = (Item *) malloc(sizeof(Item) * 2);
}

void VO::resize() {
    Item * novo;
    size = size * 2;
    novo = (Item *) malloc(sizeof(Item) * size);
    for(int i = 0; i < fim; i++) {
        novo[i] = vetor[i];
    }
    fim++;
    free(vetor);
    vetor = novo;
}
/* FUnção strcmp(a, b):
    Devolve  0 - Se a == b;
    Devolve -1 - Se a < b;
    Devolve 1 - Se a > b;
*/

void VO::add(Item item){
    int start = 0, end = fim;
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
        else if(comp < 0) {
            // Palavra atual é menor que a palavra do meio;
            end = meio;
        }
        else {
            start = meio + 1;
        }
    }

    if(!colocado) {
        if(fim + 1 == size) resize();

        for(int i = meio; i < fim; i++) { 
            vetor[i + 1] = vetor[i];
        }
        vetor[meio] = item;
    }
}