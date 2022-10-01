---
title: 最短路
date: 2022-10-01 09:55:57
tags:
  - 图论
  - 最短路
category:
  - 笔记
mathjax: true
---

### SPFA

SPFA（Shortest Path Faster Algorithm）是 Bellman-Ford 算法的队列优化版本，其时间复杂度为 $O(km)$，一般来说 $k$ 是一个很小的常数，但部分图（网格图、菊花图）会退化到 $O(nm)$。

SPFA 的队列优化是通过维护一个队列来实现的，每次从队列中取出一个点 $u$，然后遍历 $u$ 的所有出边，对于每一条出边 $(u,v)$，如果 $d[v] > d[u] + w(u,v)$，则更新 $d[v]$ 并将 $v$ 入队。

```c++
struct Edge {
    int v, w;
    Edge (int v = 0, int w = 0): v(v), w(w) {}
};
vector<Edge> es[N];
int n, m, d[N], cnt[N];
bool inq[N];
bool spfa (int s) {
    fill(d, d+n+1, numeric_limits<int>::max());
    fill(inq, inq+n+1, false);
    fill(cnt, cnt+n+1, 0);
    queue<int> q;
    q.push(s); inq[s] = true; d[s] = 0;
    while (!q.empty()) {
        int t = q.front(); q.pop();
        inq[t] = false;
        for (auto &e: es[t]) {
            if (d[e.v] > d[t] + e.w) {
                d[e.v] = d[t] + e.w;
                if (!inq[e.v]) {
                    q.push(e.v);
                    inq[e.v] = true;
                    if (++cnt[e.v] >= n) return false;
                }
            }
        }
    }
    return true;
}
```

关于怎么卡SPFA，可以参考 [fstqwq 的回答](https://www.zhihu.com/question/292283275/answer/484871888)。

### Dijkstra

Dijkstra 算法是一种单源最短路算法，其堆优化版时间复杂度为 $O(m\log n)$。

Dijkstra 算法的核心是维护一个优先队列，每次从队列中取出一个点 $u$，然后遍历 $u$ 的所有出边，对于每一条出边 $(u,v)$，如果 $d[v] > d[u] + w(u,v)$，则更新 $d[v]$ 并将 $v$ 入队。

```c++
struct Edge {
    int v, w;
    Edge (int v = 0, int w = 0): v(v), w(w) {}
};
struct Dst {
    int u, d;
    Dst (int u = 0, int d = 0): u(u), d(d) {}
    bool operator < (const Dst &o) const { return d > o.d; }
};
vector<Edge> es[N];
int n, m, d[N];
bool vst[N];
void dijkstra (int s) {
    fill(d, d+n+1, numeric_limits<int>::max());
    fill(vst, vst+n+1, false);
    priority_queue<dst> q;
    q.push({0, s}); d[s] = 0;
    while (!q.empty()) {
        auto t = q.top(); q.pop();
        if (vst[t.u]) continue;
        vst[t.u] = true;
        for (auto &e: es[t.u]) {
            if (d[e.v] > d[t.u] + e.w) {
                d[e.v] = d[t.u] + e.w;
                q.push({e.v, d[e.v]});
            }
        }
    }
}
```

### Floyd

Floyd 算法是一种多源最短路算法，其时间复杂度为 $O(n^3)$。

Floyd 算法的核心是维护一个 $n\times n$ 的矩阵 $d$，其中 $d_{ij}$ 表示从 $i$ 到 $j$ 的最短路长度，然后枚举中间点 $k$，对于每一对点 $(i,j)$，如果 $d_{ij} > d_{ik} + d_{kj}$，则更新 $d_{ij}$。

```c++
int n, m, d[N][N];
void floyd() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
```