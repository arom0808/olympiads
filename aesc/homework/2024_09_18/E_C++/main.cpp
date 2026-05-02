#include <iostream>
#include <set>
#include <bitset>

using namespace std;

const int32_t max_basis = 47;
uint64_t fib[max_basis + 1];

void fib_fill() {
    fib[0] = 1, fib[1] = 2;
    for (int32_t i = 2; i <= max_basis; ++i) fib[i] = fib[i - 1] + fib[i - 2];
}

uint64_t transform_num(uint64_t num) {
    uint64_t res = 0;
    for (int32_t i = max_basis; i >= 0; --i) if (num >= fib[i]) num -= fib[i], res |= 1ull << i;
    return res;
}

void print_num(uint64_t num) {
    bool started = false;
    for (int32_t i = max_basis; i >= 0; --i) {
        if ((num >> i) & 1ull) cout << "1", started = true;
        else if (started) cout << "0";
    }
    if (!started) cout << "0";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    uint64_t n;
    cin >> n;
    fib_fill();
    set<uint64_t> used, new_vals1, new_vals2;
    new_vals1.insert(transform_num(n));
    while (!new_vals1.empty()) {
        for (auto val: new_vals1) {
            if (used.find(val) != used.end()) continue;
            used.insert(val);
            for (int32_t i = max_basis; i >= 2; --i)
                if (((val >> (i - 2)) & 7ull) == 4ull)
                    new_vals2.insert(val ^ (7ull << (i - 2)));
        }
        new_vals1.swap(new_vals2);
        new_vals2.clear();
    }
    for (auto val: used) print_num(val), cout << "\n";
    return 0;
}
