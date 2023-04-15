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

// >>> Remove o primeiro elemento da fila da Pista;
void Pista::remove_primeiro() {
    Fila * aux = fila->prox;
    free(fila);
    fila = aux;
    quantidade--;
}

Avioes Pista::remove_na_pos(int pos) {
    --quantidade;
    Fila * f, *anterior, * inicio;
    if(pos == 1) {
        Fila * auxf = fila->prox;
        Avioes aux = fila->aviao;
        free(fila);
        fila = auxf;
        return aux;
    }

    anterior = fila;
    for(f = fila; f->prox != nullptr && quantidade - conta_posicoes(f) + 1 != pos; f = f->prox) {
            anterior = f;
            //cout << quantidade - conta_posicoes(f) + 1 << " Avião: " << f->aviao.id << endl;
    }
    
    if(quantidade - conta_posicoes(f) + 1 == pos) {
        anterior->prox = f->prox;
        Avioes aux = f->aviao;
        free(f);
        return aux;
    }
    return fila->aviao;
}

// >>> Pousa ou decola o primeiro avião da fila e imprime as informações do mesmo;
void Pista::pousa_decola_primeiro_aviao(int * mcpp, int * mtep, int * med, int * quant_dec, int * quant_pou, int t) {
    int aux = 0, aux1 = 0;
    cout << "Avião " << fila->aviao.id;
    if(fila->aviao.time_comb != 0) {
        cout << " pousando na pista "; 
    }
    else { 
        cout << " decolando na pista ";
    }
    cout << id << "!" << endl;
    if(fila->aviao.time_comb == 0) {
        cout << "   Tempo de Espera total p/ Decolagem: " << t - fila->aviao.inst << endl;
        aux = (t - fila->aviao.inst);
        *quant_dec = *quant_dec + 1;
        *med = *med + aux;
    }
    else {
        cout << "    Tempo de Espera total p/ Pouso: " << t - fila->aviao.inst << endl;
        aux = t - fila->aviao.inst;
        aux1 = fila->aviao.time_comb - aux;
        *quant_pou = *quant_pou + 1;
        *mtep = *mtep + aux;
        *mcpp = *mcpp + aux1;
        cout << "    Combustível restante no Pouso: " << aux1 << endl;
        //cout << " Quantidade >>> " << *quant_pou;
    }
    cout << endl;
    remove_na_pos(1);
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
    /*if(pos == 2 && time_voo != 0) {
        return 1;
    }*/
    int aguenta = (time_comb + time_voo) - (t - inst) - (pos - 1)*3 - time_interditada;
    if(aguenta >= 0) {
        return 1;
    }
    return 0;
}

// FUNÇÕES GERAIS: ------------------------------------------------------

// Insesere um avião no fim da fila
Fila * insere2(Fila * f, Avioes A) {
    if(f == nullptr) {
        f = (Fila *) malloc(sizeof(Fila));
        f->prox = nullptr;
        f->aviao = A;
        return f;
    }
    f->prox = insere2(f->prox, A);
    //cout << "INSERINDO AVIÃO NOVO: " << A.id << endl;
    return f;
}

// Remove um avião A da fila f;
Fila * remove2(Fila * f, Avioes A) {
    Fila * aux, * anterior, * inicio;

    if(f ==  nullptr) {
        return nullptr;
    }
    if(strcmp(f->aviao.id, A.id) == 0) {
        aux = f->prox;
        free(f);
        cout << "Removi!\n";
        return aux;
    }

    inicio = f;
    anterior = f;

    for(aux = inicio->prox; aux->prox != nullptr && strcmp(aux->aviao.id, A.id) != 0; aux = aux->prox) {
        anterior = aux;
    }

    if(strcmp(aux->aviao.id, A.id) == 0) {
        //cout << "Achei " << A.id << endl;
        anterior->prox = aux->prox;
        free(aux);
    }
    return inicio;
}

