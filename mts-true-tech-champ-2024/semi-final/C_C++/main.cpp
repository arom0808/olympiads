#pragma GCC optimize("Ofast")

#include <iostream>

using namespace std;

const int maxn1 = 1e7, maxn2 = 1e7;
bool esf[maxn1], ess[maxn2];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    uint64_t pref;
    cin >> pref;
    esf[0] = esf[1] = true;
    for (int i = 0; i < 7; ++i) pref *= 10;
    for (uint64_t i = 2; i < maxn1; ++i) {
        if (esf[i]) continue;
        for (uint64_t j = i * i; j < maxn1; j += i) esf[j] = true;
        for (uint64_t j = pref ? ((i - (pref % i)) % i) : (i * i); j < maxn2; j += i)
            ess[j] = true;
    }
    for (int i = 0; i < 7; ++i) pref /= 10;
    uint64_t a_ans = 0, b_ans = 0;
    for (uint64_t i = 0; i < maxn2; ++i) {
        if (pref ? ess[i] : esf[i]) continue;
        ++a_ans;
        bool ok = false;
        auto j = i;
        for (int k = 0; k < 4 && !ok; ++k) {
            if (j % (10000) == pref) ok = true;
            else j /= 10;
        }
        if (ok) ++b_ans;
    }
    cout << a_ans << " " << b_ans << "\n";
    return 0;
}
