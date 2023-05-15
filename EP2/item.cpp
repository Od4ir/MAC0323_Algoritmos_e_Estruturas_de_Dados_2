#include "item.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

int vogais[5];

int verifica_vogal(char atu) {
    if(atu == 'a' || atu == 'A') {
        vogais[0] = vogais[0] + 1;
        return vogais[0];
    }
    else if(atu == 'e' || atu == 'E') { 
        return ++vogais[1];
    }
    else if(atu == 'i' || atu == 'I') {
        vogais[2] = vogais[2] + 1;
        return vogais[2];
    }
    else if(atu == 'o' || atu == 'O') {
        vogais[3] = vogais[3] + 1;
        return vogais[3];
    }
    else if(atu == 'u' || atu == 'U') {
        return ++vogais[4];
    }
    return 1;
}

Item::Item(char * chave) {
    for(int i = 0; i < 5; i++) vogais[i] = 0;

    key = (char *) malloc(sizeof(char) * strlen(chave));
    strcpy(key, chave);
    repet = 1;
    tam = strlen(chave);
    
    int i;
    for(i = 0; i < tam; i++) {
        if(verifica_vogal(chave[i]) > 1) {
            i = tam + 1;
        }
    }
    vog = 0;
    if(i == tam) { 
        for(i = 0; i < 5; i++) {
            vog = vog + vogais[i];
        }
    }
}