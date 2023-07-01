#include <iostream>
#include <vector>
#include <algorithm>

struct Team {
    std::int32_t c, p, x;

    Team(std::int32_t c = 0, std::int32_t p = 0, std::int32_t x = 0) : c(c), p(p), x(x) {}
};

int main() {
    std::int32_t n, a, b;
    std::cin >> n >> a >> b;
    std::vector<Team> teams(n);
    for (auto &[c, p, x]: teams) std::cin >> c >> p >> x;
    std::sort(teams.begin(), teams.end(), [](const Team &a, const Team &b) { return a.x < b.x; });
    std::vector<std::vector<std::pair<std::int32_t, std::int32_t>>>
            dp1(n, std::vector<std::pair<std::int32_t, std::int32_t>>(b + 1, {0, 0}));
    for (std::int32_t i = 0; i < n; ++i) {
        for (std::int32_t j = 0; j <= b; ++j) {
            std::int32_t res_1 = 0, res_2 = 0;
            std::int32_t used_1 = 0, used_2 = 0;
            if (i > 0) {
                res_1 = dp1[i - 1][j].first;
                used_1 = dp1[i - 1][j].second;
            }
            if (teams[i].p * teams[i].x <= j) {
                auto x_cost = teams[i].p * teams[i].x;
                if (i > 0) {
                    res_2 = dp1[i - 1][j - x_cost].first + teams[i].c;
                    used_2 = dp1[i - 1][j - x_cost].second + x_cost;
                } else {
                    res_2 = teams[i].c;
                    used_2 = x_cost;
                }
            }
            if (res_1 == res_2) dp1[i][j].second = std::min(used_1, used_2);
            else if (res_1 > res_2) dp1[i][j].second = used_1;
            else dp1[i][j].second = used_2;
            dp1[i][j].first = std::max(res_1, res_2);
        }
    }
    std::vector<std::vector<std::pair<std::int32_t, std::int32_t>>>
            dp2(n, std::vector<std::pair<std::int32_t, std::int32_t>>(a + 1, {0, 0}));
    for (std::int32_t i = 0; i < n; ++i) {
        for (std::int32_t j = 0; j <= a; ++j) {
            std::int32_t res_1 = 0, res_2 = 0;
            std::int32_t used_1 = 0, used_2 = 0;
            if (i > 0) {
                res_1 = dp2[i - 1][j].first;
                used_1 = dp2[i - 1][j].second;
            }
            auto p_cost = teams[n - i - 1].p;
            if (p_cost <= j) {
                if (i > 0) {
                    res_2 = dp2[i - 1][j - p_cost].first + teams[n - i - 1].c;
                    used_2 = dp2[i - 1][j - p_cost].second + p_cost;
                } else {
                    res_2 = teams[n - i - 1].c;
                    used_2 = p_cost;
                }
            }
            if (res_1 == res_2) dp2[i][j].second = std::min(used_1, used_2);
            else if (res_1 > res_2) dp2[i][j].second = used_1;
            else dp2[i][j].second = used_2;
            dp2[i][j].first = std::max(res_1, res_2);
        }
    }
    std::int32_t max_res = 0;
    for (std::int32_t i1 = -1, i2 = n - 1; i1 < n && i2 >= -1; ++i1, --i2) {
        std::int32_t this_res = 0;
        if (i1 >= 0) this_res += dp1[i1][b].first;
        if (i2 >= 0) this_res += dp2[i2][a].first;
        if (this_res > max_res) max_res = this_res;
    }
    for (std::int32_t i1 = -1, i2 = n - 2; i1 < n - 1 && i2 >= -1; ++i1, --i2) {
        std::int32_t this_res = 0;
        if (i1 >= 0) this_res += dp1[i1][b].first;
        if (i2 >= 0) this_res += dp2[i2][a].first;
        std::int32_t least_x = b - (i1 >= 0 ? dp1[i1][b].second : 0), least_p = a - (i2 >= 0 ? dp2[i2][a].second : 0);
        std::int32_t max_minus_p = least_x / teams[i1 + 1].x;
        if (static_cast<std::int32_t>(teams[i1 + 1].p) - max_minus_p <= least_p) this_res += teams[i1 + 1].c;
        if (this_res > max_res) max_res = this_res;
    }
    std::cout << max_res;
    return 0;
}
