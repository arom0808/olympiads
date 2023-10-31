#include <iostream>
#include <tuple>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    std::uint32_t k;
    std::vector<std::uint32_t> ss;
    std::cin >> k >> ss[k];
}
//
//std::uint64_t gcd(std::uint64_t a, std::uint64_t b) {
//    while (b != 0) std::tie(a, b) = std::make_tuple(b, a % b);
//    return a;
//}
//
//class Fraction {
//public:
//    std::uint64_t numerator, denominator;
//
//    explicit Fraction(std::uint64_t numerator = 0, std::uint64_t denominator = 1)
//            : numerator(numerator), denominator(denominator) { simplify(); }
//
//    void simplify() {
//        auto ngcd = gcd(numerator, denominator);
//        numerator /= ngcd;
//        denominator /= ngcd;
//    }
//
//    Fraction operator+(const Fraction &other) const {
//        return Fraction(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
//    }
//
//    Fraction operator*(std::uint64_t num) const {
//        return Fraction(numerator * num, denominator);
//    }
//
//    [[nodiscard]] std::tuple<std::uint64_t, Fraction> split() const {
//        return std::make_tuple(numerator / denominator, Fraction(numerator % denominator, denominator));
//    }
//};
//
//std::uint64_t my_pow(std::uint64_t x, std::uint64_t n) {
//    std::uint64_t res = 1;
//    for (std::uint64_t t_p = x; n != 0; n >>= 1, t_p *= t_p) if (n & 1) res *= t_p;
//    return res;
//}
//
//std::uint64_t reverse_num(std::uint64_t num) {
//    std::uint64_t res = 0;
//    while (num != 0) {
//        res = res * 10 + num % 10;
//        num /= 10;
//    }
//    return res;
//}
//
//Fraction get_full_fract_from_period(std::string not_period_str, const std::string &period_str) {
//    std::uint32_t not_period_size = not_period_str.size(), period_size = period_str.size();
//    if (not_period_str.empty()) not_period_str = "0";
//    Fraction not_period(std::stoull(not_period_str), my_pow(10, not_period_size));
//    Fraction period(std::stoull(period_str), (my_pow(10, period_size) - 1) * my_pow(10, not_period_size));
//    return not_period + period;
//}
//
//std::tuple<std::string, std::string, std::string> get_period_from_fract(std::uint64_t int_part, Fraction fract_part) {
//    std::uint64_t rev_numerator = reverse_num(fract_part.numerator);
//    std::vector<std::uint64_t> remainders_history, digits_history;
//    std::set<std::uint64_t> got_remainders;
//    std::uint64_t now_remainder = rev_numerator % 10, divider = fract_part.denominator;
//    rev_numerator /= 10;
//    bool is_periodical = false;
//    while (now_remainder != 0 || rev_numerator != 0) {
//        while ((now_remainder * 10 + rev_numerator % 10) / divider < 10) {
//            now_remainder = now_remainder * 10 + rev_numerator % 10;
//            rev_numerator /= 10;
//        }
//        remainders_history.push_back(now_remainder);
//        digits_history.push_back(now_remainder / divider);
//        if (rev_numerator == 0 && got_remainders.find(now_remainder) != got_remainders.end()) {
//            is_periodical = true;
//            break;
//        }
//        got_remainders.emplace(now_remainder);
//        now_remainder %= divider;
//    }
//    std::vector<std::uint64_t> not_period, period;
//    if (!remainders_history.empty()) {
//        std::uint64_t first_period_dig_pos =
//                std::distance(remainders_history.begin(),
//                              std::find(remainders_history.begin(), remainders_history.end(),
//                                        remainders_history.back()));
//        if (is_periodical) {
//            std::copy(digits_history.begin(), std::next(digits_history.begin(), first_period_dig_pos),
//                      std::back_inserter(not_period));
//            std::copy(std::next(digits_history.begin(), first_period_dig_pos), std::prev(digits_history.end()),
//                      std::back_inserter(period));
//        } else {
//            not_period = digits_history;
//        }
//        if (period.size() == 1 && period.back() == 0) period.clear();
//        if (period.size() == 1 && period.back() == 9) {
//            if (period.empty()) ++int_part;
//            else ++period.back();
//        }
//        for (std::uint64_t i = 0; i < not_period.size(); ++i) {
//            if (not_period[not_period.size() - 1 - i] == 10) {
//                not_period[not_period.size() - 1 - i] = 0;
//                if (not_period.size() - 1 - i > 0) ++not_period[not_period.size() - 2 - i];
//                else ++int_part;
//            }
//        }
//        if (period.empty()) while (!not_period.empty() && not_period.back() == 0) not_period.pop_back();
//    }
//    std::string int_str = std::to_string(int_part);
//    std::string not_period_str, period_str;
//    for (const auto &npi: not_period) not_period_str += std::to_string(npi);
//    for (const auto &pi: period) period_str += std::to_string(pi);
//    return std::make_tuple(int_str, not_period_str, period_str);
//}
//
//std::string
//transform_to_full_str(const std::string &int_str, const std::string &not_period_str, const std::string &period_str) {
//    std::string result;
//    if (int_str.empty()) result += "0";
//    else result += int_str;
//    if (!not_period_str.empty() || !period_str.empty()) result += ".";
//    if (!not_period_str.empty()) result += not_period_str;
//    if (!period_str.empty()) result += std::string("(") + period_str + ")";
//    return result;
//}
//
//int main() {
////    std::string int_part_str, not_period_part_str, period_part_str;
////    std::tie(int_part_str, not_period_part_str, period_part_str) = get_period_from_fract(0, Fraction(7788, 9900));
////    std::cout << transform_to_full_str(int_part_str, not_period_part_str, period_part_str);
//    std::string full_input;
//    std::uint64_t k;
//    std::vector<std::uint32_t> ss;
//    std::cin >> k >> ss[k];
//    std::cin >> full_input >> k;
//    std::string not_period_str = full_input.substr(2, full_input.find('(') - 2),
//            period_str = full_input.substr(not_period_str.size() + 3, full_input.size() - not_period_str.size() - 4);
//    Fraction fract = get_full_fract_from_period(not_period_str, period_str) * k;
//    std::uint64_t int_part;
//    std::tie(int_part, fract) = fract.split();
//    std::string int_part_str, not_period_part_str, period_part_str;
//    std::tie(int_part_str, not_period_part_str, period_part_str) = get_period_from_fract(int_part, fract);
//    std::cout << transform_to_full_str(int_part_str, not_period_part_str, period_part_str);
//    return 0;
//}
