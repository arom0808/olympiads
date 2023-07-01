#include <iostream>
#include <vector>
#include <map>
#include <set>

int main() {
    std::uint64_t n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::uint64_t> vertexes(n);
    for (auto &&vert: vertexes) std::cin >> vert;
    std::vector<std::set<std::uint64_t>> ways(n);
    std::vector<std::pair<std::uint64_t, std::uint64_t>> vector_ways(m);
    for (std::uint64_t i = 0, v, u; i < m; ++i) {
        std::cin >> v >> u;
        --v;
        --u;
        vector_ways[i] = {v, u};
        ways[v].emplace(u);
        ways[u].emplace(v);
    }
    std::vector<std::vector<std::uint64_t>> near_colors_count(n, std::vector<std::uint64_t>{0, 0, 0, 0, 0, 0});
    for (std::uint64_t i = 0; i < n; ++i)
        for (auto near_id: ways[i])
            ++near_colors_count[i][vertexes[near_id]];
    std::uint64_t res = 0;
    if (k >= 2) {
        for (const auto &way: vector_ways)
            if (vertexes[way.first] != vertexes[way.second]) res += 2;
    }
    if (k >= 3) {
        for (std::uint64_t i = 0; i < n; ++i)
            for (std::uint64_t left_color = 1; left_color <= k; ++left_color)
                for (std::uint64_t right_color = 1; right_color <= k; ++right_color)
                    if (vertexes[i] != left_color && vertexes[i] != right_color && left_color != right_color)
                        res += near_colors_count[i][left_color] * near_colors_count[i][right_color];
    }
    if (k >= 4) {
        for (const auto &[mid_left, mid_right]: vector_ways)
            for (std::uint64_t left_color = 1; left_color <= k; ++left_color)
                for (std::uint64_t right_color = 1; right_color <= k; ++right_color)
                    if (left_color != vertexes[mid_left] && left_color != vertexes[mid_right] &&
                        left_color != right_color &&
                        vertexes[mid_left] != vertexes[mid_right] && vertexes[mid_left] != right_color &&
                        vertexes[mid_right] != right_color)
                        res += near_colors_count[mid_left][left_color] * near_colors_count[mid_right][right_color] * 2;
    }
    if (k >= 5) {
//        for (const auto &[mid_left, center]: vector_ways)
//            for (auto mid_right: ways[center])
//                for (std::uint64_t left_color = 1; left_color <= k; ++left_color)
//                    for (std::uint64_t right_color = 1; right_color <= k; ++right_color)
//                        if (left_color != vertexes[mid_left] && left_color != vertexes[center] &&
//                            left_color != vertexes[mid_right] && left_color != right_color &&
//                            vertexes[mid_left] != vertexes[center] && vertexes[mid_left] != vertexes[mid_right] &&
//                            vertexes[mid_left] != right_color && vertexes[center] != vertexes[mid_right] &&
//                            vertexes[center] != right_color && vertexes[mid_right] != right_color)
//                            res += 2;
        for (std::uint64_t center = 0; center < n; ++center) {
            std::vector<std::vector<std::uint64_t>> cnt_2(6, std::vector<std::uint64_t>(6, 0));
            for (std::uint64_t second_vert: ways[center])
                for (std::uint64_t third_color = 1; third_color <= k; ++third_color)
                    cnt_2[vertexes[second_vert]][third_color] += near_colors_count[second_vert][third_color];
            for (std::uint64_t middle_left_color = 1; middle_left_color <= k; ++middle_left_color)
                for (std::uint64_t middle_right_color = 1; middle_right_color <= k; ++middle_right_color)
                    for (std::uint64_t left_color = 1; left_color <= k; ++left_color)
                        for (std::uint64_t right_color = 1; right_color <= k; ++right_color)
                            if (left_color != middle_left_color && left_color != vertexes[center] &&
                                left_color != middle_right_color && left_color != right_color &&
                                middle_left_color != vertexes[center] && middle_left_color != middle_right_color &&
                                middle_left_color != right_color && vertexes[center] != middle_right_color &&
                                vertexes[center] != right_color && middle_right_color != right_color)
                                res += cnt_2[middle_left_color][left_color] * cnt_2[middle_right_color][right_color];
        }
    }
    std::cout << res;
    return 0;
}
