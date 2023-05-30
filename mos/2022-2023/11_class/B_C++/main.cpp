#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
#include <random>
#include <functional>

std::random_device dev;
std::uint32_t seed = dev();
std::mt19937 rng(seed);

enum class Direction {
    horizontal = false,
    vertical = true
};

std::pair<std::pair<std::uint32_t, std::uint32_t>, Direction>
GetStartPosAndDirection(const std::vector<std::vector<char>> &cross) {
    std::bernoulli_distribution dist_direction(0.5);
    std::uint32_t i, j;
    bool is_found = false;
    for (i = 0; i < cross.size(); ++i) {
        for (j = 0; j < cross.size(); ++j) {
            if (cross[i][j] == '\0') {
                is_found = true;
                break;
            }
        }
        if (is_found) break;
    }
    if (!is_found) return {{cross.size(), cross.size()}, Direction::vertical};
    bool is_left_have_value = j > 0, is_top_have_value = i > 0;
    Direction direction;
    if (is_left_have_value == is_top_have_value) direction = static_cast<Direction>(dist_direction(rng));
    else if (is_left_have_value) direction = Direction::horizontal;
    else direction = Direction::vertical;
    return {{i, j}, direction};
}

std::function<char &(std::uint32_t)> GetCharInRowFGenerator(std::vector<std::vector<char>> &cross, std::uint32_t row) {
    return [&cross, row](std::uint32_t col) -> char & {
        return cross[row][col];
    };
}

std::function<char &(std::uint32_t)>
GetCharInColumnFGenerator(std::vector<std::vector<char>> &cross, std::uint32_t col) {
    return [&cross, col](std::uint32_t row) -> char & {
        return cross[row][col];
    };
}

void GetStringFromGenerator(const std::function<const char &(std::uint32_t)> &generator, std::uint32_t length,
                            std::string &res) {
    res.resize(length, '\0');
    for (std::uint32_t i = 0; i < res.size(); ++i) res[i] = generator(i);
}

void PasteStringToGenerator(const std::function<char &(std::uint32_t)> &generator, const std::string &str) {
    for (std::uint32_t i = 0; i < str.size(); ++i) generator(i) = str[i];
}

bool IsFirstNSymbolsEqual(const std::function<const char &(std::uint32_t)> &generator, const std::string &str,
                          std::uint32_t N) {
    for (std::uint32_t i = 0; i < N; ++i) if (generator(i) != str[i]) return false;
    return true;
}

bool CheckIsFinishOk(std::multiset<std::string> &words, std::vector<std::vector<char>> &cross,
                     std::vector<bool> &is_rows_ok, std::vector<bool> &is_columns_ok) {
    std::multiset<std::string> deleted_words;
    bool is_ok = true;
    auto WordCheckF = [&words, &deleted_words](const std::string &str) {
        auto it = words.find(str);
        if (it == words.end()) return false;
        deleted_words.insert(std::move(words.extract(it)));
        return true;
    };
    for (std::uint32_t row = 0; row < cross.size(); ++row) {
        if (is_rows_ok[row]) continue;
        std::string temp_str;
        GetStringFromGenerator(GetCharInRowFGenerator(cross, row), cross.size(), temp_str);
        if (!WordCheckF(temp_str)) {
            is_ok = false;
            break;
        }
    }
    if (is_ok) {
        for (std::uint32_t col = 0; col < cross.size(); ++col) {
            if (is_columns_ok[col]) continue;
            std::string temp_str;
            GetStringFromGenerator(GetCharInColumnFGenerator(cross, col), cross.size(), temp_str);
            if (!WordCheckF(temp_str)) {
                is_ok = false;
                break;
            }
        }
    }
    if (is_ok) return true;
    words.insert(deleted_words.begin(), deleted_words.end());
    return false;
}

bool IsSolute(std::multiset<std::string> &words, std::vector<std::vector<char>> &cross,
              std::vector<bool> &is_rows_ok, std::vector<bool> &is_columns_ok) {
    auto start_pos_and_direction = GetStartPosAndDirection(cross);
    std::uint32_t i = start_pos_and_direction.first.first, j = start_pos_and_direction.first.second;
    Direction direction = start_pos_and_direction.second;
    if (i >= cross.size() || j >= cross.size()) return CheckIsFinishOk(words, cross, is_rows_ok, is_columns_ok);
    auto cur_generator =
            direction == Direction::horizontal ? GetCharInRowFGenerator(cross, i) : GetCharInColumnFGenerator(cross, j);
    std::uint32_t cur_size = direction == Direction::horizontal ? j : i;
    std::uint32_t cur_id = direction == Direction::horizontal ? i : j;
    std::vector<bool> &cur_ok_arr = direction == Direction::horizontal ? is_rows_ok : is_columns_ok;
    std::set<std::string> good_strings;
    auto word_it = words.begin();
    while (true) {
        word_it = std::find_if(word_it, words.end(), [&cur_generator, cur_size](const std::string &str) {
            return IsFirstNSymbolsEqual(cur_generator, str, cur_size);
        });
        if (word_it != words.end()) good_strings.emplace(*word_it);
        else break;
        ++word_it;
    }
    for (const auto &cur_good_str: good_strings) {
        std::string start_str;
        GetStringFromGenerator(cur_generator, cross.size(), start_str);
        PasteStringToGenerator(cur_generator, cur_good_str);
        auto nh = words.extract(words.find(cur_good_str));
        cur_ok_arr[cur_id] = true;
        if (IsSolute(words, cross, is_rows_ok, is_columns_ok)) return true;
        cur_ok_arr[cur_id] = false;
        words.insert(std::move(nh));
        PasteStringToGenerator(cur_generator, start_str);
    }
    return false;
}

void SoluteForFilename(const std::string &filename) {
    std::ifstream input_file(filename + ".txt");
    std::ofstream out_file(filename + "ans.txt");
    std::uint32_t t;
    input_file >> t;
    std::vector<std::string> results(t);
    for (auto &&res: results) {
        std::uint32_t N;
        input_file >> N;
        std::multiset<std::string> words;
        std::vector<bool> is_rows_ok(N, false), is_columns_ok(N, false);
        std::string temp_str;
        for (std::uint32_t i = 0; i < N * 2; ++i) {
            input_file >> temp_str;
            words.emplace(std::move(temp_str));
        }
        std::vector<std::vector<char>> cross(N, std::vector<char>(N, '\0'));
        IsSolute(words, cross, is_rows_ok, is_columns_ok);
        res.resize(N * (N + 1));
        for (std::uint32_t str_i = 0, cross_i = 0; cross_i < cross.size(); ++cross_i, str_i += N + 1) {
            std::copy(cross[cross_i].begin(), cross[cross_i].end(), std::next(res.begin(), str_i));
            res[str_i + N] = '\n';
        }
        out_file << res << "\n";
        std::flush(out_file);
    }
    input_file.close();
    out_file.close();
}

int main() {
    SoluteForFilename("b2");
    return 0;
}