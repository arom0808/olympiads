#include <iostream>
#include <vector>

template<typename T>
T ApproximateBinarySearch(const std::vector<T> &search_list, const T &finding_value) {
    std::size_t l = 0, r = search_list.size();
    while (l != r) {
        auto middle = (l + r) / 2 + ((l + r) % 2);
        const T &middle_value = search_list[middle];
        if (middle_value == finding_value)
            return middle_value;
        else if (middle_value < finding_value)
            l = middle;
        else
            r = middle - 1;
    }
    return search_list[l];
}

int main() {
    std::uint32_t N, K;
    std::cin >> N >> K;
    std::vector<std::uint32_t> f_a(N), s_a(K);
    for (auto &&v: f_a)
        std::cin >> v;
    for (auto &&v: s_a)
        std::cin >> v;
    for (const auto &v: s_a)
        std::cout << ApproximateBinarySearch(f_a, v) << std::endl;
    return 0;
}
