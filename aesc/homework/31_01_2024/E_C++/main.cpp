#include <iostream>

using namespace std;

const char l5b = (1 << 5) - 1;

inline bool is_alpha(char c) { return (c >> 6) == 1 && (c & l5b) >= 1 && (c & l5b) <= 26; }

int main() {
    uint32_t n;
    cin >> n;
    char c;
    uint32_t arr[26];
    for (auto &val: arr) val = 0;
    for (uint32_t i = 0; i < n + 1; ++i) {
        cin.get(c);
        if (is_alpha(c)) ++arr[(c & l5b) - 1];
    }
    for (auto val : arr) cout << val << " ";
    return 0;
}
