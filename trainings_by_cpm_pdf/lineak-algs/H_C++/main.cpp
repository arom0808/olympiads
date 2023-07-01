#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    std::uint32_t N, K;
    std::cin >> N >> K;
    std::vector<std::uint32_t> trees(N);
    for (auto &&tree: trees) std::cin >> tree;
    std::uint32_t best_i = 0, best_j = trees.size() - 1, i = 0, j = 0;
    std::unordered_map<std::uint32_t, std::uint32_t> now_in; //map<type,count>
    now_in.emplace(trees.front(), 1);
    while (true) {
        if (now_in.size() < K || i == j) {
            if (i == j && now_in.size() >= K) {
                best_i = i;
                best_j = j;
            }
            if (j < trees.size() - 1) {
                ++j;
                auto it = now_in.find(trees[j]);
                if (it == now_in.end()) now_in.emplace(trees[j], 1);
                else ++it->second;
            } else break;
        } else {
            if (j - i < best_j - best_i) {
                best_i = i;
                best_j = j;
            }
            if (i < j) {
                auto it = now_in.find(trees[i]);
                --it->second;
                if (it->second == 0) now_in.erase(it);
                ++i;
            }
        }
    }
    std::cout << best_i + 1 << " " << best_j + 1;
    return 0;
}
