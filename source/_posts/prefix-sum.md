---
title: 前缀和笔记
date: 2022-08-23 21:19:19
tags:
  - oi
  - acwing
  - 基础算法
category: 笔记
mathjax: true
---

## 一维前缀和

设我们有一个数组 $\{a_1, a_2, a_3, \cdots, a_n\}$。

则令 $s_i = a_1 + a_2 + a_3 + \cdots + a_i$，则 $s_i = s_{i-1} + a_i$，可以增量式计算。

显而易见，$s_r = a_1 + a_2 + a_3 + \cdots + a_r$，$s_{l-1} = a_1 + a_2 + a_3 + \cdots + a_{l-1}$，所以 $s_r - s_{l-1} = a_l + \cdots + a_r$。

于是便可以在 $O(1)$ 时间内求出任意区间 $[l, r]$ 对应的 $\sum_{i=l}^{r} a_i$。

### 例题

给定 $n$ 个数 $a_1, a_2, \cdots, a_n$ 和 $m$ 个询问 $(l, r)$，对于每个询问，求 $\sum_{i=l}^{r} a_i$。

数据范围：$n \leq 10^6$，$m \leq 10^6$，$l, r \in [1, n]$。

```c++
#include<iostream>
using namespace std;
const int N = 1000001;
int n, m, a[N], s[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i], s[i] = s[i-1] + a[i];
    for (int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        cout << s[r] - s[l-1] << endl;
    }
    return 0;
}
```

可以使用输入优化 `cin.tie(0)` 和 `ios::sync_with_stdio(false)` 来提升 `cin` 的读取速度。但是优化之后并没有 `scanf` 快。

## 二维前缀和

一维前缀和可以快速地拓展到二维。

设 $(x_1, y_1), (x_2, y_2)$ 为所求块的左上、右下坐标。

则 $sum(x_1, y_1, x_2, y_2) = s_{x_2,y_2} - s_{x_2,y_1} - s_{x_1-1,y_1-1} + s_{x_i-1,y_i-1}$。

且可以求用如下方式求 $s$：

```c++
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
        s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
```