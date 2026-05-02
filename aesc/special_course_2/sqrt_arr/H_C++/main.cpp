#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

struct Que {
    int64_t id, l, r;
};

const int64_t maxn = 2e5, sqrt_c = 500, maxnum = 1e6 + 1;
int64_t nums[maxn], cnts[maxnum], ans[maxn];
vector<Que> ques;
int64_t n, t;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> t;
    for (int64_t i = 0; i < n; ++i) cin >> nums[i];
    ques.resize(t);
    for (int64_t i = 0; i < t; ++i) {
        ques[i].id = i;
        cin >> ques[i].l >> ques[i].r, --ques[i].l;
    }
    sort(ques.begin(), ques.end(), [](const Que &a, const Que &b) {
        if (a.l / sqrt_c != b.l / sqrt_c) return a.l < b.l;
        return a.r < b.r;
    });
    int64_t nl = 0, nr = 0;
    int64_t now_sum = 0;
    for (auto [id, l, r]: ques) {
        while (nr < r) {
            now_sum -= cnts[nums[nr]] * cnts[nums[nr]] * nums[nr];
            ++cnts[nums[nr]];
            now_sum += cnts[nums[nr]] * cnts[nums[nr]] * nums[nr];
            ++nr;
        }
        while (l < nl) {
            --nl;
            now_sum -= cnts[nums[nl]] * cnts[nums[nl]] * nums[nl];
            ++cnts[nums[nl]];
            now_sum += cnts[nums[nl]] * cnts[nums[nl]] * nums[nl];
        }
        while (r < nr) {
            --nr;
            now_sum -= cnts[nums[nr]] * cnts[nums[nr]] * nums[nr];
            --cnts[nums[nr]];
            now_sum += cnts[nums[nr]] * cnts[nums[nr]] * nums[nr];
        }
        while (nl < l) {
            now_sum -= cnts[nums[nl]] * cnts[nums[nl]] * nums[nl];
            --cnts[nums[nl]];
            now_sum += cnts[nums[nl]] * cnts[nums[nl]] * nums[nl];
            ++nl;
        }
        ans[id] = now_sum;
    }
    for (int64_t i = 0; i < t; ++i) cout << ans[i] << "\n";
    return 0;
}
