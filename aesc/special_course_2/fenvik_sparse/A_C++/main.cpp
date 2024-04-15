#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class FenwickTree {
private:
//    static inline int32_t f(int32_t x) { return x - (x & (-x)) + 1; }

    vector<T> tree;

public:
    T sum(int32_t r) {
        T res = 0;
        for (; r > 0; r -= r & -r) res += tree[r];
        return res;
    }

    T sum(int32_t l, int32_t r) { return sum(r) - sum(l); }

    void add(int32_t pos, T val) { for (++pos; pos < tree.size(); pos += pos & -pos) tree[pos] += val; }

    void set(int32_t pos, T val) { add(pos, val - sum(pos, pos + 1)); }

    explicit FenwickTree(int32_t n) : tree(n + 1, 0) {}

    explicit FenwickTree(const vector<T> &vec) : tree(vec.size() + 1, 0) {
        for (uint32_t i = 0; i < vec.size(); ++i) add(i, vec[i]);
    }
};

int main() {
    int32_t n, k;
    cin >> n >> k;
    char c;
    FenwickTree<int64_t> ft(n);
    for (int32_t i = 0, p1, p2; i < k; ++i) {
        cin >> c >> p1 >> p2;
        if (c == 'A') ft.set(p1 - 1, p2);
        else cout << ft.sum(p1 - 1, p2) << "\n";
    }
    return 0;
}
