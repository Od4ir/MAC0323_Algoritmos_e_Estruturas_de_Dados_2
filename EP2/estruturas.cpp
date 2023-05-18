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

void ABB::add(Item item) {
    arvore = put(item, arvore, 0);
}

abb * ABB::put(Item item, abb * raiz, int n) {
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
        raiz->dir = put(item, raiz->dir, n + 1);
    }
    else {
        raiz->esq = put(item, raiz->esq, n + 1);
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

void TREAP::add(Item item) {
    treap = put(item, treap, treap, 0);
}

tree_heap * TREAP::put(Item item, tree_heap * raiz, tree_heap * ant, int n) {
    if(raiz == nullptr) {
        raiz = (tree_heap *) malloc(sizeof(tree_heap));
        raiz->prioridade = rand()%valor_max_prioridade;
        cout << "Prioridade do novo elemento: " << raiz->prioridade << endl;
        raiz->dir = nullptr;
        raiz->esq = nullptr;
        raiz->pai = ant;
        raiz->val = item;
        altura = max(altura, n);
        return raiz;
    }
    int comp = strcmp(item.key, raiz->val.key);
    if(comp == 0) {
        raiz->val.repet++;
    }
    else if(comp > 0) {
        raiz->dir = put(item, raiz->dir, raiz, n + 1);
        if(raiz->dir->prioridade > raiz->prioridade) {
            // Rotaciona;
            cout << "Vamos rodar a esquerda!\n";
            raiz = rotaciona(raiz->dir, 'e');
        }
    }
    else {
        raiz->esq = put(item, raiz->esq, raiz, n + 1);
        if(raiz->esq->prioridade > raiz->prioridade) {
            // Rotaciona;
            cout << "Vamos rodar a direita!\n";
            raiz = rotaciona(raiz->esq, 'd');
        }
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

void TREAP::print_pre_order(tree_heap * raiz) {
    if(raiz != nullptr) {
        cout << raiz->val.key << endl;
        print_pre_order(raiz->esq);
        print_pre_order(raiz->dir);
    }
}

tree_heap * TREAP::rotaciona(tree_heap * p, char lado) {
    cout << p->val.key << " rodando\n";
    if(lado == 'd') {
        cout << "Girando para direita\n";
        tree_heap * aux = p->pai;
        cout << "Pai do p: " << aux->val.key << endl;
        p->pai->esq = p->dir;
        p->dir = p->pai;
        p->pai = p->pai->pai;
        aux->pai = p;
        return p;
    }
    cout << "Girando para esquerda!\n";
    tree_heap * aux = p->pai;
    cout << "Pai do p: " << aux->val.key << endl;
    p->pai->dir = p->esq;
    p->esq = p->pai;
    p->pai = p->pai->pai;
    aux->pai = p;
    return p;
}


// FUNÇÕES DE RUBRO NEGRAS //

ARN::ARN() {
    arvore = nullptr;
    n_comp_busca = 0;
    n_comp_insercao = 0;
    altura = 0;
}

void ARN::add(Item item) {
    arvore = put(item, arvore, arvore);
}

arn * ARN::put(Item item, arn * raiz, arn * ant) {
    if(raiz == nullptr) {
        raiz = (arn *) malloc(sizeof(arn));
        raiz->val = item;
        raiz->cor = 'V';
        raiz->dir = raiz->esq = nullptr;
        raiz->pai = ant;
        return raiz;
    }
    int comp = strcmp(item.key, raiz->val.key);
    n_comp_insercao++;
    if(comp == 0) {
        raiz->val.repet++;
    }
    else if(comp > 0) { // A palavra do item é maior que a palavra da raiz.val;
        raiz->dir = put(item, raiz->dir, raiz);
        if(raiz->cor ==  'V' && raiz->dir->cor == 'V') {
            cout << "Pai vermelho e filho vermelho!\n";
            // Corrige;
        }
        // Verifica a cor e corrige;
    }
    else {
        raiz->esq = put(item, raiz->esq, raiz);
        if(raiz->cor == 'V' && raiz->esq->cor == 'V') {
            cout << "Pai vermelho e filho vermelho!\n";
        }
        // Verifica a cor e corrige;
    }
    return raiz;
}

arn * ARN::corrige_cor(arn * raiz) {
    if(raiz->pai == nullptr) {
        cout << "É raiz!\n";
        return raiz;
    }
    arn * pai = raiz->pai;
    arn * avo = pai->pai;
    if(pai->cor == raiz->cor) {
        // Pai vermelho e filho vermelho;
        if(avo == nullptr) {
            // Sem avô;
            // Pai é a raiz;
            // Pinta o pai de preto e pronto!
            pai->cor = 'B';
            return raiz;
        }
        arn * tio_dir = avo->dir;
        arn * tio_esq = avo->esq;
        // Um desses tios é o pai;
        if(tio_esq == nullptr || tio_esq->cor == 'B') { // Sem tio esquerdo ou com tio esquerdo preto;
            // Roda a direita;
        }
        if(tio_dir == nullptr || tio_dir->cor == 'B') { // Sem tio direito ou com tio direito preto;
            // Roda a esquerda;
        }

        // Se não caiu em nenhum desses casos, então o tio é vermelho;
        // Trocamos a cor do pai, do tio e do avô;
        tio_esq->cor = tio_dir->cor = 'B';
        avo->cor = 'R';

        // Precisa corrigir a partir do avô;
        avo = corrige_cor(avo);
    }
    return raiz;
} 

void ARN::print_in_order(arn * raiz) {
    if(raiz != nullptr) {
        print_in_order(raiz->esq);
        cout << raiz->val.key << endl;
        print_in_order(raiz->dir);
    }
}