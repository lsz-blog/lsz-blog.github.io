---
title: 线段树基础
date: 2022-09-30 16:52:59
tags:
  - 线段树
  - 数据结构
categories:
  - 笔记
mathjax: true
---

线段树，是一种**二叉搜索树**。它将一段区间划分为若干单位区间，每一个节点都储存着一个区间。

线段树维护的信息在很多时候可以认为是满足（幺）半群的性质的信息。

线段树可以在 $O(n \log n)$ 的时间内实现单点修改等操作。

### 线段树的实现与建立

线段树的实现是将一大段区间 $[l, r]$ 分解成两个小区间。

例如，对于大区间 $[l, r]$，令 $mid = \lfloor\dfrac{l+r}{2}\rfloor$，则可以分为两个小区间 $[l, mid]$ 和 $[mid+1, r]$。

如此，对 $[1, n]$ 一直分，直到 $\exists l=r$ 为止。

线段树的最大深度约为 $\log n$。

信息学一般使用堆式存储法存储线段树。

编号为 $k$ 的左儿子 $2k$、右儿子 $2k+1$，于是可以用位运算优化为 `k << 1`，`k << 1 | 1`。

编号为 $k$ 的父亲是 $\lfloor\dfrac{k}{2}\rfloor$，于是可以用位运算优化为 `k >> 1`。

需要实现一个基础类 `Node`，以区间和为例：

```c++
struct Node {
    int l, r, sum;
    Node (int l = 0, int r = 0, int sum = 0): l(l), r(r), sum(sum) {}
} tr[N];
```

同时，需要建立线段树：

```c++
void build (int u, int l, int r) {
    tr[u] = {l, r, 0};
    if (l == r) {
        tr[u].sum = a[l];
        return;
    }
    int mid = (l+r)>>1;
    build(u<<1, l, mid);
    build(u<<1|1, mid+1, r);
    tr[u].sum = tr[u<<1].sum + tr[u<<1|1].sum;
}
```

### 线段树单点修改

单点修改有三个参数 `u`、`id`、`x`，其中 $u$ 是目前的节点编号，$id$ 是数列中要修改的编号，$x$ 是要修改为的值。

当 $tr_u.l$ 等于 $tr_u.r$ 时，则显然只有一个可以修改，$tr_u.sum$ 直接赋值为 $x$。

否则遍历，并查看编号在哪边即可。注意左区间包含 $mid$。

```c++
void modify (int u, int id, int x) {
    if (tr[u].l == tr[u].r) {
        tr[u].sum = x;
        return;
    }
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (id <= mid) modify(u<<1, id, x);
    else modify(u<<1|1, id, x);
    tr[u].sum = tr[u<<1].sum + tr[u<<1|1].sum;
}
```

### 线段树的Lazy-Tag

Lazy-Tag：本区间已经被更新过了，但是子区间却没有被更新过，被更新的信息是什么（区间求和只用记录有没有被访问过，而区间加减乘除等多种操作的问题则要记录进行的是哪一种操作）。

#### 相对标记与绝对标记

相对标记指的是可以共存的标记，且打标记的顺序与答案无关，即标记可以叠加。 比如说给一段区间中的所有数字都 $+a$ ，我们就可以把标记叠加一下，比如上一次打了一个 $+1$ 的标记，这一次要给这一段区间 $+5$ ，那么就把 $+1$ 的标记变成 $+6$ 。

绝对标记是指不可以共存的标记，每一次都要先把标记下传，再给当前节点打上新的标记。

则需要在 `Node` 中修改如下：

```c++
struct Node {
    int l, r, sum, add;
    Node (int l = 0, int r = 0, int sum = 0, int add = 0): l(l), r(r), sum(sum), add(add) {}
} tr[4*N];
```

添加一个 `add` 的懒标记。

#### 区间修改

```c++
void modify (int u, int l, int r, int x) {
    if (tr[u].l == l && tr[u].r == r) {
        tr[u].sum += (r-l+1)*x;
        tr[u].add += x;
        return;
    }
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (r <= mid) modify(u<<1, l, r, x);
    else if (l > mid) modify(u<<1|1, l, r, x);
    else modify(u<<1, l, mid, x), modify(u<<1|1, mid+1, r, x);
    tr[u].sum = tr[u<<1].sum + tr[u<<1|1].sum;
}
```

某些题目的懒惰标记属于绝对标记（如维护区间平方和），一定要先下传标记，再向下递归。

#### 线段树的下传（pushdown）

下传标记就是把一个节点的懒惰标记传给它的左右儿子，再把该节点的懒惰标记删去。

```c++
void pushdown (int u) {
    if (tr[u].l == tr[u].r) {
        tr[u].add = 0;
        return;
    }
    tr[u<<1].sum += (tr[u<<1].r - tr[u<<1].l + 1) * tr[u].add;
    tr[u<<1|1].sum += (tr[u<<1|1].r - tr[u<<1|1].l + 1) * tr[u].add;
    tr[u<<1].add += tr[u].add;
    tr[u<<1|1].add += tr[u].add;
    tr[u].add = 0;
}
```

大部分情况，要先pushdown再打lazy-tag。

### 线段树区间查询

在查询之前要及时下传标记。

```c++
int query (int u, int l, int r) {
    if (tr[u].add) pushdown(u);
    if (tr[u].l == l && tr[u].r == r) return tr[u].sum;
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (r <= mid) return query(u<<1, l, r);
    else if (l > mid) return query(u<<1|1, l, r);
    else return query(u<<1, l, mid) + query(u<<1|1, mid+1, r);
}
```