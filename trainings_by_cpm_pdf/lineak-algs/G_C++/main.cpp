#include <iostream>
#include <vector>
#include <algorithm>

using vec_iter = std::vector<std::uint32_t>::iterator;

int main() {
    std::uint32_t n_1, n_2, n_3, n_4;
    std::cin >> n_1;
    std::vector<std::uint32_t> a_1(n_1);
    for (auto &&a: a_1) std::cin >> a;
    std::cin >> n_2;
    std::vector<std::uint32_t> a_2(n_2);
    for (auto &&a: a_2) std::cin >> a;
    std::cin >> n_3;
    std::vector<std::uint32_t> a_3(n_3);
    for (auto &&a: a_3) std::cin >> a;
    std::cin >> n_4;
    std::vector<std::uint32_t> a_4(n_4);
    for (auto &&a: a_4) std::cin >> a;
    std::sort(a_1.begin(), a_1.end());
    std::sort(a_2.begin(), a_2.end());
    std::sort(a_3.begin(), a_3.end());
    std::sort(a_4.begin(), a_4.end());
    std::uint32_t min_dif = 1e9, res_1, res_2, res_3, res_4;
    auto f_4 = [&min_dif, &res_1, &res_2, &res_3, &res_4](vec_iter i_1, vec_iter i_2, vec_iter i_3, vec_iter i_4) {
        auto dif = std::max(*i_1, std::max(*i_2, std::max(*i_3, *i_4))) -
                   std::min(*i_1, std::min(*i_2, std::min(*i_3, *i_4)));
        if (dif < min_dif) {
            min_dif = dif;
            res_1 = *i_1;
            res_2 = *i_2;
            res_3 = *i_3;
            res_4 = *i_4;
        }
    };
    auto f_3 = [&a_4, &f_4](vec_iter i_1, vec_iter i_2, vec_iter i_3) {
        auto i_4_2 = std::lower_bound(a_4.begin(), a_4.end(), std::min(*i_1, std::min(*i_2, *i_3)));
        auto i_4_1 = (i_4_2 == a_4.begin() ? i_4_2 : std::prev(i_4_2));
        f_4(i_1, i_2, i_3, i_4_1);
        f_4(i_1, i_2, i_3, i_4_2);
    };
    auto f_2 = [&a_3, &f_3](vec_iter i_1, vec_iter i_2) {
        auto i_3_2 = std::lower_bound(a_3.begin(), a_3.end(), std::min(*i_1, *i_2));
        auto i_3_1 = (i_3_2 == a_3.begin() ? i_3_2 : std::prev(i_3_2));
        f_3(i_1, i_2, i_3_1);
        f_3(i_1, i_2, i_3_2);
    };
    auto f_1 = [&a_2, &f_2](vec_iter i_1) {
        auto i_2_2 = std::lower_bound(a_2.begin(), a_2.end(), *i_1);
        auto i_2_1 = (i_2_2 == a_2.begin() ? i_2_2 : std::prev(i_2_2));
        f_2(i_1, i_2_1);
        f_2(i_1, i_2_2);
    };
    for (auto i_1 = a_1.begin(); i_1 != a_1.end(); ++i_1) f_1(i_1);
    std::cout << res_1 << " " << res_2 << " " << res_3 << " " << res_4;
    return 0;
}
