#include <iostream>
#include <vector>

int main() {
    std::uint32_t N;
    std::uint64_t M;
    std::cin >> N >> M;
    std::vector<std::uint64_t> nums(N);
    for (auto &&num: nums) std::cin >> num;
    std::uint32_t result = 0;
    for (std::uint32_t l = 0; l < N; ++l) {
        std::uint32_t r = l;
        std::uint64_t cur_sum = 0;
        while (r < N) {
            cur_sum += nums[r++];
            if (cur_sum % M == 0) ++result;
        }
    }
    std::cout << result;
    return 0;
}
