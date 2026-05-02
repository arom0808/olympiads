#include <iostream>
#include <vector>

using namespace std;

int main() {
    int A = 169, B = 196, C = 9601, X0 = 961;
    int N, L, j, n, x;
    int c1 = (A * X0 + B) % C;
    int c2 = (A * ((A * X0 + B) % C) + B) % C;
    while (c1 != c2) {
        c1 = (A * c1 + B) % C;
        c2 = (A * ((A * c2 + B) % C) + B) % C;
    }
    N = 0;
    c1 = X0;
    while (c1 != c2) {
        c1 = (A * c1 + B) % C;
        c2 = (A * c2 + B) % C;
        N++;
    }
    L = 1;
    c2 = (A * c1 + B) % C;
    while (c1 != c2) {
        c2 = (A * c2 + B) % C;
        L++;
    }
    cout << "Pre-period: " << N << endl;
    cout << "Period: " << L << endl;
    vector<int> K(20, 0);
    x = X0;
    for (j = 0; j < 400; ++j) {
        int n = x * 20 / C;
        K[n]++;
        x = (A * x + B) % C;
    }
    float Z = 0;
    for (j = 0; j < 20; ++j) {
        float diff = (float) (K[j] - 20);
        Z += (diff * diff) / (20.0 * 20.0);
    }
    cout << "Z = " << Z;
}
