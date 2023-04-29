#include "item.h"
#include <cstdlib>
#include <cstring>

Item::Item(char * chave) {
    key = (char *) malloc(sizeof(char) * strlen(chave));
    strcpy(key, chave);
    tam = strlen(chave);
    vog = 2;
}