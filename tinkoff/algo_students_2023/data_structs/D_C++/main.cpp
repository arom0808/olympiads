#include <iostream>
#include <list>
#include <vector>

int main() {
    std::string temp_line;
    std::getline(std::cin, temp_line);
    std::uint32_t N = std::stoi(temp_line);
    std::list<std::uint32_t> goblins;
    std::list<std::uint32_t>::iterator middle_it;
    std::vector<std::uint32_t> results;
    results.reserve(N);
    for (std::uint32_t i = 0; i < N; ++i) {
        std::getline(std::cin, temp_line);
        if (temp_line.size() == 1) {
            results.push_back(goblins.back());
            if (goblins.size() % 2 == 0) if (middle_it != goblins.begin()) std::advance(middle_it, -1);
            goblins.pop_back();
        } else {
            std::uint32_t num = std::stoi(std::string(std::next(temp_line.begin(), 2), temp_line.end()));
            if (goblins.empty()) {
                goblins.push_back(num);
                middle_it = goblins.begin();
            } else {
                if (temp_line[0] == '+') {
                    goblins.push_front(num);
                    if (goblins.size() % 2 != 0) if (middle_it != goblins.begin()) std::advance(middle_it, -1);
                } else {
                    goblins.insert(middle_it, num);
                    if (goblins.size() % 2 != 0) if (middle_it != goblins.begin()) std::advance(middle_it, -1);
                }
            }
        }
    }
    for (const auto &res: results) std::cout << res << "\n";
    return 0;
}
