#include <iostream>
#include <vector>

std::uint64_t k = 100003, mod = 1e9 + 7;
std::vector<std::uint64_t> k_pows(100005);

void InitKPows() {
    std::uint64_t m = 1;
    for (auto &&k_p: k_pows) {
        k_p = m;
        m = (m * k) % mod;
    }
}

void BuildTreeOfSegments(const std::vector<std::uint32_t> &colors, std::vector<std::uint64_t> &tree_of_segments,
                         std::uint32_t vert_id, std::uint32_t left, std::uint32_t right) {
    if (left == right) tree_of_segments[vert_id] = colors[left] % mod;
    else {
        std::uint32_t middle = (left + right) / 2;
        BuildTreeOfSegments(colors, tree_of_segments, 2 * vert_id, left, middle);
        BuildTreeOfSegments(colors, tree_of_segments, 2 * vert_id + 1, middle + 1, right);
        tree_of_segments[vert_id] = ((tree_of_segments[2 * vert_id]) +
                                     (k_pows[middle - left + 1] * tree_of_segments[2 * vert_id + 1]) % mod) % mod;
    }
}

void UpdateTreeOfSegments() {

}

int main() {
    InitKPows();
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> colors(n);
    for (auto &&el: colors) std::cin >> el;
    std::vector<std::uint64_t> tree_of_segments(4 * n, 0);
    BuildTreeOfSegments(colors, tree_of_segments, 1, 0, n - 1);
}

//#include <iostream>
//#include <string>
//#include <vector>

//std::uint32_t index_of_char()

//const std::uint32_t k = 31, mod = 1e9 + 7;

//int hash_substring (int l, int r) {
//    return (h[r+1] - h[l]) * p[n-l] % mod;
//}

//int main() {
//    std::string s = "abacabadaba";
//    long long h = 0, m = 1;
//    for (char c : s) {
//        int x = (int) (c - 'a' + 1);
//        h = (h + m * x) % mod;
//        m = (m * k) % mod;
//    }
//    std::uint32_t N;
//    std::cin >> N;
//    std::string word;
//    std::cin >> word;
//    std::string reversed_word(word.rbegin(), word.rend());
//    std::vector<std::int64_t> word_hashes(N), rev_word_hashes(N);
//    for (std::uint32_t i = 0; i < N; ++i) {
//
//    }
//    for (char a = -100; a < 126; ++a) {
//        std::cout << static_cast<std::int32_t>(a) << " " << a << "\n";
//    }
//    return 0;
//}
//#include <iostream>
//#include <string>
//
//int main() {
//    std::uint32_t K;
//    std::cin >> K;
//    std::string commands;
//    std::cin >> commands;
//    std::uint64_t res = 0;
//    for (std::uint32_t start_i = 0; start_i < commands.size() - K; ++start_i) {
//        for (std::uint32_t i = start_i + K; i < commands.size() && commands[i] == commands[i - K]; ++i) ++res;
//    }
//    std::cout << res;
//}

//#include <iostream>
//#include <vector>
//
//int main() {
//    std::uint64_t N, M;
//    std::cin >> N >> M;
//    std::vector<std::uint64_t> dp(N);
//    std::uint64_t now_val;
//    for (std::uint64_t i = 0; i < N; ++i) {
//        std::cin >> now_val;
//        if (i == 0) {
//            dp[i] = now_val;
//        } else if (i <= M) {
//            dp[i] = std::max(now_val, dp[i - 1]);
//        } else {
//            dp[i] = std::max(dp[i - 1], dp[i - M - 1] + now_val);
//        }
//    }
//    std::cout << dp.back();
//    return 0;
//}

//#include <iostream>
//#include <set>
//#include <map>
//
//void AddTrain(std::map<std::int64_t, std::set<std::int64_t>> &trains, std::int64_t from, std::int64_t to) {
//    auto it = trains.find(from);
//    if (it == trains.end()) trains.emplace(from, std::set<std::int64_t>{to});
//    else it->second.emplace(to);
//}
//
//std::uint64_t dif(std::int64_t a, std::int64_t b) {
//    return std::max(a, b) - std::min(a, b);
//}
//
//int main() {
//    std::uint64_t E;
//    std::map<std::int64_t, std::set<std::int64_t>> trains;
//    std::cin >> E;
//    std::int64_t t_1, t_2;
//    for (std::uint64_t i = 0; i < E; ++i) {
//        std::cin >> t_1 >> t_2;
//        AddTrain(trains, t_1, t_2);
//        AddTrain(trains, t_2, t_1);
//    }
//    std::uint64_t Q;
//    std::cin >> Q;
//    for (std::uint64_t i = 0; i < Q; ++i) {
//        std::cin >> t_1 >> t_2;
//        std::set<std::uint64_t> diffs;
//        diffs.emplace(dif(t_1, t_2));
//        auto it = trains.find(t_1);
//        if (it != trains.end()) {
//            auto s_it = it->second.lower_bound(t_2);
//            if (s_it != it->second.end()) diffs.emplace(dif(t_2, *s_it));
//            if (s_it != it->second.begin()) diffs.emplace(dif(t_2, *std::prev(s_it)));
//        }
//        std::cout << (*diffs.begin()) << "\n";
//    }
//    return 0;
//}

