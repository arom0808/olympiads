#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<std::int32_t> numbers(4);
    for (auto &&num: numbers) std::cin >> num;
    std::sort(numbers.begin(), numbers.end());
    long double max_res = 0;
    std::vector<std::int32_t> res_numbers;
    do {
        if (numbers[1] == 0 || numbers[3] == 0) continue;
        long double cur_res = static_cast<long double>(numbers[0]) / static_cast<long double>(numbers[1]) +
                              static_cast<long double>(numbers[2]) / static_cast<long double>(numbers[3]);
        if (cur_res > max_res) {
            max_res = cur_res;
            res_numbers = numbers;
        }
    } while (std::next_permutation(numbers.begin(), numbers.end()));
    std::int64_t Q = res_numbers[1] * res_numbers[3];
    std::int64_t P = res_numbers[0] * res_numbers[3] + res_numbers[1] * res_numbers[2];
    if (Q < 0) {
        Q *= -1;
        P *= -1;
    }
    while (true) {
        bool is_cr = false;
        for (std::int64_t i = 2; i <= std::min(Q, std::abs(P)); ++i) {
            if (Q % i == 0 && P % i == 0) {
                Q /= i;
                P /= i;
                is_cr = true;
                break;
            }
        }
        if (!is_cr) break;
    }
    std::cout << P << " " << Q;
    return 0;
}
