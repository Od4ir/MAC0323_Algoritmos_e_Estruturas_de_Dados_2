#include "estruturas.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

vector<char *> f_words;        // Vetor para palavras mais frequentes;
long long int max_freq = 1;       // Valor para determinar qual foi a maior frequẽncia;

vector<char *> sr_words;       // Vetor para MAIORES palavras sem repetição de letras;
long long int max_tam_sr = 0;     // Valor para determinar qual foi o maior tamanho de palavra sem repetição de letra;

vector<char *> srv_words;      // Vetor para MENORES palavras com mais vogais sem repetição;
long long int max_vog = 0;        // Valor para maior número de vogais sem repetição entre todas as palavras;
long long int min_tam_srv = 101;  // Valor para menor tamanho de palavra com vog = max_vog;

vector<char *> max_words;
long long int max_size = 1;

vector<char *> www;

int est;

bool compara_caracter(char x, char y) {
    int a = x;
    int b = y;

    if(a == b) {
        return true;
    }
    if(a - 32 == b) {
        return true;
    }
    if(b - 32 == a) {
        return true;
    }
    return (a == b);
}

bool verifica_repeticoes(Key key) {
    for(int i = 0; i < strlen(key); i++) {
        for(int j = i + 1; j < strlen(key); j++) {
            if(compara_caracter(key[i], key[j])) {
                return false;
            }
        }
    }
    return true;
}

void insere_nos_vetores(Key key, Item item) {
    if(item.vog > max_vog) {
        if(!srv_words.empty()) {
            srv_words.clear();
        }
        srv_words.push_back(key);
        max_vog = item.vog;
        min_tam_srv = item.tam;
    }
    else if(item.vog == max_vog) {
        if(item.tam == min_tam_srv) {
            srv_words.push_back(key);
        }
        if(item.tam < min_tam_srv) {
            if(!srv_words.empty()) { 
                srv_words.clear();
            }
            srv_words.push_back(key);
            min_tam_srv = item.tam;
        }
    }

    if(verifica_repeticoes(key)) {
        if(item.tam == max_tam_sr) {
            sr_words.push_back(key);
        }
        else if(item.tam > max_tam_sr) {
            max_tam_sr = item.tam;
            sr_words.clear();
            sr_words.push_back(key);
        }
    }

    if(item.tam == max_size) {
        max_words.push_back(key);
    }
    else if(item.tam > max_size) {
        max_words.clear();
        max_size = item.tam;
        max_words.push_back(key);
    }
}

void mais_repetida(Key key, Item item) {
    if(item.repet == max_freq) {
        f_words.push_back(key);
    }
    else if(item.repet > max_freq) {
        max_freq = item.repet;
        f_words.clear();
        f_words.push_back(key);
    }
}


