#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct node {
    string key;
    int id;
};

typedef struct vector<node> vertices;

// Compara dois nodes a partir de suas chaves (strings);
bool compara_nodes(node& a, node& b);
// Gera uma string com as letras A, C, G e T de tamanho k;
string gera_string(int k);
// Gera uma substring de tamanho tam a partir da string dna;
string gera_substring(int tam, const string& dna);

