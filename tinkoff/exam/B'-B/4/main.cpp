#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <random>
#include <map>
#include <ctime>

//void
//SubSet(std::vector<std::uint32_t>::const_iterator current,
//       std::vector<std::uint32_t>::const_iterator end,
//       std::vector<std::uint32_t> &res_arr,
//       const std::function<void(const std::vector<std::uint32_t> &)> &callback) {
//    if (std::next(current) == end) { if (!res_arr.empty()) callback(res_arr); }
//    else SubSet(std::next(current), end, res_arr, callback);
//    res_arr.push_back((*current));
//    if (std::next(current) == end) { if (!res_arr.empty()) callback(res_arr); }
//    else SubSet(std::next(current), end, res_arr, callback);
//    res_arr.pop_back();
//}


//void print_uint64_t(std::uint64_t number) {
//    for (std::uint32_t i = 0; i < 64; ++i) std::cout << ((number & (1ULL << i)) != 0);
//    std::cout << std::endl;
//}
//
//std::size_t mex_max = 100032;
//std::size_t mex_size = 64;
//std::size_t mex_bits_size = mex_max / mex_size; // 1563
//std::uint64_t *mex_bits = new std::uint64_t[mex_bits_size];
//std::uint64_t mex_zero = 0;
//std::uint64_t mex_one = 1;
//std::uint64_t mex_uint64_t_max = std::numeric_limits<std::uint64_t>::max();
//
//std::uint32_t MEX(const std::vector<std::uint32_t> &numbers_subset) {
////    for (const auto &num: numbers_subset) {
////        std::cout << num << " ";
////    }
////    std::cout << std::endl;
//    std::size_t local_mex_size = (numbers_subset.size() >> 6);
//    if (local_mex_size < mex_bits_size) ++local_mex_size;
//    for (std::uint32_t i = 0; i <= numbers_subset.size(); ++i)
//        if (numbers_subset[i] <= numbers_subset.size())
//            mex_bits[(numbers_subset[i] >> 6)] |= (mex_one << (numbers_subset[i] % mex_size));
////    print_uint64_t(mex_bits[0]);
//    std::uint32_t result = 0;
//    for (std::uint32_t i = 0; i < numbers_subset.size(); ++i) {
//        bool is_break = false;
//        if (mex_bits[i] != mex_uint64_t_max) {
//            for (int j = 0; j < mex_size; j++) {
//                if ((mex_bits[i] & (mex_one << j)) == 0) {
//                    result = i * mex_size + j;
//                    is_break = true;
//                    break;
//                }
//            }
//        }
//        if (is_break)break;
//    }
//    mex_bits[0] = mex_one;
//    for (std::uint32_t i = 1; i < mex_bits_size; ++i) mex_bits[i] = mex_zero;
//    if (result != 0) return result;
//    return numbers_subset.size() + 1;
//}

// MEX test
//
//int main() {
//    std::cout << MEX({0});
//    return 0;
//}
//
//std::map<std::vector<std::uint32_t>, std::uint32_t> mex_buf;

std::uint32_t GetGCDOfMEXs_q(std::vector<uint32_t>::const_iterator begin, std::vector<uint32_t>::const_iterator end) {
//    std::uint32_t result = 0;
//    std::uint32_t numbers_size = std::distance(begin, end);
    std::uint32_t res = 1;
    if (std::next(begin) == end && (*begin) == 1) res = 2;
    return res;
//    temp.reserve(numbers_size);
//    SubSet(begin, end, temp,
//           [&result](const std::vector<std::uint32_t> &numbers_subset) {
////               auto buf_res = mex_buf.find(numbers_subset);
//               std::uint32_t mex;
////               if (buf_res != mex_buf.end()) mex = buf_res->second;
////               else {
//               mex = MEX(numbers_subset);
////                   mex_buf.emplace(numbers_subset, mex);
////               }
//               if (result == 0) result = mex;
//               else result = std::gcd(result, mex);
//           });
//    return result;
}
//
//std::uint32_t GetGCDOfMEXs_n(std::vector<uint32_t>::const_iterator begin, std::vector<uint32_t>::const_iterator end) {
//    std::uint32_t result = 0;
//    std::uint32_t numbers_size = std::distance(begin, end);
////    if (std::find(begin, end, 1u) == end) return 1;
////    if (std::next(begin) == end) return 2;
////    return 1;
//    std::vector<std::uint32_t> temp;
//    temp.reserve(numbers_size);
//    SubSet(begin, end, temp,
//           [&result](const std::vector<std::uint32_t> &numbers_subset) {
////               auto buf_res = mex_buf.find(numbers_subset);
//               std::uint32_t mex;
////               if (buf_res != mex_buf.end()) mex = buf_res->second;
////               else {
//               mex = MEX(numbers_subset);
////                   mex_buf.emplace(numbers_subset, mex);
////               }
//               if (result == 0) result = mex;
//               else result = std::gcd(result, mex);
//           });
//    return result;
//}

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> numbers;
    numbers.reserve(n);
    for (std::uint32_t i = 0; i < n; ++i) {
        std::uint32_t temp;
        std::cin >> temp;
        numbers.push_back(temp);
    }
    std::uint32_t q;
    std::cin >> q;
    std::vector<std::uint32_t> results;
    results.reserve(q);
    for (std::uint32_t i = 0; i < q; ++i) {
        std::uint32_t l, r;
        std::cin >> l >> r;
        results.push_back(GetGCDOfMEXs_q(std::next(numbers.begin(), l - 1), std::next(numbers.begin(), r)));
    }
    for (const auto &res: results) {
        std::cout << res << std::endl;
    }
    return 0;
}

