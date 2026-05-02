#include <iostream>
#include <vector>

using namespace std;

const int32_t maxn = 200;
int32_t n;
vector<int32_t> g[maxn];
vector<vector<int32_t>> comps;
bool used[maxn];
vector<int32_t> comp_res;
int32_t colors[maxn];

void dfs1(int32_t v) {
    if (used[v]) return;
    comps.back().push_back(v);
    used[v] = true;
    for (auto u: g[v]) dfs1(u);
}

vector<int32_t> deq1, deq2;

void process_comp(int32_t comp_id) {
    const auto &comp = comps[comp_id];
    int32_t best_res = -1;
    for (auto start_id: comp) {
        for (int32_t i = 0; i < n; ++i) used[i] = false;
        int32_t now_color = 0, max_color = 0;
        deq1.clear(), deq2.clear();
        deq1.push_back(start_id);
        while (!deq1.empty()) {
            ++now_color;
            for (auto v: deq1) {
                if (used[v]) continue;
                if (now_color > max_color) max_color = now_color;
                colors[v] = now_color;
                used[v] = true;
                for (auto u: g[v]) deq2.push_back(u);
            }
            deq1.swap(deq2);
            deq2.clear();
        }
        bool ok = true;
        for (auto v: comp) {
            for (auto u: g[v]) {
                if (std::abs(colors[v] - colors[u]) != 1) {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
        }
        if (ok && max_color > best_res) best_res = max_color;
    }
    comp_res[comp_id] = best_res;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    string temp_str;
    for (int32_t i = 0; i < n; ++i) {
        cin >> temp_str;
        for (int32_t j = 0; j < n; ++j) if (temp_str[j] == '1') g[i].push_back(j), g[j].push_back(i);
    }
    for (int32_t i = 0; i < n; ++i) {
        if (used[i]) continue;
        comps.emplace_back();
        dfs1(i);
    }
    comp_res.resize(comps.size(), -1);
    for (int32_t i = 0; i < comps.size(); ++i) process_comp(i);
    int32_t sum = 0;
    for (auto cr: comp_res) {
        if (cr == -1) {
            cout << "-1\n";
            return 0;
        }
        sum += cr;
    }
    cout << sum;
    return 0;
}
