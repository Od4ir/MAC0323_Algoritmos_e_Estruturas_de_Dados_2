#include "item.h" 
#include <cstdlib>
#include <cstring>

class VO {
    public:
        int size;
        int fim;
        Item * vetor;
        // Duplica o tamanho do vetor e copia os elementos para esse novo vetor de tamanho duplicado;
        void resize();
        // Adiciona um item ao vetor ordenado;
        void add(Item item);
        // Dada uma chave, retorna o índice do Item no vetor ou -1 se não estiver;
        void copy(int i, int j);
        int busca(char * chave);
        VO();
};