#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

class RootArr {
private:
    struct Elem {
        std::vector<std::int64_t> raw_arr;
        std::vector<std::int64_t> sorted_arr;
        std::int64_t mod;

        void rebuild() {
            sorted_arr = raw_arr;
            std::sort(sorted_arr.begin(), sorted_arr.end());
        }

        std::uint64_t full_lower_cnt(std::int64_t num) {
            return std::distance(sorted_arr.begin(), std::lower_bound(sorted_arr.begin(), sorted_arr.end(), num - mod));
        }

        explicit Elem(std::uint64_t n) : raw_arr(n), sorted_arr(n), mod(0) {}
    };

    std::uint64_t size, el_size, el_cnt;
    std::vector<Elem> elems;

    static std::uint64_t el_size_by_size(std::uint64_t size) {
        return static_cast<std::uint64_t>(std::sqrt(static_cast<double>(size))) + 1;
    }

    RootArr(std::uint64_t n, const std::function<std::int64_t(std::uint64_t)> &f)
            : size(n), el_size(RootArr::el_size_by_size(n)), el_cnt(size / el_size + (size % el_size != 0)) {
        elems.reserve(el_cnt);
        for (std::uint64_t i = 0; i + 1 < el_cnt; ++i) elems.emplace_back(el_size);
        elems.emplace_back(size % el_size != 0 ? size % el_size : el_size);
        for (std::uint64_t i = 0; i < size; ++i) elems[i / el_size].raw_arr[i % el_size] = f(i);
        for (auto &&elem: elems) elem.rebuild();
    }

public:
    RootArr(std::uint64_t n, std::istream &istream)
            : RootArr(n, [&istream](std::int64_t num) {
        istream >> num;
        return num;
    }) {}

    std::uint64_t lower_cnt(std::uint64_t l, std::uint64_t r, std::int64_t num) {
        std::uint64_t ptr = l, res = 0;
        while (ptr < r) {
            if (ptr % el_size == 0 && ptr + el_size <= r) {
                res += elems[ptr / el_size].full_lower_cnt(num);
                ptr += el_size;
            } else {
                res += elems[ptr / el_size].raw_arr[ptr % el_size] + elems[ptr / el_size].mod < num;
                ++ptr;
            }
        }
        return res;
    }

    void add(std::uint64_t l, std::uint64_t r, std::int64_t num) {
        std::uint64_t ptr = l;
        while (ptr < r) {
            if (ptr % el_size == 0 && ptr + el_size <= r) {
                elems[ptr / el_size].mod += num;
                ptr += el_size;
            } else {
                elems[ptr / el_size].raw_arr[ptr % el_size] += num;
                if ((ptr + 1) % el_size == 0 || ptr + 1 == r) elems[ptr / el_size].rebuild();
                ++ptr;
            }
        }
    }
};

int main() {
    std::uint64_t n, q;
    std::cin >> n >> q;
    RootArr ra(n, std::cin);
    std::int64_t x;
    for (std::uint64_t i = 0, t, l, r; i < q; ++i) {
        std::cin >> t >> l >> r >> x;
        if (t == 1) std::cout << ra.lower_cnt(l - 1, r, x) << "\n";
        else ra.add(l - 1, r, x);
    }
    return 0;
}