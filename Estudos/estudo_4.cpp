#include <iostream>
using namespace std;

template <class item>
class Bag {
    private:
        item *v;
        int tam;
        int n;
        void resize(int tam);
    public:
        Bag();
        ~Bag();
        void add(item obj);
        bool isEmpty();
        int size();
        item at(int i);
};

template <class item>
Bag<item>::~Bag() {
    if(v != nullptr)
        delete[]v
}

template <class item>
Bag<item>::Bag(): n(0), tam(1), v(new item[1]) {};

template <class item>
item Bag<item>::at(int i) {
    if(i >= 0 && i < n)
        return v[i];
}

template <class item>
bool Bag<item>::isEmpty() {
    return(n == 0);
}

template <class item>
int Bag<item>::size() {
    return(n);
}

template <class item>
void Bag<item>::add(item obj) {
    if(n == tam)
        resize(2*tam);
    v[n] = item;
    n++;
}

template <class item>
void Bag<item>::resize(int t) {
    item * novov = new item[t];
    for(int i = 0; i < n; i++) {
        novov[i] = v[i];
    }
    delete[]v;
    v = novov;
    tam = t;
}