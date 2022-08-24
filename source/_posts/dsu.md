---
title: 并查集笔记
date: 2022-08-25 06:19:01
tags:
  - oi
  - acwing
  - 数据结构
category: 笔记
mathjax: true
---

并查集：快速地将两个集合合并、询问两个元素是否在一个集合中。

设 $fa_x$ 等于 $x$ 所在集合的祖先。

判断树根：$fa_x = x$ 则 $x$ 就是树根。

并查集在使用路径压缩和启发式合并后，复杂度为 $O(\alpha(n))$。其中 $\alpha(n)$ 为使得 $A(m, m) \leq n$ 的最大整数 $m$，其中 Ackermann 函数 $A$ 的定义如下：

$$
A(m, n) = \begin{cases}n+1&\text{if }m=0 \\ 
A(m-1,1)&\text{if }m>0\text{ and }n=0 \\ 
A(m-1,A(m,n-1))&\text{otherwise}\end{cases}
$$

实际上使用路径压缩后，也能达到 $O(\alpha(n))$ 的效果，但最坏情况是 $O(\log n)$。

```c++
int fa[N];
void init() {
    for (int i = 1; i <= n; i++)
        fa[i] = i;
}
int find (int x) {
    if (x == fa[x]) return fa[x];
    return fa[x] = find(fa[x]);
}
void merge (int x, int y) {
    x = find(x), y = find(y);
    if (x != y) fa[x] = y;
}
```