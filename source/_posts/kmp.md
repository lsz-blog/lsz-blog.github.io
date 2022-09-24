---
title: KMP笔记
date: 2022-08-24 21:38:00
tags:
  - oi
  - 数据结构
category: 笔记
mathjax: true
---

假设有两个字符串 $s, t$，$t$ 在 $s$ 中多次出现。寻找 $t$ 在 $s$ 中所有初始位置的起始下标。（其实类似于 `Ctrl+F` 操作）

对于每模式串 $t$ 的每个元素 $t_j$，都存在一个实数 $k$ ，使得模式串 $t$ 开头的 $k$ 个字符（$t_0\cdots t_{k-1}$）依次与 $t_j$ 前面的 $k$（$t_{j-k}t_{j-k+1}\cdots t_{j-1}$，这里第一个字符 $t_{j-k}$ 最多从 $t_1$ 开始，所以 $k < j$）个字符相同。如果这样的 $k$ 有多个，则取最大的一个。

模式串 $t$ 中每个位置 $j$ 的字符都有这种信息，采用 $next$ 数组表示，即 $next_j =\max k$。

```c++
for (int i = 2, j = 0; i <= m; i++) {
    while (j && t[i] != t[j+1]) j = nxt[j];
    if (t[i] == t[j+1]) j++;
    nxt[i] = j;
}
for (int i = 1, j = 0; i <= n; i++) {
    while (j && s[i] != t[j+1]) j = nxt[j];
    if (s[i] == t[j+1]) j++;
    if (j == m) {
        cout << i-m << " ";
        j = nxt[j];
    }
}
```