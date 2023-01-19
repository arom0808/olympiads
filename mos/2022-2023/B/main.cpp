#include <iostream>
#include <vector>
#include <set>

int main() {
    std::uint32_t N;
    std::cin >> N;
    std::set<std::vector<bool>> cache;
    std::vector<bool> students(N);
    std::string inp_str;
    inp_str.reserve(N);
    std::cin >> inp_str;
    for (std::uint32_t i = 0; i < N; ++i) {
        students[i] = (inp_str[i] == '>');
    }
    cache.insert(students);
    std::uint32_t result = 0;
    while (true) {
        bool is_pairs_exists = false;
        for (std::uint32_t pre_i = 0, i = 1; i < N; ++pre_i, ++i) {
            if (students[pre_i] && (!students[i])) {
                students[pre_i] = false;
                students[i] = true;
                is_pairs_exists = true;
                ++pre_i;
                ++i;
                ++result;
            }
        }
        if (!is_pairs_exists) {
            std::cout << result;
            return 0;
        }
        if (cache.find(students) != cache.end()) {
            std::cout << -1;
            return 0;
        }
        cache.insert(students);
    }
    return 0;
}

//#include <bitset>
//const std::uint64_t const_one_value = 1ULL, const_first_digit_one_value = 1ULL << 63;
//
//void InputStudents(std::vector<std::uint64_t> &students, std::uint32_t N) {
//    students.clear();
//    students.reserve(N / 64 + (N % 64 != 0));
//    std::string inp;
//    inp.reserve(N);
//    std::cin >> inp;
//    std::uint64_t buf_num = 0, buf_move_n = const_first_digit_one_value;
//    for (std::uint32_t i = 0; i < N; ++i) {
//        if (inp[i] == '>') buf_num |= buf_move_n;
//        if (buf_move_n == const_one_value) {
//            students.push_back(buf_num);
//            buf_move_n = const_first_digit_one_value;
//            buf_num = 0;
//        } else buf_move_n >>= 1;
//    }
//    if (buf_move_n != const_first_digit_one_value) students.push_back(buf_num);
//}
//    std::uint32_t N;
//    std::cin >> N;
//    std::set<std::vector<std::uint64_t>> cache;
//    std::vector<std::uint64_t> students;
//    InputStudents(students, N);
////    for (const auto &i: students) {
////        std::bitset<64> asd(i);
////        std::cout << asd.to_string();
////    }
//    cache.insert(students);