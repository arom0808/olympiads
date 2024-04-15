#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <set>
#include <limits>
#include <list>

using namespace std;


int main() {
    uint64_t n, q, w;
    cin >> n >> q >> w;
    vector < list < pair < uint32_t, uint64_t>>> rg(n);
    vector <pair<uint32_t, uint32_t>> rebras(n - 1);
    for (uint64_t i = 0, a, b, c; i + 1 < n; ++i) {
        cin >> a >> b >> c;
        rg[a - 1].emplace_back(b - 1, c);
        rg[b - 1].emplace_back(a - 1, c);
        rebras[i] = {a - 1, b - 1};
    }
    uint32_t last = 0;
    vector <uint32_t> lists;
    lists.reserve(n);
    for (uint32_t i = 0; i < n; ++i) if (rg[i].size() == 1) lists.push_back(i);
    vector <uint32_t> used(n, 0);
    uint32_t t = 1;
    deque<pair < uint32_t, uint64_t>>
    deq;
    for (uint64_t _ = 0, d, e; _ < q; ++_) {
        cin >> d >> e;
        d = (d + last) % (n - 1);
        e = (e + last) % w;
        for (auto &ff: rg[rebras[d].first]) {
            if (ff.first == rebras[d].second) {
                ff.second = e;
                break;
            }
        }
        for (auto &ff: rg[rebras[d].second]) {
            if (ff.first == rebras[d].first) {
                ff.second = e;
                break;
            }
        }
        uint64_t best_res = 0;
        for (int32_t aaaa1 = 0; aaaa1 < lists.size(); ++aaaa1) {
            for (int32_t aaaa2 = aaaa1 + 1; aaaa2 < lists.size(); ++aaaa2) {
                auto f = lists[aaaa1], s = lists[aaaa2];
                if (f == s) continue;
                deq.clear();
                deq.emplace_back(f, 0);
                ++t;
                while (!deq.empty()) {
                    auto [v, price] = deq.front();
                    deq.pop_front();
                    if (used[v] == t) continue;
                    used[v] = t;
                    if (v == s) {
                        if (price > best_res) best_res = price;
                        break;
                    }
                    for (auto &ff: rg[v]) if (used[ff.first] != t) deq.emplace_back(ff.first, price + ff.second);
                }
            }
        }
        last = best_res;
        cout << last << "\n";
    }
    return 0;
}


//template<typename T>
//class SegmentTree {
//private:
//    struct Node {
//        T max;
//    };
//
//    vector<Node> nodes;
//    uint32_t size;
//
//    void
//    init_node(uint32_t node_id, uint32_t left, uint32_t right, const vector<T> &arr) {
//        if (left >= right) nodes[node_id].max = 0;
//        else if (left + 1 == right) nodes[node_id].max = arr[left];
//        else {
//            init_node(node_id * 2, left, (left + right) / 2, arr);
//            init_node(node_id * 2 + 1, (left + right) / 2, right, arr);
//            nodes[node_id].max = std::max(nodes[node_id * 2].max, nodes[node_id * 2 + 1].max);
//        }
//    }
//
//    void _set(uint32_t node_id, uint32_t node_left, uint32_t node_right, uint32_t req_left,
//              uint32_t req_right, T val) {
//        if (node_left >= node_right) return;
//        if (req_right <= node_left || req_left >= node_right) return;
//        if (req_left <= node_left && req_right >= node_right) {
//            nodes[node_id].max = val;
//            return;
//        }
//        _set(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right, val);
//        _set(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right, val);
//        nodes[node_id].max = std::max(nodes[node_id * 2].max, nodes[node_id * 2 + 1].max);
//    }
//
//
//    T _max(uint32_t node_id, uint32_t node_left, uint32_t node_right, uint32_t req_left,
//           uint32_t req_right) {
//        if (node_left >= node_right) return 0;
//        if (req_right <= node_left || req_left >= node_right) return 0;
//        if (req_left <= node_left && req_right >= node_right) return nodes[node_id].max;
//        return std::max(_max(node_id * 2, node_left, (node_left + node_right) / 2, req_left, req_right),
//                        _max(node_id * 2 + 1, (node_left + node_right) / 2, node_right, req_left, req_right));
//    }
//
//
//public:
//    explicit SegmentTree(const vector<T> &arr) : nodes(arr.size() * 4), size(arr.size()) {
//        init_node(1, 0, arr.size(), arr);
//    }
//
//    void set(uint32_t pos, T val) {
//        _set(1, 0, size, pos, pos + 1, val);
//    }
//
//    T max(uint32_t left, uint32_t right) {
//        return _max(1, 0, size, left, right + 1);
//    }
//};
//
//const uint32_t inf = numeric_limits<uint32_t>::max();
//
//uint32_t get_center(const vector<list<pair<uint32_t, uint64_t>>> &g) {
//    deque<uint32_t> to_visit;
//    vector<bool> used(g.size(), false);
//    uint32_t free_cnt = g.size();
//    for (uint32_t i = 0; i < g.size(); ++i) if (g[i].size() == 1) to_visit.push_back(i);
//    while (free_cnt > 1) {
//        auto t = to_visit.front();
//        to_visit.pop_front();
//        if (used[t]) continue;
//        --free_cnt;
//        used[t] = true;
//        for (const auto &[v, c]: g[t]) if (!used[v]) to_visit.push_back(v);
//    }
//    for (uint32_t i = 0; i < g.size(); ++i) if (!used[i]) return i;
//}
//
//struct Vert {
//    uint32_t max_in, max_out;
//    uint32_t parent;
//    vector<uint32_t> childs;
//    vector<uint64_t> child_prices;
//    multiset<uint64_t> child_max_outs;
//    vector<uint64_t> vec_child_max_outs;
//};
//
//void init_vert(const vector<list<pair<uint32_t, uint64_t>>> &rg, vector<Vert> &g,
//               uint32_t id, uint32_t parent) {
//    g[id].parent = parent;
//    if (rg[id].size() == 1) {
//        g[id].max_in = 0;
//        g[id].max_out = 0;
//        return;
//    }
//    vector<pair<uint32_t, uint64_t>> prr;
//    prr.reserve(rg[id].size() - 1);
//    for (auto c: rg[id]) {
//        if (c.first != parent) {
//            init_vert(rg, g, c.first, id);
//            prr.push_back(c);
//        }
//    }
//    sort(prr.begin(), prr.end(), [](const pair<uint32_t, uint64_t> &a, const pair<uint32_t, uint64_t> &b) {
//        return a.first < b.first;
//    });
//    g[id].childs.resize(prr.size());
//    g[id].child_prices.resize(prr.size());
//    for (uint32_t i = 0; i < prr.size(); ++i) {
//        g[id].childs[i] = prr[i].first;
//        g[id].child_prices[i] = prr[i].second;
//    }
//
//}
