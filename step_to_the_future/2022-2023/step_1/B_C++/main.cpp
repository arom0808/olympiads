#include <iostream>
#include <vector>
#include <algorithm>

class BigInteger {

    static const std::uint32_t BASE = 1000000000;
    std::vector<std::uint32_t> _digits{};
public:
    BigInteger() = default;

    explicit BigInteger(std::uint32_t number) {
        do {
            this->_digits.push_back(number % BigInteger::BASE);
            number /= BigInteger::BASE;
        } while (number != 0);
    }

    BigInteger operator+(const BigInteger &other) const {
        std::uint32_t carry = 0;
        BigInteger result = *this;
        for (std::uint32_t i = 0; i < std::max(result._digits.size(), other._digits.size()) || carry != 0; ++i) {
            if (i == result._digits.size()) result._digits.push_back(0);
            result._digits[i] += carry + (i < other._digits.size() ? other._digits[i] : 0);
            carry = result._digits[i] >= BigInteger::BASE;
            if (carry != 0) result._digits[i] -= BigInteger::BASE;
        }
        return result;
    }

    BigInteger &operator+=(const BigInteger &other) {
        std::uint32_t carry = 0;
        for (std::uint32_t i = 0; i < std::max(this->_digits.size(), other._digits.size()) || carry != 0; ++i) {
            if (i == this->_digits.size()) this->_digits.push_back(0);
            this->_digits[i] += carry + (i < other._digits.size() ? other._digits[i] : 0);
            carry = this->_digits[i] >= BigInteger::BASE;
            if (carry != 0) this->_digits[i] -= BigInteger::BASE;
        }
        return *this;
    }

    BigInteger operator-(const BigInteger &other) const {
        if ((*this) < other) return BigInteger(0);
        BigInteger result = (*this);
        std::uint32_t carry = 0;
        for (std::uint32_t i = 0; i < other._digits.size() || carry != 0; ++i) {
            if (result._digits[i] < carry + (i < other._digits.size() ? other._digits[i] : 0)) {
                carry = 1;
                result._digits[i] += BigInteger::BASE;
            } else carry = 0;
            result._digits[i] -= carry + (i < other._digits.size() ? other._digits[i] : 0);
        }
        result.RemoveLeadingZeros();
        return result;
    }

    BigInteger &operator-=(const BigInteger &other) {
        if ((*this) < other) {
            this->_digits.clear();
            return *this;
        }
        std::uint32_t carry = 0;
        for (std::uint32_t i = 0; i < other._digits.size() || carry != 0; ++i) {
            if (this->_digits[i] < carry + (i < other._digits.size() ? other._digits[i] : 0)) {
                carry = 1;
                this->_digits[i] += BigInteger::BASE;
            } else carry = 0;
            this->_digits[i] -= carry + (i < other._digits.size() ? other._digits[i] : 0);
        }
        this->RemoveLeadingZeros();
        return *this;
    }

    BigInteger operator*(const BigInteger &other) const {
        BigInteger result;
        result._digits.resize(this->_digits.size() + other._digits.size(), 0);
        for (std::uint32_t i = 0; i < this->_digits.size(); ++i) {
            std::uint32_t carry = 0;
            for (std::uint32_t j = 0; j < other._digits.size() || carry != 0; ++j) {
                std::uint64_t cur = result._digits[i + j] +
                                    this->_digits[i] * 1ULL * (j < other._digits.size() ? other._digits[j] : 0) + carry;
                result._digits[i + j] = static_cast<std::uint32_t>(cur % BigInteger::BASE);
                carry = static_cast<std::uint32_t>(cur / BigInteger::BASE);
            }
        }
        result.RemoveLeadingZeros();
        return result;
    }

    BigInteger &operator*=(const BigInteger &other) {
        (*this) = (*this) * other;
        return (*this);
    }

    BigInteger operator/(const BigInteger &other) const {
        const BigInteger &b = other;
        BigInteger result, current;
        result._digits.resize(this->_digits.size());
        for (std::int32_t i = static_cast<std::int32_t>(this->_digits.size()) - 1; i >= 0; --i) {
            current.ShiftRight();
            current._digits[0] = this->_digits[i];
            current.RemoveLeadingZeros();
            std::uint32_t x=0, l=0, r = BigInteger::BASE;
            while (l <= r) {
                std::uint32_t m = (l + r) / 2;
                BigInteger t = b * BigInteger(m);
                if (t <= current) {
                    x = m;
                    l = m + 1;
                } else r = m - 1;
            }
            result._digits[i] = x;
            current -= b * BigInteger(x);
        }
        result.RemoveLeadingZeros();
        return result;
    }

