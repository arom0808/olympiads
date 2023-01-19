#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

std::string k_base_symbols = R"(!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~)";
std::uint32_t k_base = k_base_symbols.size();

std::uint32_t NumberSizeInMaxBase(std::uint32_t number) {
    std::uint32_t result = 0;
    do {
        number /= k_base;
        ++result;
    } while (number != 0);
    return result;
}

std::uint32_t NumberToMaxBase(std::uint32_t number, std::string &result, std::uint32_t start_str_index) {
    std::uint32_t str_size = NumberSizeInMaxBase(number);
    std::uint32_t i = 1;
    do {
        result[start_str_index + str_size - i] = k_base_symbols[number % k_base];
        number /= k_base;
        ++i;
    } while (number != 0);
    return start_str_index + str_size;
}

std::uint32_t
MaxBaseToNumber(const std::string &k_base_number_str, std::uint32_t first_index, std::uint32_t last_index) {
    std::uint32_t result = 0;
    std::uint32_t multiplier = 1;
    for (std::int32_t i = last_index, counter = 0; i >= first_index; --i, ++counter) {
        std::uint32_t digit = k_base_symbols.find(k_base_number_str[i]);
        result += digit * multiplier;
        multiplier *= k_base;
    }
    return result;
}

void CountSegmentsSizes(const std::vector<std::uint32_t> &numbers, std::vector<std::uint32_t> &segments_sizes,
                        std::vector<std::uint32_t> &inverted_numbers) {
    std::uint32_t segment_start_number = numbers[0];
    if (segment_start_number != 1) {
        for (std::uint32_t i = 1; i < segment_start_number; ++i) inverted_numbers.push_back(i);
        segments_sizes.push_back(segment_start_number - 1);
    }
    for (std::uint32_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] - numbers[i - 1] == 1) continue;
        for (std::uint32_t j = numbers[i - 1] + 1; j < numbers[i]; ++j) inverted_numbers.push_back(j);
        segments_sizes.push_back(numbers[i - 1] - segment_start_number + 1);
        segments_sizes.push_back(numbers[i] - numbers[i - 1] - 1);
        segment_start_number = numbers[i];
    }
    segments_sizes.push_back(numbers[numbers.size() - 1] - segment_start_number + 1);
}

std::uint32_t VectorSizeInMaxBaseString(const std::vector<std::uint32_t> &numbers) {
    std::uint32_t result = (numbers.size() > 1 ? numbers.size() - 1 : 0);
    for (const auto &number: numbers) result += NumberSizeInMaxBase(number);
    return result;
}

void VectorToMaxBaseString(const std::vector<std::uint32_t> &numbers, std::string &result) {
    std::uint32_t str_size = VectorSizeInMaxBaseString(numbers);
    result.resize(str_size, '0');
    std::uint32_t it = 0;
    for (std::uint32_t i = 0; i < numbers.size(); ++i) {
        it = NumberToMaxBase(numbers[i], result, it);
        if (i != numbers.size() - 1) {
            result[it] = ' ';
            ++it;
        }
    }
}

void MaxBaseStringToVector(const std::string &first_day_data, std::uint32_t first_index,
                           std::vector<std::uint32_t> &result) {
    std::size_t space_pos = first_day_data.find(' ', first_index);
    result.push_back(MaxBaseToNumber(first_day_data, first_index,
                                     ((space_pos == std::string::npos ? first_day_data.size() : space_pos) - 1)));
    if (space_pos == std::string::npos) return;
    std::size_t pre_space_pos = space_pos;
    space_pos = first_day_data.find(' ', pre_space_pos + 1);
    while (space_pos != std::string::npos) {
        result.push_back(MaxBaseToNumber(first_day_data, pre_space_pos + 1, space_pos - 1));
        pre_space_pos = space_pos;
        space_pos = first_day_data.find(' ', pre_space_pos + 1);
    }
    result.push_back(MaxBaseToNumber(first_day_data, pre_space_pos + 1, first_day_data.size() - 1));
}

