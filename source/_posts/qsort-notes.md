---
title: 快速排序笔记
date: 2022-08-23 19:29:10
tags:
  - oi
  - acwing
  - 基础算法
category: 笔记
mathjax: true
---
快速排序的主要思想是分治。主要思路如下：

1. 确定分界点：例如 $q_1$，$q_{\frac{l+r}{2}}$，$q_r$ 或随机，令其等于 $x$。

2. ★调整区间：将所有 $\leq x$ 的放在左半边，所有 $\geq x$ 的放在右半边。注意并不一定有序。

3. 递归：递归处理左右两段。

其中最难的部分就是调整区间。

**第一种方法：**

设两个数组 $a$，$b$，则遍历 $q$，若 $\leq x$ 则插入到 $a$，否则则插入到 $b$。

然后 $a$ 放在 $q$ 的左半边，$b$ 放在 $q$ 的右半边。

时间复杂度 $O(n)$，空间复杂度 $O(n)$。

**第二种方法：**

定义两个指针 $i, j$ 分别指向左右两边，分别往中间走。

让 $i, j$ 走到分别碰到 $q_i \geq x$，$q_j \leq x$ 为止。

那么便交换 $i, j$，然后 $i, j$ 继续往中间走，直到相遇为止。

### 代码模板

```c++
void quick_sort (int q[], int l, int r) {
    if (l >= r) return;
    int mid = (l+r) >> 1;
    int i = l-1, j = r+1, x = q[mid];
    while (i < j) {
        do i++; while (q[j] < x);
        do j--; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(q, l, j);
    quick_sort(q, j+1, r);
}
```

同时，`std::sort` 也是快速排序的实现之一。