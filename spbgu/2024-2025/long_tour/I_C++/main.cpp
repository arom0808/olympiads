#ifndef LOCAL
#pragma GCC optimize("Ofast")
#endif

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxcoord = 1e5 + 1;

struct Point {
    int x = 0, y = 0;

    bool operator<(const Point &rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }

    bool operator==(const Point &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    friend istream &operator>>(istream &in, Point &p) {
        return in >> p.x >> p.y;
    }
};

int n;
vector<Point> points_by_x[maxcoord], points_by_y[maxcoord];

void solve() {
    cin >> n;
    Point temp_point;
    for (int i = 0; i < n; ++i) {
        cin >> temp_point;
        points_by_x[temp_point.x].push_back(temp_point);
        points_by_y[temp_point.y].push_back(temp_point);
    }
    for (int i = 0; i < maxcoord; ++i) {
        auto &px = points_by_x[i], &py = points_by_y[i];
        sort(px.begin(), px.end());
        px.erase(unique(px.begin(), px.end()), px.end());
        sort(py.begin(), py.end());
        py.erase(unique(py.begin(), py.end()), py.end());
    }
    long long ans = 0;
    for (int x0 = 0; x0 < maxcoord; ++x0) {
        for (int y0i = 0; y0i < points_by_x[x0].size(); ++y0i) {
            int y0 = points_by_x[x0][y0i].y;
            for (int y1i = y0i + 1; y1i < points_by_x[x0].size(); ++y1i) {
                int y1 = points_by_x[x0][y1i].y;
                for (int x0i = 0, x1i = 0; x0i < points_by_y[y0].size() && x1i < points_by_y[y1].size();) {
                    if (points_by_y[y0][x0i].x == points_by_y[y1][x1i].x)
                        ans = std::max(ans, 1ll * std::abs(points_by_y[y1][x1i].x - x0) * std::abs(y0 - y1));
                    if (points_by_y[y0][x0i].x <= points_by_y[y1][x1i].x) ++x0i;
                    else ++x1i;
                }
            }
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
