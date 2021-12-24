#include <iostream>

std::uint64_t BinSearchProcess(std::uint64_t A, std::uint64_t K, std::uint64_t B, std::uint64_t M, std::uint64_t X) {
    std::uint64_t l = 0, r = UINT64_MAX;
    while (l != r) {
        std::uint64_t m = l + (r - l) / 2;
        std::uint64_t tree_cnt = ((m / K * (K - 1) + m % K) * A) + ((m / M * (M - 1) + m % M) * B);
        if (tree_cnt < X)
            l = m + 1;
        else if (tree_cnt > X)
            r = m;
        else
            l = r = m;
    }
    return l;
}

int main() {
    std::uint64_t A, K, B, M, X;
    std::cin >> A >> K >> B >> M >> X;
    std::cout << BinSearchProcess(A, K, B, M, X);
    return 0;
}
