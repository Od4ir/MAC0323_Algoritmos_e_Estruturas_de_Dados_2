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
    if(strcmp(key, "##!PALAVRAERRO!##") == 0) { 
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
            mais_repetida(vetor[meio].key, vetor[meio].val);
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
        vetor[start].val.repet = val.repet;
        vetor[start].val.tam = val.tam;
        vetor[start].val.vog = val.vog;
        mais_repetida(vetor[start].key, val);
        insere_nos_vetores(vetor[start].key, val);
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
    n_comp_busca = 0;
    long long int aux = busca(key);
    if(aux >= 0) {
        return vetor[aux].val;
    }
    char a[] = "##!PALAVRAERRO!##";
    Item item(a);
    return item;
}

void VO::printa() {
    if(fim == -1) {
        cout << "Vetor vazio!\n";
    }
    else { 
        for(long long int i = 0; i <= fim; i++) {
            cout << i + 1 << ": " << vetor[i].key << "(" << vetor[i].val.repet << ")" << endl;
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
        insere_nos_vetores(raiz->key, val);
        mais_repetida(raiz->key, val);
        return raiz;
    }
    long long int comp = strcmp(key, raiz->key);
    n_comp_insercao++;
    if(comp == 0) {
        raiz->val.repet++;
        mais_repetida(raiz->key, raiz->val);
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
        cout << raiz->key << " (" << raiz->val.repet << ")\n";
        print_in_order(raiz->dir);
    }
}

void ABB::print_pre_order(abb * raiz) {
    if(raiz != nullptr) {
        cout << raiz->key << " (" << raiz->val.repet << ")\n";
        print_pre_order(raiz->esq);
        print_pre_order(raiz->dir);
    }
}

Item ABB::value(Key key) {
    n_comp_busca = 0;
    abb * aux = busca_aux(key, arvore);
    if(aux == nullptr) {
        char a[] = "##!PALAVRAERRO!##";
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
        insere_nos_vetores(raiz->key, val);
        mais_repetida(raiz->key, val);
        return raiz;
    }
    long long int comp = strcmp(key, raiz->key);
    n_comp_insercao++;
    if(comp == 0) {
        raiz->val.repet++;
        mais_repetida(raiz->key, raiz->val);
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
    n_comp_busca = 0;
    tree_heap * aux = busca(key, treap);
    if(aux == nullptr) {
        char a[] = "##!PALAVRAERRO!##";
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
    return busca(key, raiz->esq);
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
        cout << raiz->key << " (" << raiz->val.repet << ")\n";
        print_in_order(raiz->dir);
    }
}

void TREAP::print_pre_order(tree_heap * raiz) {
    if(raiz != nullptr) {
        cout << raiz->key << " (" << raiz->val.repet << ")\n";
        print_pre_order(raiz->esq);
        print_pre_order(raiz->dir);
    }
}

long long int TREAP::calcula_altura(tree_heap * raiz) {
    int alt_esq, alt_dir;
    if(raiz == nullptr) {
        return -1;
    }
    alt_esq = calcula_altura(raiz->esq);
    alt_dir = calcula_altura(raiz->dir);
    if(alt_esq > alt_dir) {
        return 1 + alt_esq;
    }
    return 1 + alt_dir;
}

// FUNÇÕES ÁRVORES RUBRO NEGRAS //

ARN::ARN() {
    arvore = nullptr;
    n_comp_busca = 0;
    n_comp_insercao = 0;
    n_rotacoes = 0;
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

        insere_nos_vetores(raiz->key, val);
        mais_repetida(raiz->key, val);
        return raiz;
    }
    long long int comp = strcmp(key, raiz->key);
    n_comp_insercao++;
    if(comp == 0) {
        raiz->val.repet++;
        mais_repetida(raiz->key, raiz->val);
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
    n_comp_busca = 0;
    arn * aux = busca(key, arvore);
    if(aux == nullptr) {
        char a[] = "##!PALAVRAERRO!##";
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
    return busca(key, raiz->esq);
}

void ARN::print_pre_order(arn * raiz) {
    if(raiz != nullptr) {
        printf("(%c) - ", raiz->cor);
        cout << raiz->key << " (" << raiz->val.repet << ")\n";
        print_pre_order(raiz->esq);
        print_pre_order(raiz->dir);
    }
}

void ARN::print_in_order(arn * raiz) {
    if(raiz != nullptr) {
        print_pre_order(raiz->esq);
        printf("(%c) - ", raiz->cor);
        cout << raiz->key << " (" << raiz->val.repet << ")\n";
        print_pre_order(raiz->dir);
    }
}

long long int ARN::calcula_altura(arn * raiz) {
    int alt_esq, alt_dir;
    if(raiz == nullptr) {
        return -1;
    }
    alt_esq = calcula_altura(raiz->esq);
    alt_dir = calcula_altura(raiz->dir);
    if(alt_esq > alt_dir) {
        return 1 + alt_esq;
    }
    return 1 + alt_dir;
}

// FUNÇÕES ÁRVORES 2 3 //

bool cresceu = false;

A23::A23() {
    arvore = nullptr;
    n_comp_busca = 0;
    n_comp_insercao = 0;
    quebras = 0;
}

void A23::add(Key key, Item val) {
    arvore = put(key, val, arvore, cresceu);
}

bool A23::eh_folha(arv23 * no) {
    if(no->p1 == nullptr ) {
        return true;
    }
    return false;
}

arv23 * A23::put(Key key, Item val, arv23 * raiz, bool &cresceu) {
    if(raiz == nullptr) {
        raiz = (arv23 *) malloc(sizeof(arv23));

        raiz->p1 = nullptr;
        raiz->p2 = nullptr;
        raiz->p3 = nullptr;

        raiz->key1 = (Key) malloc(sizeof(char) * strlen(key));
        strcpy(raiz->key1, key);

        raiz->val1 = val;
        raiz->eh_2no = true;
        cresceu = true;

        insere_nos_vetores(raiz->key1, val);
        mais_repetida(raiz->key1, val);
        return raiz;
    }
    if(eh_folha(raiz)) {  // Estamos em uma folha;

        if(raiz->eh_2no) {   // A folha é 2 nó;

            // Vamos comparar para ver se é maior ou menor;
            int comp = strcmp(key, raiz->key1);
            n_comp_insercao++;

            if(comp == 0) {  // Se forem iguais, apenas atualiza o valor;

                raiz->val1.repet++;

                // Verificando se ela tornou-se uma das palavras mais repetidas;
                mais_repetida(raiz->key1, raiz->val1);

                cresceu = false;
                return raiz;

            }
            if(comp > 0) {   // Se a nova palavra for maior, coloca a ela no espaço 2;
                
                raiz->key2 = (Key) malloc(sizeof(char) * strlen(key));
                strcpy(raiz->key2, key);
                raiz->val2 = val;
                raiz->eh_2no = false;

                // Inserindo nos vetores para as consultas;
                insere_nos_vetores(raiz->key2, val);
                mais_repetida(raiz->key2, val);

                cresceu = false;
                return raiz;
            }

            // Se a palavra for menor, trocamos elas de lugar;

            Key aux = raiz->key1;
            Item val_aux = raiz->val1;

            raiz->key1 = (Key) malloc(sizeof(char) * strlen(key));
            strcpy(raiz->key1, key);
            raiz->val1 = val;

            raiz->key2 = (Key) malloc(sizeof(char) * strlen(aux));
            strcpy(raiz->key2, aux);
            raiz->val2 = val_aux;

            // Inserindo nos vetores para as consultas;
            insere_nos_vetores(raiz->key1, val);
            mais_repetida(raiz->key1, val);

            raiz->eh_2no = false;
            cresceu = false;
            return raiz;
        }
        // Inserindo em uma folha 3 nó;

        arv23 * meio = (arv23 *) malloc(sizeof(arv23));
        arv23 * maior = (arv23 *) malloc(sizeof(arv23));

        char word_meio[100];
        char word_maior[100];

        // Comparando para decidir onde iremos colocar a nova chave;

        int comp1 = strcmp(key, raiz->key1);
        int comp2 = strcmp(key, raiz->key2);
        n_comp_insercao += 2;

        if(comp1 == 0) { // Se for a key1, apenas atualiza o valor da key1;

            raiz->val1.repet++;

            // Verificando se ela tornou-se uma das palavras mais repetidas;
            mais_repetida(raiz->key1, raiz->val1);

            cresceu = false;
            return raiz;
        }
        else if(comp2 == 0) { // Se for igual a key2, apenas atualiza o valor;

            raiz->val2.repet++;

            // Verificando se ela tornou-se uma das palavras mais repetidas;
            mais_repetida(raiz->key2, raiz->val2);

            cresceu = false;
            return raiz;
        }
        else if(comp1 < 0) { // O key é o menor de todos;

            strcpy(word_meio, raiz->key1);
            strcpy(word_maior, raiz->key2);

            meio->val1= raiz->val1;
            maior->val1 = raiz->val2;
            raiz->val1 = val;

            raiz->key1 = (Key) malloc(sizeof(char) * strlen(key));
            strcpy(raiz->key1, key);

            // Inserindo a nova palavra nos vetores:
            mais_repetida(raiz->key1, val);
            insere_nos_vetores(raiz->key1, val);

        } 
        else if(comp2 < 0) { // O key é o meio;
        
            strcpy(word_meio, key);
            strcpy(word_maior, raiz->key2);
            meio->val1 = val;
            maior->val1 = raiz->val2;

        }
        else { // O key é o maior;

            strcpy(word_maior, key);
            strcpy(word_meio, raiz->key2);

            meio->val1 = raiz->val2;
            maior->val1 = val;
        } 

        raiz->eh_2no = true;

        maior->key1 = (Key) malloc(sizeof(char) * strlen(word_maior));
        strcpy(maior->key1, word_maior);
        maior->eh_2no = true;

        maior->p1 = nullptr;
        maior->p2 = nullptr;
        maior->p3 = nullptr;

        meio->key1 = (Key) malloc(sizeof(char) * strlen(word_meio));
        strcpy(meio->key1, word_meio);
        meio->eh_2no = true;

        meio->p1 = raiz;
        meio->p2 = maior;
        meio->p3 = nullptr;

        if(comp2 < 0 && comp1 > 0) {
            mais_repetida(meio->key1, meio->val1);
            insere_nos_vetores(meio->key1, meio->val1);
        }
        else if(comp1 > 0) {
            mais_repetida(maior->key1, maior->val1);
            insere_nos_vetores(maior->key1, maior->val1);
        }

        cresceu = true;
        quebras++;
        return meio;
    }
    if(raiz->eh_2no) { // Não estamos em uma folha e a raiz é 2 nó;

        int comp = strcmp(key, raiz->key1);
        n_comp_insercao++;

        if(comp == 0) { // Era igual, apenas atualiza o valor;
            raiz->val1.repet++;
            mais_repetida(raiz->key1, raiz->val1);
            return raiz;
        } 
        if(comp < 0) { // Era menor, insere recursivamente no pontero p1;
            arv23 * p = put(key, val, raiz->p1, cresceu);

            if(!cresceu) {  // Se não cresceu, apenas retorna a raiz;
                return raiz;
            }
            // Se cresceu, precisa ajustar:
            // Como estamos um 2-nó, iremos coloca esse valor dentro do nó raiz;

            char aux_word[100];
            strcpy(aux_word, raiz->key1);
            Item item_aux = raiz->val1;

            raiz->key1 = (Key) malloc(sizeof(char) * strlen(p->key1));
            strcpy(raiz->key1, p->key1);
            raiz->val1 = p->val1;

            raiz->key2 = (Key) malloc(sizeof(char) * strlen(aux_word));
            strcpy(raiz->key2, aux_word);
            raiz->val2 = item_aux;

            raiz->p3 = raiz->p2;
            raiz->p2 = p->p2;
            raiz->p1 = p->p1;
            free(p);

            cresceu = false;
            raiz->eh_2no = false;
            return raiz;
        } 
        // Era maior, insere recursivamente no ponteiro p2;

        arv23 * p = put(key, val, raiz->p2, cresceu);

        if(!cresceu) {  // Se não cresceu, está tudo certo;
            return raiz;
        }
        // Se cresceu, como estamos em um 2-nó, basta colocar junto da chave;

        raiz->key2 = (Key) malloc(sizeof(char) * strlen(p->key1));
        strcpy(raiz->key2, p->key1);
        raiz->val2 = p->val1;

        raiz->p2 = p->p1;
        raiz->p3 = p->p2;
        cresceu = false;
        raiz->eh_2no = false;
        return raiz;
    }
    // Não estamos em uma folha, e a raiz é 3 nó;

    int comp1 = strcmp(key, raiz->key1);
    int comp2 = strcmp(key, raiz->key2);
    n_comp_insercao += 2;

    if(comp1 == 0) {
        raiz->val1.repet++;
        mais_repetida(raiz->key1, raiz->val1);
        cresceu = false;
        return raiz;
    }
    if(comp2 == 0) {
        raiz->val2.repet++;
        mais_repetida(raiz->key2, raiz->val2);
        cresceu = false;
        return raiz;
    }
    if(comp1 < 0) { // Key é menor que todos;

        // Insere recursivamente no ponteiro p1;
        arv23 * p = put(key, val, raiz->p1, cresceu);

        if(!cresceu) {
            return raiz;
        }
        arv23 * novo_meio = (arv23 *) malloc(sizeof(arv23));
        novo_meio->key1 = (Key) malloc(sizeof(char) * strlen(raiz->key1));
        strcpy(novo_meio->key1, raiz->key1);

        novo_meio->val1 = raiz->val1;
        novo_meio->eh_2no = true;

        raiz->p1 = raiz->p2;
        raiz->p2 = raiz->p3;
        raiz->p3 = nullptr;

        raiz->eh_2no = true;

        raiz->key1 = (Key) malloc(sizeof(char) * strlen(raiz->key2));
        strcpy(raiz->key1, raiz->key2);

        raiz->val1 = raiz->val2;

        novo_meio->p1 = p;
        novo_meio->p2 = raiz;
        novo_meio->p3 = nullptr;

        cresceu = true;
        quebras++;

        return novo_meio;
    }
    if(comp2 < 0) { // Key está no meio de todos;
        // Insere recursivamente no ponteiro p2;
        arv23 * p = put(key, val, raiz->p2, cresceu);

        if(!cresceu) {
            return raiz;
        }
        arv23 * novo_meio = (arv23 *) malloc(sizeof(arv23));

        novo_meio->key1 = (Key) malloc(sizeof(char) * strlen(p->key1));
        strcpy(novo_meio->key1, p->key1);

        novo_meio->val1 = p->val1;
        novo_meio->eh_2no = true;

        raiz->p2 = p->p1;

        raiz->eh_2no = true;

        p->key1 = (Key) malloc(sizeof(char) * strlen(raiz->key2));
        strcpy(p->key1, raiz->key2);

        p->p1 = p->p2;
        p->p2 = raiz->p3; 
        p->p3 = nullptr;

        p->eh_2no = true;

        novo_meio->p1 = raiz;
        novo_meio->p2 = p;
        novo_meio->p3 = nullptr;

        cresceu = true;
        quebras++;

        return novo_meio;  
    }
    arv23 * p = put(key, val, raiz->p3, cresceu);
    // Insere recursivamente no ponteiro p3;
    if(!cresceu) {
        return raiz;
    }
    arv23 * novo_meio = (arv23 *) malloc(sizeof(arv23));
    novo_meio->key1 = (Key) malloc(sizeof(char) * strlen(raiz->key2));
    strcpy(novo_meio->key1, raiz->key2);

    novo_meio->val1 = raiz->val2;
    novo_meio->eh_2no = true;

    raiz->p3 = nullptr;
    raiz->eh_2no = true;

    raiz->val1 = raiz->val2;

    novo_meio->p1 = raiz;
    novo_meio->p2 = p;
    novo_meio->p3 = nullptr;

    cresceu = true;
    quebras++;

    return novo_meio;
}

void A23::print_in_order(arv23 * raiz) {
    if(raiz != nullptr) {
        print_in_order(raiz->p1);
        cout << raiz->key1 << " (" << raiz->val1.repet << ")\n";
        print_in_order(raiz->p2);

        if(!raiz->eh_2no) { 
            cout << raiz->key2 << " (" << raiz->val2.repet << ")\n";
            print_in_order(raiz->p3);
        }
    }
}

void A23::print_pre_order(arv23 * raiz) {
    if(raiz != nullptr) {
        cout << raiz->key1 << " (" << raiz->val1.repet << ")\n";
        if(!raiz->eh_2no) {
            cout << " 2 ";
            cout << raiz->key2 << " (" << raiz->val2.repet << ")\n";
        }
        print_pre_order(raiz->p1);
        print_pre_order(raiz->p2);
        if(!raiz->eh_2no) {
            print_pre_order(raiz->p3);
        }
    }
}

Item A23::value(Key key) {
    n_comp_busca = 0;
    cout << "Buscando " << key << endl;
    arv23 * aux = busca(key, arvore);
    if(aux == nullptr) {
        char a[] = "##!PALAVRAERRO!##";
        Item item_aux(a);
        return item_aux;
    }
    if(strcmp(key, aux->key1) == 0)
        return aux->val1;
    return aux->val2;
}

arv23 * A23::busca(Key key, arv23 * raiz) {
    if(raiz == nullptr) {
        return nullptr;
    }
    int comp1 = strcmp(key, raiz->key1);
    n_comp_busca++;
    if(comp1 == 0) return raiz;

    if(!raiz->eh_2no) {
        int comp2 = strcmp(key, raiz->key2);
        n_comp_busca++;
        if(comp2 == 0) {
            return raiz;
        }
        if(comp2 > 0) {
            return busca(key, raiz->p3);
        }
    }
    if(comp1 < 0) {
        return busca(key, raiz->p1);
    }
    return busca(key, raiz->p2);
}

long long int A23::calcula_altura(arv23 * raiz) {
    if(raiz == nullptr) {
        return -1;
    }
    return 1 + calcula_altura(raiz->p1);
}