#include <iostream>

using namespace std;

inline bool is_digit(char c) { return c >= '0' && c <= '9'; }

inline bool is_letter(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

inline bool is_allowed_name(char c) { return is_digit(c) || is_letter(c) || c == '_'; }

bool solve(const string &str) {
    int32_t f_start = 0;
    while (f_start < str.size() && str[f_start] == ' ') ++f_start;
    if (f_start >= str.size() || is_digit(str[f_start]) || !is_allowed_name(str[f_start])) return false;
    int32_t f_end = f_start + 1;
    while (f_end < str.size() && is_allowed_name(str[f_end])) ++f_end;
    if (f_end >= str.size()) return false;
    int32_t s_start = f_end;
    while (s_start < str.size() && str[s_start] == ' ') ++s_start;
    if (s_start + 1 >= str.size() || str[s_start] != ':' || str[s_start + 1] != '=') return false;
    int32_t t_start = s_start + 2;
    while (t_start < str.size() && str[t_start] == ' ') ++t_start;
    if (t_start >= str.size() || (!is_allowed_name(str[t_start]) && str[t_start] != '-')) return false;
    int32_t t_end = t_start + 1;
    if (is_digit(str[t_start]) || str[t_start] == '-') while (t_end < str.size() && is_digit(str[t_end])) ++t_end;
    else while (t_end < str.size() && is_allowed_name(str[t_end])) ++t_end;
    for (int32_t i = t_end; i < str.size(); ++i) if (str[i] != ' ') return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string str;
    getline(cin, str);
    cout << (solve(str) ? "YES" : "NO");
    return 0;
}
