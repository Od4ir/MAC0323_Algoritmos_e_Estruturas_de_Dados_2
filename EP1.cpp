#include <iostream>
#include <cstdlib>
#include <cstring>
#include "pistas.h"
using namespace std;

// Função para fabricar aviões: 
// Sobre o tipo: ]
//      - 0 e 1 (Normal e Especial)
Avioes::Avioes(char * id_aviao, char * info_voo, int comb, int voo, int tipo, int t) {
    for(int i = 0; i < 5; i++) {
        id[i] = id_aviao[i];
    } 
    for(int i = 0; i < 3; i++) {
        id_voo[i] = id_voo[i];
    } 
    type = tipo;
    time_comb = comb;
    time_voo = voo;
    inst = t;
}

// Função para gerar aviões aleatoriamente dado os parâmetros de entrada;
    // int C - Indica a quantidade máxima de Combustível;
    // int V - Indica a quantidade máxima de Tempo de Voo;
    // int pp - Um valor de 0 a 100 que indica a probabilidade de ser um pouso;
    //     pd - É igual a 100 - pd;
    // int pe - Um valor de 0 a 100 que indica a probabilidade de ser uma emergência;
Avioes Avioes::gera_aviao(int C, int V, int pp, int pe, int t) {
    char id_aviao[5], id_voo[3];
    int comb, voo, tipo, type;

    for(int i = 0; i < 2; i++) {
        id_aviao[i] = (char)(rand()%26 + 'A');
    }
    for(int i = 2; i < 5; i++) {
        id_aviao[i] = (char)(rand()%10 + 48);
    }

    for(int i = 0; i < 3; i++) {
        id_voo[i] = (char(rand()%26 + 'A'));
    }

    tipo = rand()%100;

    if(tipo <= pp) {        // Significa que é um Pouso;
        comb = rand()%C;
        voo = 0;
    }
    else {                  // Significa que é uma Decolagem;
        voo = rand()%V;
        voo = voo/10;
        comb = 0;
    }

    type = rand()%100;
    if(type <= pe) {        // Vai ser de Emergência;
        type = 1;
    }
    else {                  // Vai ser normal;
        type = 0;
    }

    Avioes aviao_novo(id_aviao, id_voo, comb, voo, type, t);
    return aviao_novo;
}

// Insere um avião novo na fila (No final dela);
Fila * Fila::insere_na_fila(Fila * fila, Avioes aviao, int pos, Fila * ant) {
    if(fila == nullptr) {
        fila = (Fila *) malloc(sizeof(Fila));
        fila->ant = (Fila *) malloc(sizeof(Fila));
        fila->ant = ant;
        fila->aviao = aviao;
        fila->pos = pos;
        fila->prox = nullptr;
        return fila;
    }
    else  {
        ant = fila;
        fila->prox = insere_na_fila(fila->prox, aviao, pos, ant);
        return fila;
    }
}

// Insere um avião novo na posição informada;
Fila * Fila::insere_na_fila_posicao(Fila * fila, Avioes aviao, int pos) {
    Fila * f = fila;

    // Caso da fila vazia:
    if(fila == nullptr) {
        fila = (Fila *) malloc(sizeof(Fila));
        fila->ant = (Fila *) malloc(sizeof(Fila));
        fila->ant = ant;
        fila->aviao = aviao;
        fila->pos = pos;
        fila->prox = nullptr;
        return fila;
    }

    Fila * aux = (Fila *) malloc(sizeof(Fila));
    for(f = fila; f->pos != pos && f->prox != nullptr; f = f->prox);

    if(pos == 1) {                    // Caso em que é adicionado na primeira posição;
        aux->ant = nullptr;
        aux->prox = fila;
        f->ant = aux;
        fila = fila->ant;
    }
    else if(f->prox == nullptr) {      
        if(f->pos == pos) {           // Caso em que é adicionado antes da penúltima;
            aux->ant = f->ant;
            aux->prox = f;
            f->ant->prox = aux;
            f->ant = aux;
        }
        else {                        // Caso em que é adicionado ao final da fila;
            aux->ant = f;
            f->prox = aux;
            f = aux->prox;
        }
    }
    else {                             // Caso em que é adicionado entre 2 aviões;
        aux->ant = f->ant;
        aux->prox = f;
        f->ant->prox = aux;
        f->ant = aux;
    }
    aux->aviao = aviao;
    aux->pos = pos;

    while(f != nullptr) {
        f->pos++;
        f = f->prox;
    }
    return fila;
}

