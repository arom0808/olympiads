//#include<iostream>
//#include<map>
//#include<vector>
//#include<algorithm>
//
//int main() {
//    std::uint64_t n;
//    std::cin >> n;
//    std::map<std::uint64_t, std::uint64_t> c_s;
//    for (std::uint64_t i = 0, x; i < n; ++i) {
//        std::cin >> x;
//        auto it = c_s.find(x);
//        if (it != c_s.end()) ++it->second;
//        else c_s.emplace(x, 1);
//    }
//    std::vector<std::pair<std::uint64_t, std::uint64_t>> counts(c_s.begin(), c_s.end());
//    std::sort(counts.begin(), counts.end(),
//              [](const std::pair<std::uint64_t, std::uint64_t> &a, const std::pair<std::uint64_t, std::uint64_t> &b) {
//                  return a.second < b.second;
//              });
//    std::vector<std::uint64_t> odd_cnt, even_cnt;
//    odd_cnt.reserve(n);
//    even_cnt.reserve(n);
//    for (auto &&[num, cnt]: counts) {
//        if (cnt % 2 == 0) for (std::uint64_t i = 0; i < cnt; ++i) even_cnt.push_back(num);
//        else for (std::uint64_t i = 0; i < cnt; ++i) odd_cnt.push_back(num);
//    }
//    std::vector<std::uint64_t> aaa;
//    aaa.reserve(n);
//    for (auto &&even: even_cnt) aaa.push_back(even);
//    for (auto &&odd: odd_cnt) aaa.push_back(odd);
//    std::uint64_t res = 0, pre_n = n + 1;
//    for (unsigned long long &it: aaa) {
//        if (it != pre_n) {
//            ++res;
//            pre_n = it;
//        }
//    }
//    std::cout << res;
//}

//#include<iostream>
//#include<map>
//#include<vector>
//
//int main() {
//    std::uint64_t n;
//    std::cin >> n;
//    std::map<std::uint64_t, std::uint64_t> c_s;
//    for (std::uint64_t i = 0, x; i < n; ++i) {
//        std::cin >> x;
//        auto it = c_s.find(x);
//        if (it != c_s.end()) ++it->second;
//        else c_s.emplace(x, 1);
//    }
//    std::vector<std::uint32_t> aaa;
//    aaa.reserve(n);
//    while (!c_s.empty()) {
//        for (auto &&c: c_s) {
//            aaa.push_back(c.first);
//            --c.second;
//        }
//        for (auto it = c_s.begin(); it != c_s.end();) {
//            if (it->second == 0) {
//                ++it;
//                c_s.erase(std::prev(it));
//            } else ++it;
//        }
//    }
//    std::uint32_t res = 0, pre_n = n + 1;
//    for (unsigned int &it: aaa) {
//        if (it != pre_n) {
//            ++res;
//            pre_n = it;
//        }
//    }
//    std::cout << res;
//}



//#include <iostream>
//#include <vector>
//
//const std::uint64_t mod = 1000000009;
//
//int main() {
//    std::uint64_t n;
//    std::cin >> n;
//    std::vector<std::uint64_t> plus_ops, mult_ops;
//    for (std::uint64_t i = 0, x; i < n; ++i) {
//        char t;
//        std::cin >> t >> x;
//        if (t == '+') plus_ops.push_back(x);
//        else mult_ops.push_back(x);
//    }
//    std::uint64_t m;
//    std::cin >> m;
//    for (std::uint64_t i = 0, x, y; i < m; ++i) {
//        std::cin >> x >> y;
//        if (x == y) {
//            std::cout << 1;
//            continue;
//        }
//        if (x > y) {
//            std::cout << 0;
//            continue;
//        }
//        std::vector<std::uint64_t> dp(y + 1, 0);
//        dp[x] = 1;
//        for (std::uint64_t j = x; j <= y; ++j) {
//            for (auto plus_op: plus_ops) {
//                if (j + plus_op > y) continue;
//                dp[j + plus_op] += dp[j];
//                dp[j + plus_op] %= mod;
//            }
//            for (auto mult_op: mult_ops) {
//                if (j * mult_op > y) continue;
//                dp[j * mult_op] += dp[j];
//                dp[j * mult_op] %= mod;
//            }
//        }
//        std::cout << dp[y] << "\n";
//    }
//}

