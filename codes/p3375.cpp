#include<bits/stdc++.h>
using namespace std;
const int N = 1000001;
int nxt[N];
string s, t;
int main() {
    cin >> s >> t;
    int n = s.length(), m = t.length();
    s = " " + s, t = " " + t;
    for (int i = 2, j = 0; i <= m; i++) {
        while (j && t[i] != t[j+1]) j = nxt[j];
        if (t[i] == t[j+1]) j++;
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && s[i] != t[j+1]) j = nxt[j];
        if (s[i] == t[j+1]) j++;
        if (j == m) {
            cout << i-m+1 << endl;
            j = nxt[j];
        }
    }
    for (int i = 1; i <= m; i++)
        cout << nxt[i] << " ";
    return 0;
}