void calcula_media_mcpe(FilaP * p, int t, int * mcpe) {
    Fila * f;
    int auxp = 0;
    int quanti_pouso = 0;
    while(p != nullptr) {
        for(f = p->pista.fila; f != nullptr; f = f->prox) {
            if(f->aviao.time_comb != 0) { // É um avião de pouso;
                auxp = auxp + f->aviao.time_comb - (t - f->aviao.inst);
                quanti_pouso++;
            }
        }
        p = p->prox;
    }
    if(quanti_pouso != 0) 
        *mcpe = (auxp / quanti_pouso);
    else *mcpe = 0;
}

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
    Fila * f, * anterior;
    if(pos > quantidade) {
        if(fila == nullptr) {
            fila = (Fila *) malloc(sizeof(Fila));
            fila->aviao = A;
            fila->prox = nullptr;
        }
        else { // Insere no final da fila;
            anterior = nullptr;
            Fila * novo_elemento = (Fila *) malloc(sizeof(Fila));
            novo_elemento->aviao = A;
            novo_elemento->prox = nullptr;
            for(f = fila; f != nullptr; anterior = f, f = f->prox);
            anterior->prox = novo_elemento;
        }
        return fila;
    }
    else if(pos == 1) {
        Fila * novo_elemento = (Fila *) malloc(sizeof(Fila));
        novo_elemento->aviao = A;
        novo_elemento->prox = fila;
        fila = novo_elemento;
    } 
    else {
        if(quantidade - conta_posicoes(fila) + 1 == pos) {
            Fila * novo_elemento = (Fila *) malloc(sizeof(Fila));
            novo_elemento->aviao = A;
            novo_elemento->prox = fila;
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
FilaP * insere_pista(FilaP * fila, Avioes A, Pista p1, Pista p2, Pista p3, int pp) {
    if(A.time_comb == 0) { /* É de Decolagem */
        if(pp >= 60) { 
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
            if(p1.quantidade > p2.quantidade) {
                if(p2.quantidade > p3.quantidade) {
                    fila = insere(fila, p3);
                    fila = insere(fila, p2);
                }
                else {
                    fila = insere(fila, p2);
                    fila = insere(fila, p3);
                }
                fila = insere(fila, p1);
            }
            else if(p2.quantidade > p3.quantidade) {
                if(p1.quantidade > p3.quantidade) {
                    fila = insere(fila, p3);
                    fila = insere(fila, p1);
                }
                else {
                    fila = insere(fila, p1);
                    fila = insere(fila, p3);
                }
                fila = insere(fila, p2);
            }
            else {
                fila = insere(fila, p1);
                fila = insere(fila, p2);
                fila = insere(fila, p3);
            }
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
    if(pos == 1) {
        int teste = pista.fila->aviao.simula_na_pos(2, t, pista.tempo_interditada);
        return teste;
    }
    for(f = pista.fila; pista.quantidade - conta_posicoes(f) + 1 != pos && f != nullptr; f = f->prox);
    if(f != nullptr) { 
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
    printf("///------------------------------------------------------///\n");
    printf("///                     Olá Usuárix!                     ///\n");
    printf("///   Bem vindx ao Gerenciador de Aeroportos do Od4ir    ///\n");
    printf("///------------------------------------------------------///\n\n");

    cout << "/// Por favor, insira os dados da simulação: \n";
    cout << "Tempo de Execução da Simulação >>>  ";
    cin >> T; 
    cout << "Número Máximo de Aviões por unidade de tempo >>>  ";
    cin >> K;
    cout << "Número máximo de combustível por avião >>>   ";
    cin >> C;
    cout << "Número máximo de horas de voo por avião >>>   ";
    cin >> V;
    cout << "Porcentagem de aviões que irão pousar >>>   ";
    cin >> pp;
    cout << "Porcentagem de aviões especiais >>>   ";
    cin >> pe;

    char start;
    scanf("%c", &start);

    cout << "\n\n/// ------------- INICIO DA SIMULAÇÃO -------------- /// " << endl << endl;

    // Filas e outras estruturas importantes: 
    Historico * hist = nullptr;
    Pista p1(1, 0, 0, nullptr), p2(2, 0, 0, nullptr), p3(3, 0, 0, nullptr);
    FilaP * pistas = nullptr;
    Fila * emergencias = nullptr;

    // Varíaveis auxiliares e varíaveis das estatísticas da simulação;
    int mcpe, mcpp = 0, mtep = 0, med = 0, quant_dec = 0, quant_pou = 0, q_emerg = 0, atrasados = 0, quedas = 0, desvios = 0, total_av = 0;
    int quant_avioes, nao_foi, av, colocado;

    // Início Oficial da Simulação:
    for(int i = 0; i < T; i++) {
        quant_avioes = rand()%K;

        printf("/// -------------- INSTANTE ATUAL: %d --------------- /// \n\n", i);
        printf(" >>> %d Aviões entraram em contato!\n\n", quant_avioes);

        av = 0;
        total_av = total_av + quant_avioes;
        while(av < quant_avioes) {
            // Gerando um avião aleatório:
            Avioes aviao_aux = gera_aviao(C, V, pp, pe, i);

            // Verificando se é um avião válido, isto é, se comb + voo != 0;
            if(aviao_aux.time_comb + aviao_aux.time_voo == 0) {
                // é um avião inválido;
                nao_foi = 0;
            }
            else {
                hist = insere_em_hist(hist, aviao_aux, &nao_foi);
                // Se o avião não for repetido, nao_foi tem o valor 1;
            }
            if(nao_foi) {
                pistas = insere_pista(pistas, aviao_aux, p1, p2, p3, pp);
                colocado = 0;

                while(pistas != nullptr && !colocado) {
                    int posicao = simula_colocar_na_pista(pistas->pista, aviao_aux, i);
                    if(posicao == 0) {
                        FilaP * aux = pistas->prox;
                        free(pistas);
                        pistas = aux;
                    }
                    else {
                        if(pistas->pista.id == 1) {
                            p1.fila = insere_em_pos(p1.fila, posicao, aviao_aux, p1.quantidade++);
                        }
                        else if(pistas->pista.id == 2) {
                            p2.fila = insere_em_pos(p2.fila, posicao, aviao_aux, p2.quantidade++);  
                        }
                        else if(pistas->pista.id == 3) {
                            p3.fila = insere_em_pos(p3.fila, posicao, aviao_aux, p3.quantidade++);
                        }
                        colocado = 1;
                    }
                }
                // Caso a estratégia inicial não insira o avião, ele entra na fila de emergências;
                if(!colocado) {
                    cout << "!!! ATENÇÃO !!! - Avião " << aviao_aux.id << " não foi colocado nas filas!" << endl;
                    cout << "Inserindo na fila de emergência!" << endl;
                    emergencias = insere2(emergencias, aviao_aux);
                }
                av++;
            }
            pistas = nullptr;
        }

        printf(" ------------------ STATUS DAS FILAS: ------------------- \n\n");


        Pista aux = p1;
        for(int j = 0; j < 3; j++) { 
            cout << " /// ----- PISTA " << j + 1 << ": ----- /// \n"; 
            cout << " Há " << aux.quantidade << " aviões na fila!\n";
            cout << " Interdição: " << aux.tempo_interditada << "!\n\n";
            for(Fila *f = aux.fila; f != nullptr; f = f->prox) {
                cout << " Avião: " << f->aviao.id;
                if(f->aviao.time_comb != 0) 
                    cout << "  Comb Atual: " << f->aviao.time_comb - (i - f->aviao.inst);
                else 
                    cout << "  Voo Atual: " << f->aviao.time_voo - (i - f->aviao.inst);
                cout << "  Instante: " << f->aviao.inst << " Tipo: ";
                if(f->aviao.type == 1) cout << "Especial";
                else cout << "Normal";
                cout << endl;
            }
            cout << endl;
            if(j == 0) aux = p2;
            if(j == 1) aux = p3;
        } 

        printf(" ----------------- POUSOS E DECOLAGENS: -----------------  \n\n");

        // Pousar aviões e mandar aviões para decolagem;
        if(p1.quantidade != 0 && p1.tempo_interditada == 0 ) {
            p1.tempo_interditada = 3;
            if(p1.fila->aviao.time_voo -  (i - p1.fila->aviao.inst) < 0 && p1.fila->aviao.time_voo != 0) {
                atrasados++;
            }
            else if(p1.fila->aviao.time_comb - (i - p1.fila->aviao.inst) < 0 && p1.fila->aviao.time_comb != 0) {
                quedas++;
            }
            p1.pousa_decola_primeiro_aviao(&mcpp, &mtep, &med, &quant_dec, &quant_pou, i);
        }
        if(p2.quantidade != 0 && p2.tempo_interditada == 0 ) {
            p2.tempo_interditada = 3;
            if(p2.fila->aviao.time_voo -  (i - p2.fila->aviao.inst) < 0  && p2.fila->aviao.time_voo != 0) {
                atrasados++;
            }
            else if(p2.fila->aviao.time_comb - (i - p2.fila->aviao.inst) < 0 && p2.fila->aviao.time_comb != 0) {
                quedas++;
            }
            p2.pousa_decola_primeiro_aviao(&mcpp, &mtep, &med, &quant_dec, &quant_pou, i);
        }
        if(p3.quantidade != 0 && p3.tempo_interditada == 0 ) {
            p3.tempo_interditada = 3;
            if(p3.fila->aviao.time_voo -  (i - p3.fila->aviao.inst) < 0  && p3.fila->aviao.time_voo != 0) {
                atrasados++;
            }
            else if(p3.fila->aviao.time_comb - (i - p3.fila->aviao.inst) < 0  && p3.fila->aviao.time_comb != 0) {
                quedas++;
            }
            p3.pousa_decola_primeiro_aviao(&mcpp, &mtep, &med, &quant_dec, &quant_pou, i);
        }
        cout << "Aviões Pousados: " << quant_pou << endl;
        cout << "Aviões Decolados: " << quant_dec << endl << endl;


        printf(" ------------------------ MÉDIAS: -----------------------  \n\n");

        mcpe = 0;
        pistas = insere(pistas, p1);
        pistas = insere(pistas, p2);
        pistas = insere(pistas, p3);
        calcula_media_mcpe(pistas, i, &mcpe);
        cout << " >> Média de Combustível dos Aviões Esperando:............. " << mcpe << endl;
        cout << " >> Média de Combustível Restante nos Aviões Pousados:..... " << mcpp << endl;
        cout << " >> Média Tempo de Espera para Decolagem................... " << med << endl;
        cout << " >> Média Tempo de Espera para Pouso....................... " << mtep << endl << endl;

        if(p1.tempo_interditada != 0) {
            p1.tempo_interditada--;   
        }
        if(p2.tempo_interditada != 0) {
            p2.tempo_interditada--;   
        }
        if(p3.tempo_interditada != 0) {
            p3.tempo_interditada--;   
        }

        int quant_emergencias = 0, tirei = 0;

        printf(" ----------------- !!! EMERGÊNCIAS !!! ------------------  \n\n");
        int cont = 0;
        for(Fila * x = emergencias; x != nullptr; x = x->prox) {
                cout << ++cont << " Avião: " << x->aviao.id;
                if(x->aviao.time_comb != 0) 
                    cout << "  Comb Atual: " << x->aviao.time_comb - (i - x->aviao.inst);
                else 
                    cout << "  Voo Atual: " << x->aviao.time_voo - (i - x->aviao.inst);
                cout << "  Instante: " << x->aviao.inst << " Tipo: ";
                if(x->aviao.type == 1) cout << "Especial";
                else cout << "Normal";
                cout << endl;
        }
        if(emergencias == nullptr) {
            cout << "Sem aviões na fila de emergência! UFA!" << endl << endl;
        }
        else { 
            Fila * x = emergencias, *anterior = nullptr;
            while(x != nullptr && cont > 0) { 
                tirei = 0;
                //cout << "Avião atual: " << x->aviao.id << endl;
                if(x->aviao.time_comb + x->aviao.time_voo - (i - x->aviao.inst) <= 2 || x->aviao.type == 1) {
                    quant_emergencias++;
                    FilaP * aux = nullptr;

                    cout << " Avião " << x->aviao.id << " em situação crítica!" << endl;

                    for(FilaP * y = pistas; y != nullptr; y = y->prox) {
                        if(y->pista.quantidade == 0) {
                            cout << "Coloquei na pista vazia " << y->pista.id << endl;
                            if(y->pista.id == 1) {
                                p1.fila = insere_em_pos(p1.fila, 1, x->aviao, p1.quantidade);
                                p1.quantidade++;
                            }  
                            else if(y->pista.id == 2) {
                                p2.fila = insere_em_pos(p2.fila, 1, x->aviao, p2.quantidade);
                                p2.quantidade++;
                            }
                            else {
                                p3.fila = insere_em_pos(p3.fila, 1, x->aviao, p3.quantidade);
                                p3.quantidade++;
                            }
                            emergencias = remove2(emergencias, x->aviao);
                            tirei = 1;
                            break;
                        }
                        else {
                            int empurrar = simula_empurrar(y->pista, 1, i, y->pista.tempo_interditada);
                            //cout << "Empurrar " << y->pista.id << " deu " << empurrar << endl;

                            if(empurrar >= 1 && (x->aviao.time_comb - (i - x->aviao.inst) - y->pista.tempo_interditada >= 0 || x->aviao.time_voo != 0 )) {
                                //cout << "Aguenta!" << endl;
                                tirei = 0;
                                if(y->pista.id == 1) 
                                    aux = insere(aux, p1);
                                else if(y->pista.id == 2) 
                                    aux = insere(aux, p2);
                                else aux = insere(aux, p3);
                            }
                            else {
                                quant_emergencias++;
                            }
                        }
                    }
                    int teste = 1;
                    while(aux != nullptr && !tirei) {
                        int pos_atu = 1;
                        while(pos_atu <= aux->pista.quantidade && !tirei) {

                            teste = simula_empurrar(aux->pista, pos_atu, i, aux->pista.tempo_interditada);

                            //cout << "Teste: " << teste << " com pista " << aux->pista.id << "na pos: " << pos_atu << endl;
                            if(teste == 1) {
                                pos_atu++;
                                if(pos_atu > aux->pista.quantidade) {
                                    if(aux->pista.id == 1) {
                                        p1.fila = insere_em_pos(p1.fila, 1, x->aviao, p1.quantidade);
                                        p1.quantidade++;
                                    }
                                    else if(aux->pista.id == 2) {
                                        p2.fila = insere_em_pos(p2.fila, 1, x->aviao, p2.quantidade);
                                        p2.quantidade++;
                                    }
                                    else {
                                        p3.fila = insere_em_pos(p3.fila, 1, x->aviao, p3.quantidade);
                                        p3.quantidade++;
                                    }
                                    tirei = 1;
                                    emergencias = remove2(emergencias, x->aviao);

                                    //cout << x->aviao.id << endl;
                                    cout << "Coloquei na pistaaa " << aux->pista.id << endl;
                                }
                            }
                            else if(pos_atu != 1) {
                                if(aux->pista.id == 1) {
                                    p1.fila = insere_em_pos(aux->pista.fila, 1, x->aviao, aux->pista.quantidade++);
                                    p1.quantidade++;
                                    //cout << "POS ATUAL:" << pos_atu << endl;
                                    emergencias = insere2(emergencias, p1.remove_na_pos(pos_atu));
                                }
                                else if(aux->pista.id == 2) {
                                    p2.fila = insere_em_pos(aux->pista.fila, 1, x->aviao, aux->pista.quantidade++);
                                    p2.quantidade++;
                                    emergencias = insere2(emergencias, p2.remove_na_pos(pos_atu));
                                }
                                else {
                                    p3.fila = insere_em_pos(aux->pista.fila, 1, x->aviao, aux->pista.quantidade++);
                                    p3.quantidade++;
                                    emergencias = insere2(emergencias, p3.remove_na_pos(pos_atu));
                                }
                                emergencias = remove2(emergencias, x->aviao);
                                cout << "Coloquei na pista " << aux->pista.id << endl;
                                tirei = 1;
                            }
                        }
                        aux = aux->prox;
                    }
                    pistas = nullptr;
                    pistas = insere(pistas, p1);
                    pistas = insere(pistas, p2);
                    pistas = insere(pistas, p3);
                    quant_emergencias = 0;
                    if(tirei != 1 && x->aviao.time_voo == 0) {
                        if(x->aviao.time_comb - (i - x->aviao.inst) <= 0) {
                            quedas++;
                            cout << "Avião " << x->aviao.id << " caiu!" << endl;
                            cout << " Combustível inicial: " << x->aviao.time_comb << endl;
                        }
                        else { 
                            cout << "Mandando Avião " << x->aviao.id << " para outro aeroporto!" << endl;
                            desvios++;
                        }
                        emergencias = remove2(emergencias, x->aviao);
                        if(emergencias == nullptr) {
                            x = nullptr;
                        }
                        else if(emergencias->prox !=  nullptr) {
                                if(anterior != nullptr) {
                                    x = anterior->prox;
                                }
                                else {
                                    x = emergencias;
                                } 
                        }
                        else {
                            x = emergencias;
                        }
                    }
                    else {
                        if(tirei == 1) {
                            //cout << "JA BOTEI\n";
                            if(emergencias == nullptr) {
                                cout << "É null\n";
                                x = nullptr;
                            }
                            else if(emergencias->prox !=  nullptr) {
                                if(anterior != nullptr) {
                                    x = anterior->prox;
                                }
                                else {
                                    x = emergencias;
                                } 
                            }
                            else {
                                x = emergencias;
                            }
                        }
                        else {
                            cout << "Ainda está na fila\n";
                            x = x->prox;
                        }
                    }
                }
                else {
                    anterior = x;
                    x = x->prox;
                }
                cont--;
            }
        }
        printf("/// ------------ FIM INSTANTE ATUAL: %d ------------- /// \n\n\n", i);
        cout << endl;
        pistas = nullptr;

        char s;
        scanf("%c", &s);
    }
    cout << "/// -------------- FIM DA SIMULAÇÃO ---------------- /// " << endl;
    cout << "Estatísticas finais: " << endl;
    cout << " >> Aviões que entraram em contato:...................... " << total_av << endl;
    cout << " >> Média de Combustível dos Aviões Esperando:........... " << mcpe << endl;
    cout << " >> Média de Combustível Restante nos Aviões Pousados:... " << mcpp << endl;
    cout << " >> Média Tempo de Espera para Decolagem................. " << med << endl;
    cout << " >> Média Tempo de Espera para Pouso..................... " << mtep << endl;
    cout << " >> Quedas............................................... " << quedas << endl;
    cout << " >> Decolagens Atrasadas................................. " << atrasados << endl;
    cout << " >> Pousos:.............................................. " << quant_pou << endl;
    cout << " >> Decolagens:.......................................... " << quant_dec << endl;
    cout << " >> Desvios:............................................. " << desvios << endl << endl;

    return 0;
}