int montagem() {
    cout << " --------- Bem Vindx ao EP2 - Od4ir --------- \n\n";
    char E[10];
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
    cout << "\nDigite o número de palavras: ";
    long long int N; cin >> N; cout << endl;
    long long int cont = 0;
    char aux_linha[10000];
    char * word;

    VO vetor_ordenado(N);
    ABB arvore_abb;
    TREAP treaps(N);
    ARN arvore_rn;
    A23 arvore_23;

    cout << "Digite as palavras: ";

    if(est == 1) {  
        //cout << "Vetor Dinâmico Ordenado escolhido!\n";
        // LEITURA DAS PALAVRAS -----------------------
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                Item item(word);
                vetor_ordenado.add(word, item);
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
        // --------------------------------------------
        vetor_ordenado.printa();


        cout << endl;
    }
    else if(est == 2) {
        //cout << "Árvore de Busca Binária escolhida!\n";

        // LEITURA DAS PALAVRAS -----------------------
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                Item item(word);
                arvore_abb.add(word, item);
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
        // --------------------------------------------
        arvore_abb.print_pre_order(arvore_abb.arvore);

    }
    else if(est == 3) {
        //cout << "Treaps escolhida!\n";

        // LEITURA DAS PALAVRAS -----------------------
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                Item item(word);
                treaps.add(word, item);
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
        // --------------------------------------------
        treaps.print_pre_order(treaps.treap);
    }
    else if(est == 4) {
        cout << "Árvores 2-3 escolhida!\n";

        // LEITURA DAS PALAVRAS -----------------------
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                Item item(word);
                arvore_23.add(word, item);
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }

        cout << "Árvore 2-3 In Order\n";
        arvore_23.print_in_order(arvore_23.arvore);

        cout << "\nÁrvore 2-3 Pre Order\n";
        arvore_23.print_pre_order(arvore_23.arvore);
        // --------------------------------------------

    }
    else { 
        //cout << "Árvores Rubro-Negras\n";

        // LEITURA DAS PALAVRAS -----------------------
        while(cont < N) {
            cin.getline (aux_linha, 10000);
            word = strtok(aux_linha, " .,?!");
            while(word != nullptr && cont < N) {
                Item item(word);
                arvore_rn.add(word, item);
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
        // --------------------------------------------
        arvore_rn.print_pre_order(arvore_rn.arvore);
    }

    char querie[100];
    char aux_word[100];
    vector<int> consultas;
    cout << "Hora das Consultas: \n";
    cout << " [ F  ] - Palavras mais frequente; " << endl;
    cout << " [ O  ] 'termo' - Quantas vezes 'termo' aparece no texto;" << endl;
    cout << " [ L  ]- Palavras mais longas;" << endl;
    cout << " [ SR ] - Maiores palavras sem repetição;" << endl;
    cout << " [ VD ] - Menores palavras com mais vogais sem repetição;" << endl;

    cout << "\nDigite o número de consultas que deseja fazer: \n";
    cout << "   >> ";
    int n_queries; cin >> n_queries;

    cout << endl << "Digite as consultas: \n" << endl;

    for(int i = 0; i < n_queries; i++) {
        cout << "   >> ";
        cin >> querie;

        if(strcmp(querie, "F") == 0) {
            consultas.push_back(1);
        }
        else if(querie[0] == 'O') {
            cin >> aux_word;
            consultas.push_back(2);
        }
        else if(strcmp(querie, "L") == 0) {
            consultas.push_back(3);
        }
        else if(strcmp(querie, "SR") == 0) {
            consultas.push_back(4);
        }
        else {
            consultas.push_back(5);
        }
    }

    for(int i = 0; i < n_queries; i++) {
        cout << "\n CONSULTA " << i + 1 << "! \n";
        if(consultas[i] == 1) {
            cout << "Palavras mais frequentes: \n";
            cout << "Frequência: " << max_freq << endl;
            for(int j = 0; j < f_words.size(); j++) {
                cout << j + 1 << ": " << f_words[j] << endl;
            }
        }
        else if(consultas[i] == 2) {
            cout << "Buscando " << aux_word << endl;
            if(est == 1) {
                Item item_aux = vetor_ordenado.value(aux_word);
                if(item_aux.repet == -1) {
                    cout << "Palavra: " << aux_word << " não está na estrutura!" << endl;
                }
                else {
                    cout << "Número de repetições da palavra " << aux_word << ": " << item_aux.repet << endl;
                }
            }
            else if(est == 2) {
                Item item_aux = arvore_abb.value(aux_word);
                if(item_aux.repet == -1) {
                    cout << "Palavra: " << aux_word << " não está na estrutura!" << endl;
                }
                else {
                    cout << "Número de repetições da palavra " << aux_word << ": " << item_aux.repet << endl;
                }
            }
            else if(est == 3) {
                Item item_aux = treaps.value(aux_word);
                if(item_aux.repet == -1) {
                    cout << "Palavra: " << aux_word << " não está na estrutura!" << endl;
                }
                else {
                    cout << "Número de repetições da palavra " << aux_word << ": " << item_aux.repet << endl;
                }
            }
            else if(est == 5) {
                Item item_aux = arvore_rn.value(aux_word);
                if(item_aux.repet == -1) {
                    cout << "Palavra: " << aux_word << " não está na estrutura!" << endl;
                }
                else {
                    cout << "Número de repetições da palavra " << aux_word << ": " << item_aux.repet << endl;
                }
            }
            else {
                Item item_aux = arvore_23.value(aux_word);
                if(item_aux.repet == -1) {
                    cout << "Palavra: " << aux_word << " não está na estrutura!" << endl;
                }
                else {
                    cout << "Número de repetições da palavra " << aux_word << ": " << item_aux.repet << endl;
                }
            }
        }
        else if(consultas[i] == 3) {
            cout << "Palavras mais longas: \n";
            cout << "Tamanho máximo: " << max_tam_sr << endl;
            for(int j = 0; j < max_words.size(); j++) {
                cout << j + 1 << ": " << max_words[j] << endl;
            }
            cout << endl;
        }
        else if(consultas[i] == 4) {
            cout << "Maiores palavras sem repetição de letras: \n";
            cout << "Tamanho máximo: " << max_tam_sr << endl;
            for(int j = 0; j < sr_words.size(); j++) {
                cout << j + 1 << ": " << sr_words[j] << endl;
            }
            cout << endl;
        }
        else {
            cout << "Menores palavras sem vogais repetidas: \n";
            cout << "Número de Vogais: " << max_vog << endl;
            for(int j = 0; j < srv_words.size(); j++) {
                cout << j << ": " << srv_words[j] << endl;
            }
            cout << endl;
        }
    }
} 

int main() {
    est = montagem();
    coloca_na_estrutura(est);
    cout << "-- FIM DO PROGRAMA -- " << endl;
    return 0;
}
