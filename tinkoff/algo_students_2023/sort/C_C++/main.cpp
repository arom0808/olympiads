#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
//#include <fstream>

char GetCharOfConcatenation(const std::string &a, const std::string &b, std::uint32_t pos) {
    if (pos < a.size()) return a[pos];
    return b[pos - a.size()];
}

void MySolution(std::vector<std::string> &strings, std::string &result) {
    auto SortCmpF = [](const std::string &a, const std::string &b) -> bool {
        for (std::uint32_t i = 0; i < a.size() + b.size(); ++i) {
            char ab = GetCharOfConcatenation(a, b, i);
            char ba = GetCharOfConcatenation(b, a, i);
            if (ab > ba) return true;
            else if (ab < ba) return false;
        }
        return false;
    };
    std::sort(strings.begin(), strings.end(), SortCmpF);
    result.clear();
    result.reserve(strings.size() * 100);
    for (const auto &str: strings) result += str;
}

void Input(const std::function<void(std::string &)> &callback) {
    std::string line;
    while (std::cin >> line) callback(line);
}


int main() {

    std::vector<std::string> strings;
    strings.reserve(10000);
    Input([&strings](std::string &str) { strings.emplace_back(std::move(str)); });

    std::string my_res;
    MySolution(strings, my_res);
    std::cout << my_res;
    return 0;
}


//std::random_device dev;
//std::uint32_t seed = dev();
//std::mt19937 rng(seed);
//



//
//void RightSolution(std::vector<std::string> &strings, std::string &result) {
//    std::sort(strings.begin(), strings.end());
//    std::string now_res;
//    result.clear();
//    result.reserve(strings.size() * 100);
//    now_res.reserve(strings.size() * 100);
//    for (const auto &str: strings) result += str;
//    do {
//        now_res.clear();
//        for (const auto &str: strings) now_res += str;
//        if (now_res > result) result = now_res;
//    } while (std::next_permutation(strings.begin(), strings.end()));
//}



//void Generator(std::vector<std::string> &strings) {
//    std::uniform_int_distribution dist_n(1, 10), dist_digit(0, 9), dist_not_zero_digit(1, 9);
//    strings.resize(dist_n(rng));
//    for (auto &&str: strings) {
//        str.resize(dist_n(rng));
//        for (auto &&ch: str) ch = static_cast<char>(static_cast<std::int32_t>('0') + dist_digit(rng));
//    }
//    strings[0][0] = static_cast<char>(static_cast<std::int32_t>('0') + dist_digit(rng));
//}


//void WriteInput(const std::vector<std::string> &strings) {
//    std::ofstream out("in.txt");
//    for (const auto &str: strings) out << str << "\n";
//    out.close();
//}


//    std::cout << seed << std::endl;
//    auto not_right_example = AutoTest<std::vector<std::string>, std::string>(&Generator, &RightSolution, &MySolution);
//    std::cout << "Inputs:\n";
//    for (const auto &input: not_right_example.first) std::cout << input << "\n";
//    std::cout << "\nRight solution:\n" << not_right_example.second.first << "\nMy solution:\n"
//              << not_right_example.second.second;
//    WriteInput(not_right_example.first);