#include <iostream>
#include <vector>
#include <fstream>
#include <map>

int main() {
    std::uint16_t n, nn = 0;
    std::uint64_t d;
    std::uint64_t *a, *d_i;
    std::ifstream i_f("gcd.in");
    i_f >> n >> d;
    a = new std::uint64_t[n];
    d_i = new std::uint64_t[n];
    for (std::size_t i = 0; i < n; ++i)
        i_f >> a[i];
    i_f.close();
    for (std::size_t i = 0; i < n; ++i) {
        if (a[i] % d == 0) {
            d_i[nn] = a[i];
            ++nn;
        }
    }
    if (nn == 0) {
        std::ofstream o_f("gcd.out");
        o_f << -1;
        o_f.close();
        return 0;
    }
    for (std::size_t i = 0; i < nn; ++i) {
        bool is_bigdel = true;
        for (auto t = d + 1; t < d_i[i]; ++t) {
            if (d_i[i] % t == 0) {
                is_bigdel = false;
                break;
            }
        }
        if (is_bigdel) {
            std::ofstream o_f("gcd.out");
            o_f << nn << '\n';
            for (std::size_t j = 0; j < nn; ++j) {
                o_f << d_i[j] << " ";
            }
            o_f.close();
            return 0;
        }
    }
    std::ofstream o_f("gcd.out");
    o_f << -1;
    o_f.close();
    return 0;
}
