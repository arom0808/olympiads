#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

namespace st {
    struct Node {
        int32_t max_val = 0;
        Node *l = nullptr, *r = nullptr;
    };

    const int32_t max_st_size = 1e7;

    Node tree[max_st_size];
    int32_t used_cnt = 0;
    int32_t size;

    void init(Node *&v, int32_t l, int32_t r, const vector<int32_t> &vals) {
        if (l >= r) return;
        if (!v) v = &tree[used_cnt++];
        if (r - l == 1) {
            v->max_val = vals[l];
        } else {
            init(v->l, l, (l + r) / 2, vals);
            init(v->r, (l + r) / 2, r, vals);
        }
    }

    Node *assign(const vector<int32_t> &vals) {
        size = vals.size();
        Node *root = nullptr;
        init(root, 0, size, vals);
        return root;
    }

    inline int32_t node_max_val(Node *v) { return v ? v->max_val : 0; }

    Node *_set(Node *v, int32_t l, int32_t r, int32_t pos, int32_t val) {
        if (l >= r || r <= pos || pos < l) return v;
        Node *nv = &tree[used_cnt++];
        if (r - l == 1) {
            nv->max_val = val;
        } else {
            nv->l = _set(v->l, l, (l + r) / 2, pos, val);
            nv->r = _set(v->r, (l + r) / 2, r, pos, val);
            nv->max_val = std::max(node_max_val(nv->l), node_max_val(nv->r));
        }
        return nv;
    }

    int32_t _max_val(Node *v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || r <= a || b <= l) return 0;
        if (a <= l && r <= b) return v->max_val;
        return std::max(_max_val(v->l, l, (l + r) / 2, a, b), _max_val(v->r, (l + r) / 2, r, a, b));
    }

    Node *set(Node *root, int32_t pos, int32_t val) {
        return _set(root, 0, size, pos, val);
    }

    int32_t max_val(Node *root, int32_t a, int32_t b) {
        return _max_val(root, 0, size, a, b);
    }
}

const int32_t maxm = 1e5 + 2;

st::Node *versions[maxm];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, m;
    cin >> n;
    vector<int32_t> vals(n);
    for (auto &v: vals) cin >> v;
    versions[0] = st::assign(vals);
    int32_t now_vers_cnt = 1;
    cin >> m;
    string ts;
    for (int32_t i = 0, a, b, c; i < m; ++i) {
        cin >> ts >> a >> b, --a, --b;
        if (ts == "get") {
            cout << st::max_val(versions[a], b, b + 1) << "\n";
        } else {
            cin >> c;
            versions[now_vers_cnt++] = st::set(versions[a], b, c);
        }
    }
    return 0;
}