//#include <iostream>
//#include <vector>
//#include <map>
//#include <set>
//
//std::uint64_t dif(std::int64_t a, std::int64_t b) {
//    return std::max(a, b) - std::min(a, b);
//}
//
//struct Bank {
//    std::uint64_t id;
//    std::uint64_t time;
//    std::int64_t cord;
//};
//
//int main() {
//    std::uint64_t n;
//    std::cin >> n;
//    std::map<std::uint64_t, Bank> cord_on_sum; // <sum,Bank>
////    std::vector<std::uint64_t> banks_money(n);  //, banks_time(n); // [money], [time]
//    std::vector<std::uint64_t> time_if_del_i(n, 0);
//    std::int64_t t_x;
//    for (std::uint64_t i = 0, a, t; i < n; ++i) {
//        std::cin >> t_x >> a >> t;
//        cord_on_sum.emplace(a, Bank{i, t, t_x});
////        banks_money[i] = a;
////        banks_time[i] = t;
//    }
//    std::uint64_t full_time = cord_on_sum.rbegin()->second.time;
//    for (auto now_end = std::next(cord_on_sum.rbegin()); now_end != cord_on_sum.rend(); ++now_end) {
//        full_time += now_end->second.time;
//        full_time += dif(std::prev(now_end)->second.cord, now_end->second.cord);
//    }
//    std::uint64_t max_not_f_time = 0;
//    std::set<std::uint64_t> max_good_sums;
//    for (auto it = cord_on_sum.rbegin(); it != cord_on_sum.rend(); ++it) {
//        std::uint64_t now_time = full_time - it->second.time;
//        if (std::next(it) == cord_on_sum.rend()) {
//            if (it != cord_on_sum.rbegin()) {
//                now_time -= dif(it->second.cord, std::prev(it)->second.cord);
//            }
//        } else if (it == cord_on_sum.rbegin()) {
//            if (std::next(it) != cord_on_sum.rend()) {
//                now_time -= dif(it->second.cord, std::next(it)->second.cord);
//            }
//        } else {
//            now_time -= dif(it->second.cord, std::prev(it)->second.cord);
//            now_time -= dif(it->second.cord, std::next(it)->second.cord);
//            now_time += dif(std::prev(it)->second.cord, std::next(it)->second.cord);
//        }
//        if (now_time > max_not_f_time) {
//            max_not_f_time = now_time;
//            max_good_sums.clear();
//            max_good_sums.emplace(it->first);
//        } else if (now_time == max_not_f_time) {
//            max_good_sums.emplace(it->first);
//        }
//    }
//    std::cout << cord_on_sum[*max_good_sums.rbegin()].id + 1;
//}


//#include <vector>
//#include <iostream>
//#include <unordered_map>
//#include <unordered_set>
//#include <map>
//
//void AddWay(std::unordered_map<std::uint64_t, std::unordered_set<std::uint32_t>> &ways, std::uint32_t from,
//            std::uint32_t to) {
//    auto it = ways.find(from);
//    if (it != ways.end()) it->second.emplace(to);
//    else ways.emplace(from, std::unordered_set<std::uint32_t>{to});
//}
//
//void AddNearColor(std::map<std::uint32_t, std::uint32_t> &near_colors, std::uint32_t color_to_add) {
//    auto it = near_colors.find(color_to_add);
//    if (it != near_colors.end()) ++it->second;
//    else near_colors.emplace(color_to_add, 1);
//}
//
//void DeleteNearColor(std::map<std::uint32_t, std::uint32_t> &near_colors, std::uint32_t color_to_delete) {
//    auto it = near_colors.find(color_to_delete);
//    if (it != near_colors.end()) {
//        --it->second;
//        if (it->second == 0) near_colors.erase(it);
//    }
//}
//
//int main() {
//    std::uint32_t n, m, q;
//    std::cin >> n >> m >> q;
//    std::vector<std::uint32_t> colors(n);
//    for (auto &&col: colors) std::cin >> col;
//    std::unordered_map<std::uint32_t, std::unordered_set<std::uint32_t>> ways;
//    std::vector<std::map<std::uint32_t, std::uint32_t>> near_colors(n);
//    for (std::uint32_t i = 0, t_1, t_2; i < m; ++i) {
//        std::cin >> t_1 >> t_2;
//        --t_1;
//        --t_2;
//        AddWay(ways, t_1, t_2);
//        AddWay(ways, t_2, t_1);
//        AddNearColor(near_colors[t_1], colors[t_2]);
//        AddNearColor(near_colors[t_2], colors[t_1]);
//    }
//    for (std::uint32_t i = 0, t_1, t_2, t_3; i < q; ++i) {
//        std::cin >> t_1;
//        if (t_1 == 1) {
//            std::cin >> t_2 >> t_3;
//            --t_2;
//            --t_3;
//            if (colors[t_2] == t_3) continue;
//            for (auto neighbour: ways[t_2]) {
//                DeleteNearColor(near_colors[neighbour], colors[t_2]);
//                AddNearColor(near_colors[neighbour], colors[t_3]);
//            }
//            colors[t_2] = t_3;
//        } else {
//            std::cin >> t_2;
//            std::cout << near_colors[t_2 - 1].size() << " ";
//        }
//    }
//    return 0;
//}

