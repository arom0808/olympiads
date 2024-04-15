#include <iostream>
#include <vector>
#include <random>

using namespace std;

random_device dev;
mt19937 rng(dev());

uint32_t randint(uint32_t a, uint32_t b) {
    return uniform_int_distribution(a, b)(rng);
}

int main() {
    uint32_t n;
    cin >> n;
    vector<uint32_t> hs(n);
    for (auto &h: hs) cin >> h;
    vector<pair<uint32_t, uint32_t>> ans;
    ans.reserve(23000);
    for (uint32_t _ = 0; _ < 100; ++_) {
        while (true) {
            bool changed = false;
            for (uint32_t i = 0; i + 4 < n; ++i) {
                if (hs[i] < hs[i + 4]) {
                    changed = true;
                    swap(hs[i], hs[i + 4]);
                    ans.emplace_back(i, i + 4);
                }
                if (hs[i] < hs[i + 3]) {
                    changed = true;
                    swap(hs[i], hs[i + 3]);
                    ans.emplace_back(i, i + 3);
                }
            }
            if (n >= 4) {
                if (hs[n - 4] < hs[n - 1]) {
                    changed = true;
                    swap(hs[n - 4], hs[n - 1]);
                    ans.emplace_back(n - 4, n - 1);
                }
            }
            if (!changed) break;
        }
        while (true) {
            bool changed = false;
            for (uint32_t i = 0; i + 1 < n; ++i) {
                if (hs[i] >= hs[i + 1]) continue;
                if (i >= 3 || n - i >= 5 || (i >= 2 && n - i >= 4)) {
                    changed = true;
                    swap(hs[i], hs[i + 1]);
                }
                if (i >= 3) {
                    ans.emplace_back(i, i - 3);
                    ans.emplace_back(i - 3, i + 1);
                    ans.emplace_back(i - 3, i);
                } else if (n - i >= 5) {
                    ans.emplace_back(i + 1, i + 4);
                    ans.emplace_back(i, i + 4);
                    ans.emplace_back(i + 1, i + 4);
                } else if (i >= 2 && n - i >= 4) {
                    ans.emplace_back(i + 1, i - 2);
                    ans.emplace_back(i + 3, i);
                    ans.emplace_back(i + 2, i - 2);
                    ans.emplace_back(i + 2, i - 1);
                    ans.emplace_back(i - 1, i + 3);
                    ans.emplace_back(i + 3, i);
                    ans.emplace_back(i - 1, i + 2);
                    ans.emplace_back(i - 2, i + 2);
                    ans.emplace_back(i + 1, i - 2);
                }
            }
            if (!changed) break;
        }
        bool is_bad = false;
        for (uint32_t i = 0; i + 1 < n; ++i) {
            if (hs[i] < hs[i + 1]) {
                is_bad = true;
                break;
            }
        }
        if (is_bad && n <= 8) {
            if (ans.size() >= 23000 || n < 4) continue;
            uint32_t cnt = randint(1, min<uint32_t>(100, 23000 - ans.size()));
            for (uint32_t i = 0; i < cnt; ++i) {
                if (n == 4 || randint(0, 1)) {
                    uint32_t p = randint(0, n - 4);
                    swap(hs[p], hs[p + 3]);
                    ans.emplace_back(p, p + 3);
                } else {
                    uint32_t p = randint(0, n - 5);
                    swap(hs[p], hs[p + 4]);
                    ans.emplace_back(p, p + 4);
                }
            }
        }
    }
    for (uint32_t i = 0; i + 1 < n; ++i) {
        if (hs[i] < hs[i + 1]) {
            cout << "NO";
            return 0;
        }
    }
    if (ans.size() > 23000) {
        cout << "NO";
        return 0;
    }
    cout << "YES\n" << ans.size() << "\n";
    for (auto [l, r]: ans) cout << l + 1 << " " << r + 1 << "\n";
    return 0;
}
