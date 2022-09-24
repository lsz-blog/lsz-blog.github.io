---
title: 约数
date: 2022-09-24 16:07:28
tags:
  - 数学
  - 约数
categories:
  - 笔记
mathjax: true
---
试除法：从 $1$ 开始，依次判断是否能被 $1$ 到 $\sqrt n$ 的所有整数整除，如果能整除，则将这个数和 $n$ 除以这个数的商都加入到答案中，否则将这个数加 $1$，直到 $n$ 为 $1$。

```cpp
vector<int> divisor (int n) {
    vector<int> res;
    for (int i = 1; i <= n/i; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n/i) res.push_back(n/i);
        }
    }
    return res;
}
```

约数个数：若 $n = \prod_{i=1}^k p_i^{\alpha_i}$，则 $n$ 的约数个数为 $d = \prod_{i=1}^k (\alpha_i + 1)$。

```cpp
int divisor_num (int n) {
    int res = 1;
    for (int i = 2; i <= n/i; i++) {
        int cnt = 0;
        while (n % i == 0) {
            n /= i;
            cnt++;
        }
        res *= cnt + 1;
    }
    if (n > 1) res *= 2;
    return res;
}
```

约数和：若 $n = \prod_{i=1}^k p_i^{\alpha_i}$，则 $n$ 的约数和为 $s = \prod_{i=1}^k \frac{p_i^{\alpha_i + 1} - 1}{p_i - 1}$。

```cpp
int divisor_sum (int n) {
    int res = 1;
    for (int i = 2; i <= n/i; i++) {
        int cnt = 0;
        while (n % i == 0) {
            n /= i;
            cnt++;
        }
        res *= (pow(i, cnt + 1) - 1) / (i - 1);
    }
    if (n > 1) res *= (pow(n, 2) - 1) / (n - 1);
    return res;
}
```

最大公约数：

```cpp
int gcd (int x, int y) {
    if (!y) return x;
    return gcd(y, x%y);
}
```