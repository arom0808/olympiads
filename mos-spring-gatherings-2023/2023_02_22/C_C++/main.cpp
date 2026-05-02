
#include <iostream>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

constexpr int maxlevels = 11;

vector<int> need_vals[maxlevels];
ll mpairval[1 << 20];

inline int ceil(int a, int b) {
    return (a + b - 1) / b;
}

ll get_min_val(int level, bool pre_non_zero = false) {
    if (need_vals[level].size() == 1) {
        ll ans = 0;
        bool zero_need = need_vals[level][0] & 1, found = false;
        for (int i = 1; i < 10; ++i) {
            if (need_vals[level].front() & (1 << i)) {
                ans = ans * 10 + i;
                if (zero_need && !found) {
                    found = true;
                    ans *= 10;
                }
            }
        }
        if (zero_need && !found) ans = 10;
        if (!pre_non_zero && ans == 0) return 1;
        return ans;
    }
    if (need_vals[level].size() == 2) {
        if (pre_non_zero && ((need_vals[level][0] << 10) | need_vals[level][1]) == 2) return 0;
        return mpairval[(need_vals[level][0] << 10) | need_vals[level][1]];
    }
    ll ans = 2e18;
    for (int i = 0; i < 10; ++i) {
        need_vals[level + 1].clear();
        need_vals[level + 1].resize(ceil(need_vals[level].size() + i, 10), 0);
        for (int j = 0; j < need_vals[level].size(); ++j) {
            need_vals[level + 1][(i + j) / 10] |= need_vals[level][j] & (~(1 << ((i + j) % 10)));
        }
        ans = std::min(ans, get_min_val(level + 1, pre_non_zero || i) * 10 + i);
    }
    return ans;
}

int zip_val(ll val) {
    int ans = 0;
    for (; val; val /= 10) ans |= 1 << (val % 10);
    return ans;
}

unsigned int next_mask(unsigned int mask) {
    unsigned int lowest_bit = mask & (-mask);
    unsigned int left_bits = mask + lowest_bit;
    return (((left_bits ^ mask) >> 2) / lowest_bit) | left_bits;
}

void gen_pairvals() {
    for (int val = 1; val <= 10000; ++val) {
        int zv = (zip_val(val) << 10) | zip_val(val + 1);
        if (mpairval[zv] == 0 || val < mpairval[zv]) mpairval[zv] = val;
    }
    for (int fd = 1; fd <= 9; ++fd) {
        for (int sd = 0; sd <= 9; ++sd) {
            for (int td = sd; td <= 9; ++td) {
                for (int ld = 0; ld <= 9; ++ld) {
                    for (int mask = 1; mask < (1 << (td - sd + 1)); ++mask) {
                        ll val = fd;
                        for (int i = 0; i <= td - sd; ++i) if (mask & (1 << i)) val = val * 10 + sd + i;
                        val = val * 10 + ld;
                        int zv = (zip_val(val) << 10) | zip_val(val + 1);
                        if (mpairval[zv] == 0 || val < mpairval[zv]) mpairval[zv] = val;
                    }
                }
            }
        }
    }
    for (int cnt = 19; cnt; --cnt) {
        for (int mask = (1 << cnt) - 1; mask < (1 << 20); mask = next_mask(mask)) {
            for (int i = 0; i < 20; ++i) {
                if (mpairval[mask] == 0 || mpairval[mask | (1 << i)] < mpairval[mask])
                    mpairval[mask] = mpairval[mask | (1 << i)];
            }
        }
    }
    mpairval[0] = 0;
}

void solve() {
    gen_pairvals();
    int k;
    cin >> k;
    need_vals[0].resize(k);
    for (auto &val: need_vals[0]) {
        cin >> val;
        val = 1 << val;
    }
    cout << get_min_val(0) << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt", "r",stdin);
#endif
    solve();
    return 0;
}
