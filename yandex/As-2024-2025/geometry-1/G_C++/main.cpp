#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>

using namespace std;
using ll = long long;
using ld = long double;

constexpr ld eps = 1e-7;
constexpr int maxn = 2000;

struct PV {
    ld x, y;

    PV operator-(const PV &other) const {
        return {x - other.x, y - other.y};
    }

    PV operator+(const PV &other) const {
        return {x + other.x, y + other.y};
    }

    PV operator/(ld koef) const {
        return {x / koef, y / koef};
    }

    ld operator^(const PV &other) const {
        return x * other.y - y * other.x;
    }

    ld sq_len() const {
        return x * x + y * y;
    }

    ld len() const {
        return std::sqrt(sq_len());
    }

    ld sq_dist(const PV &other) const {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
    }

    ld dist(const PV &other) const {
        return std::sqrt(sq_dist(other));
    }
};

struct Line {
    ld a, b, c;

    static Line from_point_and_normal(const PV &point, const PV &normal) {
        Line res;
        res.a = normal.x, res.b = normal.y;
        res.c = -res.a * point.x - res.b * point.y;
        return res;
    }

    static bool parallel(const Line &a, const Line &b) {
        return std::abs(a.a * b.b - b.a * a.b) <= eps;
    }

    static PV cross(Line a, Line b) {
        if (std::abs(a.a) <= eps) swap(a, b);
        ld y = (b.a / a.a * a.c - b.c) / (b.b - b.a / a.a * a.b);
        ld x = (-a.b * y - a.c) / a.a;
        return {x, y};
    }
};

int n;
PV points[maxn];
bool used[maxn];

pair<PV, ld> get_center_and_sq_rad(PV a, PV b, PV c) {
    auto l1 = Line::from_point_and_normal(b + (a - b) / 2, a - b);
    auto l2 = Line::from_point_and_normal(b + (c - b) / 2, c - b);
    PV center = Line::cross(l1, l2);
    ld sq_red = center.sq_dist(a);
    return {center, sq_red};
}

vector<PV> temp_points;

bool process_three_points(int aid, int bid, int cid) {
    PV a = points[aid], b = points[bid], c = points[cid];
    if (std::abs((a - b) ^ (c - b)) <= eps) return false;
    for (int i = 0; i < n; ++i) used[i] = false;
    used[aid] = used[bid] = used[cid] = true;
    auto [center_1, sq_rad_1] = get_center_and_sq_rad(a, b, c);
    int used_cnt = 3;
    for (int i = 0; i < n; ++i) {
        if (used[i] || std::abs(center_1.sq_dist(points[i]) - sq_rad_1) > eps) continue;
        used[i] = true;
        ++used_cnt;
    }
    if (used_cnt == n) {
        cout << used_cnt << " ";
        for (int i = 0; i < n; ++i) cout << i + 1 << " ";
        cout << "\n1 1\n";
        return true;
    }
    if (n - used_cnt < 3) {
        cout << used_cnt << " ";
        for (int i = 0; i < n; ++i) if (used[i]) cout << i + 1 << " ";
        cout << "\n" << n - used_cnt << " ";
        for (int i = 0; i < n; ++i) if (!used[i]) cout << i + 1 << " ";
        cout << "\n";
        return true;
    }
    temp_points.clear();
    for (int i = 0; i < n && temp_points.size() < 3; ++i)
        if (!used[i]) temp_points.push_back(points[i]);
    PV a2 = temp_points[0], b2 = temp_points[1], c2 = temp_points[2];
    if (std::abs((a2 - b2) ^ (c2 - b2)) <= eps) return false;
    auto [center_2, sq_rad_2] = get_center_and_sq_rad(a2, b2, c2);
    for (int i = 0; i < n; ++i) {
        if (!used[i] && std::abs(center_2.sq_dist(points[i]) - sq_rad_2) > eps) return false;
    }
    vector<int> res_ids;
    for (int i = 0; i < n; ++i)
        if (std::abs(center_2.sq_dist(points[i]) - sq_rad_2) <= eps)
            res_ids.push_back(i);
    cout << used_cnt << " ";
    for (int i = 0; i < n; ++i) if (used[i]) cout << i + 1 << " ";
    cout << "\n" << res_ids.size() << " ";
    for (auto id: res_ids) cout << id + 1 << " ";
    cout << "\n";
    return true;
}

void solve() {
    cin >> n;
    if (n == 2) {
        cout << "1 1\n1 2\n";
        return;
    }
    if (n == 3) {
        cout << "2 1 2\n1 3\n";
        return;
    }
    if (n == 4) {
        cout << "2 1 2\n2 3 4\n";
        return;
    }
    for (int i = 0; i < n; ++i) cin >> points[i].x >> points[i].y;
    vector<int> ids(5);
    iota(ids.begin(), ids.end(), 0);
    do {
        if (process_three_points(ids[0], ids[1], ids[2])) return;
    } while (next_permutation(ids.begin(), ids.end()));
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
