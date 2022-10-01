---
title: 最小生成树
date: 2022-10-01 10:23:30
tags:
  - 图论
  - 最小生成树
category:
  - 笔记
mathjax: true
---

最小生成树（Minimum Spanning Tree，MST）是一种在图论中的算法，其目的是在一个连通图中找到一棵生成树，使得这棵生成树的权值之和最小。

## Kruskal 算法

Kruskal 算法是一种贪心算法，其基本思想是每次选择一条权值最小的边，如果这条边不会形成环，则将这条边加入到最小生成树中，否则舍弃这条边。

Kruskal 算法的时间复杂度为 $O(m\log m)$，其中 $m$ 为边的数量。

$$
\begin{array}{ll}
1 &  \textbf{Input. } \text{The edges of the graph } e , \text{ where each element in } e \text{ is } (u, v, w) \\
  &  \text{ denoting that there is an edge between } u \text{ and } v \text{ weighted } w . \\
2 &  \textbf{Output. } \text{The edges of the MST of the input graph}.\\
3 &  \textbf{Method. } \\ 
4 &  result \gets \varnothing \\
5 &  \text{sort } e \text{ into nondecreasing order by weight } w \\ 
6 &  \textbf{for} \text{ each } (u, v, w) \text{ in the sorted } e \\ 
7 &  \qquad \textbf{if } u \text{ and } v \text{ are not connected in the union-find set } \\
8 &  \qquad\qquad \text{connect } u \text{ and } v \text{ in the union-find set} \\
9 &  \qquad\qquad  result \gets result\;\bigcup\ \{(u, v, w)\} \\
10 &  \textbf{return }  result
\end{array}
$$

## Prim 算法

Prim 算法是一种贪心算法，每次要选择距离最小的一个结点，以及用新的边更新其他结点的距离。其实跟 Dijkstra 算法一样，每次找到距离最小的一个点，可以暴力找也可以用堆维护。

Prim 算法的时间复杂度为 $O(m\log n)$，其中 $m$ 为边的数量，$n$ 为结点的数量。

暴力 $O(n^2 + m)$，堆优化 $O((n + m)\log n)$，斐波那契堆优化 $O(m + n\log n)$。


$$
\begin{array}{ll}
1 &  \textbf{Input. } \text{The nodes of the graph }V\text{ ; the function }g(u, v)\text{ which}\\
  &  \text{means the weight of the edge }(u, v)\text{; the function }adj(v)\text{ which}\\
  &  \text{means the nodes adjacent to }v.\\
2 &  \textbf{Output. } \text{The sum of weights of the MST of the input graph.} \\
3 &  \textbf{Method.} \\
4 &  result \gets 0 \\
5 & \text{choose an arbitrary node in }V\text{ to be the }root \\
6 &  dis(root)\gets 0 \\
7 &  \textbf{for } \text{each node }v\in(V-\{root\}) \\
8 &  \qquad  dis(v)\gets\infty \\
9 &  rest\gets V \\
10 &  \textbf{while }  rest\ne\varnothing \\
11 &  \qquad cur\gets \text{the node with the minimum }dis\text{ in }rest \\
12 &  \qquad  result\gets result+dis(cur) \\
13 &  \qquad  rest\gets rest-\{cur\} \\
14 &  \qquad  \textbf{for}\text{ each node }v\in adj(cur) \\
15 &  \qquad\qquad  dis(v)\gets\min(dis(v), g(cur, v)) \\
16 &  \textbf{return }  result 
\end{array}
$$