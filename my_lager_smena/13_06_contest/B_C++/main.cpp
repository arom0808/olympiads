#include <iostream>
#include <vector>

namespace NewSolution {
    inline std::uint32_t reverse_last_n_bits(std::uint32_t n, std::uint32_t b) {
        return ((n) ^ ((1u << (b)) - 1));
    }

    inline std::uint32_t reverse_nth_bit_from_end(std::uint32_t n, std::uint32_t b) {
        return ((n) ^ (1u << (b)));
    }

    void
    GetAnswer(const std::vector<std::uint32_t> &nums, std::uint32_t m, std::vector<std::uint32_t> &res) {
        std::vector<std::uint32_t> dist(1 << m, m);
        std::vector<bool> visited(1 << m, false);
        std::vector<std::uint32_t> to_visit((1 << (m + 1)) + 1);
        std::vector<std::uint32_t> count_in_to_visit(1 << m, 0);
        std::vector<std::uint32_t> results_for_nums(1 << m, 0);
        std::uint32_t now_visit_i = 0, now_visit_end = 0;
        for (const auto &num: nums) {
            to_visit[now_visit_end++] = num;
            ++count_in_to_visit[num];
            dist[num] = 0;
        }
        while (now_visit_i < now_visit_end) {
            auto now_num = to_visit[now_visit_i++];
            --count_in_to_visit[now_num];
            if (visited[now_num]) continue;
            visited[now_num] = true;
            results_for_nums[reverse_last_n_bits(now_num, m)] = m - dist[now_num];
            for (std::uint32_t j = 0, tt = reverse_nth_bit_from_end(now_num, j);
                 j < m; ++j, tt = reverse_nth_bit_from_end(now_num, j)) {
                if (!visited[tt] && count_in_to_visit[tt] == 0) {
                    dist[tt] = std::min(dist[tt], dist[now_num] + 1);
                    ++count_in_to_visit[tt];
                    to_visit[now_visit_end++] = tt;
                }
            }
        }
        for (std::uint32_t i = 0; i < nums.size(); ++i) res[i] = results_for_nums[nums[i]];
    }
}

int main() {
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::uint32_t> nums(n);
    for (auto &&num: nums) std::cin >> num;
    std::vector<std::uint32_t> res(nums.size());
    NewSolution::GetAnswer(nums, m, res);
    for (const auto &num: res) std::cout << num << " ";
    return 0;
}
