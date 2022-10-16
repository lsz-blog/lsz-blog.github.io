#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
struct genie {
    int r1, r2, r3;
    genie (int r1 = 0, int r2 = 0, int r3 = 0): r1(r1), r2(r2), r3(r3) {}
    int rou () {
        return floor(pow(min({r1, r2, r3}), 3)*1.0/4);
    }
} g[500001];
int main() {
    
}