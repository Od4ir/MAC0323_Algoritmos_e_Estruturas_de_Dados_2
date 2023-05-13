#include "item.h" 
#include <cstdlib>
#include <cstring>

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