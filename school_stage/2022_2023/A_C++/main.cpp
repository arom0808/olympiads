//Task 1
//
//#include <iostream>
//
//int main() {
//    std::uint64_t a, b, c;
//    std::cin >> a >> b >> c;
//    std::uint64_t min_count;
//    if (a + b <= c) min_count = 0;
//    else min_count = a + b - c;
//    if (a + c <= b) min_count = 0;
//    else if (a + c - b < min_count) min_count = a + c - b;
//    if (b + c <= a) min_count = 0;
//    else if (b + c - a < min_count) min_count = b + c - a;
//    std::cout << min_count;
//    return 0;
//}

//Task 2
//
//#include <iostream>
//
//int main() {
//    std::uint64_t n, f;
//    std::cin >> n >> f;
//    std::uint64_t three_count = 8;
//    std::uint64_t zero_count = (n - 2) * (n - 2) * (n - 2);
//    std::uint64_t one_count = (n - 2) * (n - 2) * 6;
//    std::uint64_t two_count = (n * n - (n - 2) * (n - 2) - 4) * 3;
//    if (f == 0) std::cout << zero_count;
//    else if (f == 1) std::cout << one_count;
//    else if (f == 2) std::cout << two_count;
//    else if (f == 3) std::cout << three_count;
//    return 0;
//}

//Task 3
//
//#include <iostream>
//
//int main() {
//    std::uint64_t n, m, d;
//    std::cin >> n >> m >> d;
//    std::uint64_t temp_x, temp_y;
//    std::uint64_t min_x = n, min_y = m;
//    for (std::uint64_t i = 0; i < d; ++i) {
//        std::cin >> temp_x >> temp_y;
//        if (temp_x < min_x) min_x = temp_x;
//        if (temp_y < min_y) min_y = temp_y;
//    }
//    std::cout << min_x * min_y << " " << d;
//    return 0;
//}

//Task 4
//
//#include <iostream>
//
//int main() {
//    std::uint64_t n, m;
//    std::cin >> n >> m;
//    std::uint64_t total_count = 0;
//    for (std::uint64_t a = 1; a < m; ++a) total_count += (m - a) / (n - 1);
//    std::cout << total_count;
//    return 0;
//}

//Task 5
//
//#include <iostream>
//#include <vector>
//
//char ResultForPlayer(const std::vector<std::int32_t> &players, std::vector<char> &games_results,
//                     std::vector<bool> &is_player_visited, std::uint32_t player_id) {
//    if (games_results[player_id] != 'N') return games_results[player_id];
//    if (is_player_visited[player_id]) {
//        games_results[player_id] = 'U';
//        return 'U';
//    }
//    if (static_cast<std::int32_t>(player_id) + players[player_id] <= 0) {
//        games_results[player_id] = 'L';
//        return 'L';
//    }
//    if (static_cast<std::int32_t>(player_id) + players[player_id] >= players.size()) {
//        games_results[player_id] = 'R';
//        return 'R';
//    }
//    is_player_visited[player_id] = true;
//    return ResultForPlayer(players, games_results, is_player_visited,
//                           static_cast<std::int32_t>(player_id) + players[player_id]);
//}
//
//int main() {
//    std::uint32_t n;
//    std::cin >> n;
//    std::vector<std::int32_t> players(n + 1);
//    for (std::uint32_t i = 1; i <= n; ++i) std::cin >> players[i];
//    std::vector<char> games_results(n + 1, 'N');
//    std::vector<bool> is_player_visited(n + 1, false);
//    for (std::uint32_t i = 1; i <= n; ++i) {
//        for (auto &&ipv: is_player_visited) ipv = false;
//        games_results[i] = ResultForPlayer(players, games_results, is_player_visited, i);
//    }
//    for (std::uint32_t i = 1; i <= n; ++i) std::cout << games_results[i];
//    return 0;
//}

#include <iostream>
#include <set>

int main() {
    std::set<std::set<std::uint64_t>> results;
    for (std::uint64_t a = 0; a <= 10000; ++a) {
        for (std::uint64_t b = 0; b <= 10000; ++b) {
            for (std::uint64_t c = 0; c <= 10000; ++c) {
                if ((a + 1) * (b + 1) * (c + 1) == 2 * a * b * c) {
                    std::set<std::uint64_t> res{a, b, c};
                    if (results.find(res) == results.end()) {
                        std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
                        results.insert(res);
                    }
                }
            }
        }
    }
}