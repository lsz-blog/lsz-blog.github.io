---
title: Trie笔记
date: 2022-08-25 05:56:26
tags:
  - oi
  - acwing
  - 数据结构
category: 笔记
mathjax: true
---

Trie：高效的存储和查找字符串集合的数据结构。

假设有若干字符串 $s = \{\texttt{abcdef}, \texttt{abdef}, \texttt{aced}, \texttt{bcdf}, \texttt{bcff}, \texttt{cdaa}, \texttt{bcdc}\}$。

具体的存储方式是这样：首先创建一个空根节点 $root$，然后将每个单词从第一个字符创建到最后一个字符的节点都插入到树中，第一个字符的父节点是根节点，第二个字符的父节点是第一个字符的子节点，以此类推。若之前已经有这个节点了，则不再额外创建。

那怎么高效的查找某一个单词呢：例如我们要查找 $\texttt{ac}$，则从根节点开始走，一直找到这个字符。

如下是数组模拟 Trie 的代码，用于字符串统计：

```c++
int nxt[N][26], cnt[N], idx;
void init() {
    idx = 0;
    memset(nxt, -1, sizeof(nxt));
    memset(cnt, 0, sizeof(cnt));
}
void insert (string s) {
    int p = 0;
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        if (nxt[p][c] == -1)
            nxt[p][c] = ++idx;
        p = nxt[p][c];
    }
    cnt[p]++;
}
int query (string s) {
    int p = 0;
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        if (nxt[p][c] == -1)
            return 0;
        p = nxt[p][c];
    }
    return cnt[p];
}
```

如下是指针版的代码，在 OI 中并不常用，推荐开 O2 优化，用于精确匹配字符：

```c++
struct TrieNode {
    bool is_word;
    TrieNode* next[26];
    TrieNode() : is_word(false) {
        for (int i = 0; i < 26; ++i)
            next[i] = NULL;
    }
};
void insert (string s) {
    TrieNode *p = root;
    for (int i = 0; i < s.size(); i++) {
        int index = s[i] - 'a';
        if (!p->next[index]) {
            p->next[index] = new TrieNode();
        }
        p = p->next[index];
    }
    p->isWord = true;
}
bool query (string s) {
    TrieNode *p = root;
    for (int i = 0; i < s.size(); i++) {
        int index = s[i] - 'a';
        if (!p->next[index]) {
            return false;
        }
        p = p->next[index];
    }
    return p->isWord;
}
```

同时，还可以用于存储整数，思路相同。