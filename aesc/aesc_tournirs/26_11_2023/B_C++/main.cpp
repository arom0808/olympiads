#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

vector<bool> we_temp_v;
vector<vector<bool>> temp_vs;
hash<vector<bool>> hash1;

uint64_t hash2(const vector<vector<bool>> &vec) {
    std::size_t seed = vec.size() * 2;
    for (auto &kk: vec) {
        uint64_t i1 = hash1(kk);
        uint32_t i2 = i1 >> 32, i3 = i1 & ((1ull << 32) - 1);
        seed ^= i2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= i3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

unordered_map<uint64_t, uint32_t> hashes;

void add_new(const vector<vector<bool>> &table, uint32_t x, uint32_t y, uint32_t k) {
    temp_vs.resize(k);
    we_temp_v.resize(k);
    temp_vs[0].resize(k);
    for (uint32_t j = 0; j < k; ++j) {
        we_temp_v[j] = table[x][y + j];
        temp_vs[0][j] = false;
    }
    for (uint32_t i = 1; i < k; ++i) {
        temp_vs[i].resize(k);
        bool inv = we_temp_v[0] != table[x + i][y];
        for (uint32_t j = 0; j < k; ++j) {
            temp_vs[i][j] = (inv != table[x + i][y + j]) != we_temp_v[j];
        }
    }
    auto h = hash2(temp_vs);
    auto it = hashes.find(h);
    if (it != hashes.end()) ++it->second;
    else hashes.emplace(h, 1);
}


int main() {
    uint32_t n, k;
    cin >> n >> k;
    vector<vector<bool>> table(n, vector<bool>(n));
    char c;
    for (auto &l: table) {
        for (_Bit_reference b: l) {
            cin >> c;
            b = c == 'b';
        }
    }
    vector<pair<uint32_t, uint32_t>> eqs;
    eqs.reserve(n * n);
    for (uint32_t i = 0; i + k <= n; ++i)
        for (uint32_t j = 0; j + k <= n; ++j)
            add_new(table, i, j, k);
    uint64_t res = 0;
    vector<uint32_t> cnts;
    cnts.reserve(hashes.size());
    for (auto &cc: hashes) cnts.push_back(cc.second);
    vector<uint32_t> sufsum(cnts.size());
    for (int32_t i = cnts.size() - 1; i >= 0; --i) sufsum[i] = (i + 1 < cnts.size() ? sufsum[i + 1] : 0) + cnts[i];
    for (uint32_t i = 0; i + 1 < cnts.size(); ++i)
        res += static_cast<uint64_t>(cnts[i]) * sufsum[i + 1];
    cout << res;
    return 0;
}



/*
set<vector<vector<bool>>> cache;
    make(nn);
    for (const auto &v: cache) {
        for (const auto &l: v) {
            for (bool m: l) cout << m << " ";
            cout << "\n";
        }
        cout << "\n";
    }
    cout << cache.size();

void make(vector<vector<bool>> &nn) {
    auto it = cache.find(nn);
    if (it != cache.end()) return;
    cache.emplace(nn);
    for (uint32_t i = 0; i < nn.size(); ++i) {
        for (_Bit_reference v: nn[i]) v = !v;
        make(nn);
        for (_Bit_reference v: nn[i]) v = !v;
    }
    for (uint32_t j = 0; j < nn[0].size(); ++j) {
        for (auto &v: nn) v[j] = !v[j];
        make(nn);
        for (auto &v: nn) v[j] = !v[j];
    }
}
*/
//    vector<vector<bool>> nn{{1, 1, 0, 0},
//                            {1, 1, 0, 0},
//                            {1, 0, 1, 0},
//                            {0, 1, 1, 1}};
//    make(nn);
//    for (const auto &v: cache) {
//        for (const auto &l: v) {
//            for (bool m: l) cout << m << " ";
//            cout << "\n";
//        }
//        cout << "\n";
//    }
//    cout << cache.size();

//vector<bool> full_ones;
//
//bool is_eq(const vector<vector<bool>> &table, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t k) {
//    full_ones.resize(k);
//    for (uint32_t j = 0; j < k; ++j)
//        full_ones[j] = table[x1][j + y1] == table[x2][j + y2];
//    for (uint32_t i = 1; i < k; ++i) {
//        uint32_t bad = 0;
//        for (uint32_t j = 0; j < k; ++j)
//            if ((table[x1 + i][y1 + j] == table[x2 + i][y2 + j]) != full_ones[j])
//                ++bad;
//        if (bad != 0 && bad != k) return false;
//    }
//    return true;
//}