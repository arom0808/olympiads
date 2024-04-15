#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_link(const string &raw_str, uint64_t now_start, uint64_t now_end) {
    if (now_end - now_start < 8) return false;
    if (raw_str[now_start] != 'h' ||
        raw_str[now_start + 1] != 't' ||
        raw_str[now_start + 2] != 't' ||
        raw_str[now_start + 3] != 'p' ||
        raw_str[now_start + 4] != ':' ||
        raw_str[now_start + 5] != '/' ||
        raw_str[now_start + 6] != '/')
        return false;
    for (uint32_t i = now_start + 7; i < now_end; ++i)
        if (!(raw_str[i] >= 'a' && raw_str[i] <= 'z') && !(raw_str[i] >= '0' && raw_str[i] <= '9') &&
            raw_str[i] != '/' && raw_str[i] != ':' && raw_str[i] != '.')
            return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string l_str, raw_str;
    std::getline(cin, l_str), std::getline(cin, raw_str);
    uint64_t l = stoi(l_str), now_len = raw_str.size(), now_start, now_end, next_start = 0;
    string res_str;
    res_str.reserve(raw_str.size());
    while (true) {
        now_start = next_start, now_end = raw_str.find(' ', now_start);
        if (now_end == string::npos) now_end = raw_str.size();
        next_start = now_end + 1;
        if (now_len <= l) {
            res_str += raw_str.substr(now_start);
            break;
        }
        if (is_link(raw_str, now_start, now_end)) {
            if (now_len - l >= now_end - now_start - 3) now_len -= now_end - now_start - 3;
            else {
                res_str += raw_str.substr(now_start, now_end - now_start - 3 - (now_len - l));
                now_len = l;
            }
            res_str += "...";
        } else for (uint32_t i = now_start; i < now_end; ++i) res_str.push_back(raw_str[i]);
        if (now_end != raw_str.size()) res_str.push_back(' ');
        if (now_end >= raw_str.size()) break;
    }
    cout << res_str << "\n" << (now_len > l ? now_len - l : 0);
    return 0;
}
