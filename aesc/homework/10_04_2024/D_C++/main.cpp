#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string str;
    std::getline(cin, str);
    uint32_t line_size = stoi(str);
    std::getline(cin, str);
    uint32_t now_start = 0, now_end = 0;
    while (now_start < str.size()) {
        for (now_end = now_start + line_size; now_end < str.size() && str[now_end] != ' '; --now_end) {}
        for (; now_start < now_end && now_start < str.size(); ++now_start) cout << str[now_start];
        cout << '\n';
        ++now_start;
    }
    return 0;
}
