#include <iostream>
#include <string>
#include <vector>

char english_alphabet_size = 26;
char a_ch = 'a';
std::uint64_t cr_p = static_cast<std::uint64_t>(1e9) + 7ull;

void str_next(const std::string::iterator &begin, const std::string::iterator &end, std::uint32_t k) {
    for (auto it = begin; it != end; ++it)
        (*it) = a_ch + ((*it) - a_ch + (k % english_alphabet_size)) % english_alphabet_size;
}

void arr_char_count(const std::string::iterator &begin, const std::string::iterator &end,
                    std::vector<std::uint32_t> &ch_cnt) {
    for (auto it = begin; it != end; ++it) ++ch_cnt[(*it) - a_ch];
}

std::uint64_t palindrome_count(const std::string::iterator &begin, const std::string::iterator &end) {
    std::vector<std::uint32_t> ch_cnt(26, 0);
    arr_char_count(begin, end, ch_cnt);
    std::uint64_t result = 0;
    for (const auto &cnt: ch_cnt) if (cnt > 0) ++result;
    std::uint32_t pair_cnt = 0;
    bool is_one_let_exists = false;
    for (const auto &cnt: ch_cnt) {
        pair_cnt += cnt / 2;
        if (cnt % 2 != 0) {
            if (is_one_let_exists) ++pair_cnt;
            is_one_let_exists = !is_one_let_exists;
        }
    }
    std::uint64_t prev_val = pair_cnt;
    result += pair_cnt;
    result %= cr_p;
    std::uint32_t length = 3;
    while (true) {
        if (length % 2 == 0) {
            prev_val *
        } else {

        }
        ++length;
    }
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
