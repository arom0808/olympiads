#include<iostream>

int la(int n, int m) {
    if (n < 0 || m <= 0) return 0;
    if(m==1)
}

int main() {
    std::uint32_t num;
    std::cin >> num;

}

//#include <iostream>
//#include <vector>
//#include <queue>
//
//const std::uint64_t ev_max_n = 2e9;
//
//const std::vector<std::pair<std::uint64_t, std::vector<std::uint64_t>>> easy_nums{
//        {
//                2,  {
//                            1, 2,  4,    8,      16,       32,       64,       128,      256,     512,      1024,      2048,     4096,      8192,    16384,   32768,    65536,    131072,    262144,    524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824,}},
//        {
//                3,  {
//                            1, 3,  9,    27,     81,       243,      729,      2187,     6561,    19683,    59049,     177147,   531441,    1594323, 4782969, 14348907, 43046721, 129140163, 387420489, 1162261467,}},
//        {
//                5,  {
//                            1, 5,  25,   125,    625,      3125,     15625,    78125,    390625,  1953125,  9765625,   48828125, 244140625, 1220703125,}},
//        {
//                7,  {
//                            1, 7,  49,   343,    2401,     16807,    117649,   823543,   5764801, 40353607, 282475249, 1977326743,}},
//        {
//                11, {
//                            1, 11, 121,  1331,   14641,    161051,   1771561,  19487171, 214358881,}},
//        {
//                13, {
//                            1, 13, 169,  2197,   28561,    371293,   4826809,  62748517, 815730721,}},
//        {
//                17, {
//                            1, 17, 289,  4913,   83521,    1419857,  24137569, 410338673,}},
//        {
//                19, {
//                            1, 19, 361,  6859,   130321,   2476099,  47045881, 893871739,}},
//        {
//                23, {
//                            1, 23, 529,  12167,  279841,   6436343,  148035889,}},
//        {
//                29, {
//                            1, 29, 841,  24389,  707281,   20511149, 594823321,}},
//        {
//                31, {
//                            1, 31, 961,  29791,  923521,   28629151, 887503681,}},
//        {
//                37, {
//                            1, 37, 1369, 50653,  1874161,  69343957,}},
//        {
//                41, {
//                            1, 41, 1681, 68921,  2825761,  115856201,}},
//        {
//                43, {
//                            1, 43, 1849, 79507,  3418801,  147008443,}},
//        {
//                47, {
//                            1, 47, 2209, 103823, 4879681,  229345007,}},
//        {
//                53, {
//                            1, 53, 2809, 148877, 7890481,  418195493,}},
//        {
//                59, {
//                            1, 59, 3481, 205379, 12117361, 714924299,}},
//        {
//                61, {
//                            1, 61, 3721, 226981, 13845841, 844596301,}},
//        {
//                67, {
//                            1, 67, 4489, 300763, 20151121, 1350125107,}},
//        {
//                71, {
//                            1, 71, 5041, 357911, 25411681, 1804229351,}},
//        {
//                73, {
//                            1, 73, 5329, 389017, 28398241,}},
//        {
//                79, {
//                            1, 79, 6241, 493039, 38950081,}},
//        {
//                83, {
//                            1, 83, 6889, 571787, 47458321,}},
//        {
//                89, {
//                            1, 89, 7921, 704969, 62742241,}},
//        {
//                97, {
//                            1, 97, 9409, 912673, 88529281,}},};
//
//std::uint64_t mult_counts(const std::vector<std::uint64_t> &mults_pows) {
//    std::uint64_t res = 1;
//    for (const auto &mp: mults_pows) res *= mp + 1;
//    return res;
//}
//
//void Rec(std::vector<std::pair<std::uint64_t, std::vector<std::uint64_t>>>::const_iterator ea_start,
//         std::vector<std::pair<std::uint64_t, std::vector<std::uint64_t>>>::const_iterator ea_end,
//         std::uint64_t max_pow, std::uint64_t pre_mult_num, std::uint64_t max_max_num,
//         std::uint64_t pre_dels_cnt, std::uint64_t &max_mults_num, std::uint64_t &max_mults_count) {
//    if (pre_dels_cnt > max_mults_count || (pre_dels_cnt == max_mults_count && pre_mult_num > max_mults_num)) {
//        max_mults_num = pre_mult_num;
//        max_mults_count = pre_dels_cnt;
//    }
//    std::uint64_t max_this_pow = std::min<std::uint64_t>(max_pow, ea_start->second.size());
//    for (std::uint64_t this_pow = max_this_pow; this_pow > 0; --this_pow) {
//        if (pre_mult_num * ea_start->second[this_pow] > max_max_num) continue;
//        Rec(std::next(ea_start), ea_end, this_pow, pre_mult_num * ea_start->second[this_pow],
//            max_max_num, pre_dels_cnt * (this_pow + 1), max_mults_num, max_mults_count);
//    }
//}
//
//struct DataT {
//    std::vector<std::pair<std::uint64_t, std::vector<std::uint64_t>>>::const_iterator ea_start;
//    std::uint64_t max_pow, pre_mult_num, pre_dels_cnt;
//};
//
//int main() {
//    std::uint64_t N;
//    std::cin >> N;
//    std::uint64_t max_size = 1;
//    for (auto num = easy_nums[max_size].first; num <= ev_max_n; num *= easy_nums[max_size++].first) {}
//    std::uint64_t max_mults_num = 1;
//    std::uint64_t max_mults_count = 1;
//    for (std::uint64_t size = 1; size < max_size; ++size) {
//        std::queue<DataT> que;
//        que.push(DataT{easy_nums.begin(), 1000, 1, 1});
//        while (!que.empty()) {
//            auto req = que.front();
//            que.pop();
//            if (req.pre_dels_cnt > max_mults_count ||
//                (req.pre_dels_cnt == max_mults_count && req.pre_mult_num > max_mults_num)) {
//                max_mults_num = req.pre_mult_num;
//                max_mults_count = req.pre_dels_cnt;
//            }
//            std::uint64_t max_this_pow = std::min<std::uint64_t>(req.max_pow, req.ea_start->second.size());
//            for (std::uint64_t this_pow = max_this_pow; this_pow > 0; --this_pow) {
//                if (req.pre_mult_num * req.ea_start->second[this_pow] > N) continue;
//                que.push(DataT{std::next(req.ea_start), this_pow, req.pre_mult_num * req.ea_start->second[this_pow],
//                               req.pre_dels_cnt * (this_pow + 1)});
//            }
//        }
//    }
//    std::cout << max_mults_num;
//    return 0;
//}
//
////    std::ofstream out("out.txt");
////    out << "const std::vector<std::pair<std::uint64_t,std::vector<std::uint64_t>>> {";
////    for (const auto &_en: easy_nums) {
////        out << "{" << _en << ",{";
////        for (std::uint64_t i = 0, f = _en; i < 32 && f <= 2e9; ++i, f *= _en) {
////            out << f << ",";
////        }
////        out << "}},";
////    }
////    out << "};";
