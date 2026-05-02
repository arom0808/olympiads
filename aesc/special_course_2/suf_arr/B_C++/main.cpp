#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>

using namespace std;

const int32_t maxn = 1e5, maxlogn = 18;
int32_t c[maxn], nc[maxn], p[maxn], np[maxn], ps[maxn], cnt[maxn];
int32_t hcs[maxlogn][maxn];
int32_t h_cnt = 0;
vector<int32_t> comp_pows;
int32_t n;

inline int32_t add(int32_t a, int32_t b, int32_t m) { return a + b >= m ? a + b - m : a + b; }

inline int32_t sub(int32_t a, int32_t b, int32_t m) { return a < b ? a + m - b : a - b; }

vector<int32_t> get_comp_pows(int32_t n) {
    vector<int32_t> result;
    for (int32_t i = 0; n > 0; ++i, n >>= 1) if (n & 1) result.push_back(i);
    reverse(result.begin(), result.end());
    return result;
}

bool is_eq_near(int32_t pos) {
    int32_t add_cnt = 0;
    for (int cp: comp_pows) {
        if (hcs[cp][add(p[pos], add_cnt, n)] != hcs[cp][add(p[pos - 1], add_cnt, n)])
            return false;
        add_cnt += 1 << cp;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string s;
    int32_t k;
    cin >> s >> k, --k;
    n = static_cast<int32_t>(s.size());
    int32_t c_s = 126 - 32 + 1;
    for (int32_t i = 0; i < n; ++i) ++cnt[c[i] = static_cast<int32_t>(s[i] - '$')];
    for (int32_t i = 0; i < n; ++i) hcs[h_cnt][i] = c[i];
    ++h_cnt;
    for (int32_t i = 0; i + 1 < c_s; ++i) ps[i + 1] = ps[i] + cnt[i];
    for (int32_t i = 0; i < n; ++i) p[ps[c[i]]++] = i;
    for (int32_t l2 = 1; l2 < n; l2 *= 2) {
        for (int32_t i = 0; i < n; ++i) p[i] = sub(p[i], l2, n);
        ps[0] = 0;
        for (int32_t i = 0; i + 1 < c_s; ++i) ps[i + 1] = ps[i] + cnt[i];
        for (int32_t i = 0; i < n; ++i) np[ps[c[p[i]]]++] = p[i];
        swap(p, np);
        for (int32_t i = 0; i < c_s; ++i) cnt[i] = 0;
        c_s = cnt[nc[p[0]] = 0] = 1;
        for (int32_t i = 1; i < n; ++i) {
            if (c[p[i - 1]] == c[p[i]] && c[add(p[i - 1], l2, n)] == c[add(p[i], l2, n)]) ++cnt[nc[p[i]] = c_s - 1];
            else ++cnt[nc[p[i]] = c_s++];
        }
        swap(c, nc);
        for (int32_t i = 0; i < n; ++i) hcs[h_cnt][i] = c[i];
        ++h_cnt;
    }
    comp_pows = get_comp_pows(n);
    int32_t r = 0, i = 0;
    for (; r < k && i + 1 < n; ++i) {
//        cout << s.substr(p[i]) + s.substr(0, p[i]) << "\n";
//        cout.flush();
        if (!is_eq_near(i + 1)) ++r;
    }
    if (r == k) cout << s.substr(p[i]) + s.substr(0, p[i]) << "\n";
    else cout << "IMPOSSIBLE\n";
    return 0;
}
