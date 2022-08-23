---
title: 二分查找笔记
date: 2022-08-23 20:29:30
tags:
  - oi
  - acwing
  - 基础算法
category: 笔记
mathjax: true
---

有单调性的题目一定可以二分，但是没有单调性的题目也或许可以二分。故二分的本质并不是单调性。

## 整数二分

**第一种情况：**

1. 找到中间值：$mid = \dfrac{l+r+1}{2}$。

2. 判断中间值 $mid$ 是否满足性质。如果 $check(mid)$，那么答案一定在 $[mid, r]$ 中，否则，答案一定在 $[l, mid)$，即 $[l, mid-1]$。

于是 `l = mid` 或者 `r = mid-1`。

**第二种情况：**

1. 找到中间值：$mid = \dfrac{l+r}{2}$。

2. 判断中间值 $mid$ 是否满足性质。如果 $check(mid)$，那么答案一定在 $[l, mid]$ 中，否则，答案一定在 $(mid, r]$，即 $[mid+1, r]$。

于是 `r = mid` 或者 `l = mid+1`。

同时，C++有原生的 `std::lower_bound` 和 `std::upper_bound` 和 `std::equal_range` 的支持。

### 模板代码

```c++
bool check (int x);
int binary_search (int l, int r) {
    while (l < r) {
        int mid = (l+r+1) >> 1;
        if (check(mid)) l = mid;
        else r = mid-1;
    }
    return l;
}
// second case
int binary_search (int l, int r) [
    while (l < r) {
        int mid = (l+r) >> 1;
        if (check(mid)) r = mid;
        else l = mid+1;
    } 
    return l;
]
```

## 浮点数二分

当区间长度很小时，e.g $r-l \leq 10^{-6}$ or $r-l \leq 10^{-8}$，就可以认为得到答案。

例如，开平方：

```c++
const double eps = 1e-8;
double sqrt (double x) {
    double l = 0, r = x;
    while (r-l > eps) {
        double mid = (l+r)/2;
        if (mid*mid >= x) r = mid;
        else l = mid;
    }
    return l;
}
```

浮点数二分可以不用考虑边界。浮点数有时会有精度问题，可以提高精度。例如题目保留 $n$ 小数，则大约 $10^{-n-2}$ 便没有精度问题了。