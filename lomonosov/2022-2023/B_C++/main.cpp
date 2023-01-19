#include <iostream>
#include <vector>
#include <algorithm>

const std::vector<std::uint64_t> easy_numbers{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
                                              71, 73, 79, 83, 89, 97, 101, 103, 107, 109};

std::uint64_t StringToNumber(const std::string &str, std::size_t number_start_pos, std::size_t number_end_pos) {
    std::uint64_t multiplier = 1, result = 0;
    for (auto i = static_cast<std::int64_t>(number_end_pos); i >= static_cast<std::int64_t>(number_start_pos); --i) {
        result += static_cast<std::uint64_t>(str[i] - '0') * multiplier;
        multiplier *= 10;
    }
    return result;
}

std::uint64_t PraymoradialToDex(std::string &str) {
    std::size_t number_start_pos = std::string::npos, number_end_pos;
    std::uint64_t multiplier = 1, result = 0;
    std::size_t easy_number_pos = 0;
    do {
        if (number_start_pos == std::string::npos) number_end_pos = str.size() - 1;
        else number_end_pos = number_start_pos - 2;
        number_start_pos = str.rfind(':', number_end_pos);
        if (number_start_pos == std::string::npos) number_start_pos = 0;
        else ++number_start_pos;

        result += StringToNumber(str, number_start_pos, number_end_pos) * multiplier;
        multiplier *= easy_numbers[easy_number_pos++];
    } while (number_start_pos > 0);
    return result;
}

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::string input_str;
    std::vector<std::uint64_t> numbers(N);
    for (auto &&num: numbers) {
        std::cin >> input_str;
        num = PraymoradialToDex(input_str);
    }
    std::uint64_t max_value = *std::max_element(numbers.begin(), numbers.end());
    std::uint32_t max_count = std::count(numbers.begin(), numbers.end(), max_value);
    std::cout << max_count;
    return 0;
}
