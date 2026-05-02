#include <iostream>
#include <cstdint>

using namespace std;

int32_t rec() {
    char c;
    cin >> c;
    if (c == '.') return 0;
    if (c >= '0' && c <= '9') return rec() + 1;
    return rec();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cout << rec();
    return 0;
}
