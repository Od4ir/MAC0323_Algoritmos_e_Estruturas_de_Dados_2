<!-- omit in toc -->
# 🧬 EP3 - Algoritmo Eurístico de Montagem de Fita de DNA;

<!-- omit in toc -->
## 📑 índice:

- [📄 Descrição:](#-descrição)
- [🔗 Dependências:](#-dependências)
- [▶️ Executando o código:](#️-executando-o-código)
- [🧪 Como Testar:](#-como-testar)
  - [Código Principal (EP3):](#código-principal-ep3)
  - [Código de geração de testes (make\_teste.cpp):](#código-de-geração-de-testes-make_testecpp)



## 📄 Descrição:
O objetivo do EP3 foi simular o trabalho de decodificar e remontar fitas de DNA a partir de pedaços de DNA gerados aleatoriamente. A ideia era utilizar algum algotimo que fosse capaz de encontrar padrões em comum entre os sufixos e prefixos das fitas (arquivos de texto com as letras A, C, G, T) tentando encaixá-las juntas para recompor a fita original a fim de montar a maior fita possível no final. Para tal processo, era necessária aplicar uma estratégia eurística, descrita de maneira mais detalhada no relatório do EP3, disponível abaixo:

Para entender o melhor o projeto, considere ler:
- [Enunciado do EP3](#link);
- [Relatório do EP3](#link);



## 🔗 Dependências:
Todos os testes foram feitos em um computador com **arquitetura x86_64** com sistema operacional **Linux Ubuntu - 22.04.3 LTS**.
- **g++ (GNU C++ Compiler):** g++ (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0;


## ▶️ Executando o código:
Para compilar o código, basta digitar no terminal:
```bash
g++ EP3.cpp -o EP3
```
Para executar:
```bash
./EP3
```

Para compilar e executar o código para produzir arquivos de teste:
```bash
g++ make_teste.cpp -o make
```
Para executar:
```bash
./make
```

## 🧪 Como Testar:

### Código Principal (EP3):
Para testar o código principal (EP3.cpp), basta compilá-lo e executá-lo como descrito anteriormente, colocar um arquivo de teste (Note que tem vários disponíveis na pasta Testes) na mesma pasta dos códigos, digitar o nome do arquivo quando solicitado na execução, aguardar o fim do processo e verificar os resultados.

Veja abaixo um exemplo de execução com o arquivo "teste1.txt":

```
-----------/// BEM VINDX AO EP3 - Od4ir ///-----------


Olá biologx, digite o nome do arquivo com os pedaços de DNA:
 >> teste1.txt

 Deseja imprimir os dados? S/N: 
 >> S

 DNA Original: TGCTCTGACC
 Número de cópias..............10
 Número de substrings..........20
 Substrings: 
  0: GACC
  1: GACC
  2: GACC
  3: GACC
  4: GACC
  5: TGACC
  6: TGACC
  7: TGACC
  8: TGACC
  9: TGACC
  10: TGCTC
  11: TGCTC
  12: TGCTC
  13: TGCTC
  14: TGCTC
  15: TGCTCT
  16: TGCTCT
  17: TGCTCT
  18: TGCTCT
  19: TGCTCT


---------/// PARTE 2 - MONTAGEM DOS ARCOS ///----------

Maior fita: 6
Menor fita: 4
Escolha o parâmetro K: 
3

Deseja imprimir as arestas e seus pesos? S/N: 
 >> S
 [1] - Por vértice; 
 [2] - Ordenadas por peso
 >> 1


------------------/// IMPRESSÃO ///-------------------

 0: GACC
  Grau de saída: 4
  Grau de entrada: 5
  >1: GACC(4)
  >2: GACC(4)
  >3: GACC(4)
  >4: GACC(4)
 1: GACC
  Grau de saída: 3
  Grau de entrada: 6
  >2: GACC(4)
  >3: GACC(4)
  >4: GACC(4)
 2: GACC
  Grau de saída: 2
  Grau de entrada: 7
  >3: GACC(4)
  >4: GACC(4)
 3: GACC
  Grau de saída: 1
  Grau de entrada: 8
  >4: GACC(4)
 4: GACC
  Grau de saída: 0
  Grau de entrada: 9
 5: TGACC
  Grau de saída: 9
  Grau de entrada: 0
  >6: TGACC(5)
  >7: TGACC(5)
  >8: TGACC(5)
  >9: TGACC(5)
  >0: GACC(4)
  >1: GACC(4)
  >2: GACC(4)
  >3: GACC(4)
  >4: GACC(4)
 6: TGACC
  Grau de saída: 8
  Grau de entrada: 1
  >7: TGACC(5)
  >8: TGACC(5)
  >9: TGACC(5)
  >0: GACC(4)
  >1: GACC(4)
  >2: GACC(4)
  >3: GACC(4)
  >4: GACC(4)
 7: TGACC
  Grau de saída: 7
  Grau de entrada: 2
  >8: TGACC(5)
  >9: TGACC(5)
  >0: GACC(4)
  >1: GACC(4)
  >2: GACC(4)
  >3: GACC(4)
  >4: GACC(4)
 8: TGACC
  Grau de saída: 6
  Grau de entrada: 3
  >9: TGACC(5)
  >0: GACC(4)
  >1: GACC(4)
  >2: GACC(4)
  >3: GACC(4)
  >4: GACC(4)
 9: TGACC
  Grau de saída: 5
  Grau de entrada: 4
  >0: GACC(4)
  >1: GACC(4)
  >2: GACC(4)
  >3: GACC(4)
  >4: GACC(4)
 10: TGCTC
  Grau de saída: 9
  Grau de entrada: 0
  >11: TGCTC(5)
  >12: TGCTC(5)
  >13: TGCTC(5)
  >14: TGCTC(5)
  >15: TGCTCT(5)
  >16: TGCTCT(5)
  >17: TGCTCT(5)
  >18: TGCTCT(5)
  >19: TGCTCT(5)
 11: TGCTC
  Grau de saída: 8
  Grau de entrada: 1
  >12: TGCTC(5)
  >13: TGCTC(5)
  >14: TGCTC(5)
  >15: TGCTCT(5)
  >16: TGCTCT(5)
  >17: TGCTCT(5)
  >18: TGCTCT(5)
  >19: TGCTCT(5)
 12: TGCTC
  Grau de saída: 7
  Grau de entrada: 2
  >13: TGCTC(5)
  >14: TGCTC(5)
  >15: TGCTCT(5)
  >16: TGCTCT(5)
  >17: TGCTCT(5)
  >18: TGCTCT(5)
  >19: TGCTCT(5)
 13: TGCTC
  Grau de saída: 6
  Grau de entrada: 3
  >14: TGCTC(5)
  >15: TGCTCT(5)
  >16: TGCTCT(5)
  >17: TGCTCT(5)
  >18: TGCTCT(5)
  >19: TGCTCT(5)
 14: TGCTC
  Grau de saída: 5
  Grau de entrada: 4
  >15: TGCTCT(5)
  >16: TGCTCT(5)
  >17: TGCTCT(5)
  >18: TGCTCT(5)
  >19: TGCTCT(5)
 15: TGCTCT
  Grau de saída: 4
  Grau de entrada: 5
  >16: TGCTCT(6)
  >17: TGCTCT(6)
  >18: TGCTCT(6)
  >19: TGCTCT(6)
 16: TGCTCT
  Grau de saída: 3
  Grau de entrada: 6
  >17: TGCTCT(6)
  >18: TGCTCT(6)
  >19: TGCTCT(6)
 17: TGCTCT
  Grau de saída: 2
  Grau de entrada: 7
  >18: TGCTCT(6)
  >19: TGCTCT(6)
 18: TGCTCT
  Grau de saída: 1
  Grau de entrada: 8
  >19: TGCTCT(6)
 19: TGCTCT
  Grau de saída: 0
  Grau de entrada: 9

---------------/// FIM IMPRESSÃO /// -----------------



-------------/// PARTE 3 - RESPOSTAS ///---------------


Deseja imprimir a ordenação topológica? S/N 
 >> S
Ordenação Topológica: 
10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 5 - 6 - 7 - 8 - 9 - 0 - 1 - 2 - 3 - 4 - 

Tamanho previsto: 10
Tamanho real: 10

PRONTO PARA A RESPOSTA? (Digite qualquer coisa)
SIIIIMMM


Caminho máximo saindo de 5: TGACC
Tamanho: 5
Diferença Mínima: 5


Caminho máximo saindo de 10: TGCTC
Tamanho: 6
Diferença Mínima: 4

---------------/// RESPOSTA FINAL /// ----------------

Deu um valor menor que o previsto
Diferença: 4

Original  --> TGCTCTGACC
Resposta  --> TGCTCT
Tamanho final...................6
Tamanho original................10
```

### Código de geração de testes (make_teste.cpp):
Para testar o código gerador de testes (make_teste.cpp) basta compilá-lo e executá-lo como descrito anteriormente, preencher os parâmetros solicitados na execução para a produção do arquivo e verificar a criação dele ao final da execução com o nome criado. Lembrando que os arquivos processados são todos '.txt', então é necessário adicionar o '.txt' ao final do nome do novo arquivo teste criado. 

```
-----------/// GERADOR DE TESTES EP3 - Od4ir ///-----------

Digite o tamanho da string que deseja gerar: 
 >> 1000

 Deseja imprimir? S/N
 >> N

Digite alguns parâmetros para produção da substring: 
 Tam. MIN >> 25
 Tam. MAX >> 75

Digite o número de cópias que deseja gerar a partir da string DNA: 
 >> 50

 Deseja imprimir? S/N
 >> N

Vamos ordenar as substrings geradas para facilitar processos posteriores. 
 Deseja imprimir a versão ordenada? S/N
 >> N

Digite o nome do arquivo em que deseja salvar o teste: 
 >> teste16.txt
Arquivo teste16.txt gerado!
```