//#include <iostream>
//#include <list>
//
//int main() {
//    std::uint32_t n;
//    std::cin >> n;
//    std::list<std::uint32_t> to_add, added;
//    to_add.resize(n);
//    for (auto &&t_d: to_add) std::cin >> t_d;
//    added.splice(added.end(), to_add, to_add.begin());
//    while (!to_add.empty()) {
//        auto last_add = added.back();
//        for (auto it = to_add.begin(); it != to_add.end(); ++it) {
//            if (std::next(it) == to_add.end() || *it != last_add) {
//                added.splice(added.end(), to_add, it);
//                break;
//            }
//        }
//    }
//    std::uint32_t pre_t = n + 2;
//    std::uint32_t res = 0;
//    for (auto a: added) {
//        if (a != pre_t) ++res;
//        pre_t = a;
//    }
//    std::cout << res;
//}

//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <map>


//int main() {
//    std::map<std::uint32_t, std::uint32_t> a_map{{1,          1},
//                                                 {2,          2},
//                                                 {4,          3},
//                                                 {6,          4},
//                                                 {12,         6},
//                                                 {24,         8},
//                                                 {36,         9},
//                                                 {48,         10},
//                                                 {60,         12},
//                                                 {120,        16},
//                                                 {180,        18},
//                                                 {240,        20},
//                                                 {360,        24},
//                                                 {720,        30},
//                                                 {840,        32},
//                                                 {1260,       36},
//                                                 {1680,       40},
//                                                 {2520,       48},
//                                                 {5040,       60},
//                                                 {7560,       64},
//                                                 {10080,      72},
//                                                 {15120,      80},
//                                                 {20160,      84},
//                                                 {25200,      90},
//                                                 {27720,      96},
//                                                 {45360,      100},
//                                                 {50400,      108},
//                                                 {55440,      120},
//                                                 {83160,      128},
//                                                 {110880,     144},
//                                                 {166320,     160},
//                                                 {221760,     168},
//                                                 {277200,     180},
//                                                 {332640,     192},
//                                                 {498960,     200},
//                                                 {554400,     216},
//                                                 {665280,     224},
//                                                 {720720,     240},
//                                                 {1081080,    256},
//                                                 {1441440,    288},
//                                                 {2162160,    320},
//                                                 {2882880,    336},
//                                                 {3603600,    360},
//                                                 {4324320,    384},
//                                                 {6486480,    400},
//                                                 {7207200,    432},
//                                                 {8648640,    448},
//                                                 {10810800,   480},
//                                                 {14414400,   504},
//                                                 {17297280,   512},
//                                                 {21621600,   576},
//                                                 {32432400,   600},
//                                                 {36756720,   640},
//                                                 {43243200,   672},
//                                                 {61261200,   720},
//                                                 {73513440,   768},
//                                                 {110270160,  800},
//                                                 {122522400,  864},
//                                                 {147026880,  896},
//                                                 {183783600,  960},
//                                                 {245044800,  1008},
//                                                 {294053760,  1024},
//                                                 {367567200,  1152},
//                                                 {551350800,  1200},
//                                                 {698377680,  1280},
//                                                 {735134400,  1344},
//                                                 {1102701600, 1440},
//                                                 {1396755360, 1536}};
//    std::uint64_t n;
//    std::cin >> n;
//    auto it = a_map.upper_bound(n);
//    std::cout << std::prev(it)->first;
////    std::ofstream out_f("out_file.txt");
////    std::vector<std::uint16_t> deleters(n + 1, 0);
////    for (std::uint64_t i = 1; i <= n; ++i) {
////        for (std::uint64_t j = 1; i * j <= n; ++j) ++deleters[i * j];
////    }
////    std::uint64_t last_max_val = 1, last_max_dels = deleters[1];
////    for (std::uint64_t i = 1; i <= n; ++i) {
////        if (deleters[i] > last_max_dels) {
////            out_f << "{" << last_max_val << ", " << last_max_dels << "}, ";
////            last_max_dels = deleters[i];
////            last_max_val = i;
////        }
////    }
////    out_f << "{" << last_max_val << ", " << last_max_dels << "}";
//}

//#include<iostream>
//#include<map>
//
//int main() {
//    std::uint64_t n;
//    std::cin >> n;
//    std::map<std::uint64_t, std::uint64_t> c_s;
//    for (std::uint64_t i = 0, x; i < n; ++i) {
//        std::cin >> x;
//        auto it = c_s.find(x);
//        if (it != c_s.end()) ++it->second;
//        else c_s.emplace(x, 1);
//    }
//    std::uint64_t last_n = 0, res = 0;
//    for (std::uint64_t i = 0; i < n; ++i) {
//        if (c_s.empty()) break;
//        if (c_s.begin()->first == last_n) {
//            if (c_s.size() == 1) {
//                break;
//            } else {
//                auto it = ++c_s.begin();
//                last_n = it->first;
//                ++res;
//                --it->second;
//                if (it->second == 0) c_s.erase(it);
//            }
//        } else {
//            last_n = c_s.begin()->first;
//            ++res;
//            --c_s.begin()->second;
//            if (c_s.begin()->second == 0) c_s.erase(c_s.begin());
//        }
//    }
//    std::cout << res;
//}


