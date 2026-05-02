#include "grader.h"

using namespace std;

vector<int> a;
int n;

int init(int _n, std::vector<int> _a) {
    n = _n;
    a = std::move(_a);
    return 4;
}

void go(int k, bool b) {
    vector<bool> vs(n);
    --k;
    if (k == 0) {
        for (int i = 0; i < n; ++i) b = setb(b);
    } else if (k == 1) {
        for (int i = 0; i < n; ++i) {
            if (i == 0) b = setb(vs[i] = b);
            else b = setb(vs[i] = (b ^ vs[i - 1]));
        }
    } else if (k == 2) {
        for (int i = n - 1; i >= 0; --i) {
            vs[i] = b;
            if (i == n - 1) b = setb(vs[i]);
            else b = setb(b ^ vs[i + 1]);
        }
    } else if (k == 3) {
        bool pf = false;
        for (int i = 0; i < n; ++i) {
            if (i != n - 1) {
                pf ^= b;
                b = setb(b);
            } else {
                setb(b ^ pf);
            }
        }
    }
}
