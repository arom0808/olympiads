#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string str;
    std::getline(cin, str);
    uint32_t start = 0, end = str.size();
    while (str[start] == ' ') ++start;
    while (end > 0 && str[end - 1] == ' ') --end;
    for (uint32_t i = start; i < end; ++i) if (str[i] != ' ' || str[i - 1] != ' ') cout << str[i];
    cout << "\n";
    return 0;
}
