---
title: 单调栈笔记
date: 2022-08-24 20:56:45
tags:
  - oi
  - acwing
  - 数据结构
category: 笔记
mathjax: true
---

单调栈用于解决”每个数左边离它最近的且比它小的数是什么“的问题，当然，若没有比其小的数，返回 $-1$。

例如 $a=\{3, 4, 2, 7, 5\}$，所以 $ans = \{-1, 3, -1, 2, 2\}$。

暴力做法：

```c++
for (int i = 1; i <= n; i++) {
    int ans = -1;
    for (int j = i-1; j; j--) {
        if (a[j] < a[i]) {
            ans = a[j];
            break;
        }
    }
    cout << ans << " ";
}
```

时间复杂度 $O(n^2)$，对于大数据是无法通过的。

发现，随着往右走的过程中，可以用一个栈来维护左边的所有元素。每一次查找，从栈顶往后找，找到第一个为止。这便是暴力做法的思路。

但是，可以发现，有些元素永远不会作为答案输出。例如，$a_3 \geq a_5$，那么 $a_3$ 就永远不能被作为答案输出。所以存在 $a_x \geq a_y$ 且 $x < y$ （逆序关系）的情况，这时候，$a_x$ 就不能作为答案输出。则将所有逆序点全部删掉，就剩下单调递增的栈。

```c++
stack<int> s;
for (int i = 1; i <= n; i++) {
    while (!s.empty() && s.top() >= a[i]) s.pop();
    if (!s.empty()) cout << s.top() << " ";
    else cout << -1 << " ";
    s.push(a[i]);
}
```

同时，可以用 `printf` 对输出作优化。

```c++
stack<int> s;
for (int i = 1; i <= n; i++) {
    while (!s.empty() && s.top() >> a[i]) s.pop();
    printf("%d ", s.empty() ? -1 : s.top());
    s.push(a[i]);
}
```
