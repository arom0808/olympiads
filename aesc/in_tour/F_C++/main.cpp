#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <deque>

const std::int64_t mod = 1e9 + 9;

int main() {
    std::int64_t n;
    std::cin >> n;
    std::set<std::int64_t> plus, mult;
    for (std::int64_t i = 0, num; i < n; ++i) {
        char c;
        std::cin >> c >> num;
        if (c == '*') mult.emplace(num);
        else plus.emplace(num);
    }
    std::vector<std::int64_t> dp(1e5 + 2, -1);
    std::int64_t m;
    std::cin >> m;
    for (std::int64_t i = 0, x, y; i < m; ++i) {
        std::cin >> x >> y;
        std::deque<std::int64_t> deq;
        deq.push_back(y);
        if (x == y) {
            std::cout << 1 << "\n";
            continue;
        } else if (x > y) {
            std::cout << 0 << "\n";
            continue;
        }
        dp[x] = 1;
        while (!deq.empty()) {
            auto now = deq.front();
            bool was_add = false;
            if (dp[now] != -1 || now < x) {
                deq.pop_front();
                continue;
            }
            std::int64_t cnt = 0;
            for (const auto p: plus) {
                if (now < p || now - p < x) continue;
                if (dp[now - p] == -1) {
                    was_add = true;
                    deq.push_front(now - p);
                } else if (!was_add) {
                    cnt = (cnt + dp[now - p]) % mod;
                }
            }
            for (const auto p: mult) {
                if (now < p || now % p != 0 || now / p < x) continue;
                if (dp[now / p] == -1) {
                    was_add = true;
                    deq.push_front(now / p);
                } else if (!was_add) {
                    cnt = (cnt + dp[now / p]) % mod;
                }
            }
            if (!was_add) {
                dp[now] = cnt;
                deq.pop_front();
            }
        }
        std::cout << dp[y] << "\n";
        std::fill(dp.begin(), dp.end(), -1);
    }
    return 0;
}
