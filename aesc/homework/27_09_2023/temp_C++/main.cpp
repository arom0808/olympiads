#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

std::map<char, std::uint32_t> tr(const std::string &a) {
    std::map<char, std::uint32_t> res;
    for (const auto c: a) {
        auto it = res.find(c);
        if (it == res.end()) res.emplace(c, 1);
        else ++it->second;
    }
    return res;
}

std::string atr(const std::map<char, std::uint32_t> &s) {
    std::string res;
    for (const auto &ss: s)
        for (std::uint32_t i = 0; i < ss.second; ++i)
            res += ss.first;
    return res;
}

int main() {
    std::string istr = "abcd";
    std::set<std::map<char, std::uint32_t>> mps;
    mps.emplace();
    do {
        mps.emplace(tr(istr.substr(0, 1)));
        mps.emplace(tr(istr.substr(0, 2)));
        mps.emplace(tr(istr.substr(0, 3)));
        mps.emplace(tr(istr.substr(0, 4)));
    } while (std::next_permutation(istr.begin(), istr.end()));
//    auto cmp = [](const std::string &a, const std::string &b) {
//        if (a.size() < b.size()) return true;
//        if (a.size() > b.size()) return false;
//        return a < b;
//    };
    std::set<std::string/*, decltype(cmp)*/> strs;
    for (const auto &ss: mps) {
        strs.emplace(atr(ss));
    }
    std::cout << strs.size() << "\n";
    std::vector<std::string> vstrs(strs.begin(), strs.end());
    for (std::uint32_t i = 0; i < vstrs.size(); ++i) {
        std::cout << i + 1 << (i < 9 ? " " : "") << ": " <<
                  (vstrs[i].find('a') != std::string::npos ? "a" : " ") <<
                  (vstrs[i].find('b') != std::string::npos ? "b" : " ") <<
                  (vstrs[i].find('c') != std::string::npos ? "c" : " ") <<
                  (vstrs[i].find('d') != std::string::npos ? "d" : " ") <<
                  "\n";
    }
    return 0;
}
