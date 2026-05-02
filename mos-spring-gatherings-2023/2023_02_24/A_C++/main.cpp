#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using ld = long double;

struct PV {
    ll x, y;
};

struct PVd {
    ld x, y;
};

struct Line {
    ll a, b, c;

    Line() = default;

    Line(PV f, PV s) {
        a = s.y - f.y;
        b = f.x - s.x;
        c = s.x * f.y - f.x * s.y;
    }
};

bool is_parallel(const Line &f, const Line &s) {
    return f.a * s.b == f.b * s.a;
}

PVd cross(const Line &f, const Line &s) {
    ld x = static_cast<ld>(f.b * s.c - s.b * f.c) / (f.a * s.b - s.a * f.b);
    ld y = static_cast<ld>(f.c * s.a - s.c * f.a) / (f.a * s.b - s.a * f.b);
    return {x, y};
}

void solve() {
    int n;
    cin >> n;
    vector<Line> lines;
    bool any_ex = false;
    ld minx = 0, maxx = 0, miny = 0, maxy = 0;
    cout << fixed << setprecision(20);
    for (int i = 0; i < n; ++i) {
        char c;
        ll x1, y1, x2, y2;
        cin >> c >> x1 >> y1 >> x2 >> y2;
        if (c == '+') {
            Line cur_line(PV(x1, y1), PV(x2, y2));
            for (auto pre_line: lines) {
                if (is_parallel(pre_line, cur_line)) continue;
                auto cur_point = cross(pre_line, cur_line);
                if (!any_ex) {
                    minx = maxx = cur_point.x;
                    miny = maxy = cur_point.y;
                    any_ex = true;
                } else {
                    minx = std::min(minx, cur_point.x);
                    maxx = std::max(maxx, cur_point.x);
                    miny = std::min(miny, cur_point.y);
                    maxy = std::max(maxy, cur_point.y);
                }
            }
            lines.push_back(cur_line);
        } else {
            cout << (maxx - minx) * (maxy - miny) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#elifdef TEST
    freopen("input.txt","r",stdin);
#endif
    solve();
    return 0;
}
