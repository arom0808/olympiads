#include <iostream>
#include <string>

std::string plus_str(const std::string &num, std::uint32_t plus_num) {

}

std::uint32_t last_n_digits(const std::string &num, std::uint32_t n) {
    std::uint32_t res = 0, counter = 0, multiplier = 1;
    for (auto it = num.rbegin(); it != num.rend() && counter < n; ++it, ++counter, multiplier *= 10)
        res += ((*it) - '0') * multiplier;
    return res;
}

int main() {
    std::uint32_t K;
    std::string num;
    std::cin >> K >> num;
    if (K == 1) std::cout << 0;
    else if (K == 2) std::cout << (last_n_digits(num, 1) % 2);
    else if (K == 3) {

    } else if (K == 4) std::cout << (last_n_digits(num, 2) % 4);
    else if (K == 5) std::cout << (last_n_digits(num, 1) % 5);
    else if (K == 6)
        return 0;
}
