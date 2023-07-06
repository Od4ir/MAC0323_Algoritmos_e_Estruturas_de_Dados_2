#include <iostream>
#include <vector>
#include <stack>
#include "grafo.h"

bool igual_simbolos(char aux) {
    if(aux == '*') return true;
    if(aux == '(') return true;
    if(aux == ')') return true;
    if(aux == '+') return true;
    return false;
}

string modifica_exp_reg(string &exp_reg) {
    string exp_final;
    int i, j;
    for(i = 0; i < (int)exp_reg.size(); i++) {
        if(exp_reg[i] == '[') {
            exp_final += '(';
            for(j = i + 1; j < (int)exp_reg.size(); j++) {
                if(exp_reg[j] == ']') {
                    exp_final.pop_back();
                    exp_final += ')';
                    break;
                }
                else {
                    exp_final += exp_reg[j];
                    exp_final += '|';
                }
            }
            i = j;
        }
        else {
            exp_final += exp_reg[i];
        }
    }
    return exp_final;

}

void constroi_grafo(Grafo& G, const string& exp_reg) {
    stack<int> pilha;

    int i;

    for(i = 0; i < (int)exp_reg.size(); i++) {
        //cout << i << " atual: " << exp_reg[i] << endl;
        if(exp_reg[i] != ' ') { 
            if(exp_reg[i] == '[') {

            }
            int ant = i;
            if(exp_reg[i] == '(' || exp_reg[i] == '|') {
                pilha.push(i);
                if(exp_reg[i] == '(') {
                    G.add_aresta(i, i + 1);
                }
            }
            else {
                //if(exp_reg[i] == Um caractere) -> Continuamos;
                if(exp_reg[i] == ')') {
                    int topo = pilha.top();
                    pilha.pop();
                    if(exp_reg[topo] == '|') {
                        // Vou desempilhando até encontrar um '(' e salvo eles em um vector;
                        // Se for um '|' eu conecto diretamente com o '(' + 1;

                        vector<int> ous;
                        ous.push_back(topo);
                        while(!pilha.empty()) {
                            ant = pilha.top();
                            pilha.pop();
                            ous.push_back(ant);
                            if(exp_reg[ant] == ')') {
                                // O ant salva o ')';
                                break;
                            }
                        }
                        // Preciso adicionar uma aresta entre todos os 'ous' do vector 'ous' com o ant + 1;

                        for(int ou: ous) {
                            if(exp_reg[ou] == '|') {
                                G.add_aresta(ant, ou + 1);
                                G.add_aresta(ou, i + 1);
                            }
                        }
                    }
                    else {
                        ant = topo;
                    }
                }
                if(i < (int)exp_reg.size() - 1 && exp_reg[i + 1] == '*') {
                    G.add_aresta(ant, i + 1);
                    G.add_aresta(i + 1, ant);
                }
                if(i < (int)exp_reg.size() - 1 && exp_reg[i + 1] == '+') {
                    G.add_aresta(i + 1, ant);
                }
                if(i < (int)exp_reg.size() - 1 && igual_simbolos(exp_reg[i])) {
                    //cout << "Here\n";
                    G.add_aresta(i, i + 1);
                }
            }
        }
    }
    G.add_aresta((int)exp_reg.size() - 1, (int)exp_reg.size());
}

bool reconhece(Grafo& G, string palavra, string exp) {
    bool * atingidos = new bool[G.V];
    bool * prox = new bool[G.V];
    bool * marc = new bool[G.V];
    for(int i = 0; i < G.V; i++) {
        atingidos[i] = false;
    }

    G.dfsR(0, atingidos);

    /*for(int i = 0; i < G.V; i++) {
        if(atingidos[i]) {
            cout << i << " atingido!\n" << " " << exp[i] << endl;
        }
    }*/

    for(int i = 0; i < (int)palavra.size(); i++) {
        for(int k = 0; k < G.V; k++) prox[k] = false;
        for(int j = 0; j < G.V; j++) {
            if(atingidos[j] && (exp[j] == palavra[i] || exp[j] == '.')) {
                prox[j + 1] = true;
            }
        }
        bool * marc = new bool[G.V];
        for(int j = 0; j < G.V; j++) atingidos[j] = false;
        for(int k = 0; k < G.V; k++) marc[k] = false;
        for(int j = 0; j < G.V; j++) {
            if(prox[j]) {
                //cout << j << " está no prox\n";
                G.dfsR(j, marc);
                /*for(int y = 0; y < G.V; y++) {
                    if(marc[y]) {
                        cout << y << " alcançado!\n";
                    }
                }*/
            }
        }
        for(int k = 0; k < G.V; k++) {
            if(marc[k]) atingidos[k] = true;
        }
    }
    bool resp = atingidos[G.V - 1];
    delete[] prox;
    delete[] atingidos;
    return resp;
}

int main() {
    cout << " \n-----------/// BEM VINDX AO EP4 - Od4ir ///-----------\n\n";

    cout << "Digite a expressão regular: \n > ";
    string exp_reg; 
    getline(cin, exp_reg);

    exp_reg =  modifica_exp_reg(exp_reg);

    Grafo G((int)exp_reg.size() + 1);
    constroi_grafo(G, exp_reg);

    int p = 0;

    for(auto aux: G.adj) {
        cout << "Vértice " << p << ": " << exp_reg[p] << endl;
        p++;
        for(int x: aux) {
            cout << " > " << x << ": " << exp_reg[x] << endl;
        }
    }

    cout << "\nDigite quantas palavras deseja testar: \n > ";
    int n; cin >> n;

    cout << "\nDigite as palavras: \n";
    for(int i = 0; i < n; i++) {
        cout << " > ";
        string aux; cin >> aux;

        if(reconhece(G, aux, exp_reg)) {
            cout << "  > Reconhece!\n";
        }
        else cout << "  > Não reconhece\n";
        cout << endl;
    }

    return 0;
}