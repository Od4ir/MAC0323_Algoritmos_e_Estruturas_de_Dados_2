<!-- omit in toc -->
# ✈️ EP1 - Simulador de um Gerenciamento de um Aeroporto

<!-- omit in toc -->
## 📑 índice:

- [📄 Descrição:](#-descrição)
- [🔗 Dependências:](#-dependências)
- [▶️ Executando o código:](#️-executando-o-código)
- [🧪 Como Testar:](#-como-testar)



## 📄 Descrição:

O algoritmo é um simulador de um sistema de gerenciamento de pousos e decolagens de aviões gerados aleatoriamente utilizando filas e pilhas com uma determinada estratégia para evitar atrasos e quedas. 


Para entender o melhor o projeto, considere ler:
- [Enunciado do EP1](#https://github.com/Od4ir/MAC0323_Algoritmos_e_Estruturas_de_Dados_2/blob/main/EP1/EP1_Enunciado.pdf);
- [Relatório do EP1](#https://github.com/Od4ir/MAC0323_Algoritmos_e_Estruturas_de_Dados_2/blob/main/EP1/EP1_Relatorio.pdf);


## 🔗 Dependências:
Todos os testes foram feitos em um computador com **arquitetura x86_64** com sistema operacional **Linux Ubuntu - 22.04.3 LTS**.
- **g++ (GNU C++ Compiler):** g++ (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0;


## ▶️ Executando o código:
Para compilar o código, basta digitar no terminal:
```bash
g++ EP1.cpp -o EP1
```
Para executar:
```bash
./EP1
```

## 🧪 Como Testar:

Ao executar o código, basta ler as instruções iniciais e colocar os valores dos parâmetros solicitados. Veja o exemplo abaixo:

```
///------------------------------------------------------///
///                     Olá Usuárix!                     ///
///   Bem vindx ao Gerenciador de Aeroportos do Od4ir    ///
///------------------------------------------------------///

/// Por favor, insira os dados da simulação: 
Tempo de Execução da Simulação >>>  10
Número Máximo de Aviões por unidade de tempo >>>  10
Número máximo de combustível por avião >>>   10
Número máximo de horas de voo por avião >>>   10
Porcentagem de aviões que irão pousar >>>   10
Porcentagem de aviões especiais >>>   10
```
Após isso, basta pressionar *enter* e verificar as informações da simulação a cada instante. Veja abaixo um exemplo das informações exibidas:

```
/// ------------- INICIO DA SIMULAÇÃO -------------- /// 

/// -------------- INSTANTE ATUAL: 0 --------------- /// 

 >>> 6 Aviões entraram em contato!

!!! ATENÇÃO !!! - Avião TA802 não foi colocado nas filas!
Inserindo na fila de emergência!
!!! ATENÇÃO !!! - Avião ET282 não foi colocado nas filas!
Inserindo na fila de emergência!
 ------------------ STATUS DAS FILAS: ------------------- 

 /// ----- PISTA 1: ----- /// 
 Há 2 aviões na fila!
 Interdição: 0!

 Avião: DQ023  Comb Atual: 2  Instante: 0 Tipo: Normal
 Avião: FR621  Comb Atual: 4  Instante: 0 Tipo: Normal

 /// ----- PISTA 2: ----- /// 
 Há 2 aviões na fila!
 Interdição: 0!

 Avião: HO786  Comb Atual: 1  Instante: 0 Tipo: Normal
 Avião: KV064  Comb Atual: 6  Instante: 0 Tipo: Normal

 /// ----- PISTA 3: ----- /// 
 Há 0 aviões na fila!
 Interdição: 0!


 ----------------- POUSOS E DECOLAGENS: -----------------  

Avião DQ023 pousando na pista 1!
    Tempo de Espera total p/ Pouso: 0
    Combustível restante no Pouso: 2
    Combustível inicial: 2

Avião HO786 pousando na pista 2!
    Tempo de Espera total p/ Pouso: 0
    Combustível restante no Pouso: 1
    Combustível inicial: 1

Aviões Pousados: 2
Aviões Decolados: 0

 ------------------------ MÉDIAS: -----------------------  

 >> Média de Combustível dos Aviões Esperando:............. 5
 >> Média de Combustível Restante nos Aviões Pousados:..... 1
 >> Média Tempo de Espera para Pouso....................... 0
 >> Média Tempo de Espera para Decolagem................... 0

 ----------------- !!! EMERGÊNCIAS !!! ------------------  

1 Avião: TA802  Comb Atual: 1  Instante: 0 Tipo: Normal
2 Avião: ET282  Comb Atual: 2  Instante: 0 Tipo: Normal
Situações críticas: 
 Avião TA802 em situação crítica!
Coloquei na pista vazia 3
Removi!
 Avião ET282 em situação crítica!
Removi!
Coloquei na pista 2

/// ------------ FIM INSTANTE ATUAL: 0 ------------- /// 
```