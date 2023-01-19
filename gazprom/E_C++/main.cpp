#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <random>
#include <set>
#include <sstream>

struct MyString {
    std::u16string string;
    std::uint32_t sign_symbols_count;

    bool operator<(const MyString &other) const {
        return string < other.string;
    }

    explicit MyString(const std::u16string &string = std::u16string(0, 0), std::uint32_t sign_symbols_count = 0)
            : string(string), sign_symbols_count(sign_symbols_count) {}
};

template<class T>
void PrintRecipes(const T &recipes) {
    for (const auto &recipe: recipes) {
        for (const auto &ch: recipe.string) std::cout << static_cast<std::uint32_t>(ch) << " ";
        std::cout << std::endl;
    }
}

std::uint32_t MySolution(std::set<MyString> &start_recipes) {
    if (start_recipes.size() == 1) {
        return 1;
    }
    std::set<MyString> recipes;

    for (auto &&recipe: start_recipes) {
        MyString copy_recipe = recipe;
        std::sort(copy_recipe.string.begin(), std::next(copy_recipe.string.begin(), copy_recipe.sign_symbols_count));
        recipes.insert(copy_recipe);
    }
    std::cout << std::endl;
    PrintRecipes(recipes);

    std::uint32_t sequence_count = 1;

    for (auto first = recipes.rbegin(), second = std::next(first); second != recipes.rend(); ++first, ++second) {
        auto a = std::set<char16_t>{second->string.begin(), std::next(second->string.begin(),second->sign_symbols_count)},
                b = std::set<char16_t>{first->string.begin(), std::next(first->string.begin(),first->sign_symbols_count)};
        if (!std::ranges::includes(a,b))
            ++sequence_count;
    }
    return sequence_count;
}

std::set<MyString> &InputRecipesFromKeyboard(std::set<MyString> &recipes) {
    std::uint32_t N, K, tmp_m, tmp_num;
    std::cin >> N >> K;
    recipes.clear();
    for (std::uint32_t l = 0; l < N; ++l) {
        std::cin >> tmp_m;
        MyString recipe;
        recipe.sign_symbols_count = tmp_m;
        recipe.string.resize(K, static_cast<std::u16string::value_type>(0));
        for (std::uint32_t i = 0; i < tmp_m; ++i) {
            std::cin >> tmp_num;
            recipe.string[i] = static_cast<std::u16string::value_type>(tmp_num);
        }
        recipes.insert(recipe);
    }
    return recipes;
}

void GenerateRandomNumbersSet(std::set<std::uint32_t> &numbers_set,
                              std::uint32_t need_size, std::uint32_t max_number) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_max(1, max_number);
    numbers_set.clear();
    while (numbers_set.size() != need_size)
        numbers_set.insert(dist_max(rng));
}

//std::uint32_t Factorial(std::uint32_t number) {
//    std::uint32_t res;
//    for (std::uint32_t i = 1; i <= number; i++) res = res * i;
//    return res;
//}

std::set<MyString> &GenerateRandomRecipes(std::set<MyString> &recipes, std::uint32_t min_n_k, std::uint32_t max_n_k) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist_n_k(min_n_k, max_n_k);
    std::uint32_t N = dist_n_k(rng), K = dist_n_k(rng), tmp_m;
    std::uniform_int_distribution<std::mt19937::result_type> dist_m(1, K);
    recipes.clear();
    std::set<std::uint32_t> temp_nums_set;
    for (std::uint32_t l = 0; l < N; ++l) {
        tmp_m = dist_m(rng);
        GenerateRandomNumbersSet(temp_nums_set, tmp_m, K);
        MyString recipe;
        recipe.sign_symbols_count = tmp_m;
        recipe.string.resize(K, static_cast<std::u16string::value_type>(0));
        auto it = temp_nums_set.begin();
        for (std::uint32_t i = 0; i < tmp_m; ++i) {
            recipe.string[i] = static_cast<std::u16string::value_type>(*it);
            ++it;
        }
        recipes.insert(recipe);
    }
    std::set<MyString> temp_recipes;
    for (const auto &st_recipe: recipes) {
        MyString recipe = st_recipe;
        std::vector<std::uint32_t> nnnums(recipe.sign_symbols_count);
        for (std::uint32_t i = 0; i < recipe.sign_symbols_count; ++i)
            nnnums[i] = static_cast<std::uint32_t>(recipe.string[i]);
        std::shuffle(nnnums.begin(), nnnums.end(), rng);
        for (std::uint32_t i = 0; i < recipe.sign_symbols_count; ++i)
            recipe.string[i] = static_cast<std::u16string::value_type>(nnnums[i]);
        temp_recipes.insert(recipe);
    }
    recipes = temp_recipes;
    return recipes;
}

