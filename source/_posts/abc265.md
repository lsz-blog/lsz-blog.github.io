---
title: AtCoder Beginner Contest 265 题解
date: 2022-08-22 06:18:04
tags:
  - atcoder
  - solutions
  - oi
category: 题解
mathjax: true
toc: true
---
### A. Apple

尽量买一个苹果的时候，当且仅当他买三个要划算，即 $3x < y$。

故 $3x < y$ 时，答案为买一个苹果，即 $nx$。

反之，答案为尽量买$3$个苹果。

```c++
#include<iostream>
using namespace std;
int x, y, n;
int main() {
    cin >> x >> y >> n;
    if (3*x < y)
        cout << n*x << endl;
    else cout << n/3*y + n%3*x << endl;
    return 0;
}
```

### B. Explore

模拟题。模拟走到每个房间即可。

在走到每个房间时，执行：

- 将 $t$ 增加该房间的 $bonus$；

- 检查剩余的是否能走。

```c++
#include<iostream>
using namespace std;
typedef long long ll;
const int N = 100001;
ll n, m, t, a[N], bonus[N];
int main() {
    cin >> n >> m >> t;
    for (int i = 1; i <= n-1; i++)
        cin >> a[i];
    for (int i = 1, x, y; i <= m; i++)
        cin >> x >> y, bonus[x] = y;
    ll tottime = 0;
    for (int i = 1; i <= n-1; i++) {
        t += bonus[i];
        if (tottime + a[i] >= t) return cout << "No" << endl, 0;
        else tottime += a[i];
    }
    cout << "Yes" << endl;
    return 0;
}
```

### C. Belt Conveyor

模拟。初始位置在 $(1, 1)$，则每次根据 $g_{i, j}$ 的字符走即可。

若走出界，则视为结束，答案为走出界前的一个 $(x, y)$。

否则，若访问了已经访问的，答案为 $-1$。

```c++
#include<iostream>
#include<queue>
#include<map>
using namespace std;
const int N = 501;
int h, w;
char g[N][N];
struct grid {
    int x, y;
    grid (int x = 0, int y = 0): x(x), y(y) {}
    bool move (char _t) {
        if (_t == 'L') y--;
        else if (_t == 'R') y++;
        else if (_t == 'U') x--;
        else x++;
        if (x < 1 || x > h || y < 1 || y > w) return true;
        return false;
    }
    bool operator < (const grid & _g) const {
        return x < _g.x || (x == _g.x && y < _g.y);
    }
};
map<grid, bool> mp;
int main() {
    cin >> h >> w;
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            cin >> g[i][j];
    queue<grid> q;
    q.push({1, 1});
    while (!q.empty()) {
        auto t = q.front(); q.pop();
        int x = t.x, y = t.y;
        if (mp[t]) {
            cout << -1 << endl;
            return 0;
        }
        mp[t] = true;
        char c = g[x][y];
        bool f = t.move(c);
        if (f) {
            printf("%d %d\n", x, y);
            return 0;
        }
        q.push({t.x, t.y});
    }
    return 0;
}
```

### D. Iroha and Haiku (New ABC Edition)

对于 $\{a_n\}$，先计算出其前缀和 $\{s_n\}$。由 $a_i$ 的数据范围可知，$\{s_n\}$ 是单调递增的。

则对于 $s$，令 $x=s_i$，则若能找到 $x, x+p, x+p+q, x+p+q+r$，则输出 `Yes`。

题目保证了 $s_i$ 的单调性，所以如上四个的编号必是从左到右。

```c++
#include<iostream>
#include<set>
using namespace std;
long long n, p, q, r;
set<long long> s;
int main() {
    cin >> n >> p >> q >> r;
    long long cur = 0;
    s.insert(0);
    for (int i = 1, x; i <= n; i++)
        cin >> x, s.insert(cur += x);
    for (auto x: s) {
        if (s.find(x+p) != s.end() && s.find(x+p+q) != s.end() && s.find(x+p+q+r) != s.end()) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
    return 0;
}
```

### E. Warp

我原来的思路：

令 $f_{x, y, n}$ 为从 $(x, y)$ 走 $n$ 步的种类数。

则记忆化即可。

```c++
#include<iostream>
#include<map>
using namespace std;
const int p = 998244353;
int n, m, a, b, c, d, e, f;
map<pair<int, int>, bool> occu;
map<tuple<int, int, int>, int> _f;
int F (int x, int y, int mv = 1) {
    if (occu.count({x, y})) return 0;
    if (mv == n+1) return 1;
    if (_f.count(make_tuple(x, y, mv))) return _f[make_tuple(x, y, mv)];
    return _f[make_tuple(x, y, mv)] = ((F(x+a, y+b, mv+1) + F(x+c, y+d, mv+1)) % p + F(x+e, y+f, mv+1)) % p;
}
int main() {
    cin >> n >> m >> a >> b >> c >> d >> e >> f;
    for (int i = 1, x, y; i <= m; i++)
        cin >> x >> y, occu[{x, y}] = true;
    cout << F(0, 0) << endl;
    return 0;
}
```

但是尽管加了记忆化搜索，还是会 TLE。所以可以考虑换换状态定义。

令 $f_{x, y, n}$ 为走了 $n$ 步到 $(x, y)$ 的种类数。

数据范围点数并不多，故可以用 `std::map` 记录。

同时，$\{x, y, n\}$ 的空间复杂度略高，可以滚动数组。

```c++
#include<iostream>
#include<map>
using namespace std;
const int p = 998244353;
int n, m, a, b, c, d, e, f;
map<pair<int, int>, int> _f;
map<pair<int, int>, bool> occu;
int main() {
    cin >> n >> m >> a >> b >> c >> d >> e >> f;
    for (int i = 1, x, y; i <= m; i++)
        cin >> x >> y, occu[{x, y}] = true;
    _f[{0, 0}] = 1;
    for (int i = 1; i <= n; i++) {
        map<pair<int, int>, int> nf;
        for (auto it: _f) {
            auto [x, y] = it.first;
            if (!occu.count({x+a, y+b}))
                nf[{x+a, y+b}] = (nf[{x+a, y+b}] + it.second) % p;
            if (!occu.count({x+c, y+d}))
                nf[{x+c, y+d}] = (nf[{x+c, y+d}] + it.second) % p;
            if (!occu.count({x+e, y+f}))
                nf[{x+e, y+f}] = (nf[{x+e, y+f}] + it.second) % p;
        }
        swap(_f, nf);
    }
    int ans = 0;
    for (auto &it: _f)
        ans = (ans + it.second) % p;
    cout << ans << endl;
    return 0;
}
```

时间复杂度 $O(n^2(\log n+\log m))$。