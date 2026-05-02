// #ifndef LOCAL
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx,avx2")
// #endif

#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

constexpr int maxn = 3e5;

int vals[maxn];
int n, q;
pair<int, int> ques[maxn];

// namespace Solve1 {
//     int sort_vals[maxn];
//
//     void solve() {
//         for (int i = 0; i < n; ++i) sort_vals[i] = vals[i];
//         for (int _ = 0; _ < q; ++_) {
//             auto [x,c] = ques[_];
//             if (x == 1) {
//                 for (int i = 0; i < n; ++i) vals[i] &= c;
//                 for (int i = 0; i < n; ++i) sort_vals[i] &= c;
//             } else if (x == 2) {
//                 for (int i = 0; i < n; ++i) vals[i] |= c;
//                 for (int i = 0; i < n; ++i) sort_vals[i] |= c;
//             } else if (x == 3) {
//                 for (int i = 0; i < n; ++i) vals[i] ^= c;
//                 for (int i = 0; i < n; ++i) sort_vals[i] ^= c;
//             } else if (x == 4) {
//                 cout << vals[c - 1] << "\n";
//             } else if (x == 5) {
//                 nth_element(sort_vals, sort_vals + c - 1, sort_vals + n);
//                 cout << sort_vals[c - 1] << "\n";
//             }
//         }
//     }
// }

namespace Solve2 {
    class BitArr {
    public:
        bool bits[maxn];
        int all_setted_val = -1;
        bool reversed = false;

        void init() {
            all_setted_val = -1;
            reversed = false;
        }

        void set_bit(int pos, bool val) {
            bits[pos] = val;
        }

        void make_zero() {
            all_setted_val = 0;
        }

        void make_one() {
            all_setted_val = 1;
        }

        void make_xor() {
            if (all_setted_val != -1) all_setted_val = 1 - all_setted_val;
            else reversed = !reversed;
        }

        int get_val(int pos) {
            if (all_setted_val == 0) return 0;
            if (all_setted_val == 1) return 1;
            return bits[pos] ^ reversed;
        }
    };

    BitArr arrs[30];

    void solve2() {
        for (int i = 0; i < 30; ++i) arrs[i].init();
        for (int i = 0; i < 30; ++i)
            for (int j = 0; j < n; ++j)
                arrs[i].set_bit(j, (vals[j] >> i) & 1);
        for (int _ = 0; _ < q; ++_) {
            auto [x,c] = ques[_];
            if (x == 1) {
                for (int i = 0; i < 30; ++i) if (!((c >> i) & 1)) arrs[i].make_zero();
            } else if (x == 2) {
                for (int i = 0; i < 30; ++i) if ((c >> i) & 1) arrs[i].make_one();
            } else if (x == 3) {
                for (int i = 0; i < 30; ++i) if ((c >> i) & 1) arrs[i].make_xor();
            } else if (x == 4) {
                int ans = 0;
                for (int i = 0; i < 30; ++i) ans |= arrs[i].get_val(c - 1) << i;
                cout << ans << "\n";
            }
        }
    }

    namespace Bor {
        int xor_val = 0;

        struct Node {
            Node *l = nullptr, *r = nullptr;
            int size = 0;

            void init() {
                size = 0;
                l = nullptr, r = nullptr;
            }
        };

        Node nodes[maxn * 40];
        int used_nodes = 0;

        Node *get_new_node() {
            nodes[used_nodes].init();
            return &nodes[used_nodes++];
        }

        Node *root = nullptr;

        void init() {
            used_nodes = 0;
            xor_val = 0;
            root = get_new_node();
        }

        void add_val(int val) {
            Node *v = root;
            for (int i = 29; i >= 0; --i) {
                ++v->size;
                auto &nu = ((val >> i) & 1) ? v->r : v->l;
                if (nu == nullptr) nu = get_new_node();
                v = nu;
            }
            ++v->size;
        }

        void rec_copy(Node *a, Node *b) {
            if (!b) return;
            a->size += b->size;
            if (b->l) {
                if (!a->l) a->l = b->l;
                else rec_copy(a->l, b->l);
            }
            if (b->r) {
                if (!a->r) a->r = b->r;
                else rec_copy(a->r, b->r);
            }
        }

        int nth_val(int c) {
            int ans = 0;
            auto v = root;
            for (int i = 29; i >= 0; --i) {
                if (arrs[i].all_setted_val != -1 && v->l && v->r) {
                    if (arrs[i].all_setted_val == 0) {
                        rec_copy(v->l, v->r);
                        v->r = nullptr;
                    } else {
                        rec_copy(v->r, v->l);
                        v->l = nullptr;
                    }
                }
                if (arrs[i].all_setted_val == 0 && v->l == nullptr) swap(v->l, v->r);
                if (arrs[i].all_setted_val == 1 && v->r == nullptr) swap(v->l, v->r);
                auto l = v->l, r = v->r;
                if (arrs[i].all_setted_val == -1) {
                    if (arrs[i].reversed) swap(l, r);
                    int lsz = l ? l->size : 0;
                    if (c < lsz) v = l;
                    else {
                        ans |= 1 << i;
                        c -= lsz;
                        v = r;
                    }
                }
                if (arrs[i].all_setted_val == 0) {
                    v = l;
                }
                if (arrs[i].all_setted_val == 1) {
                    ans |= 1 << i;
                    v = r;
                }
            }
            return ans;
        }

        void make_xor(int val) {
            xor_val ^= val;
        }
    }

    void solve3() {
        for (int i = 0; i < 30; ++i) arrs[i].init();
        for (int i = 0; i < 30; ++i)
            for (int j = 0; j < n; ++j)
                arrs[i].set_bit(j, (vals[j] >> i) & 1);
        Bor::init();
        for (int i = 0; i < n; ++i) Bor::add_val(vals[i]);
        for (int _ = 0; _ < q; ++_) {
            auto [x,c] = ques[_];
            if (x == 1) {
                for (int i = 0; i < 30; ++i) if (!((c >> i) & 1)) arrs[i].make_zero();
            } else if (x == 2) {
                for (int i = 0; i < 30; ++i) if ((c >> i) & 1) arrs[i].make_one();
            } else if (x == 3) {
                for (int i = 0; i < 30; ++i) if ((c >> i) & 1) arrs[i].make_xor();
                Bor::make_xor(c);
            } else if (x == 4) {
                int ans = 0;
                for (int i = 0; i < 30; ++i) ans |= arrs[i].get_val(c - 1) << i;
                cout << ans << "\n";
            } else {
                cout << Bor::nth_val(c - 1) << "\n";
            }
        }
    }
}


void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> vals[i];
    cin >> q;
    bool first_op = false, sec_op = false, fivth_op = false;
    for (int i = 0; i < q; ++i) {
        cin >> ques[i].first >> ques[i].second;
        if (ques[i].first == 1) first_op = true;
        if (ques[i].first == 2) sec_op = true;
        if (ques[i].first == 5) fivth_op = true;
    }
    Solve2::solve3();
    // if (!first_op && !sec_op) Solve2::solve3();
    // else if (!fivth_op) Solve2::solve2();
    // else if (n * q <= 1e8) Solve1::solve();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int cfmod = 1, t = 1;
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cfmod = 1;
#endif
    if (cfmod) cin >> t;
    while (t--) solve();
    return 0;
}
