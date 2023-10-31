#include <iostream>

//#include <vector>
//
//bool is_pal(const std::vector<std::uint32_t> &tt) {
//    auto it1 = tt.begin();
//    auto it2 = tt.rbegin();
//    for (; it1 != tt.end(); ++it1, ++it2) if (*it1 != *it2) return false;
//    return true;
//}
//
//std::uint32_t fb(std::uint32_t n) {
//    for (std::uint32_t b = n - 1; b > 1; --b) {
//        if (n % b == 0) continue;
//        std::vector<std::uint32_t> br;
//        auto num = n;
//        while (num > 0) {
//            br.push_back(num % b);
//            num /= b;
//        }
//        if (is_pal(br)) return b;
//    }
//}
//
int main() {
    std::uint32_t n;
    std::cin >> n;
    std::cout << n - 1;
}

//#include <iostream>
//#include <vector>
//#include <set>
//#include <map>
//
//int main() {
//    std::uint64_t n, k;
//    std::cin >> n >> k;
//    std::vector<std::uint64_t> a(n);
//    for (auto &&el: a) std::cin >> el;
////    std::set<std::vector<std::uint64_t>> rrr;
////    for (std::uint64_t l = 0; l < n; ++l) {
////        for (std::uint64_t r = l + 1; r <= n; ++r) {
////            rrr.emplace(std::next(a.begin(), l), std::next(a.begin(), r));
////        }
////    }
//    std::map<std::uint64_t, std::set<std::uint64_t>> positions;
//    for (std::uint64_t i = 0; i < a.size(); ++i) {
//        auto it = positions.find(a[i]);
//        if (it == positions.end()) positions.emplace(a[i], std::set<std::uint64_t>{i});
//        else it->second.emplace(i);
//    }
//    std::set<std::uint64_t> seta(a.begin(), a.end());
//    std::set<std::vector<std::uint64_t>> mnv;
//    for (const auto &fn: seta) {
//        auto &cp = positions[fn];
//        for (std::uint64_t size = 1; size <= n; ++size) {
//            for (const auto &st_pos: cp) {
//                std::vector<std::uint64_t> ff(std::next(a.begin(), st_pos),
//                                              std::next(a.begin(), st_pos + size < n ? st_pos + size : n));
//                mnv.emplace(std::move(ff));
//            }
//        }
//        if (mnv.size() >= k) break;
//    }
//    if (mnv.size() < k) std::cout << -1;
//    else for (auto num: *std::next(mnv.begin(), k - 1)) std::cout << num << " ";
////    std::cout << "\n";
////    if (rrr.size() < k) std::cout << -1 << "\n";
////    else for (auto num: *std::next(rrr.begin(), k - 1)) std::cout << num << " ";
//}

//#include <iostream>
//#include <vector>
//#include <set>
//#include <map>
//#include <random>
//
//std::random_device dev;
//std::mt19937 rng(dev());
//
//std::int32_t randint(std::int32_t a, std::int32_t b) {
//    return std::uniform_int_distribution(a, b)(rng);
//}
//
//int main() {
//    while (true) {
//        std::uint32_t n = randint(1, 100), k = randint(1, 30);
////    std::cin >> n >> k;
//        std::cout << n << " " << k << "\n";
//        std::vector<std::uint32_t> a(n);
////    for (auto &&el: a) std::cin >> el;
//        for (auto &&el: a) el = randint(1, 1000);
//        for (auto &&el: a) std::cout << el << " ";
//        std::cout << "\n";
//        std::set<std::vector<std::uint32_t>> rrr;
//        for (std::uint32_t l = 0; l < n; ++l) {
//            for (std::uint32_t r = l + 1; r <= n; ++r) {
//                rrr.emplace(std::next(a.begin(), l), std::next(a.begin(), r));
//            }
//        }
//        std::map<std::uint32_t, std::set<std::uint32_t>> positions;
//        for (std::uint32_t i = 0; i < a.size(); ++i) {
//            auto it = positions.find(a[i]);
//            if (it == positions.end()) positions.emplace(a[i], std::set<std::uint32_t>{i});
//            else it->second.emplace(i);
//        }
//        std::set<std::uint32_t> seta(a.begin(), a.end());
//        std::set<std::vector<std::uint32_t>> mnv;
//        for (const auto &fn: seta) {
//            auto &cp = positions[fn];
//            for (std::uint32_t size = 1; size <= n - (*cp.begin()); ++size) {
//                for (const auto &st_pos: cp) {
//                    mnv.emplace(std::next(a.begin(), st_pos),
//                                std::next(a.begin(), st_pos + size < n ? st_pos + size : n));
//                }
//            }
//            if (mnv.size() >= k) break;
//        }
//        if (mnv.size() < k) std::cout << -1;
//        else for (auto num: *std::next(mnv.begin(), k - 1)) std::cout << num << " ";
//        std::cout << "\n";
//        if (rrr.size() < k) std::cout << -1;
//        else for (auto num: *std::next(rrr.begin(), k - 1)) std::cout << num << " ";
//        std::cout << "\n";
//        if ((mnv.size() < k != rrr.size() < k))
//            break;
//        if (mnv.size() >= k && *std::next(mnv.begin(), k - 1) != *std::next(rrr.begin(), k - 1))
//            break;
////        if ((mnv.size() < k != rrr.size() < k) &&
////            *std::next(mnv.begin(), k - 1) != *std::next(rrr.begin(), k - 1))
////            break;
//        std::cout << "\n";
//    }
//}

//#include <iostream>
//#include <vector>
//#include <set>
//#include <random>
//
//std::random_device dev;
//std::mt19937 rng(dev());
//
//std::int32_t randint(std::int32_t a, std::int32_t b) {
//    return std::uniform_int_distribution(a, b)(rng);
//}
//
//int main() {
//    std::vector<std::uint32_t> fff(10);
//    for (auto &&f: fff)
//        f = randint(0, 1);
//    while (true) {
//        std::uint32_t l = randint(0, fff.size() - 1), r = randint(l, fff.size() - 1);
//        std::uint32_t res1 = 0, res2 = 0;
//        for (std::uint32_t l1 = l; l1 <= r; ++l1) {
//            for (std::uint32_t r1 = l1; r1 <= r; ++r1) {
//                for (std::uint32_t i = l1; i <= r1; ++i) {
//                    res1 = (res1 + fff[i]) % 2;
//                }
//            }
//        }
//        for (std::uint32_t i = l; i < r; ++i) res2 = res2 xor fff[i];
//        std::cout << res1 << " " << !res2;
//        if (res1 == res2) return 0;
//        std::cout << "\n";
//    }
//    return 0;
//}
//