//int main() {
////    std::vector<std::uint32_t> rrr_numbers = {13, 1};
////    std::uint32_t rrr_l = 1, rrr_r = 2;
////    std::uint32_t rrr_res = GetGCDOfMEXs_n(std::next(rrr_numbers.begin(), rrr_l - 1),
////                                           std::next(rrr_numbers.begin(), rrr_r));
////    std::cout << rrr_res;
//
//    std::random_device rd;
//    std::mt19937 gen(time(0));
//    std::uniform_int_distribution<std::uint32_t> dist_1(1, 10);
//    std::uniform_int_distribution<std::uint32_t> dist_2(1, 50);
//    for (std::uint32_t qq = 0; qq < 100; ++qq) {
//        std::uint32_t n = 10;
//        std::vector<std::uint32_t> numbers;
//        for (std::uint32_t i = 0; i < n; ++i) {
//            std::uint32_t temp = dist_2(gen);
//            while (std::find(numbers.begin(), numbers.end(), temp) != numbers.end()) temp = dist_2(gen);
//            numbers.push_back(temp);
//        }
//        std::cout << "numbers: " << std::endl;
//        for (const auto &num: numbers) std::cout << num << " ";
//        std::cout << std::endl << std::endl;
//        std::uint32_t q = 100;
//        std::vector<std::uint32_t> results_n, results_q;
//        results_n.reserve(q);
//        results_q.reserve(q);
//        for (std::uint32_t i = 0; i < q; ++i) {
//            std::cout << "i: " << i << std::endl;
//            std::uint32_t l = dist_1(gen), r = dist_1(gen);
//            if (l > r) std::swap(l, r);
//            if (l == r) continue;
//            std::cout << "l: " << l << std::endl;
//            std::cout << "r: " << r << std::endl;
//            results_q.push_back(GetGCDOfMEXs_q(std::next(numbers.begin(), l - 1), std::next(numbers.begin(), r)));
//            std::cout << "quick: " << results_q[i] << std::endl;
//            results_n.push_back(GetGCDOfMEXs_n(std::next(numbers.begin(), l - 1), std::next(numbers.begin(), r)));
//            std::cout << "normal: " << results_n[i] << std::endl;
//            if (results_n[i] != results_q[i]) {
//                results_n[i] = GetGCDOfMEXs_n(std::next(numbers.begin(), l - 1), std::next(numbers.begin(), r));
//                std::cout << "normal_2: " << results_n[i] << std::endl;
//                results_q[i] = GetGCDOfMEXs_q(std::next(numbers.begin(), l - 1), std::next(numbers.begin(), r));
//                std::cout << "quick_2: " << results_q[i] << std::endl;
//                if (results_n[i] == results_q[i]) continue;
//                std::vector<std::uint32_t> for_print(std::next(numbers.begin(), l - 1), std::next(numbers.begin(), r));
//                std::cout << "numbers: ";
//                for (const auto &num: for_print) {
//                    std::cout << num << " ";
//                }
//                std::cout << std::endl;
//                std::cout << "Not equal" << std::endl;
//                return 0;
//            }
//        }
//    }
//    return 0;
//}

//
//int main() {
//    std::cout << 324234 / 64 << std::endl;
//    std::cout << (324234 >> 6) << std::endl;
//    std::cout << mex_first_bit_only;
//    return 0;
//}