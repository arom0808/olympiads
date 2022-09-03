#include <iostream>
#include <set>
#include <algorithm>

using Word = std::string;
using WordConstIt = Word::const_iterator;
using WordDict = std::set<Word>;

std::uint32_t MinDeletionsForOneWord(WordConstIt word_begin, WordConstIt word_end, const Word &search_word,
                                     WordConstIt &searched_end) {
    if (word_begin == word_end) {
        searched_end = word_end;
        return 0;
    }
    std::uint32_t deleted_letters_count = 0;
    auto last_end = word_begin;
    for (const auto &letter: search_word) {
        auto it = std::find(last_end, word_end, letter);
        if (it == word_end) {
            searched_end = word_end;
            return std::distance(word_begin, word_end);
        }
        deleted_letters_count += std::distance(last_end, it);
        last_end = std::next(it);
    }
    searched_end = last_end;
    return deleted_letters_count;
}

std::uint32_t MinDeletionsForManyWords(WordConstIt word_begin, WordConstIt word_end, const WordDict &search_word_dict) {
    if (word_begin == word_end)
        return 0;
    std::uint32_t min_deletions = std::distance(word_begin, word_end);
    for (const auto &search_word: search_word_dict) {
        WordConstIt searched_end;
        auto del_cnt = MinDeletionsForOneWord(word_begin, word_end, search_word, searched_end);
        if (searched_end == word_end) {
            if (del_cnt < min_deletions)
                min_deletions = del_cnt;
        } else {
            del_cnt += MinDeletionsForManyWords(searched_end, word_end, search_word_dict);
            if (del_cnt < min_deletions)
                min_deletions = del_cnt;
        }
    }
    return min_deletions;
}

int main() {
    std::uint16_t N, M;
    std::string S;
    std::cin >> N >> M;
    std::cin >> S;
    WordDict dict;
    std::string tmp;
    for (std::uint16_t i = 0; i < M; ++i) {
        std::cin >> tmp;
        dict.insert(tmp);
    }
    if (N == 0 || M == 0) {
        std::cout << 0;
        return 0;
    }
    std::cout << MinDeletionsForManyWords(S.begin(), S.end(), dict);
    return 0;
}
