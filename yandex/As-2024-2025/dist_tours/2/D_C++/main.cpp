#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;

class BigInt {
public:
    static constexpr int base = 1000000000;
    vector<uint32_t> digits;
    bool is_negative = false;

    explicit BigInt(const string &s) {
        if (s.empty()) {
            digits.push_back(0);
            return;
        }
        for (ll i = s.size(); i > 0; i -= 9) digits.push_back(stoi(s.substr(std::max<ll>(i - 9, 0), i)));
        remove_leading_zeros();
    }

    void remove_leading_zeros() {
        while (digits.size() > 1 && !digits.back()) digits.pop_back();
        if (digits.size() == 1 && digits.back() == 0) is_negative = false;
    }

    bool isZero() const {
        return digits.empty() || (digits.size() == 1 && !digits.back());
    }

    void setZero() {
        digits.clear();
        digits.push_back(0);
        is_negative = false;
    }

    bool operator==(const BigInt &rhs) const {
        if (digits.size() != rhs.digits.size()) return false;
        for (ll i = 0; i < digits.size(); ++i) if (digits[i] != rhs.digits[i]) return false;
        return true;
    }

    bool operator<(const BigInt &rhs) const {
        if (digits.size() != rhs.digits.size()) return digits.size() < rhs.digits.size();
        for (ll i = digits.size() - 1; i >= 0; --i) if (digits[i] != rhs.digits[i]) return digits[i] < rhs.digits[i];
        return false;
    }

    bool operator>(const BigInt &rhs) const {
        return rhs < *this;
    }

    BigInt &operator+=(const BigInt &rhs) {
        int carry = 0;
        for (ll i = 0; i < std::max(digits.size(), rhs.digits.size()) || carry; ++i) {
            if (i == digits.size()) digits.push_back(0);
            digits[i] += carry + (i < rhs.digits.size() ? rhs.digits[i] : 0);
            carry = digits[i] >= base;
            if (carry) digits[i] -= base;
        }
        return *this;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
