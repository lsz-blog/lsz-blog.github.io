---
title: 质数
date: 2022-09-24 15:28:59
tags:
  - 数学
  - 质数
categories:
  - 笔记
mathjax: true
---
定义：在大于 $1$ 的整数中，只包含 $1$ 和它本身两个约数的数称为质数（素数）。

试除法：从 $2$ 开始，依次判断是否能被 $2$ 到 $\sqrt n$ 的所有整数整除，如果能整除，则不是质数，否则是质数。

```cpp
bool is_prime (int n) {
    if (n < 2) return false;
    for (int i = 2; i <= n/i; i++)
        if (n % i == 0) return false;
    return true;
}
```

时间复杂度 $O(\sqrt n)$，空间复杂度 $O(1)$。

那为什么是 `i <= n/i` 而不是 `i <= n` 呢？因为如果 `i > n/i`，那么 `n/i` 就是 `i` 的约数，而 `i` 也是 `n/i` 的约数，所以只需要判断到 `n/i` 就可以了。

不推荐使用 `i*i <= n`，因为 `i*i` 可能会溢出。

分解质因数（试除法）：从 $2$ 开始，依次判断是否能被 $2$ 到 $\sqrt n$ 的所有整数整除，如果能整除，则将 $n$ 除以这个数，否则将这个数加 $1$，直到 $n$ 为 $1$。

```cpp
vector<int> factorize (int n) {
    vector<int> res;
    for (int i = 2; i <= n/i; i++)
        while (n % i == 0) {
            res.push_back(i);
            n /= i;
        }
    if (n > 1) res.push_back(n);
    return res;
}
```

时间复杂度 $O(\sqrt n)$，空间复杂度 $O(1)$。

Eratosthenes 筛法：从 $2$ 开始，将所有的数标记为质数，然后从 $2$ 开始，将所有 $2$ 的倍数标记为合数，然后从 $3$ 开始，将所有 $3$ 的倍数标记为合数，依次类推，直到 $n$。

```cpp
vector<int> primes (int n) {
    vector<int> res;
    vector<bool> is_prime (n+1, true);
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) res.push_back(i);
        for (int j = 0; j < res.size() && i*res[j] <= n; j++) {
            is_prime[i*res[j]] = false;
            if (i % res[j] == 0) break;
        }
    }
    return res;
}
```

时间复杂度 $O(n\log\log n)$，空间复杂度 $O(n)$。

$1 \sim n$ 的质数个数大约是 $\log\log n$。

线性筛：

```cpp
vector<int> primes (int n) {
    vector<int> primes;
    vector<bool> st (n+1);
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes.push_back(i);
        for (int j = 0; primes[j] <= n/i; j++) {
            st[primes[j]*i] = true;
            if (i % primes[j] == 0) break;
        }
    }
    return primes;
}
```