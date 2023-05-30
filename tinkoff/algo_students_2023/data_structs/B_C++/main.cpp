#include <iostream>
#include <set>
#include <vector>
#include <queue>

int main() {
    std::uint32_t N, K;
    std::cin >> N >> K;
    std::vector<std::int32_t> results(N - K + 1);
    std::multiset<std::int32_t> window;
    std::queue<std::int32_t> queue_window;
    std::int32_t temp;
    for (std::uint32_t i = 0; i < K; ++i) {
        std::cin >> temp;
        window.insert(temp);
        queue_window.push(temp);
    }
    for (std::uint32_t start = 0, end = K; end <= N; ++start, ++end) {
        results[start] = *window.begin();
        if (end < N) {
            std::cin >> temp;
            window.erase(window.find(queue_window.front()));
            queue_window.pop();
            window.insert(temp);
            queue_window.push(temp);
        }
    }
    for (const auto &res: results) std::cout << res << " ";
    return 0;
}
