#include <iostream>
#include <cstdint>

using namespace std;

struct Snowman {
    int32_t mass = 0, pre_add_id, add_cnt = 0;

    Snowman() : pre_add_id(-1) {}
};

const int32_t maxn = 2e5 + 2;

Snowman snowmen[maxn];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    freopen("snowmen.in", "r", stdin);
    freopen("snowmen.out", "w", stdout);
    int32_t n;
    cin >> n;
    uint64_t ans = 0;
    for (int32_t i = 1, t, m; i <= n; ++i) {
        cin >> t >> m;
        snowmen[i] = snowmen[t];
        auto &[mass, pre_add_id, add_cnt] = snowmen[i];
        if (m == 0) {
            if (add_cnt > 0) mass -= add_cnt;
            else mass -= snowmen[pre_add_id].add_cnt, pre_add_id = snowmen[pre_add_id].pre_add_id;
            add_cnt = 0;
        } else {
            mass += m;
            if (add_cnt > 0) pre_add_id = t;
            add_cnt = m;
        }
        ans += mass;
    }
    cout << ans << "\n";
    return 0;
}
