#include "item.h" 
#include <cstdlib>
#include <cstring>

typedef struct cel{
    Item val;
    struct cel * esq;
    struct cel * dir;
} abb;

class ABB {
    public:
        abb * arvore;
        int n_comp_busca;
        int n_comp_insercao;
        int altura;

        // Cria um objeto do tipo ABB - Árvore de Busca Binária
        ABB();
        // Adiciona um item na ABB.arvore e devolve um ponteiro para a nova raiz;
        abb * add(Item item, abb * raiz, int n);
        // Printa os valores salvos nos nós da árvore 'in order' (Esquerda - Raiz - Direita);
        void print_in_order(abb * raiz);
        // Dada uma chave, retorna um ponteiro para o nó em que está a chave, retorna nullptr se não houver item com aquela chave na ABB.arvore;
        abb * busca(char * key, abb * raiz);
        int calcula_altura(abb * raiz);
};