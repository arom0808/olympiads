#include <iostream>
//#include <algorithm>
//#include <vector>
//
//bool ProcessStartPoint(std::uint32_t i, std::vector<bool> &visited, std::vector<bool> &results) {
//    if (i > 8848) return false;
//    if (i == 8848) return true;
//    if (visited[i]) return results[i];
//    visited[i] = true;
//    if (i % 2 == 0) results[i] = ProcessStartPoint(i / 2, visited, results);
//    else results[i] = ProcessStartPoint(i * 3 + 1, visited, results);
//    return results[i];
//}

int main() {
//    std::vector<bool> visited(8849, false), results(8849, false);
//    for (std::uint32_t i = 1; i < 8849; ++i) {
//        ProcessStartPoint(i, visited, results);
//        std::uint32_t start_value = i, now_value = i;
//        while (now_value < 8848) {
//            if (now_value % 2 == 0) now_value /= 2;
//            else now_value = now_value = now_value * 3 + 1;
//        }
//        if (now_value == 8848) std::cout << start_value << std::endl;
//        std::cout << "--" << i << "--" << std::endl;
//    }
//    std::erase_if(visited, [](bool b) { return !b; });
//    for (std::uint32_t i = 1; i < results.size(); ++i) if (results[i])std::cout << i << std::endl;
    std::uint32_t i;
    std::cin >> i;
    if (i == 1) std::cout << 2949;
    else if (i == 2) std::cout << 5898;
    else if (i == 3) std::cout << 8848;
    else std::cout << "-1";
    return 0;
}
