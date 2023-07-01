#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize(3)
#pragma GCC optimize("O3")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")


#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <iomanip>

class BigInt {
public:
    static const std::uint32_t BASE = 1000000000;
    std::vector<std::int32_t> digits;
    bool is_neg;

    explicit BigInt(std::uint64_t val) : is_neg(false) {
        do {
            digits.push_back(val % BASE);
            val /= BASE;
        } while (val != 0);
    }

    explicit BigInt(std::int64_t val) {
        if (val < 0) {
            is_neg = true;
            val = -val;
        } else is_neg = false;
        do {
            digits.push_back(val % BASE);
            val /= BASE;
        } while (val != 0);
    }

    BigInt() : BigInt(std::uint64_t(0)) {}

    void remove_lead_zeros() {
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
        if (digits.size() == 1 && digits.back() == 0) is_neg = false;
    };

    void shift_right() {
        if (digits.empty()) {
            digits.push_back(0);
            return;
        }
        digits.push_back(digits[digits.size() - 1]);
        for (std::uint64_t i = digits.size() - 2; i > 0; --i) digits[i] = digits[i - 1];
        digits[0] = 0;
    }

    BigInt operator*(const BigInt &other) const {
        BigInt res;
        res.digits.resize(digits.size() + other.digits.size());
        for (std::uint64_t i = 0; i < digits.size(); ++i) {
            std::uint32_t carry = 0;
            for (std::uint64_t j = 0; j < other.digits.size(); ++j) {
                std::int64_t cur =
                        res.digits[i + j] + digits[i] * 1ll * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                res.digits[i + j] = static_cast<std::int32_t>(cur % BASE);
                carry = static_cast<std::int32_t>(cur / BASE);
            }
        }
        res.is_neg = is_neg != other.is_neg;
        res.remove_lead_zeros();
        return res;
    }

    BigInt &operator+=(const BigInt &other) {
        return *this = (*this + other);
    }

    BigInt operator%(const BigInt &other) const {
        BigInt result = (*this) - ((*this) / other) * other;
        if (result.is_neg) result += other;
        return result;
    }

    BigInt operator/(const BigInt &other) const {
        if (other == BigInt(static_cast<std::int64_t>(0))) throw std::runtime_error("DIVIDING BY ZERO");
        BigInt b = other, res, cur;
        b.is_neg = false;
        res.digits.resize(digits.size());
        for (std::int64_t i = static_cast<std::int64_t>(digits.size()) - 1; i >= 0; --i) {
            cur.shift_right();
            cur.digits[0] = digits[i];
            cur.remove_lead_zeros();
            std::int32_t x = 0, l = 0, r = BASE;
            while (l <= r) {
                std::int32_t m = (l + r) / 2;
                BigInt t = b * BigInt(static_cast<std::int64_t>(m));
                if (t <= cur) {
                    x = m;
                    l = m + 1;
                } else r = m - 1;
            }
            res.digits[i] = x;
            cur = cur - b * BigInt(static_cast<std::int64_t>(x));
        }
        res.is_neg = is_neg != other.is_neg;
        res.remove_lead_zeros();
        return res;
    }

    BigInt operator-() const {
        BigInt copy(*this);
        copy.is_neg = !copy.is_neg;
        return copy;
    }

    bool operator==(const BigInt &other) const {
        if (is_neg != other.is_neg) return false;
        if (digits.empty())
            return other.digits.empty() || (other.digits.size() == 1 && other.digits.back() == 0);
        if (other.digits.empty())
            return digits.size() == 1 && digits.back() == 0;
        if (digits.size() != other.digits.size()) return false;
        for (std::uint64_t i = 0; i < digits.size(); ++i) if (digits[i] != other.digits[i]) return false;
        return true;
    }


    bool operator<(const BigInt &other) const {
        if ((*this) == other) return false;
        if (is_neg) {
            if (other.is_neg) return ((-other) < (-(*this)));
            else return true;
        } else if (other.is_neg) return false;
        if (digits.size() != other.digits.size()) return digits.size() < other.digits.size();
        for (std::int64_t i = digits.size() - 1; i >= 0; --i)
            if (digits[i] != other.digits[i]) return digits[i] < other.digits[i];
        return false;
    }

    bool operator<=(const BigInt &other) const {
        return ((*this) < other || (*this) == other);
    }

    BigInt operator+(const BigInt &other) const {
        if (is_neg) {
            if (other.is_neg) return -(-(*this) + (-other));
            else return other - (-(*this));
        }
        if (other.is_neg) return (*this) - (-other);
        std::uint32_t carry = 0;
        BigInt left(*this);
        for (std::uint64_t i = 0; i < std::max(left.digits.size(), other.digits.size()) || carry != 0; ++i) {
            if (i == left.digits.size()) left.digits.push_back(0);
            left.digits[i] += carry + (i < other.digits.size() ? other.digits[i] : 0);
            carry = left.digits[i] >= BASE;
            if (carry != 0) left.digits[i] -= BASE;
        }
        return left;
    }

