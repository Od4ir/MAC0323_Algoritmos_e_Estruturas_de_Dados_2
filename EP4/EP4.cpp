#include <iostream>
#include <vector>
#include <stack>
#include "grafo.h"

bool igual_simbolos(char aux) {
    if(aux == '*') return true;
    if(aux == '(') return true;
    if(aux == ')') return true;
    return false;
}

void constroi_grafo(Grafo& G, const string& exp_reg) {
    stack<int> pilha;

    int i;

    for(i = 0; i < (int)exp_reg.size(); i++) {
        cout << i << " atual: " << exp_reg[i] << endl;
        if(exp_reg[i] != ' ') { 
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
                        ant = pilha.top();
                        pilha.pop();
                        G.add_aresta(ant, topo + 1);
                        G.add_aresta(topo, i + 1);
                    }
                    else {
                        ant = topo;
                    }
                }
                if(i < (int)exp_reg.size() - 1 && exp_reg[i + 1] == '*') {
                    G.add_aresta(ant, i + 1);
                    G.add_aresta(i + 1, ant);
                }
                if(i < (int)exp_reg.size() - 1 && igual_simbolos(exp_reg[i])) {
                    cout << "Here\n";
                    G.add_aresta(i, i + 1);
                    if(exp_reg[i] == '*') pilha.push(i);
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

    for(int i = 0; i < (int)palavra.size(); i++) {
        for(int k = 0; k < G.V; k++) prox[i] = false;
        for(int j = 0; j < G.V; j++) {
            if(atingidos[j] && exp[j] == palavra[i]) {
                prox[j + 1] = true;
            }
        }
        bool * marc = new bool[G.V];
        for(int j = 0; j < G.V; j++) atingidos[j] = false;
        for(int k = 0; k < G.V; k++) marc[k] = false;
        for(int j = 0; j < G.V; j++) {
            if(prox[j]) {
                G.dfsR(j, marc);
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

    cout << "Digite quantas palavras deseja testar: \n > ";
    int n; cin >> n;

    cout << "Digite as palavras: \n";
    for(int i = 0; i < n; i++) {
        string aux; cin >> aux;

        if(reconhece(G, aux, exp_reg)) {
            cout << "Reconhece!\n";
        }
        else cout << "Não reconhece\n";
    }

    return 0;
}