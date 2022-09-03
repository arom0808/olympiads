#include <iostream>

void full_move(std::uint16_t str_length, std::uint16_t one_count_need, const std::string &pre_str) {
    if (str_length == 0)
        std::cout << pre_str << std::endl;
    else if (str_length == one_count_need)
        full_move(str_length - 1, one_count_need - 1, pre_str + "1");
    else if (one_count_need == 0) {
        full_move(str_length - 1, one_count_need, pre_str + "0");
    } else {
        full_move(str_length - 1, one_count_need, pre_str + "0");
        full_move(str_length - 1, one_count_need - 1, pre_str + "1");
    }
}

int main() {
    std::uint16_t N, K;
    std::cin >> N >> K;
    full_move(N, K, "");
    return 0;
}
