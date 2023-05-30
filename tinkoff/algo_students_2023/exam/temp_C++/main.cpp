#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <map>
#include <set>

class Ingredient {
public:
    bool is_in_shop = false;
    std::uint64_t price_in_shop;
    bool is_ingredient_have = false;
    std::set<Ingredient *> ingredients;
    bool is_optimal_price_calculated = false;
    std::uint64_t optimal_price;

    std::pair<bool, std::uint64_t> GetPossibleAndOptimalPrice() {
        if (is_in_shop) {
            if (is_ingredient_have) {
                std::uint64_t one_price = price_in_shop;
                std::uint64_t second_price = 0;
                for (const auto &ingr: ingredients) {
                    auto mini_res = ingr->GetPossibleAndOptimalPrice();
                    if (!mini_res.first) {
                        is_ingredient_have = false;
                        return {true, one_price};
                    }
                    second_price += mini_res.second;
                }
                return {true, std::min(one_price, second_price)};
            } else {
                return {true, price_in_shop};
            }
        } else {
            if (is_ingredient_have) {
                std::uint64_t price = 0;
                for (const auto &ingr: ingredients) {
                    auto mini_res = ingr->GetPossibleAndOptimalPrice();
                    if (!mini_res.first) {
                        is_ingredient_have = false;
                        return {false, 0};
                    }
                    price += mini_res.second;
                }
                return {true, price};
            } else {
                return {false, 0};
            }
        }
    }
};

int main() {
    std::map<std::string, Ingredient *> ingredients;
    std::uint32_t n;
    std::set<Ingredient *> need_ingredients;
    std::cin >> n;
    std::string temp_str;
    for (std::uint32_t i = 0; i < n; ++i) {
        std::cin >> temp_str;
        need_ingredients.emplace(ingredients.emplace(temp_str, new Ingredient()).first->second);
    }
    std::uint32_t m;
    std::cin >> m;
    std::uint32_t temp_int;
    for (std::uint32_t i = 0; i < m; ++i) {
        std::cin >> temp_str >> temp_int;
        auto it = ingredients.find(temp_str);
        if (it == ingredients.end()) it = ingredients.emplace(temp_str, new Ingredient()).first;
        it->second->price_in_shop = temp_int;
        it->second->is_in_shop = true;
    }
    std::uint32_t k;
    std::cin >> k;
    for (std::uint32_t i = 0; i < k; ++i) {
        std::uint32_t c;
        std::cin >> c;
        std::cin >> temp_str;
        auto it = ingredients.find(temp_str);
        if (it == ingredients.end()) it = ingredients.emplace(temp_str, new Ingredient()).first;
        auto now_ingr = it->second;
        now_ingr->is_ingredient_have = true;
        for (std::uint32_t j = 0; j < c; ++j) {
            std::cin >> temp_str;
            auto it2 = ingredients.find(temp_str);
            if (it2 == ingredients.end()) it2 = ingredients.emplace(temp_str, new Ingredient()).first;
            now_ingr->ingredients.emplace(it2->second);
        }
    }

    std::uint64_t result = 0;
    for (const auto &ff: need_ingredients) {
        auto mini_res = ff->GetPossibleAndOptimalPrice();
        if (!mini_res.first) {
            std::cout << "-1\n";
            return 0;
        }
        result += mini_res.second;
    }
    std::cout << result << "\n";
    return 0;
}
