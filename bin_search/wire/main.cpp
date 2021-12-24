#include <iostream>
#include <vector>

int main() {
    std::uint64_t N, K;
    std::cin >> N >> K;
    std::vector<std::uint64_t> L(N);
    std::uint64_t sum = 0;
    for (auto &Li: L) {
        std::cin >> Li;
        sum += Li;
    }
    if (sum < K) {
        std::cout << 0;
        return 0;
    }
    if (sum == K) {
        std::cout << 1;
        return 0;
    }
    std::uint64_t l = 1, r = 1e7, x = (l + r) / 2;
    while (l != r) {
        bool bigger = false, smaller = false;
        std::uint64_t count = 0, countp1 = 0;
        for (const auto &Li: L) {
            count += Li / x;
            countp1 += Li / (x + 1);
        }
        if (count < K)
            bigger = true;
        if (countp1 >= K)
            smaller = true;
        if (bigger) {
            r = x - 1;
        } else if (smaller) {
            l = x + 1;
        } else {
            l = x;
            r = x;
        }
        x = (l + r) / 2;
    }
    std::cout << x;
    return 0;
}
