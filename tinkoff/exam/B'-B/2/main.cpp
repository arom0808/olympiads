#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string in_str;
    std::getline(std::cin, in_str);
    std::uint32_t bracket_level = 0;
    std::stringstream out_str_stream;
    for (auto &ch: in_str) {
        if (ch == '(') {
            ++bracket_level;
            if (bracket_level == 1) out_str_stream << '{';
            else if (bracket_level == 2) out_str_stream << '[';
            else out_str_stream << '(';
        } else if (ch == ')') {
            if (bracket_level == 1) out_str_stream << '}';
            else if (bracket_level == 2) out_str_stream << ']';
            else out_str_stream << ')';
            --bracket_level;
        } else out_str_stream << ch;
    }
    std::cout << out_str_stream.str();
    return 0;
}
