#include <iostream>

using namespace std;

int main() {
    int32_t n;
    cin >> n;
    int32_t arr[n];
    for (auto &val: arr) cin >> val;
    int32_t eqs = 0, res = 0;
    for (int32_t i = 0; i + 1 < n; ++i) if (arr[i] == arr[i + 1]) ++eqs;
    bool comps[n - eqs - 1];
    for (int32_t i = 0, j = 0; i + 1 < n; ++i) {
        if (arr[i] < arr[i + 1]) comps[j++] = false;
        else if (arr[i] > arr[i + 1]) comps[j++] = true;
    }
    for (int32_t i = 0; i + 1 < n - eqs - 1; ++i) if (comps[i] == comps[i + 1]) ++res;
    cout << eqs + res;
    return 0;
}
