#include <iostream>
#include <set>
#include <vector>
#include <limits>
#include <map>
#include <queue>

struct OddTable {
public:
    std::pair<std::int32_t, std::int32_t> nearest_table;
    std::set<std::pair<std::int32_t, std::int32_t>> by_nearest_in;
};


std::pair<std::int32_t, std::int32_t> find_nearest_odd_table(std::pair<std::int32_t, std::int32_t> now_table,
                                                             const std::map<std::pair<std::int32_t, std::int32_t>, OddTable> &odd_tables,
                                                             std::int32_t n, std::int32_t m) {
    std::set<std::pair<std::int32_t, std::int32_t>> visited;
    std::queue<std::pair<std::int32_t, std::int32_t>> queue;
    queue.push(now_table);
    while (!queue.empty()) {
        auto table_coord = queue.front();
        queue.pop();
        if (visited.find(table_coord) != visited.end()) continue;
        visited.insert(table_coord);
        if (table_coord != now_table && odd_tables.find(table_coord) != odd_tables.end()) {
            return table_coord;
        }
        if (table_coord.first > 0)
            queue.push(std::pair<std::int32_t, std::int32_t>(table_coord.first - 1, table_coord.second));
        if (table_coord.second > 0)
            queue.push(std::pair<std::int32_t, std::int32_t>(table_coord.first, table_coord.second - 1));
        if (table_coord.first + 1 < n)
            queue.push(std::pair<std::int32_t, std::int32_t>(table_coord.first + 1, table_coord.second));
        if (table_coord.second + 1 < m)
            queue.push(std::pair<std::int32_t, std::int32_t>(table_coord.first, table_coord.second + 1));
    }
}

int main() {
    std::int32_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::int32_t>> tables(n, std::vector<std::int32_t>(m));
    std::map<std::pair<std::int32_t, std::int32_t>, OddTable> odd_tables;
    for (std::int32_t i = 0; i < n; ++i) {
        for (std::int32_t j = 0; j < m; ++j) {
            std::cin >> tables[i][j];
            if (tables[i][j] % 2 == 1) odd_tables.emplace(std::pair<std::int32_t, std::int32_t>(i, j), OddTable());
        }
    }
    if (odd_tables.size() < 2) {
        std::cout << 0;
        return 0;
    }
    std::set<std::pair<std::int32_t, std::int32_t>> to_process;
    for (const auto &odd_table: odd_tables) to_process.insert(odd_table.first);
    while (!to_process.empty()) {
        auto now_table = *to_process.begin();
        to_process.erase(now_table);
        auto table_coord = find_nearest_odd_table(now_table, odd_tables, n, m);
        odd_tables[now_table].nearest_table = table_coord;
        odd_tables[table_coord].by_nearest_in.insert(now_table);
    }
    std::map<std::int32_t, std::set<std::pair<std::int32_t, std::int32_t>>> odd_table_by_len;
    for (const auto &table: odd_tables) {
        auto dist = std::abs(table.first.first - table.second.nearest_table.first) +
                    std::abs(table.first.second - table.second.nearest_table.second);
        auto it = odd_table_by_len.find(dist);
        if (it != odd_table_by_len.end()) it->second.insert(table.first);
        else odd_table_by_len.emplace(dist, std::set<std::pair<std::int32_t, std::int32_t>>{table.first});
    }
    std::int32_t ops = n * m;
    std::vector<std::pair<std::pair<std::int32_t, std::int32_t>, std::pair<std::int32_t, std::int32_t>>> moves;
    moves.reserve(n * m);
    while (odd_tables.size() >= 2) {
        std::int32_t best_res = odd_table_by_len.begin()->first;
        std::pair<std::int32_t, std::int32_t> b1 = *odd_table_by_len.begin()->second.begin(), b2 = odd_tables[b1].nearest_table;
        odd_table_by_len[best_res].erase(b1);
        odd_table_by_len[best_res].erase(b2);
        if (odd_table_by_len[best_res].empty()) odd_table_by_len.erase(best_res);
        odd_tables[b2].by_nearest_in.erase(b1);
        odd_tables[odd_tables[b2].nearest_table].by_nearest_in.erase(b2);
        std::set<std::pair<int32_t, int32_t>> nin1(std::move(odd_tables[b1].by_nearest_in)),
                nin2(std::move(odd_tables[b2].by_nearest_in));
        odd_tables.erase(b1);
        odd_tables.erase(b2);
        if (odd_tables.size() >= 2) {
            for (const auto &tt: nin1) {
                auto table_coord = find_nearest_odd_table(tt, odd_tables, n, m);
                odd_tables[tt].nearest_table = table_coord;
                odd_tables[table_coord].by_nearest_in.insert(tt);
            }
            for (const auto &tt: nin2) {
                auto table_coord = find_nearest_odd_table(tt, odd_tables, n, m);
                odd_tables[tt].nearest_table = table_coord;
                odd_tables[table_coord].by_nearest_in.insert(tt);
            }
        }
        if (best_res <= ops) {
            for (std::int32_t x = b1.first; x != b2.first; b1.first < b2.first ? ++x : --x) {
                moves.emplace_back(std::pair<std::int32_t, std::int32_t>(x, b1.second),
                                   std::pair<std::int32_t, std::int32_t>(b1.first < b2.first ? x + 1 : x - 1,
                                                                         b1.second));
            }
            for (std::int32_t y = b1.second; y != b2.second; b1.second < b2.second ? ++y : --y) {
                moves.emplace_back(std::pair<std::int32_t, std::int32_t>(b2.first, y),
                                   std::pair<std::int32_t, std::int32_t>(b2.first,
                                                                         b1.second < b2.second ? y + 1 : y - 1));
            }
            odd_tables.erase(b1);
            odd_tables.erase(b2);
            ops -= best_res;
        } else break;
    }
    std::cout << moves.size() << "\n";
    for (const auto &move: moves) {
        std::cout << move.first.first + 1 << " " << move.first.second + 1 << " " << move.second.first + 1 << " "
                  << move.second.second + 1 << "\n";
    }
    return 0;
}
