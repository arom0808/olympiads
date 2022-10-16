#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct PairCount {
    std::vector<std::uint32_t> pairs_for_char_count;
    std::uint32_t pair_count;
    std::uint32_t one_excess_char_symbol_count;

    explicit PairCount(const std::vector<std::uint32_t> &pairs_for_char_count = {}, std::uint32_t pair_count = 0,
                       std::uint32_t one_excess_char_symbol_count = 0) :
            pairs_for_char_count(pairs_for_char_count), pair_count(pair_count),
            one_excess_char_symbol_count(one_excess_char_symbol_count) {}
};

char english_alphabet_size = 26;
char a_ch = 'a';
std::uint64_t maximum_result_size = static_cast<std::uint64_t>(1e9) + 7ull;

void str_next(const std::string::iterator &begin, const std::string::iterator &end, std::uint32_t k) {
    for (auto it = begin; it != end; ++it)
        (*it) = a_ch + ((*it) - a_ch + (k % english_alphabet_size)) % english_alphabet_size;
}

void arr_char_count(const std::string::iterator &begin, const std::string::iterator &end,
                    std::vector<std::uint32_t> &char_counts) {
    char_counts.clear();
    char_counts.resize(26, 0);
    for (auto it = begin; it != end; ++it) ++char_counts[(*it) - a_ch];
}

void CountPairs(const std::vector<std::uint32_t> &char_counts, PairCount &result) {
    result.pair_count = 0;
    result.one_excess_char_symbol_count = 0;
    result.pairs_for_char_count.clear();
    result.pairs_for_char_count.reserve(english_alphabet_size);
    for (const auto &cnt: char_counts) {
        result.pairs_for_char_count.push_back(cnt / 2);
        result.pair_count += cnt / 2;
        if (cnt % 2 != 0) ++result.one_excess_char_symbol_count;
    }
}

std::uint64_t palindrome_count(const std::string::iterator &begin, const std::string::iterator &end) {
    std::uint64_t result = std::distance(begin, end);
    std::vector<std::uint32_t> char_counts;
    arr_char_count(begin, end, char_counts);
    PairCount pair_count;
    CountPairs(char_counts, pair_count);
    for (std::uint32_t current_palindrome_length = 2;; ++current_palindrome_length) {
        std::uint32_t current_need_pairs_count = current_palindrome_length / 2;
        std::uint32_t available_pairs_count = pair_count.pair_count;
        if (available_pairs_count < current_need_pairs_count) break;
        std::uint64_t current_result = 1;
        if (current_palindrome_length % 2 == 0) {
            for (; current_need_pairs_count > 0; --current_need_pairs_count, --available_pairs_count) {
                current_result = (current_result * available_pairs_count) % maximum_result_size;
            }
            result = (result + current_result) % maximum_result_size;
        } else {
            if (available_pairs_count == current_need_pairs_count && pair_count.one_excess_char_symbol_count == 0)
                break;
            std::uint32_t minimum_remain_pairs_count = 0;
            if (pair_count.one_excess_char_symbol_count == 0) minimum_remain_pairs_count = 1;
            for (; current_need_pairs_count > minimum_remain_pairs_count;
                   --current_need_pairs_count, --available_pairs_count) {
                current_result = (current_result * available_pairs_count) % maximum_result_size;
            }
            current_result = (current_result * pair_count.one_excess_char_symbol_count) % maximum_result_size;
            result = (result + current_result) % maximum_result_size;
        }
    }
    return result;
}

int main() {
    std::uint32_t n, q;
    std::cin >> n >> q;
    std::string s;
    std::cin >> s;
    std::vector<std::uint64_t> results;
    results.reserve(q);
    for (std::uint32_t i_counter = 0; i_counter < q; ++i_counter) {
        std::uint32_t t, i, j, k;
        std::cin >> t >> i >> j;
        auto str_begin = std::next(s.begin(), i);
        auto str_end = std::next(s.begin(), j + 1);
        if (t == 1) {
            std::cin >> k;
            str_next(str_begin, str_end, k);
        } else {
            results.push_back(palindrome_count(str_begin, str_end));
        }
    }
    for (const auto &result: results)
        std::cout << result << std::endl;
    return 0;
}
