#include <iostream>
#include <cstdlib>
#include <cstring>
#include "aeroporto.h"
using namespace std;

// FUNÇÕES CLASS PISTA: -------------------------------------------------
// >>> Cria um objeto do tipo Pista:
Pista::Pista(int id_pista, int quant, int time, Fila * f) {
    id = id_pista;
    quantidade = quant;
    tempo_interditada = time;
    fila = f;
}

// >>> Insere um avião no fim da fila da Pista;
void Pista::insere_no_fim(Avioes A) {
    Fila * f;
    if(fila == nullptr) {
        fila = (Fila *) malloc(sizeof(Fila));
        fila->aviao = A;
        fila->ant = nullptr;
    }
    else { 
        for(f = fila; f->prox != nullptr; f = f->prox);
        f->prox = (Fila *) malloc(sizeof(Fila));
        f->prox->aviao = A;
        f->prox->ant = f;
    }
    quantidade++;
}

// >>> Insere um avião na posiçao x da fila da Pista; 
Fila * insere_em_pos(Fila * fila, int pos, Avioes A, int quantidade) {
    Fila * f;
    if(pos > quantidade) {
        if(fila == nullptr) {
            fila = (Fila *) malloc(sizeof(Fila));
            fila->aviao = A;
            fila->ant = nullptr;
            fila->prox = nullptr;
        }
        else { 
            for(f = fila; f->prox != nullptr; f = f->prox);
            f->prox = (Fila *) malloc(sizeof(Fila));
            f->prox->aviao = A;
            f->prox->ant = f;
        }
    }
    else if(pos == 1) {
        Fila * novo_elemento = (Fila *) malloc(sizeof(Fila));
        novo_elemento->aviao = A;
        novo_elemento->ant = nullptr;
        novo_elemento->prox = fila;
        fila = novo_elemento;
    } 
    else {
        cout << quantidade << endl;
        cout << conta_posicoes(fila) << endl;
        cout << "Posição " << quantidade - conta_posicoes(fila) + 1 << endl;
        if(quantidade - conta_posicoes(fila) + 1 == pos) {
            Fila * novo_elemento = (Fila *) malloc(sizeof(Fila));
            novo_elemento->aviao = A;
            novo_elemento->prox = fila;
            novo_elemento->ant = fila->ant;
            fila->ant = novo_elemento;
            return novo_elemento;
        }
        fila->prox = insere_em_pos(fila->prox, pos, A, quantidade);
    }
    return fila;
} 

// >>> Insere um avião no começo da fila da Pista;
void Pista::insere_no_comeco(Avioes A) {
    Fila * novo_elemento = (Fila *) malloc(sizeof(Fila));
    novo_elemento->aviao = A;
    novo_elemento->ant = nullptr;
    novo_elemento->prox = fila;
    fila = novo_elemento;
    quantidade++;
}

// FUNÇÕES CLASS AVIOES: ------------------------------------------------
// >>> Cria um objeto do tipo Avioes:
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

// FUNÇÕES GERAIS: ------------------------------------------------------

// >>> Conta quantos objetos estão na fila;
int conta_posicoes(Fila * fila) {
    if(fila == nullptr) {
        return 0;
    }
    return(1 + conta_posicoes(fila->prox));
}

