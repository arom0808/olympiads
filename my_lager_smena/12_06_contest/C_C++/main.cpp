#include <iostream>
#include <vector>
#include <algorithm>

struct Team {
    std::int64_t c = 0, p = 0, x = 0;
};

int main() {
    std::int64_t n, a, b;
    std::cin >> n >> a >> b;
    std::vector<Team> teams(n);
    for (auto &&team: teams) std::cin >> team.c >> team.p >> team.x;
    std::sort(teams.begin(), teams.end(), [](const Team &a, const Team &b) { return a.x < b.x; });
    std::vector<std::vector<std::int64_t>> dp1(n, std::vector<std::int64_t>(b + 1, 0)),
            dp2(n, std::vector<std::int64_t>(a + 1, 0));
    for (std::int64_t i = 0; i < n; ++i) {
        for (std::int64_t j = 0; j <= b; ++j) {
            std::int64_t first_ans = 0, second_ans = 0;
            if (j >= teams[i].p * teams[i].x) {
                if (i > 0) first_ans = dp1[i - 1][j - teams[i].p * teams[i].x] + teams[i].c;
                else first_ans = teams[i].c;
            }
            if (i > 0) second_ans = dp1[i - 1][j];
            dp1[i][j] = std::max(first_ans, second_ans);
        }
    }
    for (std::int64_t i = 0; i < n; ++i) {
        for (std::int64_t j = 0; j <= a; ++j) {
            std::int64_t first_ans = 0, second_ans = 0;
            if (j >= teams[n - i - 1].p) {
                if (i > 0) first_ans = dp2[i - 1][j - teams[n - i - 1].p] + teams[n - i - 1].c;
                else first_ans = teams[n - i - 1].c;
            }
            if (i > 0) second_ans = dp2[i - 1][j];
            dp2[i][j] = std::max(first_ans, second_ans);
        }
    }
    std::int64_t max_res = 0;
    dp1.emplace(dp1.begin(), b + 1, 0);
    dp2.emplace(dp2.begin(), a + 1, 0);
    for (std::int64_t left_count = 0, right_count = n - left_count - 1;
         left_count < n && right_count >= 0; ++left_count, --right_count) {
        std::int64_t this_res = 0;
        std::int64_t b_used = std::distance(dp1[left_count].begin(),
                                            std::lower_bound(dp1[left_count].begin(), dp1[left_count].end(),
                                                             dp1[left_count].back()));
        std::int64_t a_used = std::distance(dp2[right_count].begin(),
                                            std::lower_bound(dp2[right_count].begin(), dp2[right_count].end(),
                                                             dp2[right_count].back()));
        std::int64_t e_a = a - a_used, e_b = b - b_used;
        this_res += dp1[left_count][b_used];
        this_res += dp2[right_count][a_used];
//        std::int64_t this_b_to_use = e_b / teams[left_count].x * teams[left_count].x;
        if (teams[left_count].p <= e_a + e_b / teams[left_count].x) this_res += teams[left_count].c;
        if (this_res > max_res) max_res = this_res;
    }
    std::cout << max_res;
    return 0;
}