std::pair<std::uint32_t, std::vector<MyString>> RightSolution(std::set<MyString> &recipes_set) {
    std::vector<MyString> recipes(recipes_set.begin(), recipes_set.end());
    std::sort(recipes.begin(), recipes.end());
    std::uint32_t min_result = 400;
    std::vector<MyString> right_recipes;
    do {
        std::uint32_t cur_res = 1;
        for (auto first = recipes.begin(), second = std::next(first); second != recipes.end(); ++first, ++second) {
            if (second->sign_symbols_count >= first->sign_symbols_count) {
                ++cur_res;
                continue;
            }
            std::set<std::uint32_t> first_set, second_set;
            for (std::uint32_t i = 0; i < first->sign_symbols_count; ++i)
                first_set.insert(static_cast<std::uint32_t>(first->string[i]));
            for (std::uint32_t i = 0; i < second->sign_symbols_count; ++i)
                second_set.insert(static_cast<std::uint32_t>(second->string[i]));
            if (!std::includes(first_set.begin(), first_set.end(), second_set.begin(), second_set.end()))
                ++cur_res;
        }
        if (cur_res < min_result) {
            min_result = cur_res;
            right_recipes = recipes;
        }
    } while (std::next_permutation(recipes.begin(), recipes.end()));
    return {min_result, right_recipes};
}

std::set<MyString> &GenerateRecipesFromPrinted(std::set<MyString> &recipes, const std::string &string) {
    std::uint32_t cur_pos = 0;
    recipes.clear();
    while (true) {
        MyString recipe;
        bool is_end_of_all = false;
        while (true) {
            auto first_space = string.find_first_of(' ', cur_pos);
            auto first_next_str = string.find_first_of('\n', cur_pos);
            if (first_space == std::string::npos && first_next_str == std::string::npos) {
                auto num = std::stoi(std::string(string, cur_pos));
                recipe.string += static_cast<std::u16string::value_type>(num);
                if (num != 0) ++recipe.sign_symbols_count;
                is_end_of_all = true;
                break;
            } else if (first_space == std::string::npos) {
                auto num = std::stoi(std::string(string, cur_pos, first_next_str - cur_pos));
                recipe.string += static_cast<std::u16string::value_type>(num);
                if (num != 0) ++recipe.sign_symbols_count;
                cur_pos = first_next_str + 1;
                break;
            } else if (first_next_str == std::string::npos) {
                auto num = std::stoi(std::string(string, cur_pos, first_space - cur_pos));
                recipe.string += static_cast<std::u16string::value_type>(num);
                if (num != 0) ++recipe.sign_symbols_count;
                cur_pos = first_space + 1;
            } else {
                if (first_space < first_next_str) {
                    auto num = std::stoi(std::string(string, cur_pos, first_space - cur_pos));
                    recipe.string += static_cast<std::u16string::value_type>(num);
                    if (num != 0) ++recipe.sign_symbols_count;
                    cur_pos = first_space + 1;
                } else {
                    auto num = std::stoi(std::string(string, cur_pos, first_next_str - cur_pos));
                    recipe.string += static_cast<std::u16string::value_type>(num);
                    if (num != 0) ++recipe.sign_symbols_count;
                    cur_pos = first_next_str + 1;
                    break;
                }
            }
        }
        recipes.insert(recipe);
        if (is_end_of_all) break;
    }
    return recipes;
}

int main() {
    std::set<MyString> recipes;
//    GenerateRecipesFromPrinted(recipes, "1 4 3 2\n3 2 0 0\n4 0 0 0");
    GenerateRandomRecipes(recipes, 1, 10);
    const std::set<MyString> recipes_orig = recipes;
    std::set<MyString> recipes_for_1 = recipes_orig, recipes_for_2 = recipes_orig;
    PrintRecipes(recipes_orig);
    std::cout << "My: " << MySolution(recipes_for_1) << std::endl;
    auto pp = RightSolution(recipes_for_2);
    std::cout << "Right: " << pp.first << std::endl;
    PrintRecipes(pp.second);
    return 0;
}
