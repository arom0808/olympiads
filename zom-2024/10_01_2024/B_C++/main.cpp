#pragma GCC optimize("Ofast")
#pragma GCC optimize(O3)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int32_t n;
    cin >> n;
    vector<int32_t> frl(n);
    for (auto &f: frl) cin >> f;
    auto d_frl = frl;
    d_frl.resize(frl.size() * 2);
    copy(frl.begin(), frl.end(), next(d_frl.begin(), frl.size()));
    vector<int32_t> right_sec(d_frl.size());
    for (int32_t i = 0; i < d_frl.size(); ++i) {
        int32_t j = i, vv = 0;
        for (; j < d_frl.size(); ++j) {
            if (d_frl[j] & vv) break;
            vv |= d_frl[j];
        }
        right_sec[i] = j - 1;
    }
    int32_t best_size = 1e9, now_size;
    vector<int32_t> best_res, now_res;
    for (int32_t g_s = n - 1, g_e = g_s + n - 1; g_s >= 0 && n - g_s < 40;) {
        now_size = 0;
        now_res.resize(0);
        now_res.reserve(best_res.size());
        int32_t pre_r = 0, n_r = g_s - 1;
        while (n_r < g_e) {
            int32_t br = -1, bi = -1;
            for (int32_t i = pre_r; i <= n_r + 1; ++i) if (right_sec[i] > br) br = right_sec[i], bi = i;
            pre_r = n_r + 1, n_r = br;
            now_res.push_back(bi);
            ++now_size;
        }
        for (int32_t nstart = g_s - 1; nstart >= now_res.front(); --nstart) {
            while (now_size > 1 && right_sec[now_res[now_size - 2]] >= nstart + n - 1) {
                now_res.pop_back();
                --now_size;
            }
        }
        g_s = now_res.front() - 1, g_e = g_s + n - 1;
        if (now_size < best_size) {
            swap(best_size, now_size);
            swap(best_res, now_res);
        }
    }
    cout << best_size << " " << best_res[0] + 1 << "\n";
    for (uint32_t i = 1; i < best_res.size(); ++i) cout << best_res[i] - best_res[i - 1] << " ";
    cout << n - (best_res.back() - best_res.front());
    return 0;
}
