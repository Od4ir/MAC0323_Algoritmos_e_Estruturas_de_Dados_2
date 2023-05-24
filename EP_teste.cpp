#include "estruturas.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

/* Esta versão do EP foi feita para realizar os testes: */

void testes() {
    cout << " ----------- EP2 - Versão de Testes ------------ " << endl << endl;
    cout << " >> Digite o tipo de teste que deseja realizar: " << endl << endl;
    cout << " 1 - Lista de palavras em ordem crescente;" << endl;
    cout << " 2 - Lista de palavras em ordem descrescente;" << endl;
    cout << " 3 - Lista de palavras em ordem aleatória;" << endl << " >> ";

    long long int op; cin >> op;
    char nome_arquivo[20];

    cout << "\n >> Digite o número de palavras que deseja testar: ";
    long long int tam;

    if(op == 1) {
        cout << "[TAM_MAX = 256k]\n";
        cout << " >> ";
        cin >> tam;
        strcpy(nome_arquivo, "teste_oc.txt");
    }
    else if(op == 2) {
        cout << "[TAM_MAX = 256k]\n";
        cout << " >> ";
        cin >> tam;
        strcpy(nome_arquivo, "teste_od.txt");
    }
    else {
        cout << "[TAM_MAX = 640k]\n";
        cout << " >> ";
        cin >> tam;
        if(tam > 256000) {
            strcpy(nome_arquivo, "teste_640k.txt");
        }
        else {
            strcpy(nome_arquivo, "teste_a.txt");
        }
    }

    // Abertura do arquivo escolhido pelo teste:
    FILE * f;
    f = fopen(nome_arquivo, "rt");

    // Varíaveis auxiliares para leitura do arquivo: 
    char word[100]; // 100 - É o tamanho máximo de uma palavra;
    char * aux_word;

    // Estruturas utilizadas nos testes:
    VO vetor_ordenado(tam);
    ABB arvore_busca_binaria;
    TREAP treeheap(tam);
    ARN arvorerubronegra;
    A23 arvore23;

    // Contador para inserir o número de palavras indicado:
    long long int cont = 0;

    // Inserção das palavras nas estruturas: 
    while(cont < tam) {
        fscanf(f, "%s", word);
        aux_word = strtok(word, ".?!;,:"); // Filtragem dos caracteres das palavras;

        Item item(aux_word);
        vetor_ordenado.add(aux_word, item);
        arvore_busca_binaria.add(aux_word, item);
        treeheap.add(aux_word, item);
        arvorerubronegra.add(aux_word, item);
        arvore23.add(aux_word, item);

        cont++;
    }

    int S;

    while(S != 0) { 
        cout << "\nDigite os códigos para impressão dos dados da estrutura: \n\n";
        cout << " 1 - Vetor Ordenado - Palavras Ordenadas\n";
        cout << " 2 - Árvore de Busca Binária - In Order\n";
        cout << " 3 - Árvore de Busca Binária - Pre Order\n";
        cout << " 4 - Treap - In Order\n";
        cout << " 5 - Treap - Pre Order\n";
        cout << " 6 - Árvores Rubro Negras - In Order\n";
        cout << " 7 - Árvores Rubro Negras - Pre Order\n";
        cout << " 8 - Árvores 2-3 - In Order\n";
        cout << " 9 - Árvores 2-3 - Pre Order\n";
        cout << " 0 - Sair\n\n";
        cin >> S;
        if(S == 1) {
            cout << "Vetor Ordenado: \n";
            vetor_ordenado.printa();
        }
        else if(S == 2) {
            cout << "ABB - In Order: \n";
            arvore_busca_binaria.print_in_order(arvore_busca_binaria.arvore);
        }
        else if(S == 3) { 
            cout << "ABB - Pre Order: \n";
            arvore_busca_binaria.print_pre_order(arvore_busca_binaria.arvore);
        }
        else if(S == 4) {
            cout << "Treap - In Order: \n";
            treeheap.print_in_order(treeheap.treap);
        }
        else if(S == 5) {
            cout << "Treap - Pre Order: \n";
            treeheap.print_pre_order(treeheap.treap);
        }
        else if(S == 6) {
            cout << "ARN - In Order: \n";
            arvorerubronegra.print_in_order(arvorerubronegra.arvore);
        }
        else if(S == 7) {
            cout << "ARN - Pre Order: \n";
            arvorerubronegra.print_pre_order(arvorerubronegra.arvore);
        }
        else if(S == 8) {
            cout << "A23 - In Order:\n";
            arvore23.print_in_order(arvore23.arvore);
        }
        else if(S == 9) {
            cout << 'A23 - Pre Order: \n';
            arvore23.print_pre_order(arvore23.arvore);
        }
    }


    cout << ">>> Resultados para testes com " << tam << " palavras!" << endl;

    cout << " 1 - VETOR ORDENADO: " << endl;
    cout << "Número de Comparações Inserção......." << vetor_ordenado.n_comp_insercao << endl;
    cout << "Número de Trocas....................." << vetor_ordenado.n_trocas << endl << endl;

    cout << " 2 - ÁRVORE DE BUSCA BINÁRIA: " << endl;
    cout << "Número de Comparações Inserção......." << arvore_busca_binaria.n_comp_insercao << endl;
    cout << "Altura..............................." << arvore_busca_binaria.altura << endl << endl;

    cout << " 3 - TREAPS: " << endl;
    cout << "Número de Comparações Inserção......." << treeheap.n_comp_insercao << endl;
    cout << "Altura..............................." << treeheap.altura << endl;
    cout << "Número de Rotações..................." << treeheap.n_rotacoes << endl << endl;

    cout << " 4 - ÁRVORES RUBRO NEGRAS: " << endl;
    cout << "Número de Comparações Inserção......." << arvorerubronegra.n_comp_insercao << endl;
    cout << "Altura..............................." << arvorerubronegra.altura << endl;
    cout << "Número de Rotações..................." << arvorerubronegra.n_rotacoes << endl << endl;

    cout << " 5 - ÁRVORE 2-3: " << endl;
    cout << "Número de Comparações Inserção......." << arvore23.n_comp_insercao << endl;
    cout << "Altura..............................." << arvore23.altura << endl;
    cout << "Número de Quebras...................." << arvore23.quebras << endl << endl;

}
int main() {
    testes();
    return 0;
}
