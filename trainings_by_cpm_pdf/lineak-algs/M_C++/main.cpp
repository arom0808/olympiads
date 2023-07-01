#include <iostream>
#include <string>

int main() {
    std::uint32_t n;
    std::string str;
    std::cin >> n >> str;
    std::uint32_t girls_cnt = 0, boys_cnt = 0;
    std::uint64_t res = 0;
    if (str.front() == 'a') ++girls_cnt;
    else ++boys_cnt;
    for (std::uint32_t i = 0; i < str.size() - 1;) {
        for (std::uint32_t j = i; j < str.size() - 1;) {
            ++j;
            if (str[j] == 'a') ++girls_cnt;
            else ++boys_cnt;
            if (girls_cnt == boys_cnt) ++res;
        }
        ++i;
        girls_cnt = boys_cnt = 0;
        if (str[i] == 'a') ++girls_cnt;
        else ++boys_cnt;
    }
    std::cout << res;
    return 0;
}
