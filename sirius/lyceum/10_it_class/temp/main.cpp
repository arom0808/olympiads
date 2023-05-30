#include <iostream>
#include <vector>

int main() {
    std::uint64_t N, K;
    std::cin >> N >> K;
    std::vector<std::uint64_t> bushes(N * 3);
    for (std::uint64_t i = 0; i < N; ++i) {
        std::cin >> bushes[i];
        bushes[i + N] = bushes[i];
        bushes[i + N * 2] = bushes[i];
    }
    std::uint64_t now_sum = 0, max_sum;
    for (std::uint64_t i = 0; i < K * 2 + 1; ++i) now_sum += bushes[i];
    max_sum = now_sum;
    for (std::uint64_t i = K + 1; i < 3 * N - K; ++i) {
        now_sum += bushes[i + K];
        now_sum -= bushes[i - K - 1];
        if (now_sum > max_sum) max_sum = now_sum;
    }
    std::cout << max_sum;
    return 0;
}