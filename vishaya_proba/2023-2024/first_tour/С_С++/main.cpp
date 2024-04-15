#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>

using ull = unsigned long long;
using uint32_t = unsigned int;
using std::vector;
using std::cin;
using std::cout;
using std::map;
using std::set;
using std::swap;
using std::unordered_set;

const uint32_t inf = 1e9;
const ull mod = 1e9 + 7;

struct El {
    uint32_t p = inf, l = 0;
    std::unordered_set<uint32_t> pmn;
};

void make_tree(vector<El> &tree, uint32_t v, vector<map<uint32_t, uint32_t>> &rebs1,
               vector<map<uint32_t, uint32_t>> &rebs2, const vector<uint32_t> &re) {
    map<uint32_t, uint32_t> visit1(std::move(rebs1[v])), visit2(std::move(rebs2[v]));
    auto process = [&](uint32_t son, uint32_t c) {
        rebs1[son].erase(v);
        rebs2[son].erase(v);
        tree[son].p = v;
        tree[son].l = tree[v].l + 1;
        auto &mns = tree[son].pmn;
        while (c > 1) {
            auto d = re[c];
            auto itm = mns.find(d);
            if (itm == mns.end()) mns.insert(d);
            else mns.erase(itm);
            c /= d;
        }
        make_tree(tree, son, rebs1, rebs2, re);
    };
    for (auto &[son, c]: visit1) process(son, c);
    for (auto &[son, c]: visit2) process(son, c);
}

void add_mns(unordered_set<uint32_t> &a, const unordered_set<uint32_t> &ta) {
    for (auto &v: ta) {
        auto it = a.find(v);
        if (it == a.end()) a.insert(v);
        else a.erase(v);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<uint32_t> re(1000001, 0), primes;
    primes.reserve(78500);
    for (uint32_t i = 2; i < re.size(); ++i) {
        if (re[i] == 0) {
            re[i] = i;
            primes.push_back(i);
        }
        for (uint32_t j = 0; j < re.size() && primes[j] <= re[i] && i * primes[j] < re.size(); ++j)
            re[i * primes[j]] = primes[j];
    }
    uint32_t n;
    cin >> n;
    vector<map<uint32_t, uint32_t>> rebs1(n), rebs2(n);
    for (uint32_t i = 0, a, b, c; i + 1 < n; ++i) {
        cin >> a >> b >> c;
        --a;
        --b;
        rebs1[a].emplace(b, c);
        rebs1[b].emplace(a, c);
    }
    vector<El> tree(n);
    make_tree(tree, 0, rebs1, rebs2, re);
    uint32_t q;
    cin >> q;
    unordered_set<uint32_t> now;
    for (uint32_t i, u, v; i < q; ++i) {
        cin >> u >> v;
        --u;
        --v;
        if (tree[u].l < tree[v].l) swap(u, v);
        now.clear();
        while (tree[u].l > tree[v].l) {
            add_mns(now, tree[u].pmn);
            u = tree[u].p;
        }
        while (u != v) {
            add_mns(now, tree[u].pmn);
            add_mns(now, tree[v].pmn);
            u = tree[u].p;
            v = tree[v].p;
        }
        ull res = 1;
        for (auto val: now) res = (res * val) % mod;
        cout << res << "\n";
    }
    return 0;
}
