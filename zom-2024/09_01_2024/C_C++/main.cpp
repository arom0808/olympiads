#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

uint32_t gcd(uint32_t a, uint32_t b) {
    uint32_t t;
    while (b) { t = a, a = b, b = t % b; }
    return a;
}

const uint64_t mod = 1e9 + 7;

int main() {
    uint32_t N, M, K;
    cin >> N >> M >> K;
    vector<uint32_t> m_divs;
    m_divs.reserve(M);
    for (uint32_t i = 1; i * i <= M; ++i) {
        if (M % i == 0) {
            m_divs.push_back(i);
            if (i != M / i) m_divs.push_back(M / i);
        }
    }
    auto inds = m_divs;
    inds.push_back(0);
    sort(inds.begin(), inds.end());
    vector<vector<uint64_t>> dp(N + 1, vector<uint64_t>(inds.size(), 0));
    for (uint32_t i = 1; i <= K; ++i)
        ++dp[1][distance(inds.begin(), lower_bound(inds.begin(), inds.end(), gcd(i % M, M) % M))];
    uint32_t pre_proc_size = 0;
    vector<map<uint32_t, uint32_t>> pre_proc_map(M);
    for (auto j: m_divs) {
        for (uint32_t k = 1; k <= K; ++k) {
            uint32_t l = distance(inds.begin(), lower_bound(inds.begin(), inds.end(), gcd(j * k % M, M) % M)),
                    r = distance(inds.begin(), lower_bound(inds.begin(), inds.end(), j % M));
            auto it = pre_proc_map[l].find(r);
            if (it == pre_proc_map[l].end()) {
                pre_proc_map[l].emplace(r, 1);
                ++pre_proc_size;
            } else ++it->second;
        }
    }
    vector<tuple<uint32_t, uint32_t, uint32_t>> pre_proc;
    pre_proc.reserve(pre_proc_size);
    for (uint32_t l = 0; l < M; ++l)
        for (auto [r, cnt]: pre_proc_map[l])
            pre_proc.emplace_back(l, r, cnt);
    for (uint32_t i = 0; i < N; ++i)
        for (auto [l, r, cnt]: pre_proc)
            dp[i + 1][l] = (dp[i + 1][l] + dp[i][r] * cnt) % mod;
    cout << dp[N][0];
    return 0;
}
