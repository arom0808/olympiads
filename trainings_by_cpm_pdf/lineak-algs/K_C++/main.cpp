#include <iostream>
#include <vector>
#include <deque>

int main() {
    std::uint32_t N, K;
    std::cin >> N >> K;
    std::vector<std::uint32_t> nums(N);
    for (auto &&num: nums) std::cin >> num;
    std::deque<std::uint32_t> com;
    for (std::uint32_t i = 0; i < N; ++i) {
        if (i >= K && !com.empty() && com.front() == i - K) com.pop_front();
        while (!com.empty() && nums[com.back()] >= nums[i]) com.pop_back();
        com.push_back(i);
        if (i >= K - 1) std::cout << nums[com.front()] << "\n";
    }
    return 0;
}
