#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string str;
    std::getline(cin, str);
    uint32_t start = 0, end = str.size();
    while (str[start] == ' ') ++start;
    while (end > 0 && str[end - 1] == ' ') --end;
    uint32_t spaces_cnt = count(str.begin(), str.end(), ' '), groups_cnt = 0;
    for (uint32_t i = start; i < end; ++i) if (str[i] == ' ' && str[i - 1] != ' ') ++groups_cnt;
    uint32_t spaces_in_group_cnt = spaces_cnt / groups_cnt, to_add_cnt = spaces_cnt % groups_cnt;
    for (uint32_t i = start, group = 0; i < end; ++i) {
        if (str[i] != ' ') cout << str[i];
        else if (str[i - 1] != ' ') {
            for (uint32_t j = 0; j < spaces_in_group_cnt; ++j) cout << ' ';
            if (group + to_add_cnt >= groups_cnt) cout << ' ';
            ++group;
        }
    }
    cout << '\n';
    return 0;
}
