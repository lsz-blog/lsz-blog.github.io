---
title: 常用STL
date: 2022-08-22 12:00:00
tags:
  - oi
  - stl
category: 笔记
mathjax: true
toc: true
---
### memset
```c++
void *memset (void * ptr, int value, size_t num);
```
注意`memset`按byte初始化。
例如：
```c++
char ch;
cin >> ch;
memset(carr, ch, sizeof(carr));
```
初始化`int`时，memset只能进行一些特定的初始化，例如 `0`、`-1`、`0x3F` 等。
```c++
memset(a, 0, sizeof(a));
```

### fill
```c++
template<class ForwardIt, class T>
void fill (ForwardIt first, ForwardIt last, const T& value);
```
常见用法：
```c++
fill(v.begin(), v.end(), 1);
fill(a+1, a+n+1, 23);
```
通常，`fill`要比`memset`慢。

### sort
```c++
template<class RandomAccessIterator, class Compare>
void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```
常见用法：
```c++
sort(v.begin(), v.end());
sort(a+1, a+n+1);
```
同时，结构体可以使用 `operator<`（推荐）或 `cmp` 或使用 lambda 来进行排序，例如：
```c++
struct grid {
    int x, y;
    grid (int x = 0, int y = 0): x(x), y(y) {}
};
int main() {
    ...
    sort(grids.begin(), grids.end(), [](const grid& a, const grid& b) {
        return a.x < b.x;
    });
    ...
}
```