std::pair<std::uint32_t, std::uint32_t> WhatNotExists(const std::vector<std::uint32_t> &numbers, std::uint32_t n) {
    std::pair<std::uint32_t, std::uint32_t> result{0, 0};
    if (numbers[numbers.size() - 1] != n) {
        result.first = n;
        if (n - numbers[numbers.size() - 1] > 1) {
            result.second = n - 1;
            return result;
        }
    }
    if (numbers[0] != 1) {
        if (result.first == 0) result.first = 1;
        else {
            result.second = 1;
            return result;
        }
        if (numbers[0] != 2) {
            result.second = 2;
            return result;
        }
    }
    for (std::uint32_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] - numbers[i - 1] == 1) continue;
        if (numbers[i] - numbers[i - 1] == 2) {
            if (result.first == 0) result.first = numbers[i - 1] + 1;
            else {
                result.second = numbers[i - 1] + 1;
                return result;
            }
        } else {
            if (result.first == 0) {
                result.first = numbers[i - 1] + 1;
                result.second = numbers[i - 1] + 2;
                return result;
            } else {
                result.second = numbers[i - 1] + 1;
                return result;
            }
        }
    }
    return result;
}

void FirstWithoutInputAndOutput(const std::vector<std::uint32_t> &numbers, std::uint32_t n,
                                std::string &result) {
    std::vector<std::uint32_t> segments_sizes, inverted_numbers;
    segments_sizes.reserve(numbers.size() * 2);
    inverted_numbers.reserve(n - numbers.size());
    CountSegmentsSizes(numbers, segments_sizes, inverted_numbers);
    std::uint32_t numbers_str_size = VectorSizeInMaxBaseString(numbers),
            inverted_numbers_str_size =
            NumberSizeInMaxBase(numbers[numbers.size() - 1]) + 1 + VectorSizeInMaxBaseString(inverted_numbers),
            segments_sizes_str_size = 1 + VectorSizeInMaxBaseString(segments_sizes);
    std::uint32_t minimum_str_size = std::min(std::min(numbers_str_size, inverted_numbers_str_size),
                                              segments_sizes_str_size);
    if (minimum_str_size == numbers_str_size) {
        VectorToMaxBaseString(numbers, result);
        result = "1" + result;
    } else if (minimum_str_size == inverted_numbers_str_size) {
        VectorToMaxBaseString(inverted_numbers, result);
        std::string max_number_max_base;
        max_number_max_base.resize(NumberSizeInMaxBase(numbers[numbers.size() - 1]), '0');
        NumberToMaxBase(numbers[numbers.size() - 1], max_number_max_base, 0);
        result = "2" + max_number_max_base + " " + result;
    } else {
        VectorToMaxBaseString(segments_sizes, result);
        result = std::string("3") + (numbers[0] == 1 ? "1" : "0") + result;
    }
}

std::pair<std::uint32_t, std::uint32_t>
SecondWithoutInputAndOutput(std::vector<std::uint32_t> &numbers, const std::string &first_day_data, std::uint32_t n) {
    if (first_day_data[0] == '1') {
        std::vector<std::uint32_t> first_numbers;
        first_numbers.reserve(n - numbers.size());
        MaxBaseStringToVector(first_day_data, 1, first_numbers);
        numbers.insert(numbers.end(), first_numbers.begin(), first_numbers.end());
    } else if (first_day_data[0] == '2') {
        std::size_t space_pos = first_day_data.find(' ', 1);
        std::uint32_t max_first_day_value = MaxBaseToNumber(first_day_data, 1, space_pos - 1);
        std::vector<std::uint32_t> inverted_first_numbers;
        inverted_first_numbers.reserve(numbers.size() + 2);
        MaxBaseStringToVector(first_day_data, space_pos + 1, inverted_first_numbers);
        inverted_first_numbers.push_back(max_first_day_value + 1);
        if (inverted_first_numbers[0] != 1)
            for (std::uint32_t i = 1; i < inverted_first_numbers[0]; ++i)
                numbers.push_back(i);
        for (std::uint32_t i = 1; i < inverted_first_numbers.size(); ++i) {
            if (inverted_first_numbers[i] - inverted_first_numbers[i - 1] == 1) continue;
            for (std::uint32_t j = inverted_first_numbers[i - 1] + 1; j < inverted_first_numbers[i]; ++j)
                numbers.push_back(j);
        }
    } else {
        bool one_exists = first_day_data[1] == '1';
        std::vector<std::uint32_t> segments_sizes_first;
        segments_sizes_first.reserve(numbers.size() + 2);
        MaxBaseStringToVector(first_day_data, 2, segments_sizes_first);
        for (std::uint32_t i = 0, counter = 0;
             i < segments_sizes_first.size(); counter += segments_sizes_first[i], ++i) {
            if (one_exists == i % 2) continue;
            for (std::uint32_t j = counter + 1; j <= counter + segments_sizes_first[i]; ++j)
                numbers.push_back(j);
        }
    }
    std::sort(numbers.begin(), numbers.end());
    return WhatNotExists(numbers, n);
}

