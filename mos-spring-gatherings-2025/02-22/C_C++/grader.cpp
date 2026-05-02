#include "grader.h"
#include <string>
#include <iostream>
#include <cstdlib>

namespace {
    int k = 0;
    int n;
    int verbose;
    int pos;
    std::string bs;
}

bool setb(bool b) {
    if (k == 0) {
        std::cout << "invalid call of setb before first go\n";
        return 0;
    }
    if (verbose) {
        std::cout << "\tset(" << b << ")\n";
    }
    if (pos == -1) {
        std::cout << "invalid set, already called set " << n << " times\n";
        std::exit(1);
    }
    bs[pos] = b + '0';
    bool ret;
    if (k % 2 == 1) {
        pos++;
        if (pos == n) {
            pos = -1;
            ret = false;
        } else {
            ret = bs[pos] - '0';
        }
    } else {
        pos--;
        if (pos == -1) {
            ret = false;
        } else {
            ret = bs[pos] - '0';
        }
    }
    if (verbose) {
        std::cout << "return " << ret << '\n';
    }
    return ret;
}

int main() {
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
    std::cin >> n >> verbose;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::string initial;
    std::cin >> bs;
    initial = bs;
    if (verbose) {
        std::cout << "init\n";
    }
    int m = init(n, a);
    if (verbose) {
        std::cout << "\treturn " << m << '\n';
    }
    if (m > 60) {
        std::cout << "m is too large, should be less than 60\n";
        std::exit(1);
    }
    for (k = 1; k <= m; k++) {
        if (k % 2 == 1) {
            pos = 0;
        } else {
            pos = n - 1;
        }
        if (verbose) {
            std::cout << "turn " << k << '\n';
            std::cout << "b = " << bs << '\n';
            std::cout << "go(" << k << ", " << bs[pos] << ")\n";
        }
        go(k, bs[pos] - '0');
    }
    if (verbose) {
        std::cout << "final b = " << bs << '\n';
    }
    for (int i = 0; i < n; i++) {
        if (bs[i] != initial[a[i]]) {
            std::cout << "wrong final b, b["  << i << "] should be " << initial[a[i]] << '\n';
            std::exit(1);
        }
    }
    std::cout << m << '\n';
}