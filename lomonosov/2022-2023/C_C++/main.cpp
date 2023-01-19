#include <iostream>
#include <vector>
#include <algorithm>

std::uint32_t GetCasePrice(const std::string &str) {
    std::uint32_t result = 0;
    for (const auto ch: str) {
        if (ch == 'a') ++result;
        else if (ch == 'b') result += 5;
        else if (ch == 'c') result += 10;
        else if (ch == 'd') result += 50;
        else if (ch == 'e') result += 100;
        else if (ch == 'f') result += 200;
        else if (ch == 'g') result += 500;
        else if (ch == 'h') result += 1000;
        else if (ch == 'i') result += 2500;
    }
    return result;
}

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::string buffer;
    std::vector<std::uint32_t> cases(N);
    for (auto &&cur_case: cases) {
        std::cin >> buffer;
        cur_case = GetCasePrice(buffer);
    }
    std::uint32_t k = 0, l = 1;
    for (std::uint32_t i = 1; i < N; ++i) {
        for (std::uint32_t j = 0; j < i; ++j) {
            if (cases[i] + cases[j] > cases[k] + cases[l]) {
                k = i;
                l = j;
            } else if (cases[i] + cases[j] == cases[k] + cases[l] && i + j < k + l) {
                k = i;
                l = j;
            }
        }
    }
    if (k > l) std::swap(k, l);
    std::cout << k + 1 << std::endl << l + 1;
    return 0;
}
