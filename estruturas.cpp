#include "estruturas.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

// FUNÇÕES ITEM //

long long int vogais[5];

long long int verifica_vogal(char atu) {
    if(atu == 'a' || atu == 'A') {
        vogais[0] = vogais[0] + 1;
        return vogais[0];
    }
    else if(atu == 'e' || atu == 'E') { 
        vogais[1] = vogais[1] + 1;
        return vogais[1];
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
        vogais[4] = vogais[4] + 1;
        return vogais[4];
    }
    return 1;
}

Item::Item(Key key) {
    if(strcmp(key, "000") == 0) { 
        repet = -1;
        tam = 0;
        vog = 0;
    }
    else { 
        for(long long int i = 0; i < 5; i++) vogais[i] = 0;

        repet = 1;
        tam = strlen(key);
        
        long long int i;
        for(i = 0; i < tam; i++) {
            if(verifica_vogal(key[i]) > 1) {
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
}


// FUNÇÕES VETOR ORDENADO // 

VO::VO(long long int n) {
    fim = -1;
    vetor = (vo *) malloc(sizeof(vo) * (n + 2));
    n_comp_insercao = 0;
    n_trocas = 0;
    n_comp_busca = 0;
}

void VO::add(Key key, Item val) {
    long long int start = 0, end = fim + 1, meio;
    bool colocado = false;

    while(start < end && !colocado) {
        meio = (start + end)/2;
        long long int comp = strcmp(key, vetor[meio].key);
        n_comp_insercao++;
        if(comp == 0) {
            // palavra do item é igual a palavra so vetor[meio];

            vetor[meio].val.repet++;
            //mais_repetida(vetor[meio].);
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
            for(long long int i = fim; i >= start; i--) {
                vetor[i + 1] = vetor[i];
                n_trocas++;
            } 
        }
        fim++;
        vetor[start].key = (Key) malloc(sizeof(char) * strlen(key));
        strcpy(vetor[start].key, key);
        vetor[start].val = val;
        //mais_repetida(item);
        //insere_nos_vetores(item);
    }
}

long long int VO::busca(Key key) {
    long long int start = 0, end = fim + 1, meio;

    while(start < end) {
        meio = (start + end)/2;
        long long int comp = strcmp(key, vetor[meio].key);
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

Item VO::value(Key key) {
    long long int aux = busca(key);
    if(aux >= 0) {
        return vetor[aux].val;
    }
    char a[] = "000";
    Item item(a);
    return item;
}

void VO::printa() {
    if(fim == -1) {
        cout << "Vetor vazio!\n";
    }
    else { 
        for(long long int i = 0; i <= fim; i++) {
            cout << i + 1 << ": " << vetor[i].key << endl;
        }
    }
}

// FUNÇÕES ÁRVORE DE BUSCA BINÁRIA //

ABB::ABB() {
    arvore = nullptr;
    n_comp_busca = 0;
    n_comp_insercao = 0;
    altura = -1;
}

void ABB::add(Key key, Item val) {
    arvore = put(key, val, arvore, 0);
}

abb * ABB::put(Key key, Item val, abb * raiz, long long int n) {
    if(raiz == nullptr) {
        raiz = (abb *) malloc(sizeof(abb));
        raiz->val = val;
        raiz->key = (Key) malloc(sizeof(char) * strlen(key));
        strcpy(raiz->key, key);
        altura = max(altura, n);
        raiz->dir = raiz->esq = nullptr;
        //insere_nos_vetores(item);
        //mais_repetida(item);
        return raiz;
    }
    long long int comp = strcmp(key, raiz->key);
    n_comp_insercao++;
    if(comp == 0) {
        raiz->val.repet++;
        //mais_repetida(raiz->val);
    }
    else if(comp > 0) { // A palavra do item é maior que a palavra da raiz.val;
        raiz->dir = put(key, val, raiz->dir, n + 1);
    }
    else {
        raiz->esq = put(key, val, raiz->esq, n + 1);
    }
    return raiz;
}

void ABB::print_in_order(abb * raiz) {
    if(raiz != nullptr) {
        print_in_order(raiz->esq);
        cout << raiz->key << endl;
        print_in_order(raiz->dir);
    }
}

void ABB::print_pre_order(abb * raiz) {
    if(raiz != nullptr) {
        cout << raiz->key << endl;
        print_pre_order(raiz->esq);
        print_pre_order(raiz->dir);
    }
}

Item ABB::value(Key key) {
    abb * aux = busca_aux(key, arvore);
    if(aux == nullptr) {
        char a[] = "000";
        Item item(a);
        return item;
    }
    return aux->val;
}

abb * ABB::busca_aux(Key key, abb * raiz) {
    if(raiz == nullptr) {
        return nullptr;
    }
    long long int comp = strcmp(key, raiz->key);
    n_comp_busca++;
    if(comp == 0) {
        return raiz;
    }
    else if(comp > 0) {
        return busca_aux(key, raiz->dir);
    }
    return busca_aux(key, raiz->dir);
}


// FUNÇÕES TREAPS //

TREAP::TREAP(long long int n) {
    treap = nullptr;
    n_comp_busca = 0;
    n_comp_insercao = 0;
    n_rotacoes = 0;
    altura = -1;
    valor_max_prioridade = 2 * n;
}

void TREAP::add(Key key, Item val) {
    treap = put(key, val, treap);
}

tree_heap * TREAP::put(Key key, Item val, tree_heap * raiz) {
    if(raiz == nullptr) {
        raiz = (tree_heap *) malloc(sizeof(tree_heap));
        raiz->esq = raiz->dir = nullptr;
        raiz->prioridade = rand() % valor_max_prioridade;
        raiz->key = (Key) malloc(sizeof(char) * strlen(key));
        strcpy(raiz->key, key);
        raiz->val = val;
        //insere_nos_vetores(item);
        //mais_repetida(item);
        return raiz;
    }
    long long int comp = strcmp(key, raiz->key);
    n_comp_insercao++;
    if(comp == 0) {
        raiz->val.repet++;
        //mais_repetida(raiz->val);
    }
    else if(comp > 0){
        raiz->dir = put(key, val, raiz->dir);
    }
    else {
        raiz->esq = put(key, val, raiz->esq);
    }

    if(raiz->dir !=  nullptr && raiz->dir->prioridade > raiz->prioridade) {
        raiz = rotaciona(raiz, 'e');
        n_rotacoes++;
    }
    if(raiz->esq != nullptr && raiz->esq->prioridade > raiz->prioridade) {
        raiz = rotaciona(raiz, 'd');
        n_rotacoes++;
    }
    return raiz;
}

Item TREAP::value(Key key) {
    tree_heap * aux = busca(key, treap);
    if(aux == nullptr) {
        char a[] = "000";
        Item item(a);
        return item;
    }
    return aux->val;
}

tree_heap * TREAP::busca(Key key, tree_heap * raiz) {
    if(raiz == nullptr) {
        return nullptr;
    }
    long long int comp = strcmp(key, raiz->key);
    n_comp_busca++;
    if(comp == 0) {
        return raiz;
    }
    else if(comp > 0) {
        return busca(key, raiz->dir);
    }
    return busca(key, raiz->dir);
}

tree_heap * TREAP::rotaciona(tree_heap * p, char lado) {
    if(lado == 'e') {
        tree_heap * x = p->dir;
        p->dir = x->esq;
        x->esq = p;
        return x;
    }
    tree_heap * x = p->esq;
    p->esq = x->dir;
    x->dir = p;
    return x;
}

void TREAP::print_in_order(tree_heap * raiz) {
    if(raiz != nullptr) {
        print_in_order(raiz->esq);
        cout << raiz->key << endl;
        print_in_order(raiz->dir);
    }
}

void TREAP::print_pre_order(tree_heap * raiz) {
    if(raiz != nullptr) {
        cout << raiz->key << endl;
        print_pre_order(raiz->esq);
        print_pre_order(raiz->dir);
    }
}

// FUNÇÕES ÁRVORES RUBRO NEGRAS //

ARN::ARN() {
    arvore = nullptr;
    n_comp_busca = 0;
    n_comp_insercao = 0;
    n_rotacoes = 0;
    altura = 0;
}

void ARN::add(Key key, Item val) {
    arvore = put(key, val, arvore);
    arvore->cor = 'B';
}

arn * ARN::rotaciona(arn * p, char lado) {
    if(lado == 'e') {
        arn * x = p->dir;
        p->dir = x->esq;
        x->esq = p;
        x->cor = p->cor;
        p->cor = 'R';
        return x;
    }
    arn * x = p->esq;
    p->esq = x->dir;
    x->dir = p;
    x->cor = p->cor;
    p->cor = 'R';
    return x;
}

bool ARN::eh_vermelho(arn * no) {
    if(no == nullptr) {
        return false;
    }
    else return (no->cor == 'R');
}

arn * ARN::put(Key key, Item val, arn * raiz) {
    if(raiz == nullptr) {
        raiz = (arn *) malloc(sizeof(arn));
        raiz->cor = 'R';
        raiz->esq = raiz->dir = nullptr;
        raiz->val = val;
        raiz->key = (Key) malloc(sizeof(char) * strlen(key));
        strcpy(raiz->key, key);

        //insere_nos_vetores(item);
        //mais_repetida(item);
        return raiz;
    }
    long long int comp = strcmp(key, raiz->key);
    n_comp_insercao++;
    if(comp == 0) {
        raiz->val.repet++;
        //mais_repetida(raiz->val);
    }
    else if(comp > 0){
        raiz->dir = put(key, val, raiz->dir);
    }
    else {
        raiz->esq = put(key, val, raiz->esq);
    }

    if(eh_vermelho(raiz->dir) && !eh_vermelho(raiz->esq)) {
        raiz = rotaciona(raiz, 'e');
        n_rotacoes++;
    }
    if(eh_vermelho(raiz->esq) && eh_vermelho(raiz->esq->esq)) {
        raiz = rotaciona(raiz, 'd');
        n_rotacoes++;
    }
    if(eh_vermelho(raiz->esq) && eh_vermelho(raiz->dir)) {
        raiz->cor = 'R';
        raiz->esq->cor = 'B';
        raiz->dir->cor = 'B';
    }
    return raiz;
}

Item ARN::value(Key key) {
    arn * aux = busca(key, arvore);
    if(aux == nullptr) {
        char a[] = "000";
        Item item(a);
        return item;
    }
    return aux->val;
}

arn * ARN::busca(Key key, arn * raiz) {
    if(raiz == nullptr) {
        return nullptr;
    }
    long long int comp = strcmp(key, raiz->key);
    n_comp_busca++;
    if(comp == 0) {
        return raiz;
    }
    else if(comp > 0) {
        return busca(key, raiz->dir);
    }
    return busca(key, raiz->dir);
}

void ARN::print_pre_order(arn * raiz) {
    if(raiz != nullptr) {
        cout << raiz->key << endl;
        print_pre_order(raiz->esq);
        print_pre_order(raiz->dir);
    }
}

void ARN::print_in_order(arn * raiz) {
    if(raiz != nullptr) {
        print_pre_order(raiz->esq);
        cout << raiz->key << endl;
        print_pre_order(raiz->dir);
    }
}