#include <iostream>
#include <cstdint>
#include <map>

using namespace std;

int32_t ask(int32_t pos) {
    cout << "? " << pos + 1 << endl;
    int32_t res;
    cin >> res;
    return res;
}

map<int32_t, int32_t> cache;

int32_t get_val(int32_t pos) {
    auto it = cache.find(pos);
    if (it != cache.end()) return it->second;
    return cache.emplace(pos, ask(pos)).first->second;
}

void ans(int32_t pos) {
    cout << "! " << pos + 1 << endl;
    exit(0);
}

int main() {
    int32_t n, k;
    cin >> n >> k;
    int32_t l = 0, r = n - 1;
    while (r - l >= 3) {
        int32_t m1 = l + (r - l) / 3, m2 = l + (r - l) * 2 / 3;
        if (get_val(m1) < get_val(m2)) l = m1;
        else r = m2;
    }
    int32_t mr = l, mv = get_val(l);
    for (int32_t i = l; i <= r; ++i) if (get_val(i) > mv) mr = i, mv = get_val(i);
    l = 0, r = mr;
    while (l < r) {
        int32_t m = (l + r) / 2;
        if (get_val(m) < k) l = m + 1;
        else if (get_val(m) > k) r = m - 1;
        else l = r = m;
    }
    if (get_val(l) == k) ans(l);
    l = mr, r = n - 1;
    while (l < r) {
        int32_t m = (l + r) / 2;
        if (get_val(m) > k) l = m + 1;
        else if (get_val(m) < k) r = m - 1;
        else l = r = m;
    }
    ans(l);
    return 0;
}
