#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

unordered_map<uint64_t, bool> cache;

bool rec_check(uint32_t sum, uint32_t mult) {
    if (sum + 1 == mult) return true;
    auto it = cache.find((static_cast<uint64_t>(sum) << 32) | mult);
    if (it != cache.end()) return it->second;
    for (uint32_t i = 1; i <= sum; ++i) {
        if (mult % (i + 1) == 0 && rec_check(sum - i, mult / (i + 1))) {
            cache.emplace((static_cast<uint64_t>(sum) << 32) | mult, true);
            return true;
        }
    }
    cache.emplace((static_cast<uint64_t>(sum) << 32) | mult, false);
    return false;
}

int main() {
    uint32_t n;
    cin >> n;
    list<uint32_t> res;
    for (uint32_t i = __lg(n); i < n; ++i) if (rec_check(i, n)) res.push_back(i);
    cout << res.size() << "\n";
    for (auto v: res) cout << v << " ";
    return 0;
}
