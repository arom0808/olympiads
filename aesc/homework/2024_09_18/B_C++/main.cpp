#include <iostream>

using namespace std;

int32_t n, k;
string str;

void rec(int32_t level = 0, int32_t now_ones = 0) {
    if (level == n) {
        cout << str << "\n";
        return;
    }
    if (n - level > k - now_ones) rec(level + 1, now_ones);
    if (now_ones < k) {
        str[level] = '1';
        rec(level + 1, now_ones + 1);
        str[level] = '0';
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> k;
    str.assign(n, '0');
    rec();
    return 0;
}
