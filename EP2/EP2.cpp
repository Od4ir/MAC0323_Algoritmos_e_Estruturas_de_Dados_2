#include "estruturas.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

long long int montagem() {
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

void coloca_na_estrutura(long long int est) {
    cout << "Digite o número de palavras: ";
    long long int N; cin >> N; cout << endl;
    long long int cont = 0;
    char aux_linha[10000];
    char * word;

    if(est == 1) {  
        cout << "Vetor Dinâmico Ordenado escolhido!\n";
        VO vetor_ordenado(N);

        // LEITURA DAS PALAVRAS -----------------------
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                Item item(word);
                vetor_ordenado.add(item);
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
        // --------------------------------------------
        vetor_ordenado.printa();
    }
    else if(est == 2) {
        cout << "Árvore de Busca Binária escolhida!\n";
        ABB arvo;
        // LEITURA DAS PALAVRAS -----------------------
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                Item item(word);
                arvo.add(item);
                //arvo.arvore = arvo.add(item, arvo.arvore, 0);
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
        // --------------------------------------------
        arvo.print_in_order(arvo.arvore);

        char busc[1000];
        cin >> busc;
        abb * b = arvo.busca(busc, arvo.arvore);
        if(b == nullptr) {
            cout << "Não há!\n";
        }
        else {
            cout << b->val.key << " | " << b->val.repet << endl;
        }
        cout << arvo.n_comp_insercao << " comparações na inserção\n";
        cout << arvo.n_comp_busca << " comparações na busca\n";
        cout << arvo.altura << " altura da arvore\n";

    }
    else if(est == 3) {
        cout << "Treaps escolhida!\n";
        TREAP arv(N);

        // LEITURA DAS PALAVRAS -----------------------
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                Item item(word);
                arv.add(item);
                //arv.treap = arv.add(item, arv.treap, arv.treap, 0, 'x');
                word = strtok(nullptr, " .,?!");
                cout << "\n\n ----- Árvore Atual: ----- \n";
                arv.print_pre_order(arv.treap);
                cout << endl;
                cont++;
            }
        }
        // --------------------------------------------
        arv.print_in_order(arv.treap);
    }
    else if(est == 4) {
        cout << "Árvores 2-3 escolhida!\n";

        // LEITURA DAS PALAVRAS -----------------------
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                Item item(word);
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
        // --------------------------------------------

    }
    else { 
        cout << "Árvores Rubro-Negras\n";
        ARN arv;

        // LEITURA DAS PALAVRAS -----------------------
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                Item item(word);
                arv.add(item);
                word = strtok(nullptr, " .,?!");
                cont++;
                cout << "------ Árvore Atual: -------\n";
                arv.print_pre_order(arv.arvore);
            }
        }
        // --------------------------------------------
        cout << endl << "Árvore FINAL: " << endl;
        arv.print_in_order(arv.arvore);
    }
} 

int main() {
    coloca_na_estrutura(montagem());
    return 0;
}
