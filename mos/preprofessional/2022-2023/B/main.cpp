#include <iostream>
#include <algorithm>

bool CheckIsBLockOfPal(const std::string &str, bool is_pal_mid_on_next_mid, std::uint32_t mid) {
    std::int32_t i1 = mid, i2 = (is_pal_mid_on_next_mid ? mid + 1 : mid);
    while (i1 >= 0 && i2 < str.size()) {
        if (str[i1] != str[i2]) return false;
        --i1;
        ++i2;
    }
    return true;
}

int main() {
    std::string str;
    std::cin >> str;
    if (str.size() < 2) {
        std::cout << str;
        return 0;
    }
    bool is_pal_mid_on_next_mid = str.size() % 2 == 0;
    std::uint32_t mid = str.size() / 2;
    if (str.size() % 2 == 0) --mid;
    while (!CheckIsBLockOfPal(str, is_pal_mid_on_next_mid, mid)) {
        if (is_pal_mid_on_next_mid) {
            ++mid;
            is_pal_mid_on_next_mid = false;
        } else is_pal_mid_on_next_mid = true;
    }
    std::uint32_t reverse_start = (is_pal_mid_on_next_mid ? mid : mid - 1);
    std::uint32_t already_right_block_wrote_size = str.size() - mid - 1;
    reverse_start -= already_right_block_wrote_size;
    auto ee = str.substr(0, reverse_start + 1);
    std::reverse(ee.begin(), ee.end());
    std::cout << str << ee;
    return 0;
}
