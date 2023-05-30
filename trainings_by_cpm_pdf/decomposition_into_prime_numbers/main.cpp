#include <iostream>
#include <map>

void DecToPrive(std::uint64_t num, std::map<std::uint64_t, std::uint64_t> &prime_nums) {
    prime_nums.clear();
    for (std::uint64_t p = 2; p * p < num; ++p) {
        if (num % p == 0) {
            auto it = prime_nums.emplace(p, 0).first;
            while (num % p == 0) {
                ++it->second;
                num /= p;
            }
        }
    }
    if (num > 1) prime_nums.emplace(num, 1);
}

int main() {
    std::uint64_t num;
    std::cin >> num;
    std::map<std::uint64_t, std::uint64_t> prime_nums;
    DecToPrive(num, prime_nums);
    for (auto it = prime_nums.begin(); it != std::prev(prime_nums.end()); ++it) {
        std::cout << it->first;
        if (it->second > 1) std::cout << "^" << it->second;
        std::cout << "*";
    }
    std::cout << prime_nums.rbegin()->first;
    if (prime_nums.rbegin()->second > 1) std::cout << "^" << prime_nums.rbegin()->second;
}
