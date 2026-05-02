#include <iostream>
#include <vector>
//#include <random>
//#include <set>

using namespace std;

struct AllQue {
    int32_t type;
    string str;
    int32_t val;
};

const int32_t maxS = 1000002, k = 26;
namespace FullSol {
    template<typename T>
    class SegmentTree {
    public:
        struct Node {
            T max_val = 0, change = 0;
        };

        int32_t size;
        vector<Node> tree;

        void _init(int32_t id, int32_t l, int32_t r) {
            if (l >= r) return;
            if (r - l == 1) tree[id].max_val = 1;
            else {
                _init(id * 2, l, (l + r) / 2);
                _init(id * 2 + 1, (l + r) / 2, r);
                tree[id].max_val = max(tree[id * 2].max_val, tree[id * 2 + 1].max_val);
            }
        }

        void transfer_changes(int32_t id) {
            if (tree[id].change == 0) return;
            if (id * 2 + 1 < static_cast<int32_t>(tree.size())) {
                auto c = tree[id].change;
                auto &l = tree[id * 2], &r = tree[id * 2 + 1];
                l.max_val += c, l.change += c, r.max_val += c, r.change += c;
            }
            tree[id].change = 0;
        }

        T _max_val(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b) {
            if (l >= r || b <= l || r <= a) return 0;
            transfer_changes(id);
            if (a <= l && b >= r) return tree[id].max_val;
            return max(_max_val(id * 2, l, (l + r) / 2, a, b), _max_val(id * 2 + 1, (l + r) / 2, r, a, b));
        }

        void _add(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b, T val) {
            if (l >= r || b <= l || r <= a) return;
            transfer_changes(id);
            if (a <= l && b >= r) tree[id].max_val += val, tree[id].change += val;
            else {
                _add(id * 2, l, (l + r) / 2, a, b, val);
                _add(id * 2 + 1, (l + r) / 2, r, a, b, val);
                tree[id].max_val = max(tree[id * 2].max_val, tree[id * 2 + 1].max_val);
            }
        }

        explicit SegmentTree(int32_t size) : size(size), tree(size * 4) {
            _init(1, 0, size);
        }

        T max_val(int32_t a, int32_t b) {
            return _max_val(1, 0, size, a, b);
        }

        void add(int32_t a, int32_t b, T val) {
            _add(1, 0, size, a, b, val);
        }
    };

    struct Node {
        int32_t go[k]{};
        int32_t real_child_cnt[k]{};
        int32_t near_twice = -1, in_c = 0, p = -1;
        bool can_term = false, term = false;

        explicit Node() {
            for (auto &i: go) i = -1;
        }
    };

    struct Que {
        int32_t type, s_id;
    };


    vector<Node> bor(maxS);
    int32_t bor_size = 1, root = 0;
    int32_t q;
    vector<Que> ques;
    vector<int32_t> que_ids;
    vector<int32_t> tin(maxS), tout(maxS);
    int32_t timer = 0;
    SegmentTree<int32_t> st(maxS);

    int32_t add_str(const string &str) {
        int32_t v = root;
        for (auto c: str) {
            if (bor[v].go[c - 'a'] != -1) v = bor[v].go[c - 'a'];
            else v = bor[v].go[c - 'a'] = bor_size++;
        }
        bor[v].can_term = true;
        return v;
    }

    void dfs(int32_t v, int32_t near_twice = -1, int32_t in_c = 0, int32_t p = -1) {
        tin[v] = timer++;
        bor[v].near_twice = near_twice, bor[v].in_c = in_c, bor[v].p = p;
        int32_t c_cnt = 0;
        for (auto u: bor[v].go) if (u != -1) ++c_cnt;
        for (int32_t i = 0; i < k; ++i)
            if (bor[v].go[i] != -1)
                dfs(bor[v].go[i], c_cnt > 1 || bor[v].can_term ? v : near_twice,
                    c_cnt > 1 || bor[v].can_term ? i : in_c, v);
        tout[v] = timer;
    }

//
    bool v_state(int32_t v) {
        int32_t c_cnt = 0;
        for (auto r_cnt: bor[v].real_child_cnt) if (r_cnt > 0) ++c_cnt;
        return c_cnt >= 2 || bor[v].term;
    }

