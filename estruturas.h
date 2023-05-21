#include <cstdlib>
#include <cstring>
#include <vector>

typedef char * Key;

// FUNÇÕES ITEM // 

class Item {
    public:
        Item(char * chave);
        long long int tam;
        long long int vog;
        long long int repet;
};

bool compara_caracter(char x, char y);
bool verifica_repeticoes(Key key);
void insere_nos_vetores(Key key, Item item);
void mais_repetida(Key key, Item item);
long long int verifica_vogal(char atu);


// VETOR ORDENADO DINÃMICO -- OK //

typedef struct {
    Key key;
    Item val;
} vo;

class VO {
    public:
        long long int fim;
        vo * vetor;

        long long int n_comp_insercao;
        long long int n_comp_busca;
        long long int n_trocas;
        // Cria um objeto do tipo  VO com 'vetor' de tamanho n;
        VO(long long int n);
        // Adiciona um item ao vetor ordenado;
        void add(Key key, Item val);
        // Dada uma chave, retorna o índice do Item no vetor ou -1 se não estiver;
        Item value(Key key);
        long long int busca(Key key);
        // Imprime o vetor de 'Item's;
        void printa();
};

// ÁRVORE DE BUSCA BINÁRIA -- OK //

typedef struct cel_abb {
    Item val;
    Key key;
    struct cel_abb * esq;
    struct cel_abb * dir;
} abb;

class ABB {
    public:
        abb * arvore;
        long long int n_comp_busca;
        long long int n_comp_insercao;
        long long int altura;

        // Cria um objeto do tipo ABB - Árvore de Busca Binária
        ABB();
        // Adiciona um item na ABB.arvore e devolve um ponteiro para a nova raiz;
        void add(Key key, Item val);
        abb * put(Key key, Item val, abb * raiz, long long int n);
        // Prlong long inta os valores salvos nos nós da árvore 'in order' (Esquerda - Raiz - Direita);
        void print_in_order(abb * raiz);
        void print_pre_order(abb * raiz);
        // Dada uma chave, retorna um ponteiro para o nó em que está a chave, retorna nullptr se não houver item com aquela chave na ABB.arvore;
        Item value(Key key);
        abb * busca_aux(Key key, abb * raiz);
};

// TREAPS - OK //

typedef struct cel_treap {
    Item val;
    Key key;
    cel_treap * esq;
    cel_treap * dir;
    long long int prioridade;
} tree_heap;

class TREAP {
    public:
        tree_heap * treap;
        long long int n_comp_busca;
        long long int n_comp_insercao;
        long long int n_rotacoes;
        long long int altura;
        long long int valor_max_prioridade;

        TREAP(long long int n);
        void add(Key key, Item val);
        Item value(Key key);
        tree_heap * busca(Key key, tree_heap * raiz);
        tree_heap * put(Key key, Item val, tree_heap * raiz);
        tree_heap * rotaciona(tree_heap * p, char lado);
        void print_in_order(tree_heap * raiz);
        void print_pre_order(tree_heap * raiz);

};


// ÁRVORES RUBRO NEGRAS - OK //

typedef struct cel_arn {
    Item val;
    struct cel_arn * esq;
    struct cel_arn * dir;
    char cor;
    Key key;
} arn;

class ARN {
    public:
        arn * arvore;
        long long int n_comp_busca;
        long long int n_comp_insercao;
        long long int n_rotacoes;
        long long int altura;

        ARN();
        void add(Key key, Item val);
        arn * put(Key key, Item val, arn * raiz);
        bool eh_vermelho(arn * no);
        arn * rotaciona(arn * p, char lado);
        void print_in_order(arn * raiz);
        void print_pre_order(arn * raiz);
        Item value(Key key);
        arn * busca(Key key, arn * raiz);
};


// ÁRVORES 2-3 BALANCEADAS // 