#include <iostream>
#include <cstdlib>
#include <cstring>
#include "item.h"
using namespace std;

int montagem() {
    char * E;
    cout << "Escolha a estrutura a ser utilizada: \n";
    printf("  [ VO  ] - Vetor Dinâmico Ordenado\n");
    printf("  [ ABB ] - Árvore de Busca Binária\n");
    printf("  [ TR  ] - Treaps\n");
    printf("  [ A23 ] - Árvores 2-3\n");
    printf("  [ ARN ] - Árvores Rubro-Negras\n\n");
    while(1) { 
        cout << "   >> ";
        cin >> E;
        if(strcmp(E, "VO") == 0) {
            return 1;
        }
        else if(strcmp(E, "ABB") == 0) {
            return 2;
        }
        else if(strcmp(E, "TR") == 0) {
            return 3;
        }
        else if(strcmp(E, "A23") == 0) {
            return 4;
        } 
        else if(strcmp(E, "ARN") == 0) {
            return 5;
        }
        else {
            cout << "   Por favor, digite novamente: " << endl;
        }
    }
    return 1;
}

void coloca_na_estrutura(int est) {
    cout << "Digite o número de palavras: ";
    int N; cin >> N; cout << endl;
    int cont = 0;
    char aux_linha[10000];
    char * word;

    if(est == 1) {  
        cout << "Vetor Dinâmico Ordenado escolhido!\n";
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                cout << word << endl;
                Item item(word);
                // Insere item na estrutura;
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
    }
    else if(est == 2) {
        cout << "Árvore de Busca Binária escolhida!\n";
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                cout << word << endl;
                Item item(word);
                // Insere item na estrutura;
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }

    }
    else if(est == 3) {
        cout << "Treaps escolhida!\n";
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                cout << word << endl;
                Item item(word);
                // Insere item na estrutura;
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
    }
    else if(est == 4) {
        cout << "Árvores 2-3 escolhida!\n";
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                cout << word << endl;
                Item item(word);
                // Insere item na estrutura;
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }

    }
    else { 
        cout << "Árvores Rubro-Negras\n";
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                cout << word << endl;
                Item item(word);
                // Insere item na estrutura;
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
    }
} 

int main() {
    coloca_na_estrutura(montagem());
    return 0;
}
