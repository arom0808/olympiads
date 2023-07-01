#include <iostream>
#include <set>
#include <vector>
#include <algorithm>


struct Worker {
    std::uint64_t a = 0, b = 0;
};

int main() {
    std::uint64_t n;
    std::cin >> n;
    std::vector<Worker> workers(n);
    for (auto &&worker: workers) std::cin >> worker.a >> worker.b;
    std::sort(workers.begin(), workers.end(), [](const Worker &a, const Worker &b) { return a.a < b.a; });
    auto cmp_b = [](const Worker &a, const Worker &b) { return a.b < b.b; };
    std::multiset<Worker, decltype(cmp_b)> bot_workers;
    std::uint32_t max_res = 0;
    for (auto it = workers.rbegin(); it != workers.rend(); ++it) {
        std::uint32_t now_k = 1, now_min_a = it->a, now_b_sum = it->b;
        std::uint32_t now_res = (now_k * now_min_a >= now_b_sum);
        for (const auto &bot_w: bot_workers) {
            if (bot_w.b > now_min_a && (now_k + 1) * now_min_a < now_b_sum + bot_w.b) break;
            ++now_k;
            now_b_sum += bot_w.b;
            ++now_res;
        }
        if (now_res > max_res) max_res = now_res;
        bot_workers.emplace(*it);
    }
    std::cout << max_res;
    return 0;
}
