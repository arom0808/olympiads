#include <iostream>
#include <vector>
#include <algorithm>

using Permutation = std::vector<std::uint32_t>;
using Experiment = std::pair<std::uint32_t, long double>;
using Experiments = std::vector<Experiment>;

long double getProbability(Permutation &permutation, Experiments &experiments) {
    long double last_probability = 1;
    while (permutation.back() == permutation.size()) {
        experiments.erase(std::remove_if(experiments.begin(), experiments.end(),
                                         [&last_probability, permutation](const Experiment &a) {
                                             if (a.first == permutation.size()) {
                                                 last_probability *= 1 - a.second;
                                                 return true;
                                             }
                                             return false;
                                         }), experiments.end());
        permutation.erase(std::next(permutation.end(), -1));
    }
    if (permutation.empty()) return 1;
    std::sort(experiments.begin(), experiments.end(), [](const Experiment &a, const Experiment &b) {
        return a.first >= b.first;
    });
    if (experiments.front().first < permutation.size()) return 0;
    for (auto it = experiments.begin(); it != experiments.end() && it->first == experiments.front().first; ++it)
        last_probability *= 1 - it->second;
    return 1 - last_probability;
}

int main() {
    std::uint32_t t;
    std::cin >> t;
    std::vector<long double> results(t);
    for (auto &&res: results) {
        std::uint32_t n, m;
        std::cin >> n >> m;
        Permutation permutation(n);
        Experiments experiments(m);
        for (auto &&perm_item: permutation) std::cin >> perm_item;
        for (auto &&experiment: experiments) std::cin >> experiment.first >> experiment.second`;
        res = getProbability(permutation, experiments);
    }
    std::cout.precision(10);
    for (const auto &res: results) std::cout << res << std::endl;
    return 0;
}