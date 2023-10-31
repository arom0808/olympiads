#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::int64_t ia, ib, ic;
    std::cin >> ia >> ib >> ic;
    if (ia == 0) {
        if (ib == 0) {
            if (ic == 0) std::cout << "-1";
            else std::cout << "0";
        } else {
            long double x = -(static_cast<long double>(ic) / static_cast<long double>(ib));
            std::cout << "1 " << x;
        }
    } else {
        std::int64_t iD = ib * ib - 4 * ia * ic;
        if (iD >= 0) {
            auto a = static_cast<long double>(ia), b = static_cast<long double>(ib), D = static_cast<long double>(iD);
            if (iD > 0) {
                auto sqrtD = std::sqrt(D);
                auto x1 = (-b - sqrtD) / (a + a), x2 = (-b + sqrtD) / (a + a);
                if (x1 > x2) std::swap(x1, x2);
                std::cout << "2 " << x1 << " " << x2;
            } else std::cout << "3 " << ((-b) / (a + a));
        } else {
            std::cout << "0";
        }
    }
    return 0;
}
