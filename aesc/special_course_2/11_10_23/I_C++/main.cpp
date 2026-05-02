#include <iostream>

using namespace std;

class OrderedMultiset {
private:
    struct Elem {
        uint32_t elems_cnt;
        Elem *left = nullptr, *right = nullptr;
    };

    Elem *root = nullptr;
    uint32_t size;

    void _change(Elem *el, uint32_t l, uint32_t r, uint32_t x, bool change_type) {
        if (x < l || x >= r || l >= r) return;
        if (change_type) ++el->elems_cnt;
        else --el->elems_cnt;
        if (r - l == 1) return;
        if (x < (l + r) / 2) {
            if (!el->left) el->left = new Elem();
            _change(el->left, l, (l + r) / 2, x, change_type);
        } else {
            if (!el->right) el->right = new Elem();
            _change(el->right, (l + r) / 2, r, x, change_type);
        }
    }

    uint32_t _count(Elem *el, uint32_t l, uint32_t r, uint32_t x) {
        if (x < l || x >= r || l >= r) return 0;
        if (r - l == 1) return el->elems_cnt;
        if (x < (l + r) / 2) {
            if (el->left) return _count(el->left, l, (l + r) / 2, x);
            else return 0;
        } else {
            if (el->right) return _count(el->right, (l + r) / 2, r, x);
            else return 0;
        }
    }

    uint32_t _kth(Elem *el, uint32_t less_cnt, uint32_t l, uint32_t r, uint32_t k) {
        if (r - l == 1) return l;
        bool lr = (!el->left) || (el->right && k >= less_cnt + el->left->elems_cnt);
        if (!lr) return _kth(el->left, less_cnt, l, (l + r) / 2, k);
        return _kth(el->right, less_cnt + (el->left ? el->left->elems_cnt : 0), (l + r) / 2, r, k);
    }

    uint32_t _count_less(Elem *el, uint32_t l, uint32_t r, uint32_t x) {
        if (x < (l + r) / 2) return el->left ? _count_less(el->left, l, (l + r) / 2, x) : 0;
        return (el->left ? el->left->elems_cnt : 0) + (el->right ? _count_less(el->right, (l + r) / 2, r, x) : 0);
    }

public:
    explicit OrderedMultiset(uint32_t size) : root(new Elem()), size(size) {}

    void insert(uint32_t x) {
        _change(root, 0, size, x, true);
    }

    void erase(uint32_t x) {
        _change(root, 0, size, x, false);
    }

    uint32_t count(uint32_t x) {
        return _count(root, 0, size, x);
    }

    uint32_t kth(uint32_t k) {
        return _kth(root, 0, 0, size, k);
    }

    uint32_t count_less(uint32_t x) {
        return _count_less(root, 0, size, x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    OrderedMultiset st(1e9 + 2);
    uint32_t q, x;
    cin >> q;
    string tmp;
    for (uint32_t i = 0; i < q; ++i) {
        cin >> tmp >> x;
        if (tmp == "insert") st.insert(x);
        else if (tmp == "erase") st.erase(x);
        else if (tmp == "count") cout << st.count(x) << "\n";
        else if (tmp == "kth") cout << st.kth(x - 1) << "\n";
        else cout << st.count_less(x) << "\n";
    }
    return 0;
}
