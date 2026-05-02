#pragma GCC optimize("Ofast,O3")

#include <iostream>
#include <cstdint>

using namespace std;

const int64_t maxn = 1e5, maxm = 1e5, block_size = 500;

struct Req {
    int64_t l, r, x, y;
};

int64_t n, m, max_bid;
int64_t avs[maxm / block_size + 1][maxn];
int64_t bs[maxn], first_der[maxn], second_der[maxn];
int64_t bid[maxn];
Req reqs[maxn];

void get_der(const int64_t orig[maxn], int64_t der[maxn]) {
    der[0] = orig[0];
    for (int64_t i = 1; i < n; ++i) der[i] = orig[i] - orig[i - 1];
}

void get_integral(const int64_t der[maxn], int64_t orig[maxn]) {
    orig[0] = der[0];
    for (int64_t i = 1; i < n; ++i) orig[i] = orig[i - 1] + der[i];
}

void add(int64_t l, int64_t r, int64_t x, int64_t y) {
    second_der[l] += x;
    if (l == r) {
        if (l + 1 < n) second_der[l + 1] -= x * 2;
        if (l + 2 < n) second_der[l + 2] += x;
    } else {
        if (l + 1 < n) second_der[l + 1] += y - x;
        if (r + 1 < n) second_der[r + 1] += -x - y * (r - l + 1);
        if (r + 2 < n) second_der[r + 2] += x + y * (r - l);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int64_t i = 0; i < n; ++i) cin >> avs[0][i];
    for (int64_t i = 0; i < n; ++i) cin >> bs[i];
    get_der(avs[0], first_der), get_der(first_der, second_der);
    cin >> m;
    max_bid = (m - 1) / block_size + 1;
    for (auto &el: bid) el = max_bid;
    for (int64_t req_id = 0; req_id < m; ++req_id) {
        if (req_id % block_size == 0) {
            auto cbid = req_id / block_size;
            get_integral(second_der, first_der), get_integral(first_der, avs[cbid]);
            for (int32_t i = 0; i < n; ++i) if (bid[i] == max_bid && avs[cbid][i] >= bs[i]) bid[i] = cbid;
        }
        auto &[l, r, x, y] = reqs[req_id];
        cin >> l >> r >> x >> y, --l, --r;
        add(l, r, x, y);
    }
    for (int64_t i = 0; i < n; ++i) {
        int64_t c_id = std::max<int64_t>(0, (bid[i] - 1) * block_size), to = std::min<int64_t>(m, bid[i] * block_size);
        int64_t val = avs[c_id / block_size][i];
        for (; c_id < to; ++c_id) {
            if (val >= bs[i]) break;
            auto [l, r, x, y] = reqs[c_id];
            if (l <= i && i <= r) val += x + (i - l) * y;
        }
        if (val < bs[i]) cout << "-1 ";
        else cout << c_id << " ";
    }
    return 0;
}
