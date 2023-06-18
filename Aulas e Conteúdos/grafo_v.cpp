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
    vector<int> dist(V, infinito);

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

void GrafoL::imprime_caminho_curto(int u, int v) {
    int infinito = V + 100;
    vector<int> dist(V, infinito);
    vector<int> pred(V, -1);

    acha_caminho_curtos(u, dist, pred);
    cout << pred[u] << endl;
    cout << pred[v] << endl;

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

void GrafoL::acha_caminho_curtos(int u, vector<int>& dist, vector<int>& pred) { 
    queue<int> fila;
    fila.push(u);
    dist[u] = 0;
    pred[u] = u;

    while(!fila.empty()) {
        int w = fila.front();
        fila.pop();
        for(int v: adj[w]) {
            if(dist[v] > dist[w] + 1) {
                dist[v] = dist[w] + 1;
                pred[v] = w;
                fila.push(v);
            }
        }
    }
}


// DIGRAFOS - Grafos Dirigidos //

/* Em um grafo no qual as arestas tem direção, elas recebem o nome de arcos. 
Cada vértice tem um grau de entrada e um de sáida que indicam quantos arcos
apontam para ele e quantos saem dele. 

Os algoritmos de busca em largura e profundidade funcionam normalmente em 
dografos, não é necessário fazer um especial. 

Vamos ver a seguir alguns algoritmos para grafos dirigidos. 

*/

// Guardamos em pre[i] o instante em que o vértice começou a 
// ser visitado.
// Em pos[i], o instante que terminamos de visitar i;
// Em pred[i] o vértice predecessor do vértice i;
// Comparando os tempos de pre e pos podemos determinar o tipo
// de arco.
/*
    >> De arborescência - Visitando um vértice que ainda não
    começou a ser visitado;
    >> De retorno - Visitando um vértice que já começou a ser
    visitado mas essa visita ainda não foi encerrada;
    >> Descendente - Visitando um vértice que já foi visita-
    do e foi visitado antes do atual;
    >> Cruzado - Visitando um vértice que já foi visitado e 
    foi visitado depois do ínicio do atual;

*/

void GrafoL::dfsR2(int u, int * pre, int * pos, int * pred, int& tempo) {
    pre[u] = tempo++;


    for(int w: adj[u]) {
        if(pre[w] == -1) {
            pred[w] = u;
            dfsR2(w, pre, pos, pred, tempo);
        }
    }
    /*for(int w = 0; w < V; w++) {
        if(find(adj[u].begin(), adj[u].end(), w) != adj[u].end() && pre[w] == -1) {
            pred[w] = u;
            dfsR2(w, pre, pos, pred, tempo);
        }
    }*/
    pos[u] = tempo++;

}

void GrafoL::dfs2() {
    int * pre = new int[V + 2];
    int * pos = new int[V + 2];
    int * pred = new int[V + 2];
    int tempo = 0;

    for(int v = 0; v < V; v++) { // Inicia todos os vetores com -1; 
        pre[v] = pos[v] = pred[v] = -1;
    }

    for(int v = 0; v < V; v++) {
        if(pre[v] == -1) {
            pred[v] = v;
            dfsR2(v, pre, pos, pred, tempo);
        }
    }
}

// Vamos verificar se um digrafo tem ciclos ou não:
bool GrafoL::circ_r(int u, int * pre, int * pos, int * pred, int& tempo) {
    pre[u] = tempo++;
    for(int w: adj[u]) {
        if(pre[w] == -1) {
            pred[w] = u;
            if(circ_r(w, pre, pos, pred, tempo)) return true;
        }
        if(pos[w] == -1) {
            // Se em algum mommento a gente retornar para algum vértice
            // que já teve sua visita iniciada, mas não foi concluída, sa-
            // bemos que esse grafo tem ciclos. 
            return true;
        }
    }
    pos[u] = tempo++;
    return false;
}

bool GrafoL::tem_circuito() {
    int * pre = new int[V + 1];
    int * pos = new int[V + 1];
    int * pred = new int[V + 1];
    int tempo = 0;

    for(int i = 0; i < V; i++) {
        pre[i] = pos[i] = pred[i] = -1;
    }

    for(int i = 0; i < V; i++) { // A gnt itera por todas os vértices pois
        // não tem certeza se o grafo tem mais de uma comp. conexa;
        if(pre[i] == -1) {
            pred[i] = i;
            if(circ_r(i, pre, pos, pred, tempo)) return true;
        }
    }
    return false;
}

/*
Vamos determinar de um grafo tem componentes fortemente conexas, 
isto é, se existe um caminho entre todos os pares de vértices;
*/

int * GrafoL::comp_fortemente_conexas() {
    int * sc = new int[V + 1];
    int * pre = new int[V + 1];
    int * low = new int[V + 1];
    stack<int> pilha;
    int cont = 0, k = 0;

    for(int i = 0; i < V; i++) {
        sc[i] = pre[i] = low[i] = -1;
    }

    for(int v = 0; v < V; v++) {
        if(pre[v] == -1) {
            dfsCFCR(v, pre, sc, low, cont, k, pilha);
        }
    }
    delete[] pre;
    delete[] low;
    return sc;
    // cont - Tempo; (Marcado no pre);
    // k - Número de componentes fortemente conexas;
}

/* Como funciona isso na prática?*/
/*
O  vetor pre marca o instante em que o vértice foi visitado. O 
vetor sc (Strong Component) marca o número da componente forte-
mente conexa a qual o vértice pertencee. E o low marca o 'menor'
vértice que pode ser acessado a partir daquele vértice. 


*/
void GrafoL::dfsCFCR(int v, int * pre, int * sc, int * low, int& cont, int& k, stack<int>& pilha) {
    pre[v] = cont++;
    low[v] = pre[v];

    pilha.push(v);

    for(int w: adj[v]) { 
        if(pre[w] == -1) {
            dfsCFCR(w, pre, sc, low, cont, k, pilha);
            if(low[w] < low[v]) { 
                low[v] = low[w];
            }
        }
        else if(pre[w] < pre[v] && sc[w] == -1) {
            low[v] = min(low[v], pre[w]);
        }
    }
    if(low[v] == pre[v]) {
        int u;
        do {
            u = pilha.top();
            pilha.pop();
            sc[u] = k;
        } while(u != v);
        k++;
    }
}

bool GrafoL::aresta_em_circ(int u, int v) {
    bool * vis = new bool[V + 1];
    for(int i = 0; i < V; i++) vis[i] = false;

    dfsR(v, vis);
    if(vis[u]) return true;
    return false;
}

void GrafoL::dfs_ordem_topologica(int u, bool * vis, stack<int>& order) {
    vis[u] = true;

    for(int v: adj[u]) {
        if(!vis[v]) {
            dfs_ordem_topologica(v, vis, order);
        }
    }

    order.push(u);
}

vector<int> GrafoL::ordem_topologica() {
    bool * vis = new bool[V + 1];
    for(int i = 0; i < V; i++) vis[i] = false;

    stack<int> order;
    vector<int> ordem_topologica;

    for(int i = 0; i < V; i++) {
        if(!vis[i]) {
            dfs_ordem_topologica(i, vis, order);
        }
    }

    while(!order.empty()) {
        ordem_topologica.push_back(order.top());
        order.pop();
    }

    return ordem_topologica;
}

vector<int> GrafoL::caminho_longo() {
    vector<int> order = ordem_topologica();

    vector<int> pred(V);
    vector<int> passos(V, 0);
    vector<int> caminho;
    int MAX = -1, ini;

    for(int i = 0; i < V; i++) {
        pred[i] = i;
    }

    for(int i = 0; i < V; i++) {
        for(int v: adj[order[i]]) {
            if(passos[v] < passos[order[i]] + 1) {
                passos[v] = passos[order[i]] + 1;
                pred[v] = order[i];
                MAX = max(MAX, passos[v]);
                if(MAX == passos[v]) {
                    ini = v;
                }
            }
        }
    }

    int i;
    cout << ini << endl;

    for(i = ini; i != pred[i]; i = pred[i]) {
        caminho.push_back(i);
    }
    caminho.push_back(i);

    return caminho;
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
        GG.add_d(a, b);
    }
    GG.print();

    /*cout << "Número de componentes conexas: " << GG.comp_conexa() << endl;

    cout << "Vetor de componentes conexas: " << endl;

    int i = 0;

    for(int v: GG.vetor_comp_conexas()) {
        cout << "Comp. do " << i << ": " << v << endl;
        i++;
        if(i == N) break;
    } 


    cout << "O grafo é bipartido? " << GG.eh_bipartido() << endl;


    int v1, v2;
    v1 = v2 = 1;
    cout << "Digite dois vértice: ";
    cin >> v1 >> v2;

    while(v1 != -1) { 
        cout << "Caminho curto entre eles: " << endl;

        GG.imprime_caminho_curto(v1, v2);
        cout << "Digite dois vértice: ";
        cin >> v1 >> v2;
    }

    int ok = 1;

    cout << "O grafo tem ciclos? \n";
    cout << GG.tem_circuito() << endl;

    cout << "Digite uma aresta: \n";
    cin >> v1 >> v2;

    while(v1 != -1) { 
        cout << GG.aresta_em_circ(v1, v2) << endl;
        cout << "Digite uma aresta: \n";
        cin >> v1 >> v2;
    }

    */

    cout << "Vamos ver a ordem topológica: \n";

    vector<int> o_top = GG.ordem_topologica();

    for(int i: o_top) {
        cout << i << " - ";
    }
    cout << endl;

    cout << "Caminho mais longo: \n";

    vector<int> caminho_longo = GG.caminho_longo();
    cout << caminho_longo.size() << endl;

    for(int i = (int)caminho_longo.size(); i > 0; i--) {
        cout << caminho_longo[i - 1] << " - ";
    }
    cout << endl;

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
    cout << "Componentes conexas: " << comp << endl;
    */

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

    Dado um grafo, queremos decidir se ele é bipartido ou não. Um grafo binpar-
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

    //--------------------------------------------------------------------------
    /* PROBLEMA 7 //

    Já sabemos encontrar o menor caminho, agora queremos imprimir ele. 
    Basta usar a técnica do vetor de predecessores. 
    */

    //--------------------------------------------------------------------------
    /* PROBLEMA 9 //

    Já resolvemos o problema de encontrar o menor caminho entre dois vértices. 
    Vamos para algumas variações. Se é uma árvore, consiguimos achar a maior 
    distância entre 2 vértices. Basta pegar uma folha e rodar uma bfs para de-
    terminar o vértice mais distante. Depois, rodar uma nova bfs nesse vértice,
    a maior distância no novo vetor dist será o maior caminho. 

    >> Problema do Diâmetro da Árvore.     
    */

    //--------------------------------------------------------------------------
    /* PROBLEMA 10 //

    Dado um digrafo, queremos saber se ele é acíclico ou não.
    A ideia é ir visitando os vértices e marcando o tempo em que começamos a vi-
    sita. Quando formos visitar um adjacente ao vértice, verificamos se ele não 
    foi visitado completamente antes. Se ele já foi, está tudo bem. Agora, se a vi-
    sita dele não foi terminada ainda, isso é (pos[v] == -1), então temos um arco
    de retorno e isso significa que temos um ciclo. 

    Todo grafo não direcionado com pelo menos um aresta entre dois vértices dife-
    rentes tem ciclo. De u -> v e de v -> u, é um ciclo. Por isso, perguntar se tem
    ciclo faz mais sentido quando os grafos são direcionados. 

    (?) - Arco de retorno indica que o grafo tem ciclo? Basta isso?
    Acho que sim.
    */

    //--------------------------------------------------------------------------
    /* PROBLEMA 11 //

    Queremos saber se um grafo é fortemente conexo. Ou, se apresenta componentes
    fortemente conexas. Isto é, verificar se a partir de todo vértice do grafo, é
    possível chegar em qualquer outro (dentro da mesma componente).

    Outra forma de dizer isso é: Dado um par de vértices u e v, um grafo é forte-
    mente conexo se para todo u e todo v, existe um caminho de u para v;

    Um grafo fortemente conexo apresenta apenas uma componente fortemente conexa.
    Se tiver mais de uma, já não é pois se temos duas, sejam A e B, isso significa
    que tem algum vértice em A do qual não é possível chegar em B. Logo, o grafo 
    não é fortemente conexo, mas apresenta componentes fortemente conexas;

    Para verificar isso, estamos utilizando o algoritmo de Tarjan (ACHO). A ideia
    é ir visitando os vértices e marcando em um vetor qual o 'menor' vértice possí-
    vel de se visitar partindo do vértice atual. Se todos marcarem o mesmo valor no
    final, então é fortemente conexo. 

    (?) - Todo grafo sem ciclo não é fortemente conexo, correto? SIM
    (?) - Um grafo fortemente conexo não pode ser ordenado topologicamente? SIM
        Consequência da resposta anterior;

    */

    //--------------------------------------------------------------------------
    /* PROBLEMA 12 //

    Ordenação Topológica - Ordenar os vértices de forma todo arco vai para frente,
    ou seja, não há nenhum arco de retorno. Não há ciclos.

    Para um grafo acíclico, com certeza deve existir um vértice de grau de entrada
    0, isto é, que não recebe nenhum arco, ou seja, não dá para chegar nele de vér-
    tice nenhum.

    Usando esse fato, podemos montar uma ordenação topológica excluindo o vértice
    de entrada 0 e analisando qual é o outro vértice de entrada zero após essa re-
    moção. 

    */

    //--------------------------------------------------------------------------
    /* PROBLEMA 13 //

    Como decidir de uma aresta entre dois vértices está em um ciclo ou não?
    Roda uma dfs naquele para a qual a aresta aponta e vê se você chega no outro vér-
    tice. Se chegar, então está num ciclo, se não chegar, então não esta. 

    */

   //--------------------------------------------------------------------------
    /* PROBLEMA 14 //

    Ordenação topológica - Dá para fazer com dfs... Veremos. 
    Mas também dá para fazer considerando os graus de entrada e saída de todos os
    vértices e ir 'removendo' aqueles com grau de entrada 0.
    */

    //--------------------------------------------------------------------------
    /* PROBLEMA 15 //

    Primeiro, eu ordeno topologicamente os vértices. Para cada vértice, na ordem 
    topológica eu faço o seguinte:  

    tam[order[0]] = 0; // O primeiro da ord. recebe o valor 0;
    Preenchi todo mundo com zero;
    int cont;

    for(int i = 0; i < V; i++) { 
        for(int v: adj[order[i]]) {
            if(tam[v] < tam[order[i]] + 1) {
                tam[v] = tam[order[i]] + 1;
                pred[v] = u;
                MAX = max(MAX, tam[v]);
                if(MAX == tam[v]) {
                    ini = v;
                }
            }
        }
    }


    */



    return 0;
}