    vector<pair<int32_t, int32_t>> temp_reverse_vec;

    void activate(int32_t _v) {
        temp_reverse_vec.clear();
        for (int32_t v = _v, to_c = 0; v != -1; to_c = bor[v].in_c, v = bor[v].near_twice)
            temp_reverse_vec.emplace_back(v, to_c);
        for (int32_t i = temp_reverse_vec.size() - 1; i >= 0; --i) {
            auto [v, to_c] = temp_reverse_vec[i];
            bool s_state = v_state(v);
            if (v == _v) bor[v].term = true;
            else ++bor[v].real_child_cnt[to_c];
            if (s_state == v_state(v)) continue;
            if (bor[v].p == -1 || v_state(bor[v].p)) {
                for (auto u: bor[v].go)
                    if (u != -1 && !v_state(u))
                        st.add(tin[u] + 1, tout[u], 1);
            } else {
                for (auto u: bor[v].go) {
                    if (u == -1) continue;
                    st.add(tin[u], tout[u], 1);
                    if (!v_state(u)) st.add(tin[u] + 1, tout[u], 1);
                }
            }
        }
    }


    void deactivate(int32_t _v) {
//        temp_reverse_vec.clear();
//        for (int32_t v = _v, to_c = 0; v != -1; to_c = bor[v].in_c, v = bor[v].near_twice)
//            temp_reverse_vec.emplace_back(v, to_c);
//        for (int32_t i = temp_reverse_vec.size() - 1; i >= 0; --i) {
//            auto [v, to_c] = temp_reverse_vec[i];
        for (int32_t v = _v, to_c = 0; v != -1; to_c = bor[v].in_c, v = bor[v].near_twice) {
            bool s_state = v_state(v);
            if (v == _v) bor[v].term = false;
            else --bor[v].real_child_cnt[to_c];
            if (s_state == v_state(v)) continue;
            if (bor[v].p == -1 || v_state(bor[v].p)) {
                for (auto u: bor[v].go)
                    if (u != -1 && !v_state(u))
                        st.add(tin[u] + 1, tout[u], -1);
            } else {
                for (auto u: bor[v].go) {
                    if (u == -1) continue;
                    st.add(tin[u], tout[u], -1);
                    if (!v_state(u)) st.add(tin[u] + 1, tout[u], -1);
                }
            }
        }
    }

    vector<int32_t> all_results;

    void init_and_ans(const vector<AllQue> &aq) {
        all_results.clear();
        bor.clear();
        bor.resize(maxS);
        bor_size = 1, root = 0;
        q = aq.size();
        ques.clear();
        que_ids.clear();
        tin.resize(maxS), tout.resize(maxS);
        timer = 0;
        st = SegmentTree<int32_t>(maxS);
        for (int32_t i = 0; i < q; ++i) {
            if (aq[i].type == 0) {
                que_ids.push_back(add_str(aq[i].str));
                ques.emplace_back(0, que_ids.back());
            } else if (aq[i].type == 1) {
                ques.emplace_back(1, que_ids[aq[i].val]);
            } else {
                ques.emplace_back(2, que_ids[aq[i].val]);
            }
        }
        dfs(0);
        for (auto [type, c_id]: ques) {
            if (type == 0) {
                activate(c_id);
            } else if (type == 1) {
                deactivate(c_id);
            } else {
                all_results.push_back(st.max_val(tin[c_id], tin[c_id] + 1));
            }
        }
    }
}
//
//void activate(int32_t _v) {
//    for (int32_t v = _v, in_c; v != -1; in_c = bor[v].in_c, v = bor[v].p) {
//        if (v == _v) bor[v].term = true;
//        else ++bor[v].real_child_cnt[in_c];
//    }
//}
//
//void deactivate(int32_t _v) {
//    for (int32_t v = _v, in_c; v != -1; in_c = bor[v].in_c, v = bor[v].p) {
//        if (v == _v) bor[v].term = false;
//        else --bor[v].real_child_cnt[in_c];
//    }
//}
//
//int32_t get_res(int32_t _v) {
//    int32_t res = 1;
//    int32_t ltd = 1;
//    for (int32_t v = bor[_v].p; v != -1; v = bor[v].p) {
//        if (real_child_cnt(v) >= 2) {
//            if (ltd >= 2) res += 2;
//            else ++res;
//            ltd = 1;
//        } else ++ltd;
//    }
//    return res;
//}