    BigInteger operator%(const BigInteger &other) const {
        BigInteger b = ((*this) / other) * other;
        BigInteger result = *this;
        if (result < b) result += other;
        result -= b;
        return result;
    }

    bool operator==(const BigInteger &other) const {
        if (this->_digits.empty()) {
            if (other._digits.empty() || (other._digits.size() == 1 && other._digits[0] == 0)) return true;
            return false;
        }
        if (other._digits.empty()) {
            if (this->_digits.size() == 1 && this->_digits[0] == 0) return true;
            return false;
        }
        if (this->_digits.size() != other._digits.size()) return false;
        for (std::uint32_t i = 0; i < this->_digits.size(); ++i) if (this->_digits[i] != other._digits[i]) return false;
        return true;
    }

    bool operator<(const BigInteger &other) const {
        if ((*this) == other) return false;
        if (this->_digits.size() != other._digits.size()) {
            return this->_digits.size() < other._digits.size();
        } else {
            for (std::int32_t i = static_cast<std::int32_t>(this->_digits.size()) - 1; i >= 0; --i)
                if (this->_digits[i] != other._digits[i]) return this->_digits[i] < other._digits[i];
            return false;
        }
    }

    bool operator<=(const BigInteger &other) const {
        return ((*this) < other || (*this) == other);
    }

private:
    void RemoveLeadingZeros() {
        while (this->_digits.size() > 1 && this->_digits.back() == 0) {
            this->_digits.pop_back();
        }
    }

    void ShiftRight() {
        if (this->_digits.empty()) {
            this->_digits.push_back(0);
            return;
        }
        this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
        for (std::uint32_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
        this->_digits[0] = 0;
    }
};

const std::vector<BigInteger> SixteenthSystemDigits
        {BigInteger(0), BigInteger(1), BigInteger(2), BigInteger(3), BigInteger(4), BigInteger(5), BigInteger(6),
         BigInteger(7), BigInteger(8), BigInteger(9), BigInteger(10), BigInteger(11), BigInteger(12), BigInteger(13),
         BigInteger(14), BigInteger(15)};

std::uint32_t in_eight_number_size(std::uint32_t number) {
    if (number == 0) return 1;
    std::uint32_t result = 0;
    while (number != 0) {
        number /= 8;
        ++result;
    }
    return result;
};

void number_to_eight_system(std::uint32_t number, std::string &str, std::uint32_t &max_digit) {
    std::uint32_t num_size = in_eight_number_size(number);
    str.reserve(str.size() + num_size + 1);
    if (number == 0) {
        str.push_back('0');
        return;
    }
    while (number != 0) {
        if (max_digit < 7) if (number % 8 > max_digit) max_digit = number % 8;
        str.push_back(static_cast<char>(static_cast<std::uint32_t>('0') + number % 8));
        number /= 8;
    }
    std::reverse(std::prev(str.end(), num_size), str.end());
}

int main() {
    std::uint32_t A, B;
    std::cin >> A >> B;
    std::uint32_t max_digit = (B - A >= 8 ? 7 : 0);
    std::string x_str;
    std::vector<std::uint32_t> x_positions(B - A);
    for (std::uint32_t i = 0; i <= B - A; ++i) {
        number_to_eight_system(A + i, x_str, max_digit);
        if (i != B - A) {
            x_str.push_back('x');
            x_positions[i] = x_str.size() - 1;
        }
    }
    std::uint32_t min_system = max_digit + 1;
    for (std::uint32_t system = min_system; system < 201; ++system) {
        if (system % 2 != 0) continue;
        BigInteger system_big_int(system);
        std::uint32_t x_int = system / 2;
        char x_ch;
        if (x_int < 10) x_ch = static_cast<char>('0' + x_int);
        else x_ch = static_cast<char>('A' + (x_int - 10));
        for (const auto &x_pos: x_positions) x_str[x_pos] = x_ch;
        std::uint32_t divider = system - 1;
        BigInteger big_int(0), multiplier(1);
        for (std::int32_t i = static_cast<std::int32_t>(x_str.size()) - 1; i >= 0; --i) {
            std::uint32_t digit = (x_str[i] >= '0' && x_str[i] <= '9' ? x_str[i] - '0' : x_str[i] - 'A' + 10);
            big_int += SixteenthSystemDigits[digit] * multiplier;
            multiplier *= system_big_int;
        }
        auto xxsds = system_big_int - SixteenthSystemDigits[1];
        if (big_int % (system_big_int - SixteenthSystemDigits[1]) == SixteenthSystemDigits[0]) {
            std::cout << x_int;
            return 0;
        }
    }
    return 0;
}
