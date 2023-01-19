#include <iostream>
#include <set>

int main() {
    std::set<std::uint32_t> numbers{1};
    while (true) {
        std::uint32_t pre_size = numbers.size();
        for (const auto &num: numbers) {
            if (num % 2 == 0) if (num / 2 < 440) numbers.insert(num / 2);
            if (num + 7 < 440) numbers.insert(num + 7);
        }
        if (numbers.size() == pre_size) break;
    }
    for (const auto &num: numbers) std::cout << num << " ";
    std::cout << "\n";
    std::cout << "total count: " << numbers.size() << std::endl;
    return 0;
}
