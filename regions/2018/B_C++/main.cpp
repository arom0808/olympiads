#include <iostream>
#include <cmath>
#include <vector>

int main() {
    std::uint64_t a, b, k;
    std::cin >> a >> b >> k;
    auto gl_a_sqrt = static_cast<std::uint64_t>(sqrt(static_cast<long double>(a))),
            gl_a_cbrt = static_cast<std::uint64_t>(cbrt(static_cast<long double>(a)));
    std::uint64_t result = 0;
    if (gl_a_sqrt * gl_a_sqrt < a) ++gl_a_sqrt;
    if (gl_a_cbrt * gl_a_cbrt * gl_a_cbrt < a) ++gl_a_cbrt;
    for (std::uint64_t cube = gl_a_cbrt, cube_res = cube * cube * cube;
         cube_res <= b; ++cube, cube_res = cube * cube * cube) {
        std::uint64_t L = (cube_res >= k ? std::max(cube_res - k, a) : a);
        std::uint64_t R = std::min(cube_res + k, b);
        long double l_sqrt_ld = sqrt(static_cast<long double>(L));
        long double r_sqrt_ld = sqrt(static_cast<long double>(R));
        std::uint64_t l_sqrt, r_sqrt;
        if (l_sqrt_ld - static_cast<long double>(static_cast<std::uint64_t>(l_sqrt_ld)) > 1e-10)
            l_sqrt = static_cast<std::uint64_t>(l_sqrt_ld) + 1;
        else l_sqrt = static_cast<std::uint64_t>(l_sqrt_ld);
        r_sqrt = static_cast<std::uint64_t>(r_sqrt_ld);
        result += 1;
        result += r_sqrt;
        result -= l_sqrt;
    }
    std::cout << result;
    return 0;
}
