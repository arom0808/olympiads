#include <iostream>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Action {
    int64_t pos;
    bool type;

    Action(int64_t pos, bool type) : pos(pos), type(type) {}

    bool operator<(const Action &other) const {
        if (pos != other.pos) return pos < other.pos;
        return !type && other.type;
    }
};

int main() {
    int64_t n, x, d;
    cin >> n >> x >> d;
    if (d == 0) {
        if (x == 0) cout << 1;
        else cout << n + 1;
        return 0;
    }
//    vector<vector<Action>> acts(std::abs(d));
    unordered_map<int64_t, vector<Action>> acts;
    for (int64_t k = 0; k <= n; ++k) {
        int64_t n_min = x * k + d * (k - 1) * k / 2;
        int64_t n_max = x * k + d * (2 * n - k - 1) * k / 2;
        if (n_min > n_max) swap(n_min, n_max);
        auto ost = ((x * k) % std::abs(d) + std::abs(d)) % std::abs(d);
        auto it = acts.find(ost);
        if (it == acts.end()) it = acts.emplace(ost, vector<Action>()).first;
        it->second.emplace_back(n_min, false);
        it->second.emplace_back(n_max, true);
    }
    uint64_t result = 0;
    for (auto &[ost, iacts]: acts) {
        sort(iacts.begin(), iacts.end());
        int64_t cnt = 0, start;
        for (auto [pos, type]: iacts) {
            if (!type && cnt == 0) start = pos;
            if (type && cnt == 1) result += (pos - start) / std::abs(d) + 1;
            if (!type) ++cnt; else --cnt;
        }
    }
    cout << result;
    return 0;
}
