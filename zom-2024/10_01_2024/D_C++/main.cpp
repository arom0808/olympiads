#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Point {
    int32_t x, y;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int32_t w, h, n;
    cin >> w >> h >> n;
    vector<int32_t> ys;
    ys.reserve(n);
    vector<Point> points(n);
    for (int32_t i = 0; i < n; ++i) {
        auto &p = points[i];
        cin >> p.x >> p.y;
        ys.push_back(p.y);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    auto cmp = [](const pair<bool, int32_t> &a, const pair<bool, int32_t> &b) {
        return (!a.first && b.first) || (a.second < b.second && !(a.first && !b.first));
    };
    vector<set<pair<bool, int32_t>, decltype(cmp)>> acts(ys.size());
    for (int32_t i = 0; i + 1 < n; ++i) {
        if (points[i].y == points[i + 1].y) continue;
        auto mi = min(points[i].y, points[i + 1].y), ma = max(points[i].y, points[i + 1].y);
        acts[distance(ys.begin(), lower_bound(ys.begin(), ys.end(), mi))].emplace(true, i);
        acts[distance(ys.begin(), lower_bound(ys.begin(), ys.end(), ma))].emplace(false, i);
    }
    auto sec_cmp = [](const pair<Point, Point> &ai, const pair<Point, Point> &bi) {
        auto mi = max(min(ai.first.y, ai.second.y), min(bi.first.y, bi.second.y));
        auto ma = min(max(ai.first.y, ai.second.y), max(bi.first.y, bi.second.y));
        auto mid = static_cast<long double>(mi + ma) / 2;
        auto x1 = ai.first.x + (ai.second.x - ai.first.x) * (mid - ai.first.y) / (ai.second.y - ai.first.y);
        auto x2 = bi.first.x + (bi.second.x - bi.first.x) * (mid - bi.first.y) / (bi.second.y - bi.first.y);
        return x1 < x2;
    };
    set<pair<Point, Point>, decltype(sec_cmp)> secs;
    long double res = 0;
    for (int32_t ify = 0; ify + 1 < ys.size(); ++ify) {
        for (auto [type, s_id]: acts[ify]) {
            if (type) secs.emplace(points[s_id], points[s_id + 1]);
            else secs.erase({points[s_id], points[s_id + 1]});
        }
        if (secs.size() % 2 == 0) continue;
        auto fy = ys[ify], sy = ys[ify + 1];
        auto [x0, y0] = secs.rbegin()->first;
        auto [x1, y1] = secs.rbegin()->second;
        if (y0 > y1) swap(x0, x1), swap(y0, y1);
        auto fsx = static_cast<long double>(fy + sy - y0 * 2) / (y1 - y0) * (x1 - x0) + x0 * 2;
        res += (w * 2 - fsx) / 2 * (sy - fy);
    }
    cout << fixed << setprecision(15) << res;
    return 0;
}
