#include <algorithm>
#include <iostream>
#include <vector>

static std::int64_t e, cache_v;
static std::vector<std::int64_t> drug, cached_ls;


std::int64_t drugForce() {
    std::int64_t count = 0;
    cached_ls.resize(drug.size());
    for (auto &cls: cached_ls)
        cls = 0;
    for (std::size_t i = 0; i < drug.size(); ++i) {
        for (std::size_t j = i + 1; j < drug.size(); ++j) {
            if ((drug[i] + drug[j]) % e == 0) {
                ++count;
                ++cached_ls[i];
                ++cached_ls[j];
            }
        }
    }
    cache_v = count;
    return count;
}

int main() {
    std::int64_t n, tmp;
    std::cin >> n >> e;
    std::vector<std::pair<bool, std::int64_t>> operations(n);
    for (auto &operation: operations) {
        std::cin >> tmp;
        operation.first = tmp == 2;
        std::cin >> operation.second;
    }
    for (const auto &operation: operations) {
        if (operation.first) {
            std::size_t index = 0;
            for (; drug[index] != operation.second && index < drug.size(); ++index) {}
            cache_v -= cached_ls[index];
            drug.erase(drug.begin() + index);
            cached_ls.erase(cached_ls.begin() + index);
            std::cout << cache_v << std::endl;
        } else {
            drug.push_back(operation.second);
            std::cout << drugForce() << std::endl;
        }
    }
    return 0;
}