//#include <iostream>
//#include <vector>
//
//const std::uint64_t mod = 1e9 + 9;
//
//int main() {
//    std::uint64_t n;
//    std::cin >> n;
//    std::vector<std::uint64_t> plus_ops, mult_ops;
//    for (std::uint64_t i = 0, x; i < n; ++i) {
//        char t;
//        std::cin >> t >> x;
//        if (t == '+') plus_ops.push_back(x);
//        else mult_ops.push_back(x);
//    }
//    std::uint64_t m;
//    std::cin >> m;
//    for (std::uint64_t i = 0, x, y; i < m; ++i) {
//        std::cin >> x >> y;
//        if (x == y) {
//            std::cout << 1;
//            continue;
//        }
//        if (x > y) {
//            std::cout << 0;
//            continue;
//        }
//        std::vector<std::uint64_t> dp(y + 1, 0);
//        dp[x] = 1;
//        for (std::uint64_t j = x; j <= y; ++j) {
//            for (auto plus_op: plus_ops) {
//                if (j + plus_op > y) continue;
//                dp[j + plus_op] += dp[j];
//                dp[j + plus_op] %= mod;
//            }
//            for (auto mult_op: mult_ops) {
//                if (j * mult_op > y) continue;
//                dp[j * mult_op] += dp[j];
//                dp[j * mult_op] %= mod;
//            }
//        }
//        std::cout << dp[y] << "\n";
//    }
//}


//#include <iostream>
//#include <vector>
//#include <set>
//
//
//int main() {
//    std::uint64_t n;
//    std::cin >> n;
//    std::set<std::uint32_t> set_easy_nums;
//    std::vector<bool> easy_nums(n + 1, false);
//    for (std::uint64_t i = 2; i <= n; ++i) {
//        if (easy_nums[i]) continue;
//        for (std::uint64_t j = 1; i * j < n; ++j) easy_nums[i * j] = true;
//        set_easy_nums.emplace(i);
//    }
//
//}

//#include<iostream>
//#include<map>
//
//int main() {
//    std::uint64_t n;
//    std::cin >> n;
//    std::map<std::uint64_t, std::uint64_t> c_s;
//    for (std::uint64_t i = 0, x; i < n; ++i) {
//        std::cin >> x;
//        auto it = c_s.find(x);
//        if (it != c_s.end()) ++it->second;
//        else c_s.emplace(x, 1);
//    }
//    std::uint64_t last_n = 0, res = 0;
//    for (std::uint64_t i = 0; i < n; ++i) {
//        if (c_s.empty()) break;
//        if (c_s.begin()->first == last_n) {
//            if (c_s.size() == 1) {
//                break;
//            } else {
//                auto it = ++c_s.begin();
//                last_n = it->first;
//                ++res;
//                --it->second;
//                if (it->second == 0) c_s.erase(it);
//            }
//        } else {
//            last_n = c_s.begin()->first;
//            ++res;
//            --c_s.begin()->second;
//            if (c_s.begin()->second == 0) c_s.erase(c_s.begin());
//        }
//    }
//    std::cout << res;
//}


//#include <iostream>
//#include <vector>
//#include <functional>
//
//struct Taboon {
//    std::uint32_t a, b, c;
//
//    explicit Taboon(std::uint32_t a = 0, std::uint32_t b = 0, std::uint32_t c = 0) : a(a), b(b), c(c) {}
//};
//
//void RecursiveSol(std::uint32_t now_level, std::uint32_t n, const std::vector<Taboon> &taboons, std::uint32_t a,
//                  std::uint32_t b, std::uint32_t c,
//                  const std::function<void(std::uint32_t, std::uint32_t, std::uint32_t)> &callback) {
//    if (now_level == n) {
//        callback(a, b, c);
//        return;
//    }
//    RecursiveSol(now_level + 1, n, taboons, a, b, c, callback);
//    RecursiveSol(now_level + 1, n, taboons, a + taboons[now_level].a, b + taboons[now_level].b,
//                 c + taboons[now_level].c, callback);
//}
//
//int main() {
//    std::uint32_t n;
//    std::cin >> n;
//    std::vector<Taboon> taboons(n);
//    std::string t_str;
//    for (auto &&taboon: taboons) {
//        std::cin >> t_str;
//        for (auto c: t_str) {
//            if (c == 'a') ++taboon.a;
//            else if (c == 'b') ++taboon.b;
//            else ++taboon.c;
//        }
//    }
//    std::uint32_t min_dif = 1e9, max_power = 0;
//    RecursiveSol(0, n, taboons, 0, 0, 0, [&min_dif, &max_power](std::uint32_t a, std::uint32_t b, std::uint32_t c) {
//        if (a == 0 && b == 0 && c == 0) return;
//        auto dif = std::max(a, std::max(b, c)) - std::min(a, std::min(b, c));
//        if (dif < min_dif) {
//            min_dif = dif;
//            max_power = a + b + c;
//        } else if (dif == min_dif && a + b + c > max_power) max_power = a + b + c;
//    });
//    std::cout << max_power;
//}

