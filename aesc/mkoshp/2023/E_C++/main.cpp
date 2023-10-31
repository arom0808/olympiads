//#define _CRT_SECURE_NO_WARNINGS

#pragma GCC optimize("Ofast")
#pragma GCC optimize(O3)
#pragma comment(linker, "/stack:200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <cassert>
#include <ctime>
#include <chrono>
#include <random>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>
#include <set>
#include <map>
#include <list>
#include <unordered_set>
#include <unordered_map>


using ld = long double;
using ll = long long;
using ull = unsigned long long;

#define double long double
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define repr(i, n) for (int i = (n) - 1; i >= 0; --i)
#define fir first
#define sec second
#define pb push_back
#define mp make_pair

ll INF = 1e18;
ll MOD = 1e9 + 1000 - 7;
ll p = 101;
ld eps = 1e-8;

const ll pw = 1e12;

using namespace std;

ll powmod(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    assert(b >= 0);
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

/*struct Str {
    bool type;
    std::string str;
};*/

void solve() {
    uint32_t n, t;
    cin >> n >> t;
    vector<unordered_map<uint32_t, unordered_set<uint32_t>>> ways(t);
    for (uint32_t i = 0, m, l, r; i < t; ++i) {
        cin >> m;
        for (uint32_t j = 0; j < m; ++j) {
            cin >> l >> r;
            --l;
            --r;
            auto it1 = ways[i].find(l);
            if (it1 != ways[i].end()) it1->second.insert(r);
            else ways[i].emplace(l, unordered_set<uint32_t>{r});
            auto it2 = ways[i].find(r);
            if (it2 != ways[i].end()) it2->second.insert(l);
            else ways[i].emplace(r, unordered_set<uint32_t>{l});
        }
    }
    uint32_t k;
    cin >> k;
    vector<bool> visited(n, false), new_visited(n, false);
    visited[0] = new_visited[0] = true;
    for (uint32_t j = 0, a; j < k; ++j) {
        cin >> a;
        --a;
        
        for (auto it = ways[a].begin(); it != ways[a].end();) {
            if (visited[it->first]) {
                new_visited[it->second] = true;
                if (next(it) != ways[a].end() && it->first == next(it)->second && it->second == next(it)->first)
                    ways[a].erase(next(it));
                if (it != ways[a].begin() && it->first == prev(it)->second && it->second == prev(it)->first)
                    ways[a].erase(prev(it));
                ways[a].erase(prev(++it));
            } else ++it;
        }
        visited = new_visited;
        if (visited[n - 1]) {
            cout << j + 1;
            return;
        }
    }
    cout << "-1";
}

int main() {
//#ifdef _DEBUG
//    freopen("input.txt", "r", stdin);
//#endif // _DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(52);
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}

/*uint32_t n, m;
cin >> n >> m;
vector<int32_t> h(n), a(n), b(n), w(m), t(m), d(m);
for (uint32_t i = 0; i < n; ++i) cin >> h[i] >> a[i] >> b[i];
for (uint32_t i = 0; i < m; ++i) cin >> w[i] >> t[i] >> d[i];
*/
/*uint32_t n, m;
cin >> n >> m;
list<vector<uint32_t>> nums(m, vector<uint32_t>(n));
set<uint32_t> nums_set;
for (auto&line:nums) { for (uint32_t j = 0; j < n; ++j) { cin >> line[j]; nums_set.insert(line[j]); } }
std::vector<std::uint32_t> results(n);
for (uint32_t i = 0; i < n; ++i) {
    uint32_t max_res = 0, res_j = 0;
    for (const auto& line : nums) nums_set.erase(line[i]);
    uint32_t j = 0;
    for (auto it = nums.begin(); it != nums.end(); ++it, ++j) {
        for (const uint32_t& in_line_num : (*it)) nums_set.erase(in_line_num);
        if (nums_set.empty() || (*it)[i] > *nums_set.rbegin()) {
            if ((*it)[i] > max_res) {
                max_res = (*it)[i];
                res_j = j;
            }
        }
        for (const uint32_t& in_line_num : (*it)) nums_set.insert(in_line_num);
        nums_set.erase((*it)[i]);
    }
    if (max_res == 0) {
        j = 0;
        for (auto it = nums.begin(); it != nums.end(); ++it, ++j) {
            if ((*it)[i] > max_res) {
                max_res = (*it)[i];
                res_j = j;
            }
        }
    }
    auto it = std::next(nums.begin(), res_j);
    for (const uint32_t& in_line_num : (*it)) nums_set.erase(in_line_num);
    nums.erase(it);
    for (const auto& line : nums) nums_set.insert(line[i]);
    results[i] = max_res;
}
cout << distance(results.begin(), max_element(results.begin(), results.end())) + 1;*/