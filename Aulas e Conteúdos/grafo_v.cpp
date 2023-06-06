#include <bits/stdc++.h>
#include "grafo.h"
using namespace std;

// Funções de Grafo Implementado como Vetor:

// Criação do grafo:
GrafoL::GrafoL(int N) {
    E = 0;
    V = N;
    adj = (vector<int> *) malloc(sizeof(vector<int>) * (N + 2));
}

// Adicão de nova aresta com direção;
void GrafoL::add_d(int v, int u) {
    adj[v].push_back(u);
    E++;
}

// Adição de nova aresta sem direção;
void GrafoL::add(int v, int u) {
    add_d(v, u);
    add_d(u, v);
    E--; 
}

// Printa para cada vértice seus adjacentes;
void GrafoL::print() {
    for(int i = 0; i < V; i++) {
        cout << "Vértice: " << i << ": ";
        for(int j = 0; j < adj[i].size(); j++) {
            cout << adj[i][j] << " - ";
        }
        cout << endl;
    }
}

// BUsca em largura;
// --> Vai visitando todos os vértices (Modelo Geral);
void GrafoL::dfs() {
    // Vetor para marcar os vértices visitados;
    bool * visitado = new bool[V + 2];
    // Marcamos todos os vértices como não visitado;
    for(int i = 0; i < V; i++) visitado[i] = false;
    // Percorremos os vértices e se ele não foi visitado, chamamamos
    // a dfs recursiva nele que irá marcar os vértices conectados;
    for(int i = 0; i < V; i++) {
        if(!visitado[i]) {
            dfsR(i, visitado);
        }
    }
    delete[] visitado;
}

// A partir de um vértice, visita todos seus adjacentes e assim 
// vai recursivamente;
// --> É melhor que o modelo de matriz na maioria dos casos pois a iteração
//     ocorre somente nos vértices com adjacência, já salvos no vetor;
void GrafoL::dfsR(int u, bool * visitado) {
    // Marcamos que acabamos de visitar o vértice:
    visitado[u] = true;
    // Para todos os vértices conectados ao vértice u que ainda não
    // foram visitados, chamaos o dfs recursivo para marcá-los e marcar
    // seus adjacentes;
    for(int v: adj[u]) {
        if(!visitado[v]) {
            dfsR(v, visitado);
        }
    }
    // No final de apenas uma iteração, se o grafo não apresentar mais
    // de um componente conexo, todos os vértices estarão marcados;
}


// Dados dois vértices, determina se existe caminho eles ou não;
bool GrafoL::tem_caminho(int u, int v) {
    // Criamos um vetor para marcar que todos os vértices ainda não 
    // foram visitados;
    bool * visitado = new bool[V + 2];
    for(int i = 0; i < V; i++) visitado[i] = false;

    // Rodamos uma dfs patindo de u, se chegamos em v, então visitado[v]
    // é true, se não chegamos é false;

    dfsR(u, visitado);
    return visitado[v];
}

// Imprime o caminho entre dois vértices;
void GrafoL::imprime_caminho(int u, int v) {
    bool * visitado = new bool[V + 2];
    int * pred = new int[V + 2];

    for(int i =0; i < V; i++) {
        visitado[i] = false;
        pred[i] = -1;
    }

    pred[u] = u;
    acha_caminho_r(u, visitado, pred);

    if(pred[v] == -1) {
        cout << "Não tem caminho!\n";
    }
    else { 
        for(int w = v; w != u; w = pred[w]) {
            printf("%d - ", w);
        }
        cout << u << '\n';
    }

}

// É uma dfs que marca em pred[] o predecessor;
void GrafoL::acha_caminho_r(int v, bool * visitado, int * pred) {
    // É uma dfs com a diferença que estamos marcando o predecessor;
    visitado[v] = true;

    for(int w: adj[v]) {
        if(!visitado[w]) {
            // Salva no pred qual foi o vértice que foi visto anteriormente;
            pred[w] = v;
            acha_caminho_r(w, visitado, pred);
        }
    }
}

// Devolve o número de componentes conexas do grafo:
int GrafoL::comp_conexa() {
    bool * vis = new bool[V + 2];
    int comp = 0;
    for(int i = 0; i < V; i++) vis[i] = false;
    for(int i = 0; i < V; i++) {
        if(vis[i] == false) {
            dfsR(i, vis);
            comp++;
        }
    }
    return comp;
}

// Devolve um vetor marcando em cada i o id do componente conexo do
// i-ésimo vértice: 

