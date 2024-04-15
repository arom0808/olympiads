#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

class PrefSum {
private:
    std::vector<std::int64_t> pf;

public:
    explicit PrefSum() = default;

    explicit PrefSum(const std::vector<std::int64_t> &arr) {
        rebuild(arr);
    }

    void rebuild(const std::vector<std::int64_t> &arr) {
        pf.resize(arr.size());
        for (std::uint64_t i = 0; i < arr.size(); ++i) pf[i] = (i > 0 ? pf[i - 1] : 0ll) + arr[i];
    }

    [[nodiscard]] std::int64_t sum(std::uint64_t l, std::uint64_t r) const {
        return (r > 0 ? pf[r - 1] : 0ll) - (l > 0 ? pf[l - 1] : 0ll);
    }
};

class FastCols {
    std::vector<std::int64_t> f_cols;
    PrefSum pf;

public:
    FastCols(const std::vector<std::int64_t> &cols, std::uint64_t start, std::uint64_t step = 2) {
        f_cols.reserve(cols.size() / step + 1);
        for (std::uint64_t i = start; i < cols.size(); i += step) f_cols.push_back(cols[i]);
        std::sort(f_cols.begin(), f_cols.end());
        pf.rebuild(f_cols);
    }

    std::uint64_t sum_to_change(std::int64_t ch_val) {
        auto d = std::distance(f_cols.begin(), std::lower_bound(f_cols.begin(), f_cols.end(), ch_val));
        return (ch_val * d - pf.sum(0, d)) + (pf.sum(d, f_cols.size()) - ch_val * (f_cols.size() - d));
    }
};

std::int64_t get_min_arg(const std::function<std::uint64_t(std::int64_t)> &f) {
    std::int64_t a = -1e9;
    while (f(a) > f(a + 1)) a += 1e4;
    while (f(a) > f(a - 1)) --a;
    return a;
}

int main() {
    std::uint64_t n, k;
    std::cin >> n >> k;
    std::vector<std::int64_t> cols(n);
    for (auto &c: cols) std::cin >> c;
    FastCols fs1(cols, 0), fs2(cols, 1);
    auto f1 = [&fs1, &fs2, k](std::int64_t v) { return fs1.sum_to_change(v) + fs2.sum_to_change(v + k); };
    auto f2 = [&fs1, &fs2, k](std::int64_t v) { return fs1.sum_to_change(v) + fs2.sum_to_change(v - k); };
    auto a1 = get_min_arg(f1), a2 = get_min_arg(f2);
    std::cout << std::min(f1(a1), f2(a2));
    return 0;
}
