#include <iostream>
#include <vector>
#include <set>

int main() {
    std::uint32_t my_cnt = 0, middle_cnt = 0, other_cnt = 0;
    std::uint32_t may_minus_my_plus_middle_cnt = 0,
            may_minus_middle_plus_other_cnt = 0;
    for (std::uint32_t i = 0, x, y; i < 10; ++i) {
        std::cin >> x >> y;
        if (x <= 40) {
            if (x == 40) ++may_minus_my_plus_middle_cnt;
            ++my_cnt;
        } else if (x <= 80) {
            if (x == 80) ++may_minus_middle_plus_other_cnt;
            ++middle_cnt;
        } else ++other_cnt;
    }
    std::set<std::vector<std::uint32_t>> requests;
    requests.insert({my_cnt, middle_cnt, other_cnt});
    for (std::uint32_t i = 0; i <= may_minus_my_plus_middle_cnt; ++i) {
        for (std::uint32_t j = 0; j <= may_minus_middle_plus_other_cnt; ++j) {
            requests.insert({my_cnt, middle_cnt, other_cnt});
            --middle_cnt;
            ++other_cnt;
        }
        middle_cnt += may_minus_middle_plus_other_cnt + 1;
        other_cnt -= may_minus_middle_plus_other_cnt + 1;
        --my_cnt;
        ++middle_cnt;
    }
    std::set<std::vector<std::uint32_t>> results;
    for (const auto &req: requests) {
        for (std::uint32_t i = 1; i <= 5; ++i) {
            for (std::uint32_t j = 1; j <= 5; ++j) {
                for (std::uint32_t k = 0; k <= 3; ++k) {
                    if (i + j + k != 10) continue;
                    std::int32_t m_my_cnt = req[0], m_middle_cnt = req[1], m_other_cnt = req[2],
                            left_center_moves = 0, right_center_moves = 0;
                    for (std::uint32_t tt = 0; tt < 2; ++tt) {
                        if (m_my_cnt < i) {
                            ++m_my_cnt;
                            --m_middle_cnt;
                            ++left_center_moves;
                        }
                    }
                    for (std::uint32_t tt = 0; tt < 2; ++tt) {
                        if (m_other_cnt < k) {
                            ++m_other_cnt;
                            --m_middle_cnt;
                            ++right_center_moves;
                        }
                    }
                    for (std::uint32_t tt = 0; tt < 2; ++tt) {
                        if (m_middle_cnt < j && m_my_cnt > i && left_center_moves < 2) {
                            ++m_middle_cnt;
                            --m_my_cnt;
                            ++left_center_moves;
                        }
                    }
                    for (std::uint32_t tt = 0; tt < 2; ++tt) {
                        if (m_middle_cnt < j && m_other_cnt > k && right_center_moves < 2) {
                            ++m_middle_cnt;
                            --m_other_cnt;
                            ++right_center_moves;
                        }
                    }
                    if (m_my_cnt == i && m_middle_cnt == j && m_other_cnt == k)
                        results.insert({i, j, k});
                }
            }
        }
    }
    std::cout << results.size() << "\n";
    for (const auto &res: results) std::cout << res[0] << "-" << res[1] << "-" << res[2] << "\n";
    return 0;
}
