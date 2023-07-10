#include <iostream>
#include <vector>
#include <stack>
#include "grafo.h"

// Verifica se o char aux é igual a algum dos caracteres do seguinte conjunto:
// {*, (, ), +};
bool igual_simbolos(char aux) {
    if(aux == '*') return true;
    if(aux == '(') return true;
    if(aux == ')') return true;
    if(aux == '+') return true;
    return false;
}

// Verifica se o char atual está no intervalo de x e y;
bool verifica_intervalo(char x, char y, char atual) {
    if((int)x <= (int)atual && (int)y >= (int)atual) return true;
    return false;
}

// Modifica a expressão regular transformando [ABC..] em (A|B|C|...);
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

// Constroi um grafo de transições baseado na string exp_reg;
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
                    G.add_aresta(i, i + 1);
                }
            }
        }
    }
    if(igual_simbolos(exp_reg[(int)exp_reg.size() - 1])) G.add_aresta((int)exp_reg.size() - 1, (int)exp_reg.size());
}

// Verifica, a partir do grafo G de transições se uma string palavra
// é aceita pela expressão regular;
bool reconhece(Grafo& G, string palavra, string exp) {
    bool * atingidos = new bool[G.V];
    bool * prox = new bool[G.V];
    bool * marc = new bool[G.V];
    for(int i = 0; i < G.V; i++) atingidos[i] = false;

    G.dfsR(0, atingidos);

    for(int i = 0; i < (int)palavra.size(); i++) {
        for(int k = 0; k < G.V; k++) prox[k] = false;

        for(int j = 0; j < G.V; j++) {
            if(atingidos[j]) {
                if(exp[j] == '\\') {
                    if(exp[++j] == palavra[i]) {
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
                    for(int l = j + 2; l < exp.size(); l++) {
                        if(exp[l] == ']') {
                            prox[l + 1] = true;
                            j = l + 1;
                            break;
                        }
                        if(exp[l] == palavra[i]) return false;
                    }
                }
            }
        }
        bool * marc = new bool[G.V];
        for(int j = 0; j < G.V; j++) { 
            atingidos[j] = false;
            marc[j] = false;
        }
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

    cout << "Digite a expressão regular: (Sem espaço entre os caracteres)\n > ";
    string exp_reg; 
    getline(cin, exp_reg);

    // Adapta a expressão para montagem do grafo se necessário;
    exp_reg =  modifica_exp_reg(exp_reg);

    Grafo G((int)exp_reg.size() + 1);
    constroi_grafo(G, exp_reg);

    char op;
    cout << "\nDeseja ver as arestas por vértice? (S/N)\n > ";
    cin >> op;
    if(op == 'S', 's') {
        int p = 0;
        for(auto aux: G.adj) {
            cout << "Vértice " << p << ": " << exp_reg[p] << endl;
            p++;
            for(int x: aux) {
                cout << " > " << x << ": " << exp_reg[x] << endl;
            }
        }
    }

    cout << "\nDigite quantas palavras deseja testar: \n > ";
    int n; cin >> n;

    cout << "\nDigite as palavras: \n";
    for(int i = 0; i < n; i++) {
        cout << " > ";
        string aux; cin >> aux;

        if(reconhece(G, aux, exp_reg)) {
            cout << "  > SIM!\n";
        }
        else cout << "  > NÃO!\n";
        cout << endl;
    }
    return 0;
}