#include <iostream>
#include <deque>

struct DequeEl {
    std::uint32_t num, last_update;
    std::uint64_t count;

    DequeEl(std::uint32_t num, std::uint64_t count, std::uint32_t last_update) : num(num), count(count),
                                                                                 last_update(last_update) {}
};

int main() {
    std::uint32_t m;
    std::cin >> m;
    std::deque<DequeEl> deque;
    for (std::uint32_t i = 0, t_i, now_update = 0, x; i < m; ++i) {
        std::cin >> t_i;
        if (t_i == 1) {
            std::cin >> x;
            deque.emplace_back(x, 1, now_update);
        } else if (t_i == 2) {
            ++now_update;
        } else {
            auto &now_d_el = deque.front();
            if (now_d_el.last_update < now_update) {
                now_d_el.count <<= now_update - now_d_el.last_update;
                now_d_el.last_update = now_update;
            }
            std::cout << now_d_el.num << "\n";
            if (now_d_el.count == 1) deque.pop_front();
            else --now_d_el.count;
        }
    }
    return 0;
}


//#include <iostream>
////#include <vector>
////#include <set>
////#include <algorithm>
////#include <chrono>
//
////namespace sc = std::chrono;
//
//int main() {
//    std::uint64_t n;
//    std::cin >> n;
//    std::uint64_t res = 0, pre_a_size = 0;
////    auto time = sc::steady_clock::now();
//    for (std::uint64_t h = 1; h <= n; ++h) {
//        res += pre_a_size * pre_a_size;
//        std::uint64_t a_size = (h == 1 ? 1 : pre_a_size + 2);
//        res += (a_size * a_size - pre_a_size * pre_a_size) * (2 * h - 2);
//        std::cout << res << " ";
//        pre_a_size = a_size;
//    }
////    auto end_time = sc::steady_clock::now();
////    std::cout << sc::duration_cast<sc::milliseconds>(end_time - time).count();
//}

//
//int main() {
//    std::uint32_t n, m, q;
//    std::cin >> n >> m >> q;
//    std::vector<std::vector<std::uint32_t>> danger(n, std::vector<std::uint32_t>(m));
//    for (auto &&row: danger) for (auto &&num: row) std::cin >> num;
//    std::vector<std::vector<std::uint32_t>> rows(n), columns(m);
//    for (std::uint32_t i = 0; i < n; ++i) {
//        for (std::uint32_t j = 0; j < m; ++j) {
//            rows[i].emplace_back(danger[i][j]);
//            columns[j].emplace_back(danger[i][j]);
//        }
//    }
//    for (auto &&row: rows) std::sort(row.begin(), row.end());
//    for (auto &&column: columns) std::sort(column.begin(), column.end());
//    for (std::uint32_t i = 0, x, y, k; i < q; ++i) {
//        std::cin >> x >> y >> k;
//        auto &th_row = rows[--x], &th_col = columns[--y];
//        auto this_dang = danger[x][y];
//        auto row_first = th_row.begin(), row_last = th_row.end();
//        auto col_first = th_col.begin(), col_last = th_col.end();
//        if (k <= this_dang) {
//            row_first = std::lower_bound(th_row.begin(), th_row.end(), this_dang - k);
//            col_first = std::lower_bound(th_col.begin(), th_col.end(), this_dang - k);
//        }
//        row_last = std::upper_bound(th_row.begin(), th_row.end(), this_dang + k);
//        col_last = std::upper_bound(th_col.begin(), th_col.end(), this_dang + k);
//        auto row_res = std::distance(row_first, row_last) - 1;
//        auto col_res = std::distance(col_first, col_last) - 1;
//        std::cout << row_res + col_res << "\n";
//    }
//    return 0;
//}