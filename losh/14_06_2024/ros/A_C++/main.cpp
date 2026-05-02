#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const int64_t maxn = 1e5;

struct Way {
    int64_t u, c, g;
};
//struct Vert {
//    int64_t a = 0, b = 0, c = 0;
//};

//int64_t my_sqrt(int64_t val) {
//    if (val < 0) return -1;
//    int64_t l = 0, r = val;
//    while (l != r) {
//        int64_t m = (l + r) / 2 + (l + r) % 2;
//        if (m * m < val) l = m;
//        else if (m * m > val) r = m - 1;
//        else l = r = m;
//    }
//    return l;
//}

//int64_t max_x(int64_t a, int64_t b, int64_t c) {
////    auto [a, b, c] = vert;
//    if (a == 0) return 0;
//    int64_t d = b * b - 4 * a * c;
//    if (d < 0) return 0;
//    return (-b + my_sqrt(d)) / 2 / a;
//}
//
//int64_t max_x(const Vert &vert) {
//    return max_x(vert.a, vert.b, vert.c);
//}

vector<Way> gr[maxn];
int64_t costs[maxn];
int64_t n, m, k;

bool try_x(int64_t x) {
    for (int64_t i = 0; i < n; ++i) costs[i] = -1;
    deque<pair<int64_t, int64_t>> deq;
    deq.emplace_back(0, 0);
    while (!deq.empty()) {
        auto [v, cost] = deq.front();
        deq.pop_front();
        if (cost > k || (costs[v] != -1 && costs[v] < cost) || v == n - 1) continue;
        for (auto [u, c, g]: gr[v]) {
            int64_t ncost = cost + (x > g ? (c * (x - g) * (x - g)) : 0);
            if (ncost <= k && (costs[u] == -1 || costs[u] > ncost)) deq.emplace_back(u, ncost), costs[u] = ncost;
        }
    }
    return costs[n - 1] != -1;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int64_t i = 0, v, u, c, g; i < m; ++i) {
        cin >> v >> u >> c >> g, --v, --u;
        gr[v].emplace_back(u, c, g), gr[u].emplace_back(v, c, g);
    }
    int64_t xl = 0, xr = 1e8;
    while (xl != xr) {
        int64_t mid = (xl + xr) / 2 + (xl + xr) % 2;
        if (try_x(mid)) xl = mid;
        else xr = mid - 1;
    }
    cout << xl << "\n";
    return 0;
}
