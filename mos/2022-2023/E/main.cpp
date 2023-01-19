#include <iostream>
#include <vector>

int main() {
    std::uint32_t n, p;
    std::cin >> n >> p;
    std::vector<std::uint32_t> nums(n);
    for (auto &&num: nums) std::cin >> num;
    std::uint32_t max_res = 0, m_i = 0, m_j = 1;
    for (std::uint32_t i = 0; i < n - 1; ++i) {
        for (std::uint32_t j = i + 1; j < n; ++j) {
            if ((nums[i] + nums[j]) % p > max_res) {
                max_res = (nums[i] + nums[j]) % p;
                m_i = i;
                m_j = j;
                if (max_res == p - 1) {
                    std::cout << m_i + 1 << " " << m_j + 1;
                    return 0;
                }
            }
        }
    }
    std::cout << m_i + 1 << " " << m_j + 1;
    return 0;
}
