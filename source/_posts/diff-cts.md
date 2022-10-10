---
title: 差分约束系统
date: 2022-10-01 10:11:21
tags:
  - 图论
  - 差分约束系统
  - 最短路
category:
  - 笔记
mathjax: true
---

差分约束系统（Difference Constraint System，DCS）是一种描述一组线性不等式的形式化语言，其本质是一个有向图，每个点表示一个变量，每条边表示一个不等式，边的权值表示不等式的右端点与左端点的差。

例如有一组不等式 $x_i-x_j\leq c$、$x_k-x_l\leq c'$，则可以表示为如下的差分约束系统：

$$
(x_i, x_j, c) \\
(x_k, x_l, c')
$$

然后建立超级源 $S$，求解差分约束系统的最短路，即可得到所有变量的取值。