vector<int> GrafoL::vetor_comp_conexas() {
    bool * vis = new bool[V + 2];
    vector<int> comp_conexa(V + 2, -1);

    int comp = 0;
    for(int i = 0; i < V; i++) {  
        vis[i] = false;
    }
    for(int i = 0; i < V; i++) vis[i] = false;
    for(int i = 0; i < V; i++) {
        if(vis[i] == false) {
            dfsR(i, vis);
            comp++;
            comp_conexa[i] = comp;
        }
        else {
            comp_conexa[i] = comp;
        }
    }
    return comp_conexa;
}


// Decide se o grafo é bipartido ou não;
/* Um grafo é bipartido de pudermos pintar todos os vértices de uma tal for-
ma que toda aresta do grafo possua um vértice de cada cor em cada extremidade.
Se tiver da mesma cor, então não é bipartido. 
*/
bool GrafoL::eh_bipartido() {
    // Criamos um vetor para ir marcando as cores e o preenchemos com -1;
    vector<int> cores(V + 2, -1);
    // A variável 'resp' irá guardar a resposta final da função recursiva
    // bipartidoR(). Caso em algum momento ela retorne false, já sabemos
    // que o grafo não é, então paramos o loop e devolvemos false;
    bool resp = true;

    // Como o grafo pode ter várias componentes conexas, chamamos a função
    // para todos os vértices não visitados. Verificamos se ele já foi vi-
    // sitado olhando para o vetor cores; 
    for(int i = 0; i < V && resp; i++) {
        if(cores[i] == -1) {
            resp = bipartidoR(i, cores, 0);
        }
    }
    return resp;
}

// Essa função vai pintando os vértices para verificar se o grafo é bipar-
// tido ou não;
bool GrafoL::bipartidoR(int v, vector<int>& cores, int cor) {
    // Pintamos o vértice atual com a cor mandada;
    cores[v] = cor;

    // Verificamos os vizinhos do vértice atual. Se algum deles já estiver
    // pintado e a cor for igual a cor do vértice atual, já sabemos que a 
    // resposta é false. 
    for(int u: adj[v]) {
        if(cores[u] == cor) return false;
        // Caso ele ainda não tenha sido visitado, chamamos a função recur-
        // siva, se ela devolver false, retornamos falso e acabou. Caso con-
        // trário, apenas continuamos. 
        if(cores[u] == -1) {
            if(!bipartidoR(u, cores, 1 - cor)) {
                return false;
            }
        }
    }
    // Se der tudo certo, sabemos que é verdade e retornamos true;
    return true;
}

//--------------------------------------------------------------------------
/*
O que fizemos até agora foi uma busca em profundidade, dfs. A dfs funciona da
seguinte forma - Começo em um vértice u, marco que ele foi visitado e vou 
chamando a função recursivamente para os vértices adjacentes que não foram
visitados ainda. Quando encontro um, chamo a função para ele, ou seja, mesmo
que os vértices adjacentes do u não tenham sido todos ainda verificados, eu
vou ir verificar os adjacentes a algum adjacente. 

A diferença da dfs para bfs é isso, na bfs, busca em largura, eu visito
todos os adjacentes ao u antes de ir recursivamente para um deles. Vamos ao
código:

*/

vector<int> GrafoL::caminho_mais_curto(int u) {
    // Um valor para preencher nossa dist inicialmente;
    int infinito = V + 100;
    // Vetor dist para marcar as distâncias de u para todos os outros vérti-
    // ces. Note que não precisamos de um vetor de visitados, pois sabemos 
    // que um vértice u não foi visitado se seu dist[u] = infinito;
    vector<int> dist(V + 2, infinito);

    queue<int> fila; // queue -> Estrutura de fila do C++;
    // Dá para usar uma pilha também (stack);

    // Colocamos u na fila e marcamos que distância de u para u é 0;
    fila.push(u);
    dist[u] = 0;

    while(!fila.empty()) {
        int v = fila.front();
        fila.pop();
        for(int w: adj[v]) {
            if(dist[w] > dist[v] + 1) {
                dist[w] = dist[v] + 1;
                fila.push(w);
            }
        }
    }
    return dist;
}


