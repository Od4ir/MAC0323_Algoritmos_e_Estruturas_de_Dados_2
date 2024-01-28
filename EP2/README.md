<!-- omit in toc -->
#  5️⃣ EP2 - Implementação de 5 Estruturas de Dados

<!-- omit in toc -->
## 📑 índice:

- [📄 Descrição:](#-descrição)
- [🔗 Dependências:](#-dependências)
- [▶️ Executando o código:](#️-executando-o-código)
- [🧪 Como Testar:](#-como-testar)
  - [Modo 1 - Versão Enunciado:](#modo-1---versão-enunciado)
  - [Modo 2 - Versão Testes:](#modo-2---versão-testes)



## 📄 Descrição:
O objetivo do EP2 foi fazer uma análise comparativa de diferentes estruturas de dados na tarefa de ordenar e organizar informações de uma tabela de símbolos ordenada que contém palavras como chaves. As operações a serem implementadas são a adição de elementos (add) e a consulta de valores associados a uma chave (value). As estruturas utilizadas foram:
- Vetor Ordenado (VO);
- Árvore de Busca Binária (ABB);
- TREAPS (TR);
- Árvores 2-3 (A23);
- Árvores Rubro-Negras (ARN);

Para testar essas difererentes estruturas, foram implementados dois modos de execução do programa de testes. Mais detalhes a seguir. 


Para entender o melhor o projeto, considere ler:
- [Enunciado do EP2](https://github.com/Od4ir/MAC0323_Algoritmos_e_Estruturas_de_Dados_2/blob/main/EP2/EP2_Enunciado.pdf);
- [Relatório do EP2](https://github.com/Od4ir/MAC0323_Algoritmos_e_Estruturas_de_Dados_2/blob/main/EP2/EP2_Relatorio.pdf);
- [Resultados Testes EP2](https://github.com/Od4ir/MAC0323_Algoritmos_e_Estruturas_de_Dados_2/blob/main/EP2/EP2_Resultados_Testes.pdf);


## 🔗 Dependências:
Todos os testes foram feitos em um computador com **arquitetura x86_64** com sistema operacional **Linux Ubuntu - 22.04.3 LTS**.
- **g++ (GNU C++ Compiler):** g++ (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0;


## ▶️ Executando o código:
Para compilar o código, basta digitar no terminal:
```bash
g++ estruturas.cpp EP2.cpp -o EP2
```
Para executar:
```bash
./EP2
```

## 🧪 Como Testar:

Ao executar o código, você será capaz de optar por dois modos:
- Modo 1 - Versão Enunciado;
- Modo 2 - Versão Testes;
Basta digitar o número do modo desejado e seguir com as instruções.

### Modo 1 - Versão Enunciado:

Ao escolher o **Modo 1 - Versão Enunciado** basta escolher a estrutura que deseja testar, o número de palavras a serem testadas e, por fim, as palavras separadas por espaço que deseja inserir na estrutura.

```
Escolha a estrutura a ser utilizada: 
  [ VO  ] - Vetor Dinâmico Ordenado
  [ ABB ] - Árvore de Busca Binária
  [ TR  ] - Treaps
  [ A23 ] - Árvores 2-3
  [ ARN ] - Árvores Rubro-Negras

   >> <Digite uma estrutura>

Digite o número de palavras: <Digite um número>

Digite as palavras: <Digite um número>
```
Após isso, basta continuar com a execução e partir para as consultas que deseja fazer:

```
Hora das Consultas: 
 [ F  ] - Palavras mais frequente; 
 [ O  ] 'termo' - Quantas vezes 'termo' aparece no texto;
 [ L  ]- Palavras mais longas;
 [ SR ] - Maiores palavras sem repetição;
 [ VD ] - Menores palavras com mais vogais sem repetição;

Digite o número de consultas que deseja fazer: 
   >> <Digite um número>
```

Digite o código da consulta e pressione 'enter' para digitar a próxima até dar a quantidade de consultas que deseja realizar. Note que para a consulta "O" é necessário digitar um termo junto, que será buscado na estrutura de dados. Caso ainda tenha dúvidas, considere ler o [Enunciado do EP2](https://github.com/Od4ir/MAC0323_Algoritmos_e_Estruturas_de_Dados_2/blob/main/EP2/EP2_Enunciado.pdf) para maior esclarecimentos sobre esse modo.

### Modo 2 - Versão Testes:

Para o modo de testes, verifique que os arquivos '.txt' que se iniciam com "teste_" estão todos na mesma pasta do executável gerado na compilação. 

Após escolher o modo 2, você poderá escolher com qual lista de palavras deseja executar o teste (Lmebrando que essas listas de palavras são os arquivos '.txt' mencionados anteriormente). 

```
 >> Digite o tipo de teste que deseja realizar: 

 1 - Lista de palavras em ordem crescente;
 2 - Lista de palavras em ordem decrescente;
 3 - Lista de palavras em ordem aleatória;
 >> <Digite uma das opções>

 >> Digite o número de palavras que deseja testar: [TAM_MAX = 87k]
 >> <Digite um número>

Digite os códigos para impressão dos dados da estrutura: 

 1 - Vetor Ordenado - Palavras Ordenadas
 2 - Árvore de Busca Binária - In Order
 3 - Árvore de Busca Binária - Pre Order
 4 - Treap - In Order
 5 - Treap - Pre Order
 6 - Árvores Rubro Negras - In Order
 7 - Árvores Rubro Negras - Pre Order
 8 - Árvores 2-3 - In Order
 9 - Árvores 2-3 - Pre Order
 0 - Sair

 >> <Digite uma das opções>
```

Após digitar 0 para sair, é possível ver os resultados das operações realizadas em cada uma das estruturas na montagem e organização da tabela de símbolos, como desmontra o exemplo abaixo:

```
1 - VETOR ORDENADO: 
Número de Comparações Inserção.......8965
Número de Trocas.....................496506

 2 - ÁRVORE DE BUSCA BINÁRIA: 
Número de Comparações Inserção.......496800
Altura...............................996

 3 - TREAPS: 
Número de Comparações Inserção.......5878
Altura...............................20
Número de Rotações...................988

 4 - ÁRVORES RUBRO NEGRAS: 
Número de Comparações Inserção.......11905
Altura...............................14
Número de Rotações...................982

 5 - ÁRVORE 2-3: 
Número de Comparações Inserção.......11907
Altura...............................8
Número de Quebras....................982
```

Para explorar mais resultados e entender melhor os testes realizados, considere ler o [Relatório do EP2](https://github.com/Od4ir/MAC0323_Algoritmos_e_Estruturas_de_Dados_2/blob/main/EP2/EP2_Relatorio.pdf) e verificar os valores dos testes já realizados no arquivo [Resultados Testes EP2](https://github.com/Od4ir/MAC0323_Algoritmos_e_Estruturas_de_Dados_2/blob/main/EP2/EP2_Resultados_Testes.pdf). 
