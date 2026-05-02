#include <iostream>

using namespace std;

template<typename T>
inline T ceil(T a, T b) {
    return (a + b - 1) / b;
}

namespace SegTree {
    const int32_t max_nodes = 5e7;

    struct Node {
        int64_t first_len, other_lens, sum;
        Node *left, *right;
        bool changed;

        void init(int64_t l, int64_t r) {
            first_len = 0, other_lens = 0, sum = r - l;
            left = right = nullptr;
            changed = false;
        }

        void upd_sum(int64_t l, int64_t r) {
            sum = ceil(r - l - first_len, other_lens + 1);
        }

        int64_t del_twos(int64_t l, int64_t r, bool start_second) {
            if (!start_second) {
                first_len += other_lens;
                if (first_len >= r - l) first_len = r - l;
            }
            other_lens = other_lens * 2 + 1;
            if (first_len + 1 + other_lens > r - l) other_lens = std::max<int64_t>(r - l - first_len - 1, 0);
            int64_t pre_sum = sum;
            upd_sum(l, r);
            return pre_sum - sum;
        }

        void update(int64_t l, int64_t r, int64_t f_l, int64_t o_l) {
            first_len = f_l, other_lens = o_l;
            if (first_len >= r - l) first_len = r - l;
            if (first_len + 1 + other_lens > r - l) other_lens = std::max<int64_t>(r - l - first_len - 1, 0);
            upd_sum(l, r);
        }

        int64_t get_f_l_of_mid(int64_t l, int64_t r) {
            int64_t pos = (l + r) / 2 - l;
            if (pos < first_len) return first_len - pos;
            auto pmo = (pos - first_len) % (other_lens + 1);
            if (pmo == 0) return 0;
            return -pmo + other_lens + 1;
        }
    };

    Node tree[max_nodes];
    int64_t size;
    int32_t nodes_used = 0;
    Node *root = nullptr;

    Node *get_new_node(int64_t l, int64_t r) {
        auto node = &tree[nodes_used++];
        node->init(l, r);
        return node;
    }

    void init(int64_t _size) {
        size = _size;
        root = get_new_node(0, size);
    }

    void transfer_to_children(Node *v, int64_t l, int64_t r) {
        if (r - l <= 1) return;
        if (!v->left) v->left = get_new_node(l, (l + r) / 2);
        if (!v->right) v->right = get_new_node((l + r) / 2, r);
        if (!v->changed) return;
        v->left->update(l, (l + r) / 2, v->first_len, v->other_lens);
        v->right->update((l + r) / 2, r, v->get_f_l_of_mid(l, r), v->other_lens);
    }

    int64_t _lower_bound(Node *v, int64_t l, int64_t r, int64_t need_sum) {
        if (v->sum < need_sum) return r;
        if (r - l == 1) return l;
        transfer_to_children(v, l, r);
        auto left_r = _lower_bound(v->left, l, (l + r) / 2, need_sum);
        if (left_r != (l + r) / 2) return left_r;
        return _lower_bound(v->right, (l + r) / 2, r, need_sum - v->left->sum);
    }

    int64_t del_twos(Node *v, int64_t l, int64_t r, int64_t a, int64_t b, bool start_second = false) {
        if (l >= r || l >= b || a >= r) return 0;
        if (a <= l && r <= b) return v->del_twos(l, r, start_second);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int64_t n, m;
    cin >> n >> m;
    SegTree::init(m);
    int64_t min_left_dist = m, min_right_dist = m, cur_size = m;
    int64_t minv = m - 1, maxv = 0;
    for (int32_t i = 0, l, r; i < n; ++i) {
        cin >> l >> r, --l, --r;
        if (l < min_left_dist) minv = l, min_left_dist = l;
        if (cur_size - r - 1 < min_right_dist) maxv = m - (cur_size - r - 1), min_right_dist = cur_size - r - 1;
        cur_size -= (r - l) / 2 + 1;
        cout << minv + 1 << " " << maxv << "\n";
    }
    return 0;
}
