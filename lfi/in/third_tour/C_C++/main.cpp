#include <iostream>
#include <string>
#include <vector>
//#include <random>
//
//namespace Random {
//    std::random_device dev;
//    std::uint32_t seed = dev();
//    std::mt19937 rng(seed);
//
//    std::uint32_t GetRandInt(std::uint32_t from, std::uint32_t to) {
//        return std::uniform_int_distribution(from, to)(rng);
//    }
//}

int main() {
    std::string cmd;
    std::cin >> cmd;
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::uint32_t> vec(N);
    for (auto &&num: vec) std::cin >> num;
    if (cmd == "send") {
        for (const auto &num: vec) std::cout << num << " ";
        std::cout << 5;
//        std::cout << "\n\nchanged:\n";
//        auto key = vec[Random::GetRandInt(0, vec.size() - 1)];
//        for (const auto &num: vec) std::cout << (num ^ key) << " ";
//        std::cout << (5 ^ key);
    } else {
        std::uint32_t key = vec.back() ^ 5;
        for (std::uint32_t i = 0; i < N - 1; ++i) std::cout << (vec[i] ^ key) << " ";
    }
    return 0;
}
