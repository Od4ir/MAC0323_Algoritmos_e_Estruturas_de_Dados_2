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

// >>> Insere um avião no começo da fila da Pista;
void Pista::insere_no_comeco(Avioes A) {
    Fila * novo_elemento = (Fila *) malloc(sizeof(Fila));
    novo_elemento->aviao = A;
    novo_elemento->ant = nullptr;
    novo_elemento->prox = fila;
    fila = novo_elemento;
    quantidade++;
}

// >>> Remove o primeiro elemento da fila da Pista;
void Pista::remove_primeiro() {
    Fila * aux = fila->prox;
    free(fila);
    fila = aux;
    quantidade--;
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

// Verifica se o avião pode ser colocado na posição 'pos':
int Avioes::simula_na_pos(int pos, int t, int time_interditada){
    if(type == 1) {
        return 0;
    }
    int aguenta = (time_comb + time_voo) - (t - inst) - (pos - 1)*3 - time_interditada;

    //cout << "Aguenta: " << aguenta << endl;

    if(aguenta >= 0) {
        return 1;
    }
    return 0;
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
        //cout << quantidade << endl;
        //cout << conta_posicoes(fila) << endl;
        //cout << "Posição " << quantidade - conta_posicoes(fila) + 1 << endl;
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
FilaP * insere_pista(FilaP * fila, Avioes A, Pista p1, Pista p2, Pista p3) {
    if(A.time_comb == 0) { /* É de Decolagem */
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
            fila = insere(fila, p1);
            fila = insere(fila, p2);
        }
        if(A.type == 1) {
            fila = insere(fila, p3);
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

// Dada uma posição, confere se o avião daquela posição pode ser empurrado para a próxima;
int simula_empurrar(Pista pista, int pos, int t, int time_interditada) {
    Fila * f;
    for(f = pista.fila; pista.quantidade - conta_posicoes(f) + 1 != pos && f != nullptr; f = f->prox);
    if(f != nullptr) { 
        // Quando sair do loop, estará na pos;
        //cout << "Posição: " << pista.quantidade - conta_posicoes(f) + 1 << endl;
        //cout << f->aviao.id << endl;
        //cout << "Comb " << f->aviao.time_comb + f->aviao.time_voo << endl;
        //cout << "Inst " << f->aviao.inst << endl;
        int teste = f->aviao.simula_na_pos(pos + 1, t, time_interditada);
        return teste;
    }
    return -1;
}

// >>> Devolve 0 se não der para colocar na pista;
// >>> Devolve POS em que é possível inserir na pista;
int simula_colocar_na_pista(Pista pista, Avioes aviao, int t) {
    int teste;
    if(aviao.type == 0) {
        int pos = pista.quantidade + 1;
        int achei = 0;
        while(pos != 0 && !achei) { 
            //cout << "Testando com " << pos << endl;
            teste = aviao.simula_na_pos(pos, t, pista.tempo_interditada);
            if(teste == 1 && !achei) {
                achei = 1;
            }
            else { 
                pos--;
            }
        }
        int aux = pos; 
        while(aux <= pista.quantidade) { 
            teste = simula_empurrar(pista, aux, t, pista.tempo_interditada);
            if(teste < 1) {
                return 0;
            }
            aux++;
        }
        return pos;
    }
    if(aviao.type == 1) {
        int aux = 1;
        while(aux <= pista.quantidade) {
            teste = simula_empurrar(pista, aux, t, pista.tempo_interditada);
            if(teste == 1) {
                aux++;
            }
            else {
                return 0;
            }
        }
    }
    return 1; 
} 


int main() { 
    int T, K;
    int C, V, pp, pe;
    cout << "Tempo de Execução da Simulação: \n >>>  ";
    cin >> T; 
    cout << "Número Máximo de Aviões por unidade de tempo: \n >>>  ";
    cin >> K;
    cout << "Número máximo de combustível por avião: \n >>>   ";
    cin >> C;
    cout << "Número máximo de horas de voo por avião: \n >>>   ";
    cin >> V;
    cout << "Porcentagem de aviões que irão pousar: \n >>>   ";
    cin >> pp;
    cout << "Porcentagem de aviões especiais: \n >>>   ";
    cin >> pe;

    cout << "------------- INICIO DA SIMULAÇÃO --------------" << endl << endl;

    int quant_avioes, nao_foi, ordem[3];
    Historico * hist = nullptr;
    Pista p1(1, 0, 0, nullptr), p2(2, 0, 0, nullptr), p3(3, 0, 0, nullptr);
    FilaP * pistas = nullptr;

    int media_comb_pouso_esperando, media_comb_pouso_pousados, media_espera_pouso, media_espera_decolagem, quantidade_emergencias;

    for(int i = 0; i < T; i++) {
        quant_avioes = rand()%K;

        cout << ">>> INSTANTE ATUAL: " << i + 1 << endl;
        printf(">> %d Aviões entraram em contato!\n\n", quant_avioes);

        int av = 0;
        while(av < quant_avioes) {
            Avioes aviao_aux = gera_aviao(C, V, pp, pe, i);
            hist = insere_em_hist(hist, aviao_aux, &nao_foi);
            if(nao_foi) {
                pistas = insere_pista(pistas, aviao_aux, p1, p2, p3);
                for(FilaP * p = pistas; p != nullptr; p = p->prox) {
                    //cout << "Pista " << p->pista.id << ": " << p->pista.quantidade << " Aviões" << endl;
                }
                int colocado = 0;

                while(pistas != nullptr && !colocado) {
                    int posicao = simula_colocar_na_pista(pistas->pista, aviao_aux, i);
                    if(posicao == 0) {
                        //cout << "Na pista " << pistas->pista.id << " não deu\n";
                        FilaP * aux = pistas->prox;
                        free(pistas);
                        pistas = aux;
                        //if(aux != nullptr) 
                            //cout << "   Próxima >>> " << pistas->pista.id << endl;
                    }
                    else {
                        if(pistas->pista.id == 1) {
                            cout << "Coloquei na Pista 1\n";
                            p1.fila = insere_em_pos(p1.fila, posicao, aviao_aux, p1.quantidade++);
                        }
                        else if(pistas->pista.id == 2) {
                            cout << "Coloquei na Pista 2\n";
                            p2.fila = insere_em_pos(p2.fila, posicao, aviao_aux, p2.quantidade++);  
                        }
                        else if(pistas->pista.id == 3) {
                            cout << "Coloquei na Pista 3\n";
                            p3.fila = insere_em_pos(p3.fila, posicao, aviao_aux, p3.quantidade++);
                        }
                        colocado = 1;
                    }
                }
                if(!colocado) {
                    cout << "!!! ATENÇÃO !!! - Avião " << aviao_aux.id << " não foi colocado!" << endl;
                    cout << "Combustível/Voo: " << aviao_aux.time_comb + aviao_aux.time_voo << endl;
                    cout << "Era do tipo " << aviao_aux.type << endl << endl;
                }
                av++;
            }
            pistas = nullptr;
        }

        cout << endl <<  " ---- STATUS DAS PISTAS ---- "  << endl << endl;

        Pista aux = p1;
        for(int i = 0; i < 3; i++) { 
            cout << " --- PISTA " << i + 1 << ": --- \n"; 
            cout << " Há " << aux.quantidade << " aviões!\n";
            cout << " Interdição: " << aux.tempo_interditada << "!\n\n";
            for(Fila *f = aux.fila; f != nullptr; f = f->prox) {
                cout << f->aviao.type << " Avião: " << f->aviao.id << "  Comb/Voo: " << f->aviao.time_comb + f->aviao.time_voo << endl;
            }
            cout << endl;
            if(i == 0) aux = p2;
            if(i == 1) aux = p3;
        } 

        // Pousar aviões e mandar aviões para decolagem;
        if(p1.quantidade != 0 && p1.tempo_interditada == 0 ) {
            p1.tempo_interditada == 3;
        }
        if(p2.quantidade != 0 && p2.tempo_interditada == 0 ) {
            p2.tempo_interditada == 3;
            // Pousa o avião da p2;
        }
        if(p3.quantidade != 0 && p3.tempo_interditada == 0 ) {
            p3.tempo_interditada == 3;
            // Pousa o avião da p3;
        }

        if(p1.tempo_interditada != 0) {
            p1.tempo_interditada--;   
        }
        if(p2.tempo_interditada != 0) {
            p2.tempo_interditada--;   
        }
        if(p3.tempo_interditada != 0) {
            p3.tempo_interditada--;   
        }


        char s;
        scanf("%c", &s);
    }
    return 0;
}





