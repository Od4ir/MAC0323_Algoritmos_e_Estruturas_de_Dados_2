#include "estruturas.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <time.h>

using namespace std;

// FUNÇÕES ITEM //

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

// FUNÇÕES VETOR ORDENADO DINÂMICO //

VO::VO(int n) {
    size = 2;
    fim = -1;
    vetor = (Item *) malloc(sizeof(Item) * (n + 2));
}

void VO::add(Item item) {
    int start = 0, end = fim + 1, meio;
    bool colocado = false;

    while(start < end && !colocado) {
        meio = (start + end)/2;
        int comp = strcmp(item.key, vetor[meio].key);
        n_comp_insercao++;
        if(comp == 0) {
            // palavra do item é igual a palavra so vetor[meio];
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
    if(!colocado) { 
        if(start != fim + 1) { 
            for(int i = fim; i >= start; i--) {
                vetor[i + 1] = vetor[i];
                n_trocas++;
            } 
        }
        fim++;
        vetor[start] = item;
    }
}

int VO::busca(char * chave) {
    int start = 0, end = fim + 1, meio;

    while(start < end) {
        meio = (start + end)/2;
        int comp = strcmp(chave, vetor[meio].key);
        n_comp_busca++;
        if(comp == 0) {
            // palavra chave é igual a palavra so vetor[meio];
            return meio;
            
        }
        else if(comp > 0) { 
            // Palavra chave é maior que a palavra vetor[meio];
            start = meio + 1;
        }
        else {
            // Palavra chave é menor do que a palavra vetor[meio];
            end = meio;
        }

    }
    return -1;
}

void VO::printa() {
    if(fim == -1) {
        cout << "Vetor vazio!\n";
    }
    else { 
        for(int i = 0; i <= fim; i++) {
            cout << i << ": " << vetor[i].key << " | repet: " << vetor[i].repet << " | vog: " << vetor[i].vog << endl;
        }
    }
}


// FUNÇÕES DE ÁRVORE BINÁRIA //

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
        raiz->dir = raiz->esq = nullptr;
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


// FUNÇÕES DE TREAP // 

TREAP::TREAP(int n) {
    treap = nullptr;
    n_comp_busca = 0;
    n_comp_insercao = 0;
    n_rotacoes = 0;
    altura = -1;
    valor_max_prioridade = 2 * n;
}

tree_heap * TREAP::add(Item item, tree_heap * raiz, tree_heap * ant, int n, char lado) {
    if(raiz == nullptr) {
        raiz = (tree_heap *) malloc(sizeof(tree_heap));
        raiz->prioridade = rand()%valor_max_prioridade;
        cout << "Prioridade do novo elemento: " << raiz->prioridade << endl;
        raiz->dir = nullptr;
        raiz->esq = nullptr;
        raiz->pai = ant;
        if(ant == nullptr) {
            cout << "ESTAMOS NA RAIZ\n";
        }
        raiz->val = item;
        altura = max(altura, n);

        if(ant != nullptr) {
            if(raiz->prioridade > ant->prioridade) {
                if(lado == 'd') {
                    cout << "É filho esquerdo, roda a direita!\n";
                    return rotaciona(raiz, 'd');
                }
                else {
                    cout << "É filho direito, roda a esquerda!\n";
                    return rotaciona(raiz, 'e');
                }
                cout << raiz->val.key << endl;
                cout << ant->val.key << endl;
                // Vamos rodar;
                // Mas precisamos analisar qual lado irá rodar;
            }
        }
        return raiz;
    }
    int comp = strcmp(item.key, raiz->val.key);
    if(comp == 0) {
        raiz->val.repet++;
    }
    else if(comp > 0) {
        raiz->dir = add(item, raiz->dir, raiz, n + 1, 'e');
    }
    else {
        raiz->esq = add(item, raiz->esq, raiz, n + 1, 'd');
    }
    return raiz;
}

void TREAP::print_in_order(tree_heap * raiz) {
    if(raiz != nullptr) {
        print_in_order(raiz->esq);
        cout << raiz->val.key << endl;
        print_in_order(raiz->dir);
    }
}

tree_heap * TREAP::rotaciona(tree_heap * raiz, char lado) {
    if(lado == 'd') {
        // Rotação a direita;
        raiz->pai->esq = raiz->dir;
        raiz->dir = raiz->pai;

        if(raiz->pai->pai != nullptr) {
            if(raiz->pai->prioridade > raiz->pai->pai->prioridade)
        }
        return raiz;
    }
    else {
        // Rotação a esquerda;
        raiz->pai->dir = raiz->esq;
        raiz->dir = raiz->pai;
        return raiz;
    }
}