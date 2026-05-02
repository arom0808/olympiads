#include <iostream>

using namespace std;

void sol() {
    int32_t n;
    string s;
    cin >> n >> s;
    if (n == 0) {
        cout << "0\n";
        return;
    }
    if (n < 2) {
        cout << "-1\n";
        return;
    }
    if (s.front() != s.back()) {
        cout << "1\n";
        return;
    }
    if (n < 4) {
        cout << "-1\n";
        return;
    }
    for (int32_t i = 1; i + 2 < n; ++i) {
        if (s[i] != s.front() && s[i + 1] != s.back()) {
            cout << "2\n";
            return;
        }
    }
    cout << "-1\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t t;
    cin >> t;
    while (t--) sol();
    return 0;
}
