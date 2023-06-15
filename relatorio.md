# Relatório - EP3 de MAC0323

Nome: Gabriel Haruo Hanai Takeuchi

NUSP: 13671636

---
## Introdução

O problema consiste em encontrar o maior caminho em um dado grafo direcionado e não necessariamente acíclico.

## Montagem do grafo

O grafo foi montado a partir de arquivo de entrada, que contém os fragmentos.
A primeira linha contém o número de vértices $n$ e o número $k$ (_k-mer length_).
As próximas $n$ linhas contêm os fragmentos.

Para cada fragmento, foi criado um vértice no grafo.
Para cada par de vértices $u$ e $v$, a função `addArc(u,v)` verifica se as $k$ ou mais últimas letras de $u$ são iguais às $k$ ou mais primeiras letras de $v$.
Se sim, uma aresta de $u$ para $v$ é criada e é adiciona na lista de adjacência de $u$.

## Quebrando ciclos

Montado o grafo, é necessário quebrar todos os ciclos.
Isso pode ser feito quebrando todas as arestas de retorno.
Para isso, foi utilizado o algoritmo de busca em profundidade.
Para cada vértice $v$, a função `dfs(v)` é chamada.
Ela verifica se $v$ já foi visitado.

## Encontrando o maior caminho

O algoritmo de busca em profundidade foi utilizado para encontrar o maior caminho.
Para cada vértice $v$, a função `dfs(v)` é chamada.
Ela verifica se $v$ já foi visitado.
Se sim, retorna o valor da tabela de memoização.
Senão, para cada vértice $u$ adjacente a $v$, a função `dfs(u)` é chamada.
O valor retornado é o maior valor retornado por `dfs(u)` mais o tamanho do fragmento de $v$.
O valor retornado é armazenado na tabela de memoização e retornado.

## Complexidade

A complexidade do algoritmo é $O(n^2)$, pois para cada vértice $v$, é necessário verificar se $v$ é adjacente a cada vértice $u$.

## Referências