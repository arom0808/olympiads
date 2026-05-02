#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int32_t maxn = 1e6;
int32_t vals[maxn];
int32_t dif_cnts[maxn];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    for (int32_t i = 0; i < n; ++i) cin >> vals[i];
    int32_t ok_difs_cnt = 0;
    set<int32_t> need_difs;
    for (int32_t i = 0; i + 1 < n; ++i) {
        auto dif = std::abs(vals[i] - vals[i + 1]);
        if (dif >= 1 && dif <= n - 1) {
            if ((++dif_cnts[dif]) == 1) ++ok_difs_cnt;
            else --ok_difs_cnt;
        } else ++dif_cnts[dif];
    }
    for (int32_t i = 1; i < n; ++i) if (dif_cnts[i] == 0) need_difs.insert(i);
    vector<pair<int32_t, int32_t>> changes;
    for (int32_t i = 0; i < n; ++i) {
        if (i > 0) {
            auto dif = std::abs(vals[i] - vals[i - 1]);
            --dif_cnts[dif];
            if (dif_cnts[dif] == 0 && dif >= 1 && dif <= n - 1) need_difs.insert(dif);
        }
        if (i + 1 < n) {
            auto dif = std::abs(vals[i] - vals[i + 1]);
            --dif_cnts[dif];
            if (dif_cnts[dif] == 0 && dif >= 1 && dif <= n - 1) need_difs.insert(dif);
        }
        if (i == 0 && need_difs.size() == 1) {
            changes.emplace_back(i, vals[i + 1] - *need_difs.begin());
            changes.emplace_back(i, vals[i + 1] + *need_difs.begin());
        } else if (i == n - 1 && need_difs.size() == 1) {
            changes.emplace_back(i, vals[i - 1] - *need_difs.begin());
            changes.emplace_back(i, vals[i - 1] + *need_difs.begin());
        } else if (i > 0 && i + 1 < n && need_difs.size() <= 2) {
            int32_t l = *need_difs.begin(), r = *need_difs.rbegin();
            for (int32_t _ = 0; _ < need_difs.size(); ++_, swap(l, r)) {
                if (vals[i - 1] + l == vals[i + 1] + r) changes.emplace_back(i, vals[i - 1] + l);
                if (vals[i - 1] + l == vals[i + 1] - r) changes.emplace_back(i, vals[i - 1] + l);
                if (vals[i - 1] - l == vals[i + 1] + r) changes.emplace_back(i, vals[i - 1] - l);
                if (vals[i - 1] - l == vals[i + 1] - r) changes.emplace_back(i, vals[i - 1] - l);
            }
        }
        if (i > 0) {
            auto dif = std::abs(vals[i] - vals[i - 1]);
            ++dif_cnts[dif];
            if (dif_cnts[dif] == 1 && dif >= 1 && dif <= n - 1) need_difs.erase(dif);
        }
        if (i + 1 < n) {
            auto dif = std::abs(vals[i] - vals[i + 1]);
            ++dif_cnts[dif];
            if (dif_cnts[dif] == 1 && dif >= 1 && dif <= n - 1) need_difs.erase(dif);
        }
    }
    sort(changes.begin(), changes.end(), [](const pair<int32_t, int32_t> &a, const pair<int32_t, int32_t> &b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });
    changes.erase(unique(changes.begin(), changes.end()), changes.end());
    int32_t cnt = 0;
    for (auto [i, x]: changes) {
        if (vals[i] != x) ++cnt;
    }
    cout << cnt << "\n";
    for (auto [i, x]: changes) {
        if (vals[i] != x) cout << i + 1 << " " << x << "\n";
    }
    return 0;
}