// >>> Gera um avião com dados aleatórios;
Avioes gera_aviao(int C, int V, int pp, int pe, int t) {
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

// >>> Insere uma pista px na fila de pistas;
FilaP * insere(FilaP * fila, Pista px) {
    if(fila == nullptr) {
        fila = (FilaP *) malloc(sizeof(FilaP));
        fila->pista = px;
        fila->prox = nullptr;
        return fila;
    }
    fila->prox = insere(fila->prox, px);
    return fila;
}

// >>> Insere as pistas ordenadas na fila de pistas;
FilaP * insere_pista(FilaP * fila, int tipo, Pista p1, Pista p2, Pista p3) {
    if(tipo == 0) { /* É de Decolagem */
        fila = insere(fila, p3);
        if(p2.quantidade < p1.quantidade) {
            fila = insere(fila, p2);
            fila = insere(fila, p1);
        }
        else {
            fila = insere(fila, p1);
            fila = insere(fila, p2);
        }
    }
    else {
        if(p2.quantidade < p1.quantidade) {
            fila = insere(fila, p2);
            fila = insere(fila, p1);
        }
        else {
            fila = insere(fila, p2);
            fila = insere(fila, p1);
        }
    }
    return fila;
}

// >>> Insere um avião novo no histórico de aviões;
// >>> Devolve em v - 1 se o avião é novo, 0 se é repetido;
Historico * insere_em_hist(Historico * hist, Avioes A, int * v) {
    if(hist == nullptr) {
        hist = (Historico *) malloc(sizeof(Historico));
        hist->aviao = A;
        hist->dir = nullptr;
        hist->esq = nullptr;
        *v = 1;
        return hist;
    }
    int aux = strcmp(hist->aviao.id, A.id);
    if(aux == 0) {
        *v = 0;  // Já foi;
    }
    else if(aux < 0) {
        *v = 1;
        hist->dir = insere_em_hist(hist->dir, A, v);
    }
    else {
        *v = 1;
        hist->esq = insere_em_hist(hist->esq, A, v);
    }
    return hist;
}

// >>> Devolve 0 se não der para colocar na pista;
// >>> Devolve POS em que é possível inserir na pista;
/* int simula_colocar_na_pista(Pista pista, Avioes aviao) {
    if(aviao.type == 0) {
        int pos = conta_posicoes(pista.fila);
        while(pos != 0) {

        }


    }
    if(aviao.type == 1) {

    }
} */


int main() { 
    int T, K;
    int C, V, pp, pe;
    cout << "Tempo de Execução da Simulação: \n >>>  ";
    cin >> T; 
    cout << endl; 

    cout << "Número Máximo de Aviões por unidade de tempo: \n >>>  ";
    cin >> K;
    cout << endl;

    cout << "Número máximo de combustível por avião: \n >>>   ";
    cin >> C;
    cout << "Número máximo de horas de voo por avião: \n >>>   ";
    cin >> V;
    cout << "Porcentagem de aviões que irão pousar: \n >>>   ";
    cin >> pp;
    cout << "Porcentagem de aviões especiais: \n >>>   ";
    cin >> pe;

    int quant_avioes, nao_foi, ordem[3];
    Historico * hist = nullptr;
    Pista p1(1, 0, 0, nullptr), p2(2, 0, 0, nullptr), p3(3, 0, 0, nullptr);
    FilaP * pistas = nullptr;

    for(int i = 0; i < T; i++) {
        quant_avioes = rand()%K;

        cout << "INSTANTE ATUAL: " << i + 1 << endl << endl;
        printf("%d Aviões entraram em contato!\n", quant_avioes);

        int av = 0;
        while(av < quant_avioes) {
            Avioes aviao_aux = gera_aviao(C, V, pp, pe, i);

            hist = insere_em_hist(hist, aviao_aux, &nao_foi);
            if(nao_foi) {

                printf("Inserindo Avião %s \n", aviao_aux.id);
                cout << "  Comb: " << aviao_aux.time_comb << endl;
                cout << "  Tipo: " << aviao_aux.type << endl << endl;

                pistas = insere_pista(pistas, aviao_aux.time_comb, p1, p2, p3);
                int colocado = 0;

                if(i == 0) {
                    cout << aviao_aux.id << endl;
                    p3.fila = insere_em_pos(p3.fila, 1, aviao_aux, p3.quantidade);
                    cout << "Há " << ++p3.quantidade << " na p3\n";
                } 
                else if(i % 3 == 0) {
                    cout << aviao_aux.id << endl;
                    p3.fila = insere_em_pos(p3.fila, p3.quantidade + 1, aviao_aux, p3.quantidade);
                    cout << "Há " << ++p3.quantidade << " na p3\n"; 
                }
                if(i % 8 == 0 && i != 0) {
                    cout << "COMECEI AQUIIIII\n\n";
                    cout << p3.quantidade << endl;
                    cout << conta_posicoes(p3.fila) << endl;

                    for(Fila * p = p3.fila; p != nullptr; p = p->prox) {
                        cout << p->aviao.id << endl;
                    }

                    p3.fila = insere_em_pos(p3.fila, p3.quantidade, aviao_aux, p3.quantidade);
                    cout << "Há here " << ++p3.quantidade << " na p3\n"; 
                } 

                /*if(i == 0) {
                    cout << aviao_aux.id << endl;
                    p3.insere_em_pos(aviao_aux, 1);
                    cout << "Há " << p3.quantidade << " na p3\n";
                }
                else if(i % 3 == 0) { 
                    p3.insere_em_pos(aviao_aux, p3.quantidade + 1);
                    cout << "Inseriu no final: " << aviao_aux.id << endl;
                    cout << "Há " << p3.quantidade << " na p3\n";
                }
                else if(i % 8 == 0 && p3.quantidade <= 7 ) {
                    p3.insere_em_pos(aviao_aux, 2);
                }
                for(FilaP * p = pistas; p != nullptr; p = p->prox) {
                    cout << p->pista.id << endl;
                }
                cout << endl; 

                pistas = nullptr; */
                av++;
            }
        }
    }
    for(Fila * p = p3.fila; p != nullptr; p = p->prox) {
        cout << p->aviao.id << endl;
    }
    return 0;
}





