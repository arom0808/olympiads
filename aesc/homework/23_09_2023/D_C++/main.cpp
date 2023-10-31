#include <iostream>
#include <vector>

int main() {
    std::vector<std::uint32_t> mpd(1300000, 0), prime;
    for (std::uint32_t i = 2; i <= mpd.size(); ++i) {
        if (mpd[i] == 0) {
            mpd[i] = i;
            prime.push_back(i);
        }
        for (std::uint32_t j = 0;
             j < prime.size() && prime[j] <= mpd[i] && static_cast<std::uint64_t>(i) * prime[j] <= mpd.size(); ++j)
            mpd[i * prime[j]] = prime[j];
    }
    std::uint64_t k;
    std::cin >> k;
    for (std::uint64_t i = 2, c = 0; c < k; ++i) {
        if (mpd[i] == i) ++c;
        if (c == k) std::cout << i;
    }
    return 0;
}
