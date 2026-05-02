#include <iostream>
#include <cstdint>

using namespace std;

constexpr uint64_t mod = 998244353;

uint64_t bin_pow(uint64_t a, uint64_t n) {
    uint64_t ans = 1;
    while (n) {
        if (n & 1) ans = static_cast<__uint128_t>(ans) * a % mod;
        a = static_cast<__uint128_t>(a) * a % mod;
        n >>= 1;
    }
    return ans;
}

uint64_t minus_mod(uint64_t a, uint64_t b) {
    if (a < b) return a + mod - b;
    return a - b;
}

uint64_t plus_mod(uint64_t a, uint64_t b) {
    if (a + b >= mod) return a + b - mod;
    return a + b;
}

uint64_t mul(uint64_t a, uint64_t b) {
    return static_cast<uint64_t>(static_cast<__uint128_t>(a) * static_cast<__uint128_t>(b) % mod);
}

// uint64_t my_gcd(uint64_t a, uint64_t b) {
//     uint64_t t;
//     while (a) t = a % b, a = b, b = t;
//     return b;
// }


int main() {
    uint64_t n;
    cin >> n;
    if (n < 3) {
        cout << "0\n";
        return 0;
    }
    uint64_t nom = 0;
    for (uint64_t k = 1; k <= n - 2; ++k) {
        nom = plus_mod(nom,
                       mul(
                           (n - k - 1),
                           mul(
                               bin_pow(25, n - k - 2),
                               minus_mod(bin_pow(26, k), bin_pow(25, k)))));
    }
    uint64_t denom = bin_pow(26, n);
    // auto nom_denom_gcd = my_gcd(nom, denom);
    // if (nom_denom_gcd) nom /= nom_denom_gcd, denom /= nom_denom_gcd;
    uint64_t inv_denom = bin_pow(denom, mod - 2);
    cout << mul(nom, inv_denom) << "\n";
    return 0;
}