int main() {
    // Adição das arestas e vértices;
    cout << "Digite o número de vértices: \n";
    int N; cin >> N;
    GrafoL GG(N);

    cout << "Digite o número de arestas: \n";
    int A; cin >> A;

    cout << "Digite as arestas: \n";

    for(int i = 0; i < A; i++) {
        int a, b;
        cin >> a >> b;
        GG.add(a, b);
    }
    GG.print();

    cout << "Número de componentes conexas: " << GG.comp_conexa() << endl;

    cout << "Vetor de componentes conexas: " << endl;

    int i = 0;

    for(int v: GG.vetor_comp_conexas()) {
        cout << "Comp. do " << i << ": " << v << endl;
        i++;
        if(i == N) break;
    } 


    cout << "O grafo é bipartido? " << GG.eh_bipartido() << endl;

    cout << "Digite um vértice: ";
    int vert; cin >> vert;

    cout << "Caminho mínimo de todos os vértices até ele: " << endl;
    
    i = 0;
    for(int x: GG.caminho_mais_curto(vert)) { 
        cout << i << ": " << x << endl;
        i++;
    }

    int ok = 1;

    //--------------------------------------------------------------------------
    /* PROBLEMA 1 //
    // Tem caminho de u a v? Como resolver esse problema?
    // --> Roda a dfs recursiva partindo de u, se o visitado de u marcar
    //     falso após a dfsR, então não existe caminho;
    while(ok) { 
        cout << "Digite dois vértices: ";
        int u, v; cin >> u >> v;
        if(GG.tem_caminho(u, v)) printf("Tem caminho entre %d e %d\n", u, v);
        else printf("Não tem caminho entre %d e %d\n", u, v);
        cin >> ok;
    }*/

    //--------------------------------------------------------------------------
    /* PROBLEMA 2 //

    // Se tem caminho, como imprimir esse caminho?
    // --> Roda uma dfs e salva num vetor de predecessores qual foi o vértice
    //     que foi visitado antes do vértice de valor do índice. Exemplo: se
    //     pred[i] = y, então o vértice visitado antes do y foi o i;

    while(ok) { 
        cout << "Digite dois vértices: ";
        int u, v; cin >> u >> v;

        GG.imprime_caminho(u, v);
        cout << "Continuar? "; cin >> ok;
    }*/

    //--------------------------------------------------------------------------
    /* PROBLEMA 3 //
    Queremos encontrar as componentes conexas de um grafo;
    Usamos a dfsR, para cada vez que, dentro de um loop entre todos os vértices,
    chegarmos em um vértice que não foi visitado ainda, marcamos que temos um
    novo componenete conexo. 
    
    bool * vis = new bool[N + 2];
    int comp = 0;
    for(int i = 0; i < N; i++) vis[i] = false;
    for(int i = 0; i < N; i++) {
        if(vis[i] == false) {
            GG.dfsR(i, vis);
            comp++;
        }
    }
    cout << "Componentes conexas: " << comp << endl; */

    //--------------------------------------------------------------------------
    /* PROBLEMA 4 //
    Queremos marcar de qual componente conexa é cada vértice.
    Para isso podemos ter um vetor do tamanho do número de vértices e iniciar esse
    vetor com algum valor que sabemos que não pode ser o id de uma componente. 

    Podemos usar o id de uma componente conexa o número do conrador de componentes 
    conexas. Assim, basta rodar o dfsR e ir marcando as visitadas com um valor pas-
    sado na chamada inicial da função, o valor do comp. Cheque a seguinte função:

        vetor_comp_conexas();
    */

    //--------------------------------------------------------------------------
    /* PROBLEMA 5 //
    Análogo ao 4, porém queremos saber o seguinte, dado um id de uma componente
    queremos saber quais são os vértices desse id sem ter que percorrer o vetor 
    inteiro para fazer essa verificação. 

    Pois para determinar isso usando o vetor acima, para um número q de consultas
    e um número n de vetores, isso iria demorar O(nq), pois em toda consulta esta-
    ríamos percorrendo o vetor inteiro.

    Como fazer isso de forma melhor?

    Podemos usar mais memória. E ter um vetor de vetores de comṕonentes conexas:

    comp_conexas[i][j] - De forma que i marca o id do componente e o valor retorna-
    do é o vértice salvo na posição j;

    Para uma consulta da componente de id x, basta acessar comp_conexas[x] e per-
    correr essa linha até o final. 

    Não to afim de implementar isso, entretanto. :)
    */

    //--------------------------------------------------------------------------
    /* PROBLEMA 6 //

    Dado uum grafo, queremos decidir se ele é bipartido ou não. Um grafo binpar-
    tido é aquele em que podemos pintar os vértices de 2 cores de tal forma que
    todos os pares de 2 vértices que tem uma aresta em comum não possuem a mes-
    ma cor. 

    Como fazer isso? Comece por um vértice e pinte de uma cor x (Vamos supor que
    temos 2 cores: x e y). Então, visite todos os vizinhos e pinte-os da cor y e
    depois vá para o próximo vértice. Caso algum vizinho já esteja pintado, veri-
    fique se a cor do vértice atual é igual a cor desse vizinho, se for, já pode
    devolver que não é bipartido. Caso não seja, está ok e podemos continuar a ve-
    rificação. Se der tudo certo, ao final podemos concluir que é um grafo bipar-
    tido. 

    Veja a função: bipR();
    
    */


    return 0;
}