#include <iostream>
#include <set>
#include <vector>

int main() {
    std::set<std::uint64_t> nums{1};
    for (std::uint64_t pre_value = 1, now_value = 2; pre_value < now_value; pre_value = now_value, now_value *= 2)
        nums.insert(now_value);
    for (std::uint64_t pre_value = 1, now_value = 3; pre_value < now_value; pre_value = now_value, now_value *= 3)
        nums.insert(now_value);
    for (std::uint64_t pre_value = 1, now_value = 5; pre_value < now_value; pre_value = now_value, now_value *= 5)
        nums.insert(now_value);

    std::set<std::uint64_t> numk;
    for (const auto &a: nums) {
        for (const auto &b: nums) {
            for (const auto &c: nums) {
                std::uint64_t m = a * b;
                if (m < a) continue;
                m *= c;
                if (m < c) continue;
                numk.insert(m);
            }
        }
    }
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::uint64_t> in_nums(N);
    for (auto &&in_num: in_nums) std::cin >> in_num;
    for (const auto &in_num: in_nums) {
        auto it = numk.lower_bound(in_num);
        std::cout << (*it) << "\n";
    }
    return 0;
}
