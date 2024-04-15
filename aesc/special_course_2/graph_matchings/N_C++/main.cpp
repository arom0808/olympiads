#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <map>

using namespace std;

bool dfs(const vector<set<int32_t>> &g, vector<int32_t> &rm, vector<int32_t> &used, int32_t timer, int32_t v) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (auto u: g[v]) {
        if (rm[u] == -1) {
            rm[u] = v;
            return true;
        }
    }
    for (auto u: g[v]) {
        if (dfs(g, rm, used, timer, rm[u])) {
            rm[u] = v;
            return true;
        }
    }
    return false;
}

void rec_add(vector<string> &reducts, map<string, int32_t> &map_reducts, vector<set<int32_t>> &g, const string &raw_str,
             string &now_str, int32_t li, int32_t start, int32_t pos, int32_t level) {
    if (level == 0) {
        auto it = map_reducts.find(now_str);
        if (it == map_reducts.end()) {
            it = map_reducts.emplace(now_str, reducts.size()).first;
            reducts.push_back(now_str);
        }
        g[li].insert(it->second);
        return;
    }
    for (int32_t i = start; i < raw_str.size(); ++i) {
        now_str[pos] = raw_str[i];
        rec_add(reducts, map_reducts, g, raw_str, now_str, li, i + 1, pos + 1, level - 1);
    }
}

int main() {
    ifstream in("input.txt");
    int32_t n;
    in >> n;
    vector<string> reducts;
    reducts.reserve(2222000);
    map<string, int32_t> map_reducts;
    vector<set<int32_t>> g(n);
    string temp_1, temp_2;
    for (int32_t i = 0; i < n; ++i) {
        in >> temp_1;
        temp_2.resize(1);
        rec_add(reducts, map_reducts, g, temp_1, temp_2, i, 0, 0, 1);
        temp_2.resize(2);
        rec_add(reducts, map_reducts, g, temp_1, temp_2, i, 0, 0, 2);
        temp_2.resize(3);
        rec_add(reducts, map_reducts, g, temp_1, temp_2, i, 0, 0, 3);
        temp_2.resize(4);
        rec_add(reducts, map_reducts, g, temp_1, temp_2, i, 0, 0, 4);
    }
    vector<int32_t> rm(reducts.size(), -1), used(n, -1);
    int32_t timer = 0, ans = 0;
    for (int32_t v = 0; v < n; ++v) {
        if (dfs(g, rm, used, timer, v)) {
            ++ans;
            ++timer;
        }
    }
    ofstream out("output.txt");
    if (ans < n) {
        out << "-1";
        return 0;
    }
    vector<string> res(n);
    for (int32_t u = 0; u < reducts.size(); ++u)
        if (rm[u] >= 0)
            res[rm[u]] = reducts[u];
    for (const auto &r: res) out << r << "\n";
    return 0;
}
