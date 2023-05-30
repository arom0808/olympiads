#include <iostream>
#include <set>
#include <vector>

bool IsBigAlpha(char c) { return c >= 'A' && c <= 'Z'; }

bool IsSmallAlpha(char c) { return c >= 'a' && c <= 'z'; }

bool IsAlpha(char c) { return IsBigAlpha(c) || IsSmallAlpha(c); }

char SwitchRegTo(char c, char reg_from) {
    bool f_r = IsBigAlpha(c), s_r = IsBigAlpha(reg_from);
    if (f_r == s_r) return c;
    if (f_r) return 'a' + (c - 'A');
    return 'A' + (c - 'a');
}

bool IsNonRegCharEq(char c, char eq_to) { return SwitchRegTo(c, eq_to) == eq_to; }

void FirstReplacing(std::string &str) {
    for (std::uint32_t i = 0; i < str.size();) {
        if (IsNonRegCharEq(str[i], 'c')) {
            if (i < str.size() - 1) {
                if (IsNonRegCharEq(str[i + 1], 'i') || IsNonRegCharEq(str[i + 1], 'e'))
                    str[i] = SwitchRegTo('s', str[i]);
                else if (IsNonRegCharEq(str[i + 1], 'k')) {
                    str[i + 1] = SwitchRegTo(str[i + 1], str[i]);
                    str.erase(i, 1);
                } else str[i] = SwitchRegTo('k', str[i]);
            } else str[i] = SwitchRegTo('k', str[i]);
            if (i > 0) --i;
        } else ++i;
    }
}

void SecondReplace(std::string &str) {
    for (std::uint32_t i = 0; i < str.size() - 1;) {
        if (IsAlpha(str[i]) && IsNonRegCharEq(str[i], str[i + 1])) {
            if (IsNonRegCharEq(str[i], 'e')) str[i + 1] = SwitchRegTo('i', str[i]);
            else if (IsNonRegCharEq(str[i], 'o')) str[i + 1] = SwitchRegTo('u', str[i]);
            else str[i + 1] = str[i];
            str.erase(i, 1);
            if (i > 0) --i;
        } else ++i;
    }
}

void ThirdReplace(std::string &str) {
    for (std::uint32_t i = 1; i < str.size();) {
        if (str[i] == 'e' && IsAlpha(str[i - 1]) && (i == str.size() - 1 || (!IsAlpha(str[i + 1])))) {
            str.erase(i, 1);
            if (i > 1) --i;
        } else ++i;
    }
}

std::vector<std::string_view> &SplitStr(const std::string &str, std::vector<std::string_view> &res) {
    res.clear();
    res.reserve(str.size());
    bool now_type = IsAlpha(str.front());
    std::string_view full_str_view(str);
    std::uint32_t start = 0;
    for (std::uint32_t i = 0; i < str.size(); ++i) {
        if (IsAlpha(str[i]) == now_type) continue;
        res.push_back(full_str_view.substr(start, i - start));
        start = i;
        now_type = IsAlpha(str[i]);
    }
    res.push_back(full_str_view.substr(start));
    return res;
}

bool IsArticle(const std::string_view &str) {
    if (str.empty() || str.size() > 3) return false;
    if (IsNonRegCharEq(str.front(), 'a')) {
        if (str.size() == 1) return true;
        if (str.size() == 2 && IsNonRegCharEq(str[1], 'n')) return true;
        return false;
    } else if (IsNonRegCharEq(str.front(), 't')) {
        return str.size() == 3 && IsNonRegCharEq(str[1], 'h') && IsNonRegCharEq(str[2], 'e');
    }
    return false;
}

void DeleteExtraSpaces(std::string &str) {
    for (std::uint32_t i = 0; i < str.size() - 1;) {
        if (str[i] == ' ' && str[i + 1] == ' ') str.erase(i, 1);
        else ++i;
    }
    while ((!str.empty()) && str.front() == ' ') str.erase(0, 1);
    while ((!str.empty()) && str.back() == ' ') str.erase(str.size() - 1, 1);
}

void FourthReplace(std::string &str, const std::vector<std::string_view> &start_split) {
    std::vector<std::string_view> now_split;
    const std::string now_start_str = str;
    SplitStr(now_start_str, now_split);
    str.clear();
    for (std::uint32_t i = 0; i < start_split.size(); ++i) if (!IsArticle(start_split[i])) str.append(now_split[i]);
    DeleteExtraSpaces(str);
}

int main() {
    std::string str;
    std::getline(std::cin, str);
    const std::string start_str = str;
    FirstReplacing(str);
    SecondReplace(str);
    ThirdReplace(str);
    std::vector<std::string_view> start_split;
    FourthReplace(str, SplitStr(start_str, start_split));
    std::cout << str;
    return 0;
}
