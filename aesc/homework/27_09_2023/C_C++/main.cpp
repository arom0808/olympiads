#include <iostream>
#include <iomanip>
#include <cfenv>

#pragma STDC FENV_ACCESS ON

template<typename T>
std::pair<bool, T> fact(std::uint32_t n) {
    T pre_fact = 1, fact = 1;
    for (std::uint32_t i = 1; i <= n; ++i) {
        fact *= i;
        if (fact / i != pre_fact) return {false, fact};
        if (std::fetestexcept(FE_INEXACT | FE_ALL_EXCEPT)) {
            std::feclearexcept(FE_INEXACT | FE_ALL_EXCEPT);
            return {false, fact};
        }
        pre_fact = fact;
    }
    return {true, fact};
}

int main() {
    std::uint32_t k;
    std::cin >> k;
    std::cout << std::fixed << std::setprecision(0);
    for (std::uint32_t i = 0, n; i < k; ++i) {
        std::cin >> n;
        auto f1 = fact<std::uint32_t>(n);
        auto f2 = fact<std::uint64_t>(n);
        auto f3 = fact<long double>(n);
        if (f1.first) std::cout << f1.second << " 1\n";
        else if (f2.first) std::cout << f2.second << " 2\n";
        else if (f3.first) std::cout << f3.second << " 3\n";
        else std::cout << "0\n";
    }
    return 0;
}