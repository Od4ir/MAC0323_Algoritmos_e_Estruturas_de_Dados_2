#include <bits/stdc++.h>
using namespace std;

// Implementação por matriz:

class Grafo {
    public:
        int **adj;
        int E;
        int V;
        Grafo(int N) {
            V = N;
            *adj = (int *) malloc(sizeof(int) * N);
            for(int i = 0; i < N; i++) {
                adj[i] = (int *) malloc(sizeof(int) * N);
            }
            for(int i = 0; i < V; i++) {
                for(int j = 0; j < V; j++) {
                    adj[i][j] = 0;
                }
            }
            E = 0;
        }
        void add(int u, int v) {
            u = u - 1;
            v = v - 1;
            if(adj[u][v] == 0) {
                adj[u][v] = adj[v][u] = 1;
                E++;
            }
        }
        void print() { 
            for(int i = 0; i < V; i++) {
                for(int j = 0; j < V; j++) {
                    cout << adj[i][j] << ' ';
                }
                cout << '\n';
            }
        }
};

int main() {
    int N;
    cin >> N;
    Grafo G(N);

    G.add(1, 2);
    G.add(4, 4);
    G.print();
    return 0;
}



