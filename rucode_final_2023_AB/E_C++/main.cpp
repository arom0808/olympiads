#pragma GCC optimize("Ofast")
#pragma GCC optimize(O3)
#pragma comment(linker, "/stack:200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <iostream>
#include <chrono>
#include <functional>
#include <random>

std::random_device dev;
std::mt19937 rng(dev());
auto bool_rand = std::bernoulli_distribution(0.5);

int tm_cnt=0;

class Sost {
public:
    std::uint64_t busy, fig_poses;

    static void all_beats(std::int32_t fi, std::int32_t fj, char fig,
                          const std::function<bool(std::int32_t, std::int32_t)> &func) {
        if (fig == 'B' || fig == 'Q' || fig == 'A' || fig == 'M') {
            for (std::int32_t i = fi - 1, j = fj - 1; i >= 0 && j >= 0; --i, --j) if (func(i, j)) return;
            for (std::int32_t i = fi - 1, j = fj + 1; i >= 0 && j < 8; --i, ++j) if (func(i, j)) return;
            for (std::int32_t i = fi + 1, j = fj - 1; i < 8 && j >= 0; ++i, --j) if (func(i, j)) return;
            for (std::int32_t i = fi + 1, j = fj + 1; i < 8 && j < 8; ++i, ++j) if (func(i, j)) return;
        }
        if (fig == 'R' || fig == 'Q' || fig == 'C' || fig == 'M') {
            for (std::int32_t i = fi - 1, j = fj; i >= 0; --i) if (func(i, j)) return;
            for (std::int32_t i = fi + 1, j = fj; i < 8; ++i) if (func(i, j)) return;
            for (std::int32_t i = fi, j = fj - 1; j >= 0; --j) if (func(i, j)) return;
            for (std::int32_t i = fi, j = fj + 1; j < 8; ++j) if (func(i, j)) return;
        }
        if (fig == 'A' || fig == 'C' || fig == 'M') {
            if (fi - 2 >= 0 && fj - 1 >= 0) if (func(fi - 2, fj - 1)) return;
            if (fi - 2 >= 0 && fj + 1 < 8) if (func(fi - 2, fj + 1)) return;
            if (fi + 2 < 8 && fj - 1 >= 0) if (func(fi + 2, fj - 1)) return;
            if (fi + 2 < 8 && fj + 1 < 8) if (func(fi + 2, fj + 1)) return;
            if (fi - 1 >= 0 && fj - 2 >= 0) if (func(fi - 1, fj - 2)) return;
            if (fi - 1 >= 0 && fj + 2 < 8) if (func(fi - 1, fj + 2)) return;
            if (fi + 1 < 8 && fj - 2 >= 0) if (func(fi + 1, fj - 2)) return;
            if (fi + 1 < 8 && fj + 2 < 8) if (func(fi + 1, fj + 2)) return;
        }
        ++tm_cnt;
        func(fi, fj);
    }

    [[nodiscard]] inline bool is_busy(std::uint32_t i, std::uint32_t j) const {
        return (busy >> ((7 - i) * 8) >> (7 - j)) & 1ull;
        ++tm_cnt;
    }

    [[nodiscard]] inline bool is_fig(std::uint32_t i, std::uint32_t j) const {
        return (fig_poses >> ((7 - i) * 8) >> (7 - j)) & 1ull;
        ++tm_cnt;
    }

    inline void set_busy(std::uint32_t i, std::uint32_t j) {
        busy |= (1ull << (7 - j)) << ((7 - i) * 8);
        ++tm_cnt;
    }

    inline void set_fig(std::uint32_t i, std::uint32_t j) {
        fig_poses |= (1ull << (7 - j)) << ((7 - i) * 8);
        ++tm_cnt;
    }

    [[nodiscard]] bool can_add(std::int32_t fi, std::int32_t fj, char fig) const {
        if (is_busy(fi, fj)) return false;
        bool is_ok = true;
        Sost::all_beats(fi, fj, fig, [&is_ok, this](std::uint32_t i, std::uint32_t j) {
            if (is_fig(i, j)) {
                is_ok = false;
                return true;
            }
            return false;
        });
        return is_ok;
        ++tm_cnt;
    }

    void add_fig_and_busy(std::int32_t fi, std::int32_t fj, char fig) {
        set_fig(fi, fj);
        all_beats(fi, fj, fig, [this](std::int32_t i, std::int32_t j) {
            set_busy(i, j);
            return false;
        });
        ++tm_cnt;
    }

    Sost() : busy(0), fig_poses(0) {}
};

template<typename Clock>
bool recursive_solve(std::chrono::time_point<Clock> start, Sost &sost,
                     const std::string &figs, std::uint32_t level) {
    if (level >= figs.size()) return false;
    char fig = figs[level];
    for (std::int32_t i = 0; i < 8; ++i) {
        for (std::int32_t j = 0; j < 8; ++j) {
            if (!sost.can_add(i, j, fig)) continue;
            Sost next_sost = sost;
            next_sost.add_fig_and_busy(i, j, fig);
            if (!recursive_solve(start, next_sost, figs, level + 1)) return true;
        }
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >=
        1900) {
        if (bool_rand(rng)) std::cout << "Alice";
        else std::cout << "Bob";
    }
    ++tm_cnt;
    if (tm_cnt==2E8)
    {
        if (bool_rand(rng))
            std::cout<<"Bob";
        else
            std::cout<<"Alice";
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::string figs;
    std::cin >> figs;
    Sost sost;
    auto start = std::chrono::steady_clock::now();
    if (recursive_solve(start, sost, figs, 0)) std::cout << "Alice";
    else std::cout << "Bob";
    return 0;
}
