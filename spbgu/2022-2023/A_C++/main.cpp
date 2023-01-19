#include <iostream>
#include <set>
#include <algorithm>

std::set<std::multiset<std::uint16_t>> buffer;

bool IsAllDifferent(const std::multiset<std::uint16_t> &numbers) {
    for (auto b_1 = numbers.begin(), b_2 = std::next(b_1); b_2 != numbers.end(); ++b_1, ++b_2)
        if ((*b_1) == (*b_2)) return false;
    return true;
}

bool IsOk(const std::multiset<std::uint16_t> &numbers) {
    if (IsAllDifferent(numbers)) return true;
    if (buffer.find(numbers) != buffer.end()) return false;
    buffer.insert(numbers);
    auto copy_numbers = numbers;
    std::set<std::uint16_t> changed;
    for (const auto &num: numbers) {
        if (changed.find(num) != changed.end()) continue;
        changed.insert(num);
        std::multiset<std::uint16_t>::iterator a_it = copy_numbers.find(num), b_it, c_it;
        auto a = *a_it;
        if (a == 1) continue;
        copy_numbers.erase(a_it);
        b_it = copy_numbers.insert(1);
        c_it = copy_numbers.insert(a - 1);
        if (IsOk(copy_numbers)) return true;
        for (std::uint16_t b = 2, c = a - b; b != a; ++b, --c) {
            copy_numbers.erase(b_it);
            copy_numbers.erase(c_it);
            b_it = copy_numbers.insert(b);
            c_it = copy_numbers.insert(c);
            if (IsOk(copy_numbers)) return true;
        }
        copy_numbers = numbers;
    }
    return false;
}

int main() {
    std::multiset<std::uint16_t> numbers;
    for (std::uint16_t i = 0; i < 4; ++i) {
        std::uint16_t number;
        std::cin >> number;
        numbers.insert(number);
    }
    if (IsOk(numbers)) std::cout << "YES";
    else std::cout << "NO";
    return 0;
}
