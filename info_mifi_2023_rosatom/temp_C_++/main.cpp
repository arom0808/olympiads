//#include <iostream>
//#include <numeric>
//#include <vector>
//
//std::int64_t GetPreSum(const std::vector<std::vector<std::int64_t>> &summs, std::int64_t i, std::int64_t j) {
//    std::int64_t res = 0;
//    if (i > 0) res += summs[i - 1][j];
//    if (j > 0) res += summs[i][j - 1];
//    if (i > 0 && j > 0) res -= summs[i - 1][j - 1];
//    return res;
//}
//
//std::int64_t
//GetSum(const std::vector<std::vector<std::int64_t>> &summs, std::int64_t i1, std::int64_t j1, std::int64_t i2,
//       std::int64_t j2) {
//    std::int64_t res = summs[i2 - 1][j2 - 1];
//    if (i1 > 0 && j1 > 0) res += summs[i1 - 1][j1 - 1];
//    if (i1 > 0) res -= summs[i1 - 1][j2 - 1];
//    if (j1 > 0) res -= summs[i2 - 1][j1 - 1];
//    return res;
//}
//
//int main() {
//    std::int64_t N, M;
//    std::cin >> N >> M;
//    std::vector<std::vector<std::int64_t>> map(N, std::vector<std::int64_t>(M, 0)), summs(map);
//    for (std::int64_t i = 0; i < N; ++i) {
//        for (std::int64_t j = 0; j < M; ++j) {
//            std::cin >> map[i][j];
//            summs[i][j] = GetPreSum(summs, i, j) + map[i][j];
//        }
//    }
//    std::int64_t max_pribil = 0;
//    for (std::int64_t start_i = 0; start_i < N; ++start_i) {
//        for (std::int64_t start_j = 0; start_j < M; ++start_j) {
//            for (std::int64_t end_i = start_i + 1; end_i <= N; ++end_i) {
//                for (std::int64_t end_j = start_j + 1; end_j <= M; ++end_j) {
//                    std::int64_t pribil = 0;
//                    for (auto i = start_i; i < end_i; ++i) {
//                        for (auto j = start_j; j < end_j; ++j) {
//                            pribil += map[i][j];
//                        }
//                    }
//                    if (pribil > max_pribil) max_pribil = pribil;
//                }
//            }
//        }
//    }
//    std::cout << max_pribil;
//    return 0;
//}


#include<iostream>
#include<unordered_map>
#include <vector>

struct pair_hash {
    std::size_t operator()(const std::pair<std::uint32_t, std::uint32_t> &p) const {
        return (static_cast<std::size_t>(p.first) << 32) & static_cast<std::size_t>(p.second);
    }
};

void GetDp(std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, std::uint32_t, pair_hash> &dp,
           std::uint32_t pre_d, std::uint32_t size) {
    if (size == 1) {

    }
}

int main() {
    std::unordered_map<std::pair<std::uint32_t, std::uint32_t>, std::uint32_t, pair_hash> dp;
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::vector<bool>> sovmest(N, std::vector<bool>(N, false));
    bool is_all_1 = true, temp_bool;
    for (std::uint32_t i = 0; i < N; ++i) {
        for (std::uint32_t j = 0; j < N; ++j) {
            std::cin >> temp_bool;
            sovmest[i][j] = temp_bool;
            if (!sovmest[i][j]) is_all_1 = false;
        }
    }
    std::uint32_t M;
    std::cin >> M;
    if (is_all_1) {
        std::uint64_t mod = 1000000007;
        std::uint64_t result = 1;
        for (std::uint32_t i = 0; i < M; ++i) {
            result = ((result % mod) * (N % mod)) % mod;
        }
        std::cout << result;
    }
}