---
title: 离散化笔记
date: 2022-08-24 06:21:03
tags:
  - oi
  - acwing
  - 基础算法
mathjax: true
---

例如，值域是 $10^9$，个数是 $10^5$，就可以将这 $10^9$ 个数**映射**到 $1\cdots 10^5$ 的数。

例如：$d = \{1, 3, 100, 2000, 500000\}$，故分别映射到 $\{1, 2, 3, 4, 5\}$。

离散化过程：

1. $a$ 中可能存在重复元素，所以对 $a$ 去重。

例如：

```c++
vector<int> alls;
sort(alls.begin(), alls.end());
alls.erase(unique(alls.begin(), alls.end()), alls.end());
```

2. 可以二分求出每个 $a_i$ 对应的映射。可以自己实现二分或用 `std::lower_bound`。

### 例题 区间和

假定有一个无限长的数轴，数轴上每个坐标上的数都是 $0$。

现在，我们首先进行 $n$ 次操作，每次操作将某一位置 $x$ 上的数加 $c$。

接下来，进行 $m$ 次询问，每个询问包含两个整数 $l$ 和 $r$，你需要求出在区间 $[l,r]$ 之间的所有数的和。

暴力做法（`std::map`）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
map<int, int> mp;
int main() {
    cin >> n >> m;
    for (int i = 1, x, c; i <= n; i++)
        cin >> x >> c, mp[x] += c;
    for (int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        auto nl = mp.lower_bound(l), nr = mp.upper_bound(r);
        int sum = 0;
        for (auto it = nl; it != nr; ++it)
            sum += it->second;
        cout << sum << endl;
    }
    return 0;
}
```

显然这样第一种操作 $O(\log n)$，第二种操作 $O(n)$，时间复杂度 $O(nm)$，会TLE。

于是可以这样优化，离散化+前缀和：

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100002;
ll n, m, cnt, a[N], s[N];
map<int, int> mp, idx;
int main() {
    cin >> n >> m;
    for (int i = 1, x, c; i <= n; i++)
        cin >> x >> c, mp[x] += c;
    mp[1e9+7] = 0;
    for (auto &it: mp) {
        idx[it.first] = ++cnt;
        s[cnt] = s[cnt-1] + it.second;
    }
    for (int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        auto nl = mp.lower_bound(l), nr = mp.upper_bound(r);
        cout << s[idx[nr->first]-1] - s[idx[nl->first]-1] << endl;
    }
    return 0;
}
```

显然这样第一种操作 $O(\log n)$，第二种操作 $O(\log n)$，故时间复杂度 $O((n+m) \log n)$，能过。