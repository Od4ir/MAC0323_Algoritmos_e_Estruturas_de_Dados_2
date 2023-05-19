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

typedef struct cel_abb {
    Item val;
    struct cel_abb * esq;
    struct cel_abb * dir;
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
        void add(Item item);
        abb * put(Item item, abb * raiz, int n);
        // Printa os valores salvos nos nós da árvore 'in order' (Esquerda - Raiz - Direita);
        void print_in_order(abb * raiz);
        // Dada uma chave, retorna um ponteiro para o nó em que está a chave, retorna nullptr se não houver item com aquela chave na ABB.arvore;
        abb * busca(char * key, abb * raiz);
};

// TREAPS //

typedef struct cel_treap {
    Item val;
    cel_treap * pai;
    cel_treap * esq;
    cel_treap * dir;
    int prioridade;
} tree_heap;

class TREAP {
    public:
        tree_heap * treap;
        int n_comp_busca;
        int n_comp_insercao;
        int n_rotacoes;
        int altura;
        int valor_max_prioridade;

        TREAP(int n);
        void add(Item item);
        tree_heap * put(Item item, tree_heap * raiz, tree_heap * ant, int n);
        tree_heap * rotaciona(tree_heap * p, char lado);
        void print_in_order(tree_heap * raiz);
        void print_pre_order(tree_heap * raiz);
        tree_heap * busca(Item item, tree_heap * raiz);
};


// ÁRVORES RUBRO NEGRAS //

typedef struct cel_arn {
    Item val;
    struct cel_arn * pai;
    struct cel_arn * esq;
    struct cel_arn * dir;
    char cor;
} arn;

class ARN {
    public:
        arn * arvore;
        int n_comp_busca;
        int n_comp_insercao;
        int altura;

        ARN();
        void add(Item item);
        arn * put(Item item, arn * raiz);
        bool eh_vermelho(arn * no);
        arn * corrige_cor(arn * raiz);
        arn * rotaciona(arn * p, char lado);
        void print_in_order(arn * raiz);
        void print_pre_order(arn * raiz);
        void calcula_altura(arn * raiz);
};
