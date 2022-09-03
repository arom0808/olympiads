#include <iostream>
#include <vector>
#include <algorithm>

std::uint64_t ten_to_extent(std::uint16_t extent) {
    std::uint64_t res = 1;
    for (std::uint64_t i = 0; i < extent; ++i)
        res *= 10;
    return res;
}

std::uint64_t extent_replace(std::uint64_t number, std::int16_t old_extent, std::int16_t new_extent) {
    if (old_extent >= new_extent)
        return number * ten_to_extent(old_extent - new_extent);
    throw std::exception();
}


class Mass {
public:
    Mass() = default;

    Mass(const std::uint64_t &num, const std::string &str) {
        mass = num;
        char type, unit;
        if (str.length() == 2) {
            type = str[0];
            unit = str[1];
        } else {
            type = ' ';
            unit = str[0];
        }
        switch (type) {
            case 'm':
                ten_pow -= 3;
                break;
            case 'k':
                ten_pow += 3;
                break;
            case 'M':
                ten_pow += 6;
                break;
            case 'G':
                ten_pow += 9;
                break;
            default:
                break;
        }
        switch (unit) {
            case 'p':
                mass *= 16380;
                break;
            case 't':
                ten_pow += 6;
                break;
            default:
                break;
        }
    }

    [[nodiscard]] std::string to_string() const {
        std::uint64_t tmp_mass = mass;
        std::int16_t tmp_ten_pow = ten_pow;
        char type, unit;
        if (tmp_mass % 16380 == 0) {
            unit = 'p';
            tmp_mass /= 16380;
        } else if (tmp_ten_pow >= 6) {
            unit = 't';
            tmp_ten_pow -= 6;
        } else {
            unit = 'g';
        }
        if (tmp_ten_pow <= -3) {
            type = 'm';
            tmp_ten_pow += 3;
        } else if (tmp_ten_pow >= 9) {
            type = 'G';
            tmp_ten_pow -= 9;
        } else if (tmp_ten_pow >= 6) {
            type = 'M';
            tmp_ten_pow -= 6;
        } else if (tmp_ten_pow >= 3) {
            type = 'k';
            tmp_ten_pow -= 3;
        } else {
            type = ' ';
        }
        std::string res = std::to_string(tmp_mass) + ' ';
        if (type != ' ')
            res += type;
        res += unit;
        return res;
    }

    bool operator<(const Mass &b) const {
        if (ten_pow == b.ten_pow)
            return mass < b.mass;
        if (ten_pow < b.ten_pow)
            return mass < extent_replace(b.mass, b.ten_pow, ten_pow);
        return extent_replace(mass, ten_pow, b.ten_pow) < b.mass;
    }

public:
    std::uint64_t mass = 0;
    std::int16_t ten_pow = 0;
};

int main() {
    std::uint64_t N;
    std::cin >> N;
    std::vector<Mass> masses(N);
    std::uint64_t num;
    std::string type;
    for (auto &&mass: masses) {
        std::cin >> num >> type;
        mass = Mass(num, type);
    }
    std::sort(masses.begin(), masses.end());
    for (const auto &mass: masses)
        std::cout << mass.to_string() << std::endl;
    return 0;
}
