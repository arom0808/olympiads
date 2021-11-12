#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::size_t N, M;
    std::cin >> N >> M;
    std::string cubes(N, '1');
    for (auto &cube: cubes)
        std::cin >> cube;
    std::string init_cubes = cubes;
    cubes += std::string(cubes.rbegin(), cubes.rend());
    std::vector<std::size_t> res;
    while (cubes.size() >= N) {
        if (cubes.substr(cubes.size() - N) == init_cubes) {
            res.push_back(cubes.size() / 2);
        }
        cubes.erase(cubes.size() / 2, 2);
    }
    std::sort(res.begin(), res.end());
    bool first_out = true;
    for (const auto &r: res) {
        std::cout << (first_out ? "" : " ") << r;
        first_out = false;
    }
    return 0;
}