    BigInt operator-(const BigInt &other) const {
        if (other.is_neg) return (*this) + (-other);
        if (is_neg) return -(-(*this) + other);
        if (*this < other) return -(other - (*this));
        std::uint32_t carry = 0;
        BigInt left(*this);
        for (std::uint64_t i = 0; i < other.digits.size() || carry != 0; ++i) {
            left.digits[i] -= carry + (i < other.digits.size() ? other.digits[i] : 0);
            carry = left.digits[i] < 0;
            if (carry != 0) left.digits[i] += BASE;
        }
        left.remove_lead_zeros();
        return left;
    }
};

std::ostream &operator<<(std::ostream &os, const BigInt &bi) {
    if (bi.digits.empty()) os << 0;
    else {
        if (bi.is_neg) os << '-';
        os << bi.digits.back();
        char old_fill = os.fill('0');
        for (std::int64_t i = static_cast<std::int64_t>(bi.digits.size()) - 2; i >= 0; --i)
            os << std::setw(9) << bi.digits[i];
        os.fill(old_fill);
    }
    return os;
}

struct TimeDay {
    std::int64_t days_cnt, moved, cur_sum;

    TimeDay(std::int64_t days_cnt, std::int64_t moved, std::int64_t cur_sum) : days_cnt(days_cnt), moved(moved),
                                                                               cur_sum(cur_sum) {}
};

const std::int64_t ost_const = 1e9 + 7;
const BigInt big_ost_const(ost_const);

inline std::int64_t get_cur_sum(std::int64_t orig_day, std::int64_t days_cnt, std::int64_t moved) {
    if (days_cnt == 0) return 0;
    std::int64_t cur_sum = ((orig_day % ost_const) * (days_cnt % ost_const)) % ost_const;
    cur_sum =
            (cur_sum + (((moved % ost_const) * (days_cnt % ost_const)) % ost_const)) %
            ost_const;
    if (days_cnt % 2 == 0) {
        cur_sum = (cur_sum +
                   ((((days_cnt / 2) % ost_const) * ((days_cnt - 1) % ost_const)) %
                    ost_const)) %
                  ost_const;
    } else {
        cur_sum = (cur_sum +
                   (((days_cnt % ost_const) * (((days_cnt - 1) / 2) % ost_const)) %
                    ost_const)) %
                  ost_const;
    }
    return cur_sum;
}

inline std::int64_t
prev_end(const std::map<std::int64_t, TimeDay> &times, std::map<std::int64_t, TimeDay>::iterator it) {
    if (it == times.begin()) return 0;
    it = std::prev(it);
    return it->first + it->second.moved + it->second.days_cnt;
}

inline void UpdateSumRes(std::int64_t pre_cur_sum, std::int64_t now_cur_sum, BigInt &sum_res) {
    sum_res += BigInt(now_cur_sum - pre_cur_sum);
}

int main() {
    std::int64_t n;
    std::cin >> n;
    std::map<std::int64_t, TimeDay> times;
    BigInt sum_res;
//    std::list<TimeDay> times;
    for (std::int64_t i = 0; i < n; ++i) {
        std::int64_t d, x;
        std::cin >> d >> x;
        auto next_time = times.upper_bound(d);
        if (next_time != times.begin() && std::prev(next_time)->first == d) {
            std::prev(next_time)->second.days_cnt = x;
            auto pre_cur_sum = std::prev(next_time)->second.cur_sum;
            std::prev(next_time)->second.cur_sum =
                    get_cur_sum(std::prev(next_time)->first, std::prev(next_time)->second.days_cnt,
                                std::prev(next_time)->second.moved);
            UpdateSumRes(pre_cur_sum, std::prev(next_time)->second.cur_sum, sum_res);
        } else {
            std::int64_t s_real_start = std::max(d, prev_end(times, next_time));
            auto it = times.emplace(d, TimeDay(x, s_real_start - d, get_cur_sum(d, x, s_real_start - d))).first;
            UpdateSumRes(0, it->second.cur_sum, sum_res);
        }
        for (; next_time != times.end(); ++next_time) {
            std::int64_t real_start = std::max(next_time->first, prev_end(times, next_time));
            if (next_time->second.moved == real_start - next_time->first) break;
            next_time->second.moved = real_start - next_time->first;
            auto pre_cur_sum = next_time->second.cur_sum;
            next_time->second.cur_sum = get_cur_sum(next_time->first, next_time->second.days_cnt,
                                                    next_time->second.moved);
            UpdateSumRes(pre_cur_sum, next_time->second.cur_sum, sum_res);
        }
        std::cout << (sum_res % big_ost_const) << "\n";
    }
    return 0;
}
