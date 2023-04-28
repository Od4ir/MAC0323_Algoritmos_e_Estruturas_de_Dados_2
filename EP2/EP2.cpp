#include <iostream>
#include <cstdlib>
#include <string>
#include "item.h"
using namespace std;

char aux[1000];

Item::Item(string chave) {
    key.copy(chave);
    tam = chave.length();
    vog = 2;
}

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
    int i;
    if(est == 1) {
        for(i = 0; i < N; i++) {
            cin >> aux;
            cout << "ok! ";
            Item item(aux);
            cout << item.key << " colocado! \n";
            cout << item.tam << endl;
            cout << item.vog << endl; 
            // Calcula seus valores;
            // Adiciona o elemento na estrutura;
        }
    }
    else if(est == 2) {
        for(i = 0; i < N; i++) {
            cin >> aux;
            Item item(aux);
            // Calcula seus valores;
            // Adiciona o elemento na estrutura;
        }

    }
    else if(est == 3) {
        for(i = 0; i < N; i++) {
            cin >> aux;
            Item item(aux);
            // Calcula seus valores;
            // Adiciona o elemento na estrutura;
        }

    }
    else if(est == 4) {
        for(i = 0; i < N; i++) {
            cin >> aux;
            Item item(aux);
            // Calcula seus valores;
            // Adiciona o elemento na estrutura;
        }

    }
    else { 
        for(i = 0; i < N; i++) {
            cin >> aux;
            Item item(aux);
            // Calcula seus valores;
            // Adiciona o elemento na estrutura;
        }

    }
} 



int main() {
    //int escolha = montagem();
    coloca_na_estrutura(montagem());
    
    return 0;
}
