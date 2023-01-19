#include <iostream>
#include <vector>

struct Buyer {
    std::uint32_t A, B, C;

    explicit Buyer(std::uint32_t A = 0, std::uint32_t B = 0, std::uint32_t C = 0) : A(A), B(B), C(C) {}
};

int main() {
    std::uint32_t N;
    std::vector<Buyer> buyers(N);
    for (auto &&buyer: buyers) std::cin >> buyer.A >> buyer.B >> buyer.C;
    std::vector<std::uint32_t> dp(N);
    dp[0] = buyers[0].A;
    for (std::uint32_t i = 1; i < N; ++i) {
        std::uint32_t first_variant = dp[i - 1] + buyers[i].A;
        std::uint32_t second_variant = (i > 1 ? dp[i - 2] + buyers[i - 1].B : first_variant);
        std::uint32_t third_variant = (i > 2 ? dp[i - 3] + buyers[i - 2].C : first_variant);
        dp[i] = std::min(std::min(first_variant, second_variant), third_variant);
    }
    std::cout << dp[N - 1];
    return 0;
}
