---
title: 欧拉函数
date: 2022-09-24 16:33:04
tags:
  - 数学
  - 欧拉函数
categories:
  - 笔记
mathjax: true
---

求单数 $n$ 的欧拉函数值，即 $n$ 与 $1$ 到 $n$ 的所有整数互质的数的个数。

```cpp
int euler_func (int n) {
    int res = n;
    for (int i = 2; i <= n/i; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}
```

欧拉定理：若 $gcd(a, p) = 1$，则 $a^{\varphi(p)} \equiv 1 \pmod p$。

同时，还可以用筛法求出 $1$ 到 $n$ 的所有数的欧拉函数值。

```cpp
vector<int> euler_func (int n) {
    vector<int> res(n + 1);
    for (int i = 1; i <= n; i++) res[i] = i;
    for (int i = 2; i <= n/i; i++) {
        if (res[i] == i) {
            for (int j = i; j <= n; j += i) {
                res[j] = res[j] / i * (i - 1);
            }
        }
    }
    return res;
}
```