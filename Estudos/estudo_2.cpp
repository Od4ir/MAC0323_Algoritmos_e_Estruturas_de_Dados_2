/* Vamos estudar o que são class em C++. */
// Link de Referêmcia --> https://homepages.dcc.ufmg.br/~rodolfo/aedsi-2-10/Classes/classe.html#:~:text=Na%20linguagem%20C%2B%2B%20as%20classes,denominado%20Programa%C3%A7%C3%A3o%20Orientada%20a%20Objetos.

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Dado {
    private: 
        int face;
    public:
        Dado() {srand(time(0));rolar();};
        const static int FACES = 6;
        int obterFace();
        void rolar();
};

int Dado::obterFace() {
    return face;
};

void Dado::rolar() {
    face = rand() % FACES + 1;
};

int main(int argc, char *argv[]) {
    Dado d1;
    d1.rolar();
    cout << d1.obterFace() << "\n";
    system("PAUSE");
    return EXIT_SUCCESS;
}

