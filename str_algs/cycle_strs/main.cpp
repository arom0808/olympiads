#include <iostream>
#include <cstring>

bool
is_str_of_substr(const char *str, const std::size_t &str_size, const char *substr, const std::size_t &substr_size,
                 std::size_t &i) {
    i = 0;
    for (; i <= str_size - substr_size; i += substr_size)
        if (strncmp(str + i, substr, substr_size) != 0)
            return false;
    if (str_size % substr_size == 0)
        return true;
    if (strncmp(str, str + i, str_size - i) != 0)
        return false;
    return true;
}

int main() {
    std::string str_s;
    std::cin >> str_s;
    const char *str = str_s.c_str();
    const std::size_t str_size = str_s.length();
    std::size_t ii;
    for (std::size_t i = 1; i < str_size + 1; ++i) {
        if (is_str_of_substr(str, str_size, str, i, ii)) {
            std::cout << i;
            return 0;
        }
    }
    return 0;
}
