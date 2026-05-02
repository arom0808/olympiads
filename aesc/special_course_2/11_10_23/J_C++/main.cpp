#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

#include <iostream>
#include <array>
#include <cstdint>
//#include <x86intrin.h>

using namespace std;

const int32_t maxn = 1e5, k = 32;

namespace st {
    struct Node {
        array<int32_t, k> cnts{};
        char push;

        Node() : push(-1) {}
    };

    Node tree[maxn * 4];

    void upd_by_child(int32_t id) {
//        for (int32_t i = 0; i < k; i += 8) {
//            __m256i x = _mm256_loadu_epi32(&tree[id * 2].cnts[i]);
//            __m256i y = _mm256_loadu_epi32(&tree[id * 2 + 1].cnts[i]);
//            __m256i z = _mm256_add_epi32(x, y);
//            _mm256_store_epi32(&tree[id].cnts[i], z);
//        }
        for (int32_t i = 0; i < k; ++i) tree[id].cnts[i] = tree[id * 2].cnts[i] + tree[id * 2 + 1].cnts[i];
    }

    void init(int32_t id, int32_t l, int32_t r, const string &str) {
        if (l >= r) return;
        if (r - l == 1) {
            if (l < str.size()) tree[id].cnts[str[l] - 'a'] = 1;
        } else {
            init(id * 2, l, (l + r) / 2, str);
            init(id * 2 + 1, (l + r) / 2, r, str);
            upd_by_child(id);
        }
    }

    void assign(const string &str) {
        init(1, 0, maxn, str);
    }

    void push_changes(int32_t id, int32_t l, int32_t r) {
        if (tree[id].push == -1) return;
        if (r - l > 1) {
            tree[id * 2].cnts.fill(0), tree[id * 2 + 1].cnts.fill(0);
            tree[id * 2].cnts[tree[id].push] = (l + r) / 2 - l;
            tree[id * 2 + 1].cnts[tree[id].push] = r - (l + r) / 2;
            tree[id * 2].push = tree[id * 2 + 1].push = tree[id].push;
        }
        tree[id].push = -1;
    }


    void _set(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b, char val) {
        if (l >= r || r <= a || b <= l) return;
        push_changes(id, l, r);
        if (a <= l && r <= b) {
            tree[id].push = val;
            tree[id].cnts.fill(0);
            tree[id].cnts[val] = r - l;
            return;
        }
        _set(id * 2, l, (l + r) / 2, a, b, val);
        _set(id * 2 + 1, (l + r) / 2, r, a, b, val);
        upd_by_child(id);
    }

    void set(int32_t a, int32_t b, char val) {
        _set(1, 0, maxn, a, b, val);
    }

    void _get_cnt(int32_t id, int32_t l, int32_t r, int32_t a, int32_t b, array<int32_t, k> &cnts) {
        if (l >= r || r <= a || b <= l) return;
        push_changes(id, l, r);
        if (a <= l && r <= b) {
            for (int32_t i = 0; i < k; ++i) cnts[i] += tree[id].cnts[i];
        } else {
            _get_cnt(id * 2, l, (l + r) / 2, a, b, cnts);
            _get_cnt(id * 2 + 1, (l + r) / 2, r, a, b, cnts);
        }
    }

    void get_cnt(int32_t a, int32_t b, array<int32_t, k> &cnts) {
        cnts.fill(0);
        _get_cnt(1, 0, maxn, a, b, cnts);
    }

    void _str_build(int32_t id, int32_t l, int32_t r, string &str) {
        if (l >= r || l >= str.size()) return;
        push_changes(id, l, r);
        if (r - l == 1) {
            char c = 0;
            while (tree[id].cnts[c] == 0) ++c;
            str[l] = 'a' + c;
        } else {
            _str_build(id * 2, l, (l + r) / 2, str);
            _str_build(id * 2 + 1, (l + r) / 2, r, str);
        }
    }

    void str_build(string &str) {
        _str_build(1, 0, maxn, str);
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
//    freopen("test.txt", "r", stdin);
    int32_t n, q;
    cin >> n >> q;
    string str;
    cin >> str;
    st::assign(str);
    array<int32_t, k> tarr{};
    for (int32_t i = 0, a, b, c; i < q; ++i) {
        cin >> a >> b >> c, --a;
        st::get_cnt(a, b, tarr);
        for (int32_t d = c ? 0 : k - 1, used = 0; c ? (d < k) : d >= 0; used += tarr[d], c ? ++d : --d)
            st::set(a + used, a + used + tarr[d], d);
    }
    st::str_build(str);
    cout << str << "\n";
}