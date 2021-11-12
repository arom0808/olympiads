#include <iostream>

int main() {
    std::string str, smv;
    std::cin >> str >> smv;
    smv += smv;
    auto pos = smv.find(str);
    if (pos == std::string::npos) {
        std::cout << "-1";
        return 0;
    }
    std::cout << pos;
}