//#include <vector>
//#include <iostream>
//#include <set>
//#include <map>
//
//int main() {
//    std::uint64_t N;
//    std::cin >> N;
//    std::vector<std::uint64_t> kas_time(N);
//    for (std::uint64_t i = 0; i < N; ++i) std::cin >> kas_time[i];
//    std::uint64_t M;
//    std::cin >> M;
//    std::vector<std::uint64_t> clients(M);
//    for (std::uint64_t i = 0; i < M; ++i) std::cin >> clients[i];
//    std::map<std::uint64_t, std::set<std::uint64_t>> when_next_kas_free;
//    when_next_kas_free.emplace(0, std::set<std::uint64_t>{});
//    auto &st_s = when_next_kas_free.begin()->second;
//    for (std::uint64_t i = 0; i < N; ++i) st_s.emplace(i);
////    std::vector<std::uint64_t> when_free_on_kas(N, 0);
//    for (std::uint64_t i = 0; i < M; ++i) {
//        auto it_1 = when_next_kas_free.begin();
//        std::uint64_t now_kas = *it_1->second.begin();
//        std::uint64_t after_free_time = it_1->first + kas_time[now_kas] * clients[i];
//        it_1->second.erase(now_kas);
//        if (it_1->second.empty()) when_next_kas_free.erase(it_1);
//        auto it_2 = when_next_kas_free.find(after_free_time);
//        if (it_2 == when_next_kas_free.end())
//            it_2 = when_next_kas_free.emplace(after_free_time, std::set<std::uint64_t>{}).first;
//        it_2->second.emplace(now_kas);
//        std::cout << now_kas + 1 << " ";
//    }
//}

//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//int main() {
//    std::uint32_t n, k;
//    std::cin >> n >> k;
//    std::vector<std::uint32_t> a(n);
//    for (auto &&el: a) std::cin >> el;
//    std::sort(a.begin(), a.end());
//    std::uint32_t m_id = n / 2;
//    std::uint32_t now_add = 1;
//    for (std::uint32_t i = m_id + 1; i < n; ++i) if (a[i] <= a[m_id]) ++now_add;
//    std::uint32_t res = a[m_id];
//    while (k > 0) {
//        if (now_add <= k) {
//            std::uint32_t max_add_lvl = k / now_add;
//            std::uint32_t next_level = a[m_id + now_add];
//            std::uint32_t lvl_to_add = std::min(max_add_lvl, next_level - res);
//            k -= lvl_to_add * now_add;
//            res += lvl_to_add;
//            for (std::uint32_t i = m_id + now_add; i < n && a[i] <= res; ++i) ++now_add;
//        } else break;
//    }
//    std::cout << res;
//}



//#include <iostream>
//#include <vector>
//
//std::uint64_t gcd(std::uint64_t a, std::uint64_t b) {
//    if (a % b == 0) return b;
//    if (b % a == 0) return a;
//    if (a > b) return gcd(a % b, b);
//    return gcd(a, b % a);
//}
//
//std::uint64_t ltm(std::uint64_t a, std::uint64_t b) {
//    return a * b / gcd(a, b);
//}
//
//int main() {
//    std::uint64_t N;
//    std::cin >> N;
//    std::vector<std::uint64_t> a(N);
//    for (auto &&el: a) std::cin >> el;
//    std::uint64_t res = 1;
//    for (std::uint64_t i = 0; i < N; ++i) {
//        res = ltm(res, a[i] + 1);
//    }
//    std::cout << res - 1;
//    return 0;
//}
