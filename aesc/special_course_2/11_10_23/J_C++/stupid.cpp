#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    freopen("test.txt", "r", stdin);
    int32_t n, q;
    cin >> n >> q;
    string str;
    cin >> str;
    for (int32_t i = 0, a, b, c; i < q; ++i) {
        cin >> a >> b >> c, --a;
        if (c) sort(next(str.begin(), a), next(str.begin(), b));
        else sort(next(str.begin(), a), next(str.begin(), b), [](char s1, char s2) { return s1 > s2; });
    }
    cout << str << "\n";
}