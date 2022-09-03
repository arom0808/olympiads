#include <iostream>

inline bool IsNormal(const std::uint32_t &L, const std::uint32_t &d, const std::uint32_t &a, const std::uint32_t &N,
                     const std::uint32_t &W, const std::uint32_t &x) {
    for (std::uint32_t i = x; i < x + (N * W); i += W) {
        bool is_s_f = false, is_e_f = false;
        for (std::uint32_t j = i; j < i + W; ++j) {
            if (j < a)
                continue;
            if ((j - a) % (L + d) == 0)
                is_s_f = true;
            if ((j - a) % (L + d) == L)
                if (is_s_f)
                    is_e_f = true;
        }
        if (!is_e_f)
            return false;
    }
    return true;
}

int main() {
    std::uint32_t L, d, a, N, W;
    std::cin >> L >> d >> a >> N >> W;
    for (std::uint32_t x = 0; x < L + d; ++x) {
        if (IsNormal(L, d, a, N, W, x)) {
            std::cout << x;
            return 0;
        }
    }
    return 0;
}
