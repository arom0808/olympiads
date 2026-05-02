#include <iostream>
#include <cstdint>
#include <map>

using namespace std;

int32_t ask(int32_t i) {
    cout << "? " << i + 1 << endl;
    int32_t res;
    cin >> res;
    return res;
}

map<int32_t, int32_t> cache;

int32_t get_val(int32_t pos) {
    auto it = cache.find(pos);
    if (it != cache.end()) return it->second;
    int32_t res = ask(pos);
    cache.emplace(pos, res);
    return res;
}

void ans(int32_t x) {
    cout << "! " << x << endl;
    exit(0);
}

int main() {
    int32_t n;
    cin >> n;
    if (n == 1) ans(get_val(0));
    int32_t l = 0, r = n / 2;
    while (l != r) {
        int32_t mid = (l + r) / 2;
        int32_t a = get_val(mid * 2), b = get_val(mid * 2 + 1);
        if (a == b) l = mid + 1;
        else r = mid;
    }
    ans(get_val(l * 2));
    return 0;
}
