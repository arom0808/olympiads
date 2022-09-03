#include <iostream>
#include <fstream>
#include <vector>

std::uint32_t from_0_to_1 = 4, from_1_to_2 = 5, from_2_to_3 = 2, from_3_to_4 = 3, from_4_to_5 = 3, from_5_to_6 = 1,
        from_6_to_7 = 5, from_7_to_8 = 4, from_8_to_9 = 1, from_9_to_0 = 2;
std::uint32_t one_circle =
        from_0_to_1 + from_1_to_2 + from_2_to_3 + from_3_to_4 + from_4_to_5 + from_5_to_6 + from_6_to_7 +
        from_7_to_8 + from_8_to_9 + from_9_to_0;

std::uint32_t cnt_1 = 2;
std::uint32_t one_circle_from_disabled =
        cnt_1 + from_1_to_2 + from_2_to_3 + from_3_to_4 + from_4_to_5 + from_5_to_6 + from_6_to_7 +
        from_7_to_8 + from_8_to_9 + from_9_to_0;

std::uint32_t from_0_to_n(std::uint32_t n) {
    std::uint32_t res = 0;
    if (n >= 1)
        res += from_0_to_1;
    if (n >= 2)
        res += from_1_to_2;
    if (n >= 3)
        res += from_2_to_3;
    if (n >= 4)
        res += from_3_to_4;
    if (n >= 5)
        res += from_4_to_5;
    if (n >= 6)
        res += from_5_to_6;
    if (n >= 7)
        res += from_6_to_7;
    if (n >= 8)
        res += from_7_to_8;
    if (n >= 9)
        res += from_8_to_9;
    return res;
}

std::uint32_t from_disabled_to_n(std::uint32_t n) {
    std::uint32_t res = 0;
    if (n >= 1)
        res += cnt_1;
    if (n >= 2)
        res += from_1_to_2;
    if (n >= 3)
        res += from_2_to_3;
    if (n >= 4)
        res += from_3_to_4;
    if (n >= 5)
        res += from_4_to_5;
    if (n >= 6)
        res += from_5_to_6;
    if (n >= 7)
        res += from_6_to_7;
    if (n >= 8)
        res += from_7_to_8;
    if (n >= 9)
        res += from_8_to_9;
    return res;
}


int main() {
    std::uint32_t t, k;
    std::vector<std::uint64_t> results;
    std::ifstream inp("a_inp.txt");
    inp >> t;
    results.resize(t, 0);
    for (auto &res: results) {
        inp >> k;
        bool is_first = true;
        while (k > 0) {
            if (is_first) {
                res += (k / 10) * one_circle;
                res += from_0_to_n(k % 10);
                k /= 10;
            } else {
                if (k / 10 >= 1) {
                    res += one_circle_from_disabled;
                    res += ((k / 10) - 1) * one_circle;
                    res += from_0_to_n(k % 10);
                } else {
                    res += from_disabled_to_n(k);
                }
                k /= 10;
            }
            is_first = false;
        }
    }
    inp.close();
    std::ofstream out("a_out.txt");
    for (const auto &res: results)
        out << res << std::endl;
    out.close();
    return 0;
}
