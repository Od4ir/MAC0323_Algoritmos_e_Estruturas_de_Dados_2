#include <cstdlib>
#include <cstring>

// ITEM //
class Item {
    public:
        Item(char * chave);
        char * key;
        int tam;
        int vog;
        int repet;
};

// VETOR ORDENADO DINÃMICO //

class VO {
    public:
        int size;
        int fim;
        Item * vetor;

        int n_comp_insercao;
        int n_comp_busca;
        int n_trocas;
        // Cria um objeto do tipo  VO com 'vetor' de tamanho n;
        VO(int n);
        // Adiciona um item ao vetor ordenado;
        void add(Item item);
        // Dada uma chave, retorna o índice do Item no vetor ou -1 se não estiver;
        int busca(char * chave);
        // Imprime o vetor de 'Item's;
        void printa();
};

// ÁRVORE DE BUSCA BINÁRIA //

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

// TREAPS //

// ??? 