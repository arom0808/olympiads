#include <iostream>
#include <set>
#include <cmath>
#include <fstream>
#include <vector>


int main() {
//    std::set<std::uint64_t> multiplyers;
    std::uint64_t N = 100000000000ULL;
    std::vector<bool> prime(N + 1, true);
    std::cout << "inited";
    prime[0] = false;
    prime[1] = false;
    std::uint64_t i_max = static_cast<std::uint64_t>(sqrtl(static_cast<long double>(N))) + 1;
    for (std::uint64_t i = 2; i <= i_max; ++i)
        if (prime[i])
            for (std::uint64_t j = i * i; j <= N; j += i)
                prime[j] = false;
    std::cout << "inited2";
    std::ofstream asd("o.txt");
    for (std::uint64_t i = 0; i < prime.size(); ++i) if (prime[i]) asd << i << "ULL, ";
    asd.close();
    return 0;
}
