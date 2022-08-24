---
title: 链表笔记
date: 2022-08-24 07:31:56
tags:
  - oi
  - acwing
  - 数据结构
category: 笔记
mathjax: true
---

我们可以用数组来模拟一个链表。

为什么要用数组呢？

数组效率高：例如我们要使用结构体+指针的方式写一个链表，效率是很低的，主要原因是 `new Node()` 操作非常慢。（但在面试题比较常见）

```c++
struct Node {
    int val;
    Node *next;
};
```

## 数组模拟单链表

邻接表是单链表一个主要的应用（存储图和树）。邻接表相当于 $n$ 个单链表。

定义 $val$ 数组作单链表点的值，$next$ 表示每个点的 $next$ 指针，$head$ 表示头指针。

```c++
struct linked_list {
    int val[N], next[N], cnt, head;
    linked_list () {
        memset(next, -1, sizeof(next));
        memset(val, 0, sizeof(val));
        cnt = 0, head = -1;
    }
    void insert (int pos, int __val) {
        val[++cnt] = __val;
        next[cnt] = next[pos];
        next[pos] = cnt;
    }
    void insert_head (int __val) {
        val[++cnt] = __val;
        next[cnt] = head;
        head = cnt;
    }
    void erase (int pos) {
        val[pos] = 0;
        int prev = head;
        while (next[prev] != pos) prev = next[prev];
        next[prev] = next[pos];
        next[pos] = -1;
    }
    int &operator [] (int __x) {
        int x = head, _cnt = 0;
        while (x != -1 && ++_cnt <= __x)
            x = next[x];
        return val[x];
    }
    int size() {
        int x = head, _cnt = 0;
        while (x != -1)
            x = next[x], ++_cnt;
        return _cnt;
    }
    bool empty() { return size() == 0; }
    void clear() {
        memset(next, -1, sizeof(next));
        memset(val, 0, sizeof(val));
        cnt = 0;
    }
    void forEach (void (*f) (int)) {
        int x = head;
        while (x != -1) {
            f(val[x]);
            x = next[x];
        }
    }
};
```

## 数组模拟双链表

```c++
int val[N], l[N], r[N], cnt;
void init() {
    r[0] = 1, l[1] = 0; // 0 left, 1 right
    cnt = 1;
}
void insert (int pos, int __val) {
    val[++cnt] = __val;
    l[cnt] = pos;
    r[cnt] = r[pos];
    l[r[pos]] = cnt;
    r[pos] = cnt;
}
void erase (int pos) {
    l[r[pos]] = l[pos];
    r[l[pos]] = r[pos];
}
```