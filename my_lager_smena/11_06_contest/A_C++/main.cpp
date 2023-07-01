#include <iostream>

int main() {
    std::uint64_t n, m, x, y;
    std::cin >> n >> m >> x >> y;
//    std::uint32_t left_top_x = x, left_top_y = y, right_bottom_x = x, right_bottom_y = y;
//    while (left_top_x > 0 && left_top_y < m && right_bottom_x < n && right_bottom_y > 0) {
//        --left_top_x;
//        ++left_top_y;
//        ++right_bottom_x;
//        --right_bottom_y;
//    }
//    std::uint32_t res_plus = 0;
//    if (right_bottom_x == n) {
//
//    } else if (left_top_x == 0) {
//        if (left_top_y < m) {
//            if (right_bottom_x < n) {
//                res_plus += right_bottom_x - left_top_x + 2;
//                if ()
//            }
//        }
//    }
    std::uint64_t left_dist = x - 1, top_dist = m - y, right_dist = n - x, bottom_dist = y - 1;
    if (right_dist <= left_dist && right_dist <= top_dist && right_dist <= bottom_dist) {
        std::cout << ((right_dist * 2 + 1) * (right_dist * 2 + 1));
    } else if (bottom_dist < right_dist && bottom_dist <= left_dist && bottom_dist <= top_dist) {
        std::cout << ((bottom_dist * 2 + 1) * (bottom_dist * 2 + 2));
    } else if (left_dist < right_dist && left_dist < bottom_dist && left_dist <= top_dist) {
        std::cout << ((left_dist * 2 + 2) * (left_dist * 2 + 2));
    } else {
        std::cout << ((top_dist * 2 + 2) * (top_dist * 2 + 3));
    }
    return 0;
}
