#include <iostream>
#include <cstdint>

using namespace std;

const int32_t maxn = 5e5;
int32_t c[maxn], nc[maxn], p[maxn], np[maxn], ps[maxn], cnt[maxn];
// c - class of equality
// nc - new class of equality
// p - permutation (sorted)
// np - new sorted permutation
// ps - prefix sum
// cnt - count


inline int32_t sub(int32_t a, int32_t b, int32_t m) { return a >= b ? a - b : a + m - b; }

inline int32_t add(int32_t a, int32_t b, int32_t m) { return a + b < m ? a + b : a + b - m; }

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string str;
    cin >> str;
    auto n = static_cast<int32_t>(str.size());
    for (int32_t i = 0; i < n; ++i) ++cnt[c[i] = str[i] - 'a' + 1];
    // c_s - current count equality classes
    int32_t c_s = 27;
    // add a smallest element at the end
    c[n++] = 0, ++cnt[0];
    for (int32_t i = 0; i + 1 < c_s; ++i) ps[i + 1] = ps[i] + cnt[i];
    for (int32_t i = 0; i < n; ++i) p[ps[c[i]]++] = i;
    // l2 - len by that already sorted. l2 = l / 2, where l - len that now processing
    for (int32_t l2 = 1; l2 <= n; l2 *= 2) {
        // sort by i + l2. It works because p has already sorted at the end of prev iteration
        for (int32_t i = 0; i < n; ++i) p[i] = sub(p[i], l2, n);
        ps[0] = 0;
        for (int32_t i = 0; i < c_s; ++i) ps[i + 1] = ps[i] + cnt[i];
        // It's fucking shit, I know. But it works :)
        for (int32_t i = 0; i < n; ++i) np[ps[c[p[i]]]++] = p[i];
        swap(p, np);
        for (int32_t i = 0; i < c_s; ++i) cnt[i] = 0;
        c_s = cnt[0] = 1;
        nc[0] = 0;
        for (int32_t i = 1; i < n; ++i) {
            if (c[p[i - 1]] == c[p[i]] && c[add(p[i - 1], l2, n)] == c[add(p[i], l2, n)])
                ++cnt[nc[p[i]] = c_s - 1];
            else ++cnt[nc[p[i]] = c_s++];
        }
        swap(c, nc);
    }
    for (int32_t i = 1; i < n; ++i) cout << p[i] + 1 << " ";
    cout << "\n";
    return 0;
}