// Remove o primeiro avião da fila;
Fila * Pistas::remove_o_primeiro(Pistas pista) {
    if(pista.fila == nullptr) {
        pista.quantidade = 0;
        return pista.fila;
    }
    Fila * f = pista.fila->prox;
    if(f != nullptr) { 
        f->ant = nullptr;
    }
    free(pista.fila);

    for(Fila * k = f; k != nullptr; k = k->prox) {
        k->pos--;
    }
    return f;
}

// Devolve o primeiro avião da fila;
Avioes Fila::primeiro_fila(Fila * fila) {
    Fila *f;
    for(f = fila; f != nullptr; f = f->ant) {
        if(f->ant == nullptr) {
            return f->aviao;
        }
    }
    return f->aviao;
}

// Devolve o avião que está na posição pos;
Avioes Fila::aviao_na_pos(Fila * fila, int pos) {
    Fila * f;
    for(f = fila; f != nullptr && f->pos != pos; f = f->prox);
    return f->aviao;
}


int Fila::simulacao(Pistas pista, Avioes A, int t) {
    int pos, teste;
    pos = pista.quantidade;
    if(A.type == 1) {
        while(pos >= 0) {
            Avioes B = pista.fila->aviao_na_pos(pista.fila, pos);
            teste = pista.fila->testando_com_pos(B, pos + 1, t);
            if(teste == 1) {
                pos--;
            }
            else {
                return 0;
            }
        }
        return 1;
    }
    else {
        int N = pos + 1;
        int achei = 0;
        while(!achei && N != 0) {
            teste = pista.fila->testando_com_pos(A, N, t);
            if(teste == 1) {
                achei = 1;
            }
            else {
                N--;
            }
        }
        // Ao sair do Loop teremos a posição máxima do avião;
        // Precisamos verificar se tudo bem colocar o avião ali;
        int aux = N;
        while(aux <= pista.quantidade) {
            Avioes B = pista.fila->aviao_na_pos(pista.fila, aux);
            teste = pista.fila->testando_com_pos(B, aux + 1, t);
            if(teste != 1) { 
                return 0;
            }
            aux++;
        }
        return N;
    }
}

// 
int Fila::testando_com_pos(Avioes A, int pos, int t) {
    if(A.type == 1) {
        return 0;
    }
    int aguenta = (A.time_comb + A.time_voo) - (t - A.inst) - (pos - 1)*3;
    if(t % 3 > 0) {
        aguenta = aguenta - (3 - t%3);
    }

    if(aguenta >= 0) {
        return 1;
    }
    return 0;
}

// Cria uma pista;
Pistas::Pistas(int id, int quant, int time, int stat) {
    id_pista = id;
    quantidade = quant;
    time_interditada = time;
    fila = nullptr;
    status = stat;
}

// Devolve o primeiro avião da fila;
Avioes Pistas::primeiro_pista(Pistas pista) {
    return pista.fila[0].aviao;
}

