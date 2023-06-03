#include <iostream>
#include <string>
using namespace std;

// Valores da Tabela ASCII:
// >> A = 65;
// >> C = 67;
// >> G = 71;
// >> T = 84;

/*
Para gerar as letras, terei que fazer um rand entre 1 e 4, e dependendo
do valor, fazer um append da letra que der; 

*/

// Funções que podem ser utéis:
/*

string.size() ou string.lenght;
    >> Devolve o tamanho da string, número de caracteres;

string.substr(i, j) 
    >> Retorna uma substring entre os índices i e j;

string.find(palavra)
    >> Retorna se a palavra está na string;

string.compare(string2)
    >> Compara duas strings e:
        devolve 0 se são iguais;
        devolve < 0  se a primeira é menor;
        devolve > 0  se a primeira é maior;

string.append(string2)
    >> Acrescenta uma string ao final da outra;
*/


/*
Para verificar se o final de tamanho k de uma string bate com o
começo de outra string, podemos:

    1) Cortar o final da string1 com a função substring;
    2) Usar o find para verificar se tem um encontro;
        2.1) O find devolve o índice que ocorre esse começo;
            2.1.1) Se o índice for 0, bateu!
            2.1.2) Se o índice não for 0, mas existir achar outro
            índice vale a pena verificar 2 coisas:
                2.1.2.1) Se a string1 inteira cabe dentro dá 
                string2;
                2.1.2.2) Se a string2 inteira cabe dentro da 
                string1;
                2.1.2.3) Se ambas são iguais;
            2.1.3) Se o índice for -1, então não há ligação para
            aquele k testado;
*/


/* 
Vamos ter um grafo em que os vértices são representados por 
strings. E há uma conexão de peso x entre dois vértices se o
começo de um bate com o começo do outro;


(?) 
Professor, no seguinte exemplo, como devo proceder:

Tenho uma string ACC e uma outra CACCT, ACC está dentro da segunda,
e eu consigo verificar isso, eu posso simplesmente excluir a primeira
como se eu estivesse admitindo que ela está dentro da outra?




*/

int main() {
    string w;
    cin >> w;

    cout << w.size() << endl;
    cout << w << endl;
    return 0;

}