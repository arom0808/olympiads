#include <iomanip>
#include <iostream>

using namespace std;

int A = 890, B = 321, C = 1238, D = 2197;

void next_step(int &ppp, int &pp, int &p) {
    ppp = (A * p + B + C * ppp) % D;
    swap(ppp, pp);
    swap(pp, p);
}

int main() {
    int x0 = 370, x1 = 900, x2 = 224;
    int v00 = x0, v01 = x1, v02 = x2, v10 = x0, v11 = x1, v12 = x2;
    next_step(v10, v11, v12);
    while (v00 != v10 || v01 != v11 || v02 != v12) {
        next_step(v00, v01, v02);
        next_step(v10, v11, v12);
        next_step(v10, v11, v12);
    }
    int L = 0;
    do {
        next_step(v00, v01, v02);
        ++L;
    } while (v00 != v10 || v01 != v11 || v02 != v12);
    v00 = x0, v01 = x1, v02 = x2, v10 = x0, v11 = x1, v12 = x2;
    for (int i = 0; i < L; ++i) next_step(v10, v11, v12);
    int N = 0;
    while (v00 != v10 || v01 != v11 || v02 != v12) {
        next_step(v00, v01, v02);
        next_step(v10, v11, v12);
        ++N;
    }
    cout << "Pre-period: " << N << "\n";
    cout << "Period: " << L << "\n";
    v00 = x0, v01 = x1, v02 = x2;
    int cnt[20];
    for (int i = 0; i < 20; ++i) cnt[i] = 0;
    for (int i = 0; i < 20 * 20; ++i) {
        int cv = 0;
        if (i == 0) cv = v00;
        else if (i == 1) cv = v01;
        else {
            cv = v02;
            next_step(v00, v01, v02);
        }
        ++cnt[cv * 20 / D];
    }
    double Z = 0;
    for (int i = 0; i < 20; ++i) {
        Z += (cnt[i] - 20) * (cnt[i] - 20);
    }
    Z /= 20 * 20;
    cout << fixed << setprecision(8) << "Z: " << Z << "\n";
    return 0;
}
