#include <iostream>
#include <numeric>

using namespace std;
string s;
int n;

struct Fract {
    int a = 0, b = 0;

    Fract() = default;

    Fract(int a, int b): a(a), b(b) {
        simplify();
    }

    void simplify() {
        int g = std::gcd(a, b);
        a /= g, b /= g;
    }

    bool operator<(const Fract &rhs) const {
        return 1ll * a * rhs.b < 1ll * rhs.a * b;
    }
};

void stupid_solve() {
    cin >> s;
    n = s.size();
    Fract ans;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int len = j - i;
            while (i + len < n && s[i + len] == s[i + (len % (j - i))]) ++len;
            Fract cans(len, j - i);
            if (ans.a == 0 || ans < cans) ans = cans;
        }
    }
    cout << ans.a << "/" << ans.b << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
#ifdef TEST
    freopen("input.txt", "r", stdin);
#endif
    stupid_solve();
    return 0;
}
