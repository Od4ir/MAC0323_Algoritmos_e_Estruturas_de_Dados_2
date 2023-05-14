#include "item.h" 
#include "abb.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

ABB::ABB() {
    arvore = nullptr;
    n_comp_busca = 0;
    n_comp_insercao = 0;
    altura = -1;
}

abb * ABB::add(Item item, abb * raiz, int n) {
    if(raiz == nullptr) {
        raiz = (abb *) malloc(sizeof(abb));
        raiz->val = item;
        altura = max(altura, n);
        return raiz;
    }
    int comp = strcmp(item.key, raiz->val.key);
    n_comp_insercao++;
    if(comp == 0) {
        raiz->val.repet++;
    }
    else if(comp > 0) { // A palavra do item é maior que a palavra da raiz.val;
        raiz->dir = add(item, raiz->dir, n + 1);
    }
    else {
        raiz->esq = add(item, raiz->esq, n + 1);
    }
    return raiz;
}

void ABB::print_in_order(abb * raiz) {
    if(raiz != nullptr) {
        print_in_order(raiz->esq);
        cout << raiz->val.key <<  " | " << raiz->val.repet << endl;
        print_in_order(raiz->dir);
    }
}

abb * ABB::busca(char * key, abb * raiz) {
    if(raiz == nullptr) {
        return nullptr;
    }
    int comp = strcmp(key, raiz->val.key);
    n_comp_busca++;
    if(comp == 0) {
        return raiz;
    }
    else if(comp > 0) {
        return busca(key, raiz->dir);
    }
    return busca(key, raiz->dir);
}

