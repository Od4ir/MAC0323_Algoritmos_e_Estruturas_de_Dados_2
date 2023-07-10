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

bool verifica_intervalo(char x, char y, char atual) {
    //cout << atual << endl;
    //cout << x << " e " << y << endl;
    //cout << (int)x << " e " << (int)y << " e " << (int)atual << endl;
    if((int)x <= (int)atual && (int)y >= (int)atual) return true;
    return false;
}

string modifica_exp_reg(string &exp_reg) {
    string exp_final;
    int i, j;
    for(i = 0; i < (int)exp_reg.size(); i++) {
        if(exp_reg[i] == '[' && exp_reg[i + 2] != '-' && exp_reg[i + 1] != '^') {
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

bool verifica_complemento(Grafo& G, string& palavra, string& exp_reg) {
    return true;
}

void constroi_grafo(Grafo& G, const string& exp_reg) {
    stack<int> pilha;

    int i, k, ant;

    for(i = 0; i < (int)exp_reg.size(); i++) {
        //cout << i << " atual: " << exp_reg[i] << endl;
        ant = i;
        if(exp_reg[i] != ' ') { 
            if(exp_reg[i] == '[') {
                for(k = i; k < (int)exp_reg.size(); k++) {
                    if(exp_reg[k] == ']') {
                        break;
                    }
                    G.add_aresta(k, k + 1);
                }
                i = k;
            }

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
    if(igual_simbolos(exp_reg[(int)exp_reg.size() - 1])) G.add_aresta((int)exp_reg.size() - 1, (int)exp_reg.size());
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
        cout << i << ": " << palavra[i] << endl;

        for(int k = 0; k < G.V; k++) prox[k] = false;

        for(int j = 0; j < G.V; j++) {
            if(atingidos[j]) {
                if(exp[j] == '\\') {
                    cout << j << " >>> " << exp[j + 1] << endl;
                    if(exp[++j] == palavra[i]) {
                        cout << "Entrou\n";
                        prox[j + 1] = true;
                    }
                }
                else if(exp[j] == palavra[i] || exp[j] == '.') {
                    prox[j + 1] = true;
                }
                else if(exp[j] == '[' && (exp[j + 3] == '-' || exp[j + 2] == '-')) {
                    if(exp[j + 1] == '^') {
                        if(!verifica_intervalo(exp[j + 2], exp[j + 4], palavra[i])) {
                            prox[j + 6] = true;
                        }
                    }
                    else if(verifica_intervalo(exp[j + 1], exp[j + 3], palavra[i])) {
                        prox[j + 5] = true;
                    }
                    j = j + 4;
                }
                else if(exp[j] == '[') {
                    //cout << "Oiiii\n";
                    for(int l = j + 2; l < exp.size(); l++) {
                        //cout << exp[l] << endl;
                        if(exp[l] == ']') {
                            prox[l + 1] = true;
                            //cout << prox[l = 1] << endl;
                            //cout << l + 1 << " no prox!\n";
                            j = l + 1;
                            break;
                        }
                        if(exp[l] == palavra[i]) return false;
                    }
                }
            }
        }
        bool * marc = new bool[G.V];
        for(int j = 0; j < G.V; j++) atingidos[j] = false;
        for(int k = 0; k < G.V; k++) marc[k] = false;
        for(int j = 0; j < G.V; j++) {
            //cout << j << " prox: " << prox[j] << endl;
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
    //cout << G.V << - 1 << endl;
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
    cout << "Nova expressão: " << exp_reg << endl;

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