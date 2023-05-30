#include <iostream>
#include <algorithm>
#include <set>
#include <fstream>

int main() {
    std::ifstream in_file("input.txt");
    std::set<std::string> results;
    std::string start_str, str;
    std::getline(in_file, start_str);
    std::sort(start_str.begin(), start_str.end());
    auto last_space = start_str.rfind(' ');
    if (last_space != std::string::npos) start_str.erase(0, last_space + 1);
    do {
        str.clear();
        str.reserve(start_str.size());
        do {
            str.push_back(start_str[str.size()]);
            results.insert(str);
        } while (str.size() < start_str.size());
    } while (std::next_permutation(start_str.begin(), start_str.end()));
    results.erase("");
    std::ofstream out_file("output.txt");
    for (const auto &i: results) out_file << i << "\n";
}