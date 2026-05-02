#include <iostream>
#include <map>
#include <cstdint>

using namespace std;

map<uint64_t, bool> cache;

bool ask(uint64_t i) {
    if (cache.find(i) != cache.end()) return cache[i];
    cout << "? " << i + 1 << endl;
    bool res;
    cin >> res;
    res = !res;
    cache[i] = res;
    return res;
}

void ans(uint64_t i) {
    cout << "! " << i + 1 << endl;
    exit(0);
}

int main() {
    uint64_t n;
    cin >> n;
    cache.emplace(0, 0), cache.emplace(n - 1, 1);
    uint64_t l = 0, r = n - 1;
    while (r - l > 1) {
        uint64_t m = (l + r) / 2;
        if (ask(m)) r = m;
        else l = m;
    }
    ans(l);
    return 0;
}