void First() {
    std::uint32_t n, k1;
    std::cin >> n >> k1;
    std::vector<std::uint32_t> numbers(k1);
    for (auto &&num: numbers) std::cin >> num;
    std::sort(numbers.begin(), numbers.end());
    std::string result;
    FirstWithoutInputAndOutput(numbers, n, result);
    std::cout << result;
}

void Second() {
    std::string first_day_data;
    std::getline(std::cin, first_day_data);
    std::uint32_t n, k2;
    std::cin >> n >> k2;
    std::vector<std::uint32_t> numbers(k2);
    for (auto &&num: numbers) std::cin >> num;
    auto res = SecondWithoutInputAndOutput(numbers, first_day_data, n);
    std::cout << res.first << " " << res.second << std::endl;
}

int main() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_n(100000, 500000);
    std::uniform_int_distribution<std::mt19937::result_type> dist_bool(0, 1);
    for (std::uint32_t i = 0, operations_completed = 0; i < 100000; ++i) {
        std::uint32_t n = dist_n(rng);
        std::vector<std::uint32_t> numbers(n);
        for (std::uint32_t j = 0; j < n; ++j) numbers[j] = j + 1;

        std::uniform_int_distribution<std::mt19937::result_type> erase_1(0, n - 1), erase_2(0, n - 2);
        std::uint32_t erased_1, erased_2;
        auto erase_it_1 = std::next(numbers.begin(), erase_1(rng));
        erased_1 = *erase_it_1;
        numbers.erase(erase_it_1);
        auto erase_it_2 = std::next(numbers.begin(), erase_2(rng));
        erased_2 = *erase_it_2;
        numbers.erase(erase_it_2);

        std::shuffle(numbers.begin(), numbers.end(), rng);
        std::uniform_int_distribution<std::mt19937::result_type> dist_k1(1, n - 3);
        std::uint32_t k1 = dist_k1(rng), k2 = n - k1;
        std::vector<std::uint32_t> first_day_numbers(numbers.begin(), std::next(numbers.begin(), k1)),
                second_day_numbers(std::next(numbers.begin(), k1), numbers.end());
//    std::uint32_t n = 9;
//    std::vector<std::uint32_t> first_day_numbers{2, 1, 3, 4}, second_day_numbers{8, 9, 7};
//    std::uint32_t erased_1 = 5, erased_2 = 6;
        std::sort(first_day_numbers.begin(), first_day_numbers.end());
        std::string buffer;
        FirstWithoutInputAndOutput(first_day_numbers, n, buffer);
        auto res = SecondWithoutInputAndOutput(second_day_numbers, buffer, n);
        if (i - operations_completed >= 1000) {
            std::cout << i / 1000 << "%\n";
            operations_completed = i;
        }
        if (buffer.size() > 1000 || (!((erased_1 == res.first && erased_2 == res.second) ||
                                       (erased_1 == res.second && erased_2 == res.first)))) {
            std::cout << "n: " << n;
            std::cout << "\nfirst day numbers: ";
            for (const auto &first_day_num: first_day_numbers) std::cout << first_day_num << ", ";
            std::cout << "\nsecond day numbers: ";
            for (const auto &second_day_num: second_day_numbers) std::cout << second_day_num << ", ";
            std::cout << "\ndeleted numbers: " << erased_1 << ", " << erased_2;
            std::cout << "\nfirst program result: " << buffer;
            std::cout << "\nresult: " << res.first << ", " << res.second;
            if (buffer.size() > 1000) {
                std::cout << "\n BUFFER SIZE: " << buffer.size();
                return 0;
            }
            if (!((erased_1 == res.first && erased_2 == res.second) ||
                  (erased_1 == res.second && erased_2 == res.first))) {
                std::cout << "\nRESULTS DOESN'T MATCHES!";
                return 0;
            }
        }
    }
//    for (std::uint32_t i = 0; i < 10000; ++i) {
//
//    }
//    std::string alg;
//    std::getline(std::cin, alg);
//    if (alg == "first") First();
//    else Second();
    return 0;
}
