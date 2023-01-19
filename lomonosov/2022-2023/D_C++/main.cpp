#include <iostream>
#include <vector>

void BuildTree(const std::vector<std::uint32_t> &numbers, std::vector<std::uint32_t> &segments_tree, std::uint32_t v,
               std::uint32_t tl, std::uint32_t tr) {
    if (tl == tr) segments_tree[v] = numbers[tl];
    else {
        std::uint32_t tm = (tl + tr) / 2;
        BuildTree(numbers, segments_tree, v * 2, tl, tm);
        BuildTree(numbers, segments_tree, v * 2 + 1, tm + 1, tr);
        segments_tree[v] = std::max(segments_tree[v * 2], segments_tree[v * 2 + 1]);
    }
}

std::uint32_t Max(const std::vector<std::uint32_t> &segments_tree, std::uint32_t v, std::uint32_t tl, std::uint32_t tr,
                  std::uint32_t l, std::uint32_t r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return segments_tree[v];
    std::uint32_t tm = (tr + tl) / 2;
    return std::max(Max(segments_tree, v * 2, tl, tm, l, std::min(r, tm)),
                    Max(segments_tree, v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
}

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::vector<std::uint32_t> numbers(N);
    for (auto &&num: numbers) std::cin >> num;

    std::vector<std::uint32_t> segments_tree(4 * N);
    BuildTree(numbers, segments_tree, 1, 0, N - 1);

    std::uint32_t K;
    std::cin >> K;
    std::uint32_t l, r;
    std::vector<uint32_t> results(N - K + 1);
    for (std::uint32_t n_l = 0, n_r = K - 1, res_i = 0; n_r < N; ++n_l, ++n_r, ++res_i) {
        std::cin >> l >> r;
        std::uint32_t f_l, f_r;
        if (n_l >= l) f_l = n_l - l;
        else f_l = 0;
        if (n_r + r < N) f_r = n_r + r;
        else f_r = N - 1;
        results[res_i] = Max(segments_tree, 1, 0, N - 1, f_l, f_r);
    }
    for (const auto &res: results) std::cout << res << "\n";
    return 0;
}
