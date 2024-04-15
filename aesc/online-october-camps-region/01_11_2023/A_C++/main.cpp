#include <iostream>

int main() {
    std::uint64_t n, k, x;
    std::cin >> n >> k >> x;
    auto normal_cnt = n - k;
    auto min_ball = x / normal_cnt, max_ball = min_ball + 1;
    std::uint64_t l = 0, r = normal_cnt;
    while (l != r) {
        auto m = (l + r) / 2;
        auto now_sum = m * max_ball + (normal_cnt - m) * min_ball;
        if (now_sum < x) l = m + 1;
        else if (now_sum == x) l = r = m;
        else r = m;
    }
    if (l == 0) max_ball = min_ball;
    std::cout << max_ball * (l + k) + min_ball * (normal_cnt - l);
    return 0;
}
