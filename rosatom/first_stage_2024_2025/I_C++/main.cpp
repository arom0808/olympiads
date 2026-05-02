#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <vector>

using namespace std;

constexpr int maxn = 5e5;
map<string, int> id_by_str;
string strs[maxn];
vector<pair<int, int> > g[maxn];
vector<int> rg[maxn];
int edge_start[maxn];
vector<int> ans_seq, edge_seq;
int dist[maxn];
map<pair<int, int>, vector<int> > edge_id;

int get_str_id(string str) {
    auto it = id_by_str.find(str);
    if (it == id_by_str.end()) {
        strs[id_by_str.size()].assign(str);
        return id_by_str.emplace(strs[id_by_str.size()], id_by_str.size()).first->second;
    }
    return it->second;
}

int n, k;

void dfs(int v) {
    while (edge_start[v] < g[v].size()) {
        ++edge_start[v];
        dfs(g[v][edge_start[v] - 1].first);
    }
    ans_seq.push_back(v);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
    cin >> n >> k;
    string temp_str, tstr1, tstr2;
    for (int i = 0; i < n - k + 1; ++i) {
        cin >> temp_str;
        tstr1 = temp_str.substr(0, k - 1);
        tstr2 = temp_str.substr(1, k - 1);
        int v = get_str_id(tstr1), u = get_str_id(tstr2);
        g[v].emplace_back(u, i);
        rg[u].push_back(v);
        auto it = edge_id.find(make_pair(v, u));
        if (it != edge_id.end()) it->second.push_back(i);
        else edge_id.emplace(make_pair(v, u), vector<int>{i});
    }
    int start_v = 0, end_v = 0;
    for (int i = 0; i < id_by_str.size(); ++i) {
        if (g[i].size() > rg[i].size()) start_v = i;
        if (g[i].size() < rg[i].size()) end_v = i;
    }
    dfs(start_v);
    reverse(ans_seq.begin(), ans_seq.end());
    for (int i = 0; i + 1 < ans_seq.size(); ++i) {
        auto &eds = edge_id[make_pair(ans_seq[i], ans_seq[i + 1])];
        edge_seq.push_back(eds.back());
        eds.pop_back();
    }
    string ans = strs[ans_seq[0]];
    ans.reserve(n);
    for (int i = 1; i < ans_seq.size(); ++i) ans.push_back(strs[ans_seq[i]][k - 2]);
    cout << ans << "\n";
    for (auto el: edge_seq) cout << el + 1 << " ";
    cout << "\n";
    return 0;
}
