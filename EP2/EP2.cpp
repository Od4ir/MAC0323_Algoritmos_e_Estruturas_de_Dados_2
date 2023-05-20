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

bool verifica_repeticoes(Item item) {
    cout << "Verificando repetições!\n";
    for(int i = 0; i < item.tam; i++) {
        for(int j = i + 1; j < item.tam; j++) {
            if(compara_caracter(item.key[i], item.key[j])) {
                cout << item.key << " tem repetição!\n";
                return false;
            }
        }
    }
    cout << item.key << " não tem repetição!\n";
    return true;
}

void insere_nos_vetores(Item item) {
    cout << "Vamos inserir nos vetores!\n";
    cout << item.vog << endl;
    cout << max_vog << endl;
    if(item.vog > max_vog) {
        if(!srv_words.empty()) {
            cout << "Não estava vazio!\n";
            srv_words.clear();
        }
        srv_words.push_back(item.key);
        max_vog = item.vog;
        min_tam_srv = item.tam;
    }
    else if(item.vog == max_vog) {
        if(item.tam == min_tam_srv) {
            srv_words.push_back(item.key);
        }
        if(item.tam < min_tam_srv) {
            if(!srv_words.empty()) { 
                cout << "Estava não vazio!\n";
                srv_words.clear();
            }
            cout << "Hieee\n";
            srv_words.push_back(item.key);
            cout << "Ueh\n";
            min_tam_srv = item.tam;
        }
    }

    if(item.vog != 0) {
        if(verifica_repeticoes(item)) {
            if(item.tam == max_tam_sr) {
                sr_words.push_back(item.key);
            }
            else if(item.tam > max_tam_sr) {
                max_tam_sr = item.tam;
                sr_words.clear();
                sr_words.push_back(item.key);
            }
        }
    }
}

void mais_repetida(Item item) {
    if(item.repet == max_freq) {
        f_words.push_back(item.key);
    }
    else if(item.repet > max_freq) {
        max_freq = item.repet;
        f_words.clear();
        f_words.push_back(item.key);
    }
}

int montagem() {
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
                cout << word << endl;
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
                word = strtok(nullptr, " .,?!");
                cont++;
            }
        }
        // --------------------------------------------
        arvo.print_in_order(arvo.arvore);

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
                word = strtok(nullptr, " .,?!");
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
            }
        }
        // --------------------------------------------
    }

    cout << "Maiores palavras sem repetição de letras: \n";
    cout << "Tamanho máximo: " << max_tam_sr << endl;
    for(int i = 0; i < sr_words.size(); i++) {
        cout << i << ": " << sr_words[i] << endl;
    }
    cout << endl;

    cout << "Menores palavras sem vogais repetidas: \n";
    cout << "Número de Vogais: " << max_vog << endl;
    for(int i = 0; i < srv_words.size(); i++) {
        cout << i << ": " << srv_words[i] << endl;
    }
    cout << endl;

    cout << "Palavras mais frequentes: \n";
    cout << "Frequência: " << max_freq << endl;
    for(int i = 0; i < f_words.size(); i++) {
        cout << i << ": " << f_words[i] << endl;
    }
} 

int main() {
    coloca_na_estrutura(montagem());
    return 0;
}