// Histórico de aviões já registrados;
Historico * Historico::insere_na_arvore(Historico * hist, Avioes A, int * v) {
    if(hist == nullptr) {
        hist = (Historico *) malloc(sizeof(Historico));
        hist->aviao = A;
        hist->dir = nullptr;
        hist->esq = nullptr;
        *v = 1;
        return hist;
    }
    int aux = strcmp(hist->aviao.id, A.id);
    cout << hist->aviao.id << endl;
    cout << A.id << endl;
    cout << "AUX = " << aux << endl;
    if(aux == 0) {
        *v = 0;  // Já foi;
    }
    else if(aux < 0) {
        *v = 1;
        hist->dir = insere_na_arvore(hist->dir, A, v);
    }
    else {
        *v = 1;
        hist->esq = insere_na_arvore(hist->esq, A, v);
    }
    return hist;
}

// Imprimindo lista de aviões já registrados em ordem alfabética;
void Historico::in_order(Historico * hist) {
    if(hist != nullptr) {
        in_order(hist->esq);
        cout << hist->aviao.id << endl;
        in_order(hist->dir);
    }
}

int main() { 
    int T, K, quant_avioes, verifica, colocado, teste;
    int C, V, pp, pe;
    Historico * hist = nullptr;
    cout << "Tempo de Execução da Simulação: \n >>>  ";
    cin >> T;  
    cout << endl;

    cout << "Número Máximo de Aviões por unidade de tempo: \n >>>  ";
    cin >> K;
    cout << endl;

    cin >> C;
    cin >> V;
    cin >> pp;
    cin >> pe;

    Pistas p1(1, 0, 0, 0), p2(2, 0, 0, 0), p3(3, 0, 0, 0);
    Fila * fila = nullptr;


    for(int i = 0; i < T; i++) {
        quant_avioes = rand()%K;
        cout << "INSTANTE ATUAL: " << i + 1 << endl << endl;
        printf("%d Aviões entraram em contato!\n", quant_avioes);

        for(int j = 0; j < quant_avioes; j++) {
            Avioes aux = aux.gera_aviao(C, V, pp, pe, i);

            hist = hist->insere_na_arvore(hist, aux, &verifica);
            if(verifica) {
                // ESTRATÉGIA PARA INSERÇÃO //
                /*if(aux.type == 1) {  // Se for ESPECIAL;
                    colocado = 0;
                    if(aux.time_comb == 0) {  // Se for de Decolagem;
                        Pistas aux_pista = p3;
                        teste = 0;
                        while(teste < 3 && !colocado) {
                            if(aux_pista.quantidade == 0) {
                                aux_pista.fila = aux_pista.fila->insere_na_fila_posicao(aux_pista.fila, aux, ++aux_pista.quantidade);
                                aux_pista.time_interditada += 3;
                                colocado = 1;
                            }
                            else {
                                
                            }
                        }

                    }
                } */
                if(i % 3 == 1) {
                    p1.fila = p1.fila->insere_na_fila(p1.fila, aux, ++p1.quantidade, p1.fila);
                    p1.time_interditada+= 3;
                }
                else if(i % 3 == 2) {
                    p2.fila = p2.fila->insere_na_fila(p2.fila, aux, ++p2.quantidade, p2.fila);
                    p2.time_interditada+= 3;
                }
                else {
                    p3.fila = p3.fila->insere_na_fila(p3.fila, aux, ++p3.quantidade, p3.fila);
                    p3.time_interditada+= 3;
                } 
            }
        }
        cout << endl;
    }

    Pistas aux = p1;
    
    for(int i = 0; i < 3; i++) { 
        cout << "Na Pista " << i + 1 << ": \n"; 
        cout << "Há " << aux.quantidade << " aviões!\n";
        cout << "Interdição: " << aux.time_interditada << "!\n";
        for(Fila *f = aux.fila; f != nullptr; f = f->prox) {
            cout << "Avião " << f->pos << ": " << f->aviao.id << endl;
        }
        if(i == 0) aux = p2;
        if(i == 1) aux = p3;
    } 

    char idd[5], idv[3];
    cin >> idd;
    cin >> idv;
    int combust;
    cin >> combust;
    cin >> 

    Avioes auxx()
    return 0;
}