//namespace Stupid {
//    vector<string> strings;
//    vector<bool> use;
//
//    void add(const string &str) {
//        strings.push_back(str);
//        use.push_back(true);
//    }
//
//    void erase(int32_t id) {
//        use[id] = false;
//    }
//
//    int32_t get_ans(int32_t id) {
//        int32_t res = 0;
//        int32_t ready_size = 0;
//        int32_t next_size = 1;
//        while (ready_size < strings[id].size()) {
//            bool ok_add_next = true;
//            for (int32_t i = 0; i < strings.size(); ++i) {
//                if (!use[i] || strings[i].substr(0, ready_size) != strings[id].substr(0, ready_size)) continue;
//                if (strings[i].substr(ready_size, next_size - ready_size) !=
//                    strings[id].substr(ready_size, next_size - ready_size))
//                    ok_add_next = false;
//            }
//            if (ok_add_next) {
//                if (next_size < strings[id].size()) ++next_size;
//                else ready_size = next_size, ++res;
//            } else {
//                if (next_size - ready_size > 1) {
//                    res += 2;
//                    ready_size = next_size;
//                } else {
//                    res++;
//                    ready_size = next_size;
//                }
//            }
//        }
//        return res;
//    }
//
//    vector<int32_t> all_results;
//
//    void init_and_ans(const vector<AllQue> &aq) {
//        all_results.clear();
//        strings.clear();
//        use.clear();
//        for (int32_t i = 0; i < aq.size(); ++i) {
//            if (aq[i].type == 0) {
//                add(aq[i].str);
//            } else if (aq[i].type == 1) {
//                erase(aq[i].val);
//            } else {
//                all_results.push_back(get_ans(aq[i].val));
//            }
//        }
//    }
//}

