#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <algorithm>
#include <random>
#include <map>

using namespace std;

//namespace Test {
//    uint32_t seed = 123143423;
//    mt19937 rng(seed);
//
//
//}

pair<int32_t, int32_t> f_ask() {
    int32_t t, b;
    cin >> t >> b;
    return {t, b};
}

vector<int32_t> cache;

int32_t ask(int32_t p) {
    if (p % 10 == 0) std::fill(cache.begin(), cache.end(), -1);
    if (cache[p] != -1) return cache[p];
    cout << "? " << p + 1 << endl;
    int32_t res;
    cin >> res;
    cache[p] = res;
    return res;
}

void ans(const vector<int32_t> &a) {
    cout << "! ";
    for (auto v: a) cout << v;
    cout << endl;
    char c;
    cin >> c;
    if (c != 'Y') exit(0);
}

pair<vector<int32_t>, bool> gen1(vector<int32_t> v, int32_t p, int32_t r) {
    for (auto &c: v) {
        if (c == 1) c = 0;
        else if (c == 0) c = 1;
    }
    if (v[p] != -1 && v[p] != r) return {vector<int32_t>{}, false};
    v[p] = r;
    return {v, true};
}

pair<vector<int32_t>, bool> gen2(vector<int32_t> v, int32_t p, int32_t r) {
    reverse(v.begin(), v.end());
    if (v[p] != -1 && v[p] != r) return {vector<int32_t>{}, false};
    v[p] = r;
    return {v, true};
}

pair<vector<int32_t>, bool> gen3(vector<int32_t> v, int32_t p, int32_t r) {
    for (auto &c: v) {
        if (c == 1) c = 0;
        else if (c == 0) c = 1;
    }
    reverse(v.begin(), v.end());
    if (v[p] != -1 && v[p] != r) return {vector<int32_t>{}, false};
    v[p] = r;
    return {v, true};
}

pair<vector<int32_t>, bool> gen4(vector<int32_t> v, int32_t p, int32_t r) {
    if (v[p] != -1 && v[p] != r) return {vector<int32_t>{}, false};
    v[p] = r;
    return {v, true};
}

pair<vector<int32_t>, bool> gen(const vector<int32_t> &v, int32_t p, int32_t r, int32_t t) {
    if (t == 1) return gen1(v, p, r);
    if (t == 2) return gen2(v, p, r);
    if (t == 3) return gen3(v, p, r);
    return gen4(v, p, r);
}

void gen_vars(set<vector<int32_t>> &vset1, set<vector<int32_t>> &vset2, int32_t p, int32_t r) {
    vset2.clear();
    for (const auto &v: vset1) {
        if (p % 10 == 0) {
            for (int32_t i = 1; i <= 4; ++i) {
                auto ee = gen(v, p, r, i);
                if (ee.second) vset2.emplace(std::move(ee.first));
            }
        } else {
            auto ee = gen(v, p, r, 4);
            if (ee.second) vset2.emplace(std::move(ee.first));
        }
    }
}

void clean_vars(set<vector<int32_t>> &vset, int32_t b) {
    while (vset.size() >= 2) {
        vector<bool> fv(b, false), tv(b, false);
        for (const auto &v: vset) {
            for (int32_t i = 0; i < b; ++i) {
                if (v[i] == 0) fv[i] = true;
                if (v[i] == 1) tv[i] = true;
            }
        }
        bool deleted = false;
        for (int32_t i = 0; i < b; ++i) {
            if (!fv[i] || !tv[i] || i % 10 == 0) continue;
            deleted = true;
            int32_t r = ask(i);
            while (true) {
                bool del2 = false;
                for (auto it = vset.begin(); it != vset.end(); ++it) {
                    if ((*it)[i] != -1 && (*it)[i] != r) {
                        del2 = true;
                        vset.erase(it);
                        break;
                    }
                }
                if (!del2) break;
            }
            break;
        }
        if (!deleted) return;
    }
}

void play_game(int32_t b) {
    vector<int32_t> ss(b, -1);
    for (int32_t i = 0; i < b; ++i) if (i == 0 || i % 10 != 0) ss[i] = ask(i);
    set<vector<int32_t>> vset1{ss}, vset2;
    while (true) {
        if (vset1.size() == 1 &&
            std::find((*vset1.begin()).begin(), (*vset1.begin()).end(), -1) == vset1.begin()->end())
            break;
        int32_t p = -1;
        for (const auto &v: vset1) {
            for (int32_t i = 0; i < b; ++i) {
                if (v[i] == -1) {
                    p = i;
                    break;
                }
            }
            if (p != -1) break;
        }
        if (p == -1) p = 0;
        int32_t r = ask(p);
        gen_vars(vset1, vset2, p, r);
        clean_vars(vset2, b);
        swap(vset1, vset2);
    }
    ans(*vset1.begin());
}

int main() {
    auto [t, b] = f_ask();
    cache.resize(b);
    for (int32_t i = 0; i < t; ++i) std::fill(cache.begin(), cache.end(), -1), play_game(b);
    return 0;
}
