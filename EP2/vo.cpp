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
    free(vetor);
    vetor = novo;
}

void VO::add(Item item, int start, int end) {
    int meio = (start + end) / 2;
    int comp = strcmp(vetor[meio].key, item.key);

    if(comp == 0) {
        vetor[meio].repet++;
    }

}