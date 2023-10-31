#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
//#include <chrono>

//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("vpt")
//#pragma GCC optimize("rename-registers")
//#pragma GCC optimize("move-loop-invariants")
//#pragma GCC optimize("unswitch-loops")
//#pragma GCC optimize(3)
//#pragma GCC optimize("O3")
//#pragma GCC optimize("inline")
//#pragma GCC optimize("-fgcse")
//#pragma GCC optimize("-fgcse-lm")
//#pragma GCC optimize("-fipa-sra")
//#pragma GCC optimize("-ftree-pre")
//#pragma GCC optimize("-ftree-vrp")
//#pragma GCC optimize("-fpeephole2")
//#pragma GCC optimize("-fsched-spec")
//#pragma GCC optimize("-falign-jumps")
//#pragma GCC optimize("-falign-loops")
//#pragma GCC optimize("-falign-labels")
//#pragma GCC optimize("-fdevirtualize")
//#pragma GCC optimize("-fcaller-saves")
//#pragma GCC optimize("-fcrossjumping")
//#pragma GCC optimize("-fthread-jumps")
//#pragma GCC optimize("-freorder-blocks")
//#pragma GCC optimize("-fschedule-insns")
//#pragma GCC optimize("inline-functions")
//#pragma GCC optimize("-ftree-tail-merge")
//#pragma GCC optimize("-fschedule-insns2")
//#pragma GCC optimize("-fstrict-aliasing")
//#pragma GCC optimize("-falign-functions")
//#pragma GCC optimize("-fcse-follow-jumps")
//#pragma GCC optimize("-fsched-interblock")
//#pragma GCC optimize("-fpartial-inlining")
//#pragma GCC optimize("-freorder-functions")
//#pragma GCC optimize("-findirect-inlining")
//#pragma GCC optimize("-fhoist-adjacent-loads")
//#pragma GCC optimize("-frerun-cse-after-loop")
//#pragma GCC optimize("inline-small-functions")
//#pragma GCC optimize("-finline-small-functions")
//#pragma GCC optimize("-ftree-switch-conversion")
//#pragma GCC optimize("-foptimize-sibling-calls")
//#pragma GCC optimize("-fexpensive-optimizations")
//#pragma GCC optimize("inline-functions-called-once")
//#pragma GCC optimize("-fdelete-null-pointer-checks")

class pv {
public:
    std::int32_t x, y;

    pv(std::int32_t x = 0, std::int32_t y = 0) : x(x), y(y) {}

    pv operator-(const pv &other) const { return {x - other.x, y - other.y}; }

    std::int32_t operator*(const pv &other) const { return x * other.x + y * other.y; }

    std::int32_t operator^(const pv &other) const { return x * other.y - y * other.x; }

    pv &operator=(const pv &other) = default;

    double length() const { return std::sqrt(static_cast<double>(x * x + y * y)); }

    double angle(const pv &other) const {
        return std::atan2(static_cast<double>((*this) ^ other), static_cast<double>((*this) * other));
    }
};

//bool is_round_eq(const double &a, const double &b) { return std::abs(a - b) < 1; }

bool check_shift(const std::vector<std::int64_t> &first_params,
                 const std::vector<std::int64_t> &second_params, std::uint32_t shift) {
    for (std::uint32_t i = 0; i < first_params.size(); ++i) {
        const auto &fp = first_params[i],
                &sp = second_params[(shift + i) % second_params.size()];
//        if (!(is_round_eq(fp.first, sp.first) && is_round_eq(fp.second, sp.second))) return false;
        if (fp != sp) return false;
    }
    return true;
}

const double multiplier = 1e6;

inline std::int64_t int_round(const double &num) { return static_cast<std::int64_t>(std::round(num)); }

std::uint32_t resolve() {
//    auto start = std::chrono::steady_clock::now();
    std::uint32_t N;
    std::cin >> N;
    std::vector<pv> first_path(N), second_path(N);
    for (auto &&pv: first_path) std::cin >> pv.x >> pv.y;
    for (auto &&pv: second_path) std::cin >> pv.x >> pv.y;
    std::vector<std::int64_t> first_params(N), sec_params(N);
    pv pre_first_vec = first_path[1] - first_path[0],
            pre_sec_vec = second_path[1] - second_path[0], first_vec, sec_vec;
    for (std::uint32_t i = 1; i <= N; ++i) {
        first_vec = first_path[(i + 1) % N] - first_path[i % N];
        sec_vec = second_path[(i + 1) % N] - second_path[i % N];
        first_params[i % N] = int_round(first_vec.length() / pre_first_vec.length() * multiplier) << 32;
        first_params[i % N] |= int_round(pre_first_vec.angle(first_vec) * multiplier);
        sec_params[i % N] = int_round(sec_vec.length() / pre_sec_vec.length() * multiplier) << 32;
        sec_params[i % N] |= int_round(pre_sec_vec.angle(sec_vec) * multiplier);
        pre_first_vec = first_vec;
        pre_sec_vec = sec_vec;
    }
    std::map<std::uint64_t, std::uint32_t> fcs, scs;
    for (std::uint32_t i = 0; i < N; ++i) {
        auto a = fcs.find(first_params[i]), b = scs.find(sec_params[i]);
        if (a == fcs.end()) fcs.emplace(first_params[i], 1);
        else ++a->second;
        if (b == scs.end()) scs.emplace(sec_params[i], 1);
        else ++b->second;
    }
    std::uint32_t min_sec_cnt = scs.begin()->second;
    if (fcs.size() != scs.size()) return 0;
    for (auto it1 = fcs.begin(), it2 = scs.begin(); it1 != fcs.end() && it2 != scs.end(); ++it1, ++it2) {
        if (it1->first != it2->first || it1->second != it2->second) return 0;
        if (it2->second < min_sec_cnt) min_sec_cnt = it2->second;
    }
    std::map<std::uint32_t, std::set<std::uint64_t>> cnt_first;
    for (const auto &[param, cnt]: fcs) {
        auto it = cnt_first.find(cnt);
        if (it == cnt_first.end()) cnt_first.emplace(cnt, std::set<std::uint64_t>{param});
        else it->second.emplace(param);
    }
    std::uint64_t start_param = *cnt_first.begin()->second.begin();
    std::uint64_t start_cnt = cnt_first.begin()->first * scs[start_param];
    for (const auto &[cnt, fps]: cnt_first) {
        if (cnt * min_sec_cnt >= start_cnt) break;
        for (const auto &param: fps) {
            std::uint32_t sec_cnt = scs[param];
            if (cnt * sec_cnt < start_cnt) {
                start_cnt = cnt * sec_cnt;
                start_param = param;
                if (cnt * min_sec_cnt >= start_cnt) break;
            }
        }
    }
    std::set<std::uint32_t> fpi, spi;
    for (std::uint32_t i = 0; i < N; ++i) {
        if (first_params[i] == start_param) fpi.emplace(i);
        if (sec_params[i] == start_param) spi.emplace(i);
    }
    std::set<std::uint32_t> shiftes;
    for (const auto &first_start: fpi) {
        for (const auto &sec_start: spi) {
            shiftes.emplace((sec_start + N - first_start) % N);
        }
    }
    for (const auto &shift: shiftes) {
        if (first_params[0] != sec_params[shift]) continue;
        if (!check_shift(first_params, sec_params, shift)) continue;
        return shift + 1;
    }
//    for (std::uint32_t shift = 0; shift < N; ++shift) {
//        auto now = std::chrono::steady_clock::now();
//        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() > 1970) break;
//        if (first_params[0] != sec_params[shift]) continue;
//        if (!check_shift(first_params, sec_params, shift)) continue;
//        return shift + 1;
//    }
    return 0;
}

int main() {
    std::cout << resolve();
    return 0;
}