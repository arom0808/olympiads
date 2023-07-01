#include <iostream>
#include <stack>

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::stack<std::pair<std::uint32_t, std::uint32_t>> st;
    std::uint64_t max_res = 0;
    std::uint32_t now_x, now_h;
    for (std::uint32_t i = 0; i < N; ++i) {
        std::cin >> now_h;
        now_x = i;
        while (!st.empty() && now_h < st.top().second) {
            now_x = st.top().first;
            auto this_h = st.top().second;
            st.pop();
            auto new_res = static_cast<std::uint64_t>(this_h) * static_cast<std::uint64_t>(i - now_x);
            if (new_res > max_res) max_res = new_res;
        }
        if (st.empty() || now_h > st.top().second) st.emplace(now_x, now_h);
    }
    std::cout << max_res;
    return 0;
}
