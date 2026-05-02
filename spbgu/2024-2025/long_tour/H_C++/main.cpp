#include <iostream>

using namespace std;

int get_sum(const string &s) {
    int res = 0;
    for (auto c: s) if (c >= '0' && c <= '9') res += c - '0';
    return res;
}

void solve_arthur() {
    int n;
    string s;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        s[get_sum(s) % 10] = '?';
        cout << s << "\n";
    }
}

void solve_hercule() {
    int n;
    string s;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        int mv = s.find('?');
        int ps = get_sum(s);
        cout << ps + (mv - ps % 10 + 10) % 10 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    string s;
    cin >> s;
    if (s == "Arthur") solve_arthur();
    else solve_hercule();
    return 0;
}
