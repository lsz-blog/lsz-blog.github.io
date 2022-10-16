#include<iostream>
using namespace std;
struct frac {
    int a, b; // a/b
    frac (int a = 0, int b = 0): a(a), b(b) {}
    int gcd (int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    void upd (frac &f) {
        int g = gcd(f.a, f.b);
        f.a /= g;
        f.b /= g;
        if (f.b < 0) {
            f.a = -f.a;
            f.b = -f.b;
        }
    }
    frac operator + (const frac &f) {
        frac ret;
        ret.a = a * f.b + b * f.a;
        ret.b = b * f.b;
        upd(ret);
        return ret;
    }
    frac operator - (const frac &f) {
        frac ret;
        ret.a = a * f.b - b * f.a;
        ret.b = b * f.b;
        upd(ret);
        return ret;
    }
    frac operator += (const frac &f) {
        *this = *this + f;
        return *this;
    }
    frac operator -= (const frac &f) {
        *this = *this - f;
        return *this;
    }
};
int main() {
    int n;
    scanf("%d", &n);
    frac f(0, 1);
    for (int i = 0; i < n; i++) {
        int a, b; char opt;
        scanf("%d %d %c", &a, &b, &opt);
        opt == '1' ?
            f += frac(a, b)
            : f -= frac(a, b);
    }
    printf("%d", f.a);
    if (f.b != 1) printf("/%d\n", f.b);
    return 0;
}