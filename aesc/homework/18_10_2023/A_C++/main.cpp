#include <iostream>


//#include <tuple>
//std::tuple<std::int32_t, std::int32_t, std::int32_t> func_1(std::int32_t a, std::int32_t b, std::int32_t c) {
//    if (a < b) {
//        if (b < c) return std::make_tuple(a, b, c);
//        if (a < c) return std::make_tuple(a, c, b);
//        return std::make_tuple(c, a, b);
//    }
//    if (c < b) return std::make_tuple(c, b, a);
//    if (c < a) return std::make_tuple(b, c, a);
//    return std::make_tuple(b, a, c);
//}

void func_2(std::int32_t &a, std::int32_t &b, std::int32_t &c) {
    if (a > b) std::swap(a, b);
    if (b > c) std::swap(b, c);
    if (a > b) std::swap(a, b);
}

int main() {
    std::int32_t a, b, c;
    std::cin >> a >> b >> c;
//    std::tie(a, b, c) = func_1(a, b, c);
    func_2(a, b, c);
    std::cout << a << " " << b << " " << c;
    return 0;
}
