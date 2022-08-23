---
title: 归并排序笔记
date: 2022-08-23 19:50:27
tags:
  - oi
  - acwing
  - 基础算法
category: 笔记
mathjax: true
---

归并排序的步骤如下：

1. 确定分界点 $mid = \dfrac{l+r}{2}$。

2. 递归：递归排序左边（$left$）和右边（$right$），于是就变成了两个有序序列。

3. ★合二为一：将两个有序数组合并为一个有序数组。

定义两个指针 $i, j$，指向两个数组 $a, b$ 的最小值，其中的最小值补到答案数组。以此类推，两个指针一直往后走，直到一个到结尾为止。

### 代码模板

```c++
void merge_sort (int q[], int l, int r) {
    if (l >= r) return;
    int mid = (l+r)>>1;
    merge_sort(q, l, mid);
    merge_sort(q, mid+1, r);
    int i = l, j = mid+1, k = 0;
    while (i <= mid && j <= r) {
        if (q[i] <= q[j]) tmp[++k] = q[i++];
        else tmp[++k] = q[j++];
    }
    while (i <= mid) tmp[++k] = q[i++];
    while (j <= r) tmp[++k] = q[j++];
    for (i = l, j = 1; i <= r; i++, j++)
        q[i] = tmp[j];
}
```

同时，`std::stable_sort` 是归并排序的实现之一。