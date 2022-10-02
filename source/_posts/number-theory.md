---
title: 数论概览
date: 2022-10-02 14:00:39
tags:
  - 数论
categories:
  - 数论
mathjax: true

---

**算术基本引理：**设 $p$ 是素数，$p \mid a_1a_2$，则 $p \mid a_1$ 或 $p \mid a_2$。

算术基本引理是素数的本质属性，也是其真正定义。

事实上，上述定义称为不可约数。在一些整环中（例如唯一分解整环），素数并不等价于不可约数。

**算术基本定理（唯一分解定理）：**设 $a \in \mathbb{Z}$，则必有表示
$$
a = \Pi_{i=1}^s p_i
$$
其中 $p_j (1\leq j \leq s)$ 是素数。在不记次序的意义下，该表示唯一。

**标准素因数分解式**：合并算术基本定理的形式，变为 $a = \Pi_{i=1}^s {p_i}^{\alpha_i}$ 的形式。

算术基本定理和算术基本引理是等价的。

**C++整除和取模：**

自 C99 和 C++11 标准版本起，规定向 $0$ 取整，即 `5%3==2`、`-5%3==-2`等。

### 积性函数

若函数 $f(n)$ 满足：

1. $f(1) = 1$

2. 对任意 $x, y \in \mathbb{N}^*$、$\text{gcd}(x, y)=1$ 都有 $f(xy) = f(x)f(y)$。

则 $f(n)$ 为积性函数。

若函数 $f(n)$ 满足：

1. $f(1) = 1$
2. 对任意 $x, y \in \mathbb{N}^*$ 都有 $f(xy)=f(x)f(y)$。

则 $f(n)$ 为完全积性函数。

若 $f(x), g(x)$ 为积性函数，则 $h(x) = f(x^p)$，$h(x) = f^p(x)$， $h(x) = f(x)g(x)$，$h(x) = \sum_{d \mid x} f(d)g(\dfrac{x}{d})$ 皆为积性函数。

### 素性测试

#### Fermat 素性测试

不断选取在 $[2, n-1]$ 的基 $a$，并检验是否都有 $a^{n-1} \equiv 1 \pmod n$。

令 $ttm$ 为测试次数，一般来说 $ttm \geq 8$。

```c++
bool fermat (int n) {
	if (n < 3) return n == 2;
    for (int i = 1; i <= ttm; i++) {
        int n = rand() % (n-2) + 2;
        if (ksm(a, n-1, n) != 1)
            return false;
    }
    return true;
}
```

很遗憾，费马小定理逆定理并不成立，故而有些情况是不成立的，常称之为 Carmichael 数或伪素数（[OEIS A006931](https://oeis.org/A006931)）。

#### Miller-Rabin 素性测试

对数 $n$ 进行 $k$ 轮测试的时间复杂度是 $O(k \log^3 n)$，利用快速傅里叶变换等可以优化到 $O(k\log^2n\log\log n\log\log \log n)$.

假设广义 Riemann 猜想（GRH）成立，则只需要测试 $[2, \min\{n-2, \lfloor 2 \ln^2 n \rfloor\}]$ 中的全部整数即可确定 $n$ 的素性。

**二次探测定理：**若 $p$ 是奇素数，则 $x^2 \equiv 1 \pmod p$ 的解为 $x \equiv 1 \pmod p$ 或 $x \equiv -1 \pmod p$ 。

```c++
bool millerrabin (int n) {
    if (n < 3 || n % 2 == 0) return n == 2;
    int a = n-1, b = 0;
    while (a % 2 == 0) a/=2, ++b;
    for (int i = 1, j; i <= ttm; i++) {
        int x = rand()%(n-2) + 2, v = ksm(x,a,n);
        if (v==1) continue;
        for (j = 0; j < b; j++) {
            if (v == n-1) break;
            v = (long long) v*v%n;
        }
        if (j >= b) return false;
    }
    return true;
}
```

### 最大公约数

```c++
int gcd (int x, int y) {
    if (!y) return x;
    return gcd(y, x%y);
}
```

时间复杂度：$O(\log n)$。

最小公倍数：$\text{lcm}(x, y) = \dfrac{xy}{\text{gcd}(x, y)}$。

#### 拓展欧几里得算法

拓展欧几里得算法（EXGCD），可以求 $ax+by=\text{gcd}(a,b)$ 的可行解。

```c++
int exgcd (int a, int b, int &x, int &y) {
    if (!b) return x = 1, y = 0, a;
    int d = exgcd(b, a%b, x, y);
    int t = x;
    x = y; y = t - (a/b)*y;
    return d;
}
```

函数返回的值为最大公约数。

同时，可以写出更为简单的方法：

```c++
int exgcd (int a, int b, int &x, int &y) {
    int x1 = 1, x2 = 0, x3 = 0, x4 = 1;
    while (b) {
        int c = a/b;
        tie(x1, x2, x3, x4, a, b) = make_tuple(x3, x4, x1-x3*c, x2-x4*c, b, a-b*c);
    }
    x = x1, y = x2;
    return a;
}
```

