#include <iostream>
#include <vector>

std::uint64_t gcd(std::uint64_t a, std::uint64_t b) {
    if (a % b == 0) return b;
    if (b % a == 0) return a;
    if (a > b) return gcd(a % b, b);
    return gcd(a, b % a);
}

class Fraction {
public:
    std::uint64_t first, second;

    Fraction operator*(const Fraction &other) const {
        return {first * other.first, second * other.second};
    }

    Fraction operator/(const Fraction &other) const {
        return {first * other.second, second * other.first};
    }

    Fraction operator+(const Fraction &other) const {
        return {first * other.second + other.first * second, second * other.second};
    }

    void operator*=(const Fraction &other) {
        first *= other.first;
        second *= other.second;
        auto t = gcd(first, second);
        first /= t;
        second /= t;
    }

    void operator/=(const Fraction &other) {
        first *= other.second;
        second *= other.first;
        auto t = gcd(first, second);
        first /= t;
        second /= t;
    }

    void operator+=(const Fraction &other) {
        first = first * other.second + other.first * second;
        second *= other.second;
        auto t = gcd(first, second);
        first /= t;
        second /= t;
    }

    [[nodiscard]] Fraction GetOMT() const {
        return {second - first, second};
    }

    void SetSelfOMT() {
        first = second - first;
    }

    Fraction(std::uint64_t first = 0, std::uint64_t second = 1) : first(first), second(second) {
        auto t = gcd(first, second);
        first /= t;
        second /= t;
    }
};

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::uint64_t temp_1, temp_2, temp_3, temp_4;
    std::cin >> temp_1 >> temp_2 >> temp_3 >> temp_4;
    auto home_f = Fraction(temp_1, temp_2), omt_home_f = home_f.GetOMT();
    auto guest_f = Fraction(temp_3, temp_4), omt_guest_f = guest_f.GetOMT();
    std::vector<Fraction> home_chances(n + 1), guest_chances(n + 1);
    home_chances[0] = omt_home_f;
    home_chances[1] = home_f;
    guest_chances[0] = omt_guest_f;
    guest_chances[1] = guest_f;
    for (std::uint32_t i = 1; i <= n; ++i) {
        Fraction home_pre_f = home_chances[0], home_cur_f;
        Fraction guest_pre_f = guest_chances[0], guest_cur_f;
        home_chances[0] *= omt_home_f;
        guest_chances[0] *= omt_guest_f;
        for (std::uint32_t j = 1; j <= i; ++j) {
            home_cur_f = home_chances[j];
            guest_cur_f = guest_chances[j];
            home_chances[j] = home_pre_f * home_f + home_cur_f * omt_home_f;
            guest_chances[j] = guest_pre_f * guest_f + guest_cur_f * omt_guest_f;
            home_pre_f = home_cur_f;
            guest_pre_f = guest_cur_f;
        }
    }
    Fraction res;
    for (std::uint32_t i = 1; i <= n; ++i) {
        for (std::uint32_t j = 0; j < i; ++j) {
            res += home_chances[i] * guest_chances[j];
        }
    }
    std::cout << ((res.first % 998244353) * (((998244353 + 1) / res.second) % 998244353)) % 998244353;

    return 0;
}