//namespace Test {
//    random_device dev;
//    int32_t seed = dev();
//    mt19937 rng(seed);
//
//    template<typename T>
//    T randint(T a, T b) {
//        return uniform_int_distribution(a, b)(rng);
//    }
//
//    const int32_t maxgn = 10;
//
//    string gen_str(set<string> &ban) {
//        string s;
//        do {
//            s.assign(randint(1, maxgn), 'a');
//            for (auto &c: s) c = randint('a', 'z');
//        } while (ban.find(s) != ban.end());
//        ban.insert(s);
////        s.assign(randint(1, maxgn), 'a');
////        for (auto &c: s) c = randint('a', 'z');
//        return s;
//    }
//
//    vector<AllQue> gen() {
//        vector<AllQue> res;
//        int32_t q = randint(1, maxgn);
//        int32_t gend = 0;
//        set<string> s_gend;
//        vector<string> sssss;
//        vector<bool> use;
//        for (int32_t i = 0; i < q; ++i) {
//            int32_t op = randint(0, 2);
//            if (gend == 0 || op == 0) {
//                use.push_back(true);
//                auto ss = gen_str(s_gend);
//                res.emplace_back(0, ss, 0);
//                sssss.push_back(ss);
//                ++gend;
//            } else if (op == 1) {
//                vector<int32_t> pos_to_del;
//                for (int32_t j = 0; j < use.size(); ++j) if (use[j]) pos_to_del.push_back(j);
//                int32_t ptd = pos_to_del[randint<int32_t>(0, pos_to_del.size() - 1)];
//                use[ptd] = false;
//                --gend;
//                s_gend.erase(sssss[ptd]);
//                res.emplace_back(1, "", ptd);
//            } else {
//                vector<int32_t> pos_to_ask;
//                for (int32_t j = 0; j < use.size(); ++j) if (use[j]) pos_to_ask.push_back(j);
//                int32_t pta = pos_to_ask[randint<int32_t>(0, pos_to_ask.size() - 1)];
//                res.emplace_back(2, "", pta);
//            }
//        }
//        return res;
//    }
//
//    void print_inputs(const vector<AllQue> &ques) {
//        cout << ques.size() << "\n";
//        for (const auto &que: ques) {
//            if (que.type == 0) cout << "+ " << que.str << "\n";
//            else if (que.type == 1) cout << "- " << que.val + 1 << "\n";
//            else cout << "? " << que.val + 1 << "\n";
//        }
//    }
//
//    void Test() {
//        while (true) {
//            auto inputs = gen();
//            FullSol::all_results.clear(), Stupid::all_results.clear();
//            FullSol::all_results.shrink_to_fit(), Stupid::all_results.shrink_to_fit();
//            Stupid::init_and_ans(inputs);
//            FullSol::init_and_ans(inputs);
//            if (Stupid::all_results != FullSol::all_results) {
//                print_inputs(inputs);
//                cout << "\nStupid:\n";
//                for (auto v: Stupid::all_results) cout << v << " ";
//                cout << "\nMy:\n";
//                for (auto v: FullSol::all_results) cout << v << " ";
//                break;
//            }
//        }
//    }
//}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
//    Test::Test();
    int32_t q;
    cin >> q;
    char c;
    string str;
    int32_t tn;
    vector<AllQue> aq;
    for (int32_t i = 0; i < q; ++i) {
        cin >> c;
        if (c == '+') {
            cin >> str;
            aq.emplace_back(0, str, 0);
        } else if (c == '-') {
            cin >> tn;
            aq.emplace_back(1, "", tn - 1);
        } else {
            cin >> tn;
            aq.emplace_back(2, "", tn - 1);
        }
    }
    FullSol::init_and_ans(aq);
    for (int32_t i = 0; i < FullSol::all_results.size(); ++i) {
        cout << FullSol::all_results[i] << "\n";
    }
//    Stupid::init_and_ans(aq);
//    if (FullSol::all_results != Stupid::all_results) {
//        for (int32_t i = 0; i < FullSol::all_results.size(); ++i) {
//            cout << FullSol::all_results[i] << " ";
//        }
//        cout << "\n";
//        for (int32_t i = 0; i < Stupid::all_results.size(); ++i) {
//            cout << Stupid::all_results[i] << " ";
//        }
//        cout << "\n";
//    }

//    for (int32_t i = 0; i < q; ++i) {
//        cin >> c;
//        if (c == '+') {
//            cin >> str;
//            que_ids.push_back(add_str(str));
//            ques.emplace_back(0, que_ids.back());
//        } else if (c == '-') {
//            cin >> tn;
//            ques.emplace_back(1, que_ids[tn - 1]);
//        } else {
//            cin >> tn;
//            ques.emplace_back(2, que_ids[tn - 1]);
//        }
//    }
//    dfs(0);
//    for (auto [type, c_id]: ques) {
//        if (type == 0) {
//            activate(c_id);
//        } else if (type == 1) {
//            deactivate(c_id);
//        } else {
//            cout << st.max_val(tin[c_id], tin[c_id] + 1) << "\n";
//        }
//    }
    return 0;
}
