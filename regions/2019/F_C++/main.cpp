#include <iostream>
#include <vector>

const std::uint64_t mod_value = 1e9 + 7;
const std::uint64_t null_value = 1e9 + 10;

std::uint64_t CalculateDown(std::uint32_t n, std::uint32_t k, std::vector<std::vector<std::uint64_t>> &up,
                            std::vector<std::vector<std::uint64_t>> &down);

std::uint64_t CalculateUp(std::uint32_t n, std::uint32_t k, std::vector<std::vector<std::uint64_t>> &up,
                          std::vector<std::vector<std::uint64_t>> &down) {
    if (k > n) return 0;
    if (up[n][k] != null_value) return up[n][k];
    if (n == k) {
        up[n][k] = 1;
        return up[n][k];
    }
    up[n][k] = CalculateUp(n, k + 1, up, down) + CalculateDown(n - k, k + 1, up, down) - 1;
    up[n][k] %= mod_value;
    return up[n][k];
}

std::uint64_t CalculateDown(std::uint32_t n, std::uint32_t k, std::vector<std::vector<std::uint64_t>> &up,
                            std::vector<std::vector<std::uint64_t>> &down) {
    if (k > n) return 0;
    if (down[n][k] != null_value) return down[n][k];
    if (n == k) {
        down[n][k] = 1;
        return down[n][k];
    }
    if (k > 1)
        down[n][k] = CalculateDown(n, k - 1, up, down) + CalculateUp(n, k - 1, up, down);
    else
        down[n][k] = 0;
    down[n][k] %= mod_value;
    return down[n][k];
}

int main() {
    std::uint32_t n, k;
    std::cin >> n >> k;
    if (n == k) {
        std::cout << 1;
        return 0;
    }
    std::vector<std::vector<std::uint64_t>> up(n + 1, std::vector<std::uint64_t>(n + 1, null_value)),
            down(n + 1, std::vector<std::uint64_t>(n + 1, null_value));
    std::uint64_t result = CalculateDown(n, k, up, down) + CalculateUp(n, k, up, down);
    result %= mod_value;
    std::cout << result;
    return 0;
}
