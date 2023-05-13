#include "item.h"
#include "vo.h"
#include <cstdlib>
#include <cstring>
#include <iostream> // Remover dps;

VO::VO(int n) {
    size = 2;
    fim = -1;
    vetor = (Item *) malloc(sizeof(Item) * (n + 2));
}

void VO::add(Item item) {
    int start = 0, end = fim + 1, meio;
    bool colocado;

    while(start < end) {
        meio = (start + end)/2;
        int comp = strcmp(item.key, vetor[meio].key);
        if(comp == 0) {
            vetor[meio].repet++;
            colocado = true;
            
        }
        else if(comp > 0) { 
            // Palavra do item é maior que a palavra vetor[meio];
            start = meio + 1;
        }
        else {
            // Palavra do item é menor do que a palavra vetor[meio];
            end = meio;
        }

    }

    if(start != fim + 1) { 
        for(int i = fim; i >= start; i--) {
            vetor[i + 1] = vetor[i];
        } 
    }
    fim++;
    vetor[start] = item;
}




