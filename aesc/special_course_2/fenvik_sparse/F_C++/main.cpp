#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

template<typename T>
class FenwickTree {
private:
//    static inline int64_t f(int64_t x) { return x - (x & (-x)) + 1; }

    vector<T> tree;

public:
    T sum(int64_t r) {
        T res = 0;
        for (; r > 0; r -= r & -r) res += tree[r];
        return res;
    }

    T sum(int64_t l, int64_t r) { return sum(r) - sum(l); }

    void add(int64_t pos, T val) { for (++pos; pos < tree.size(); pos += pos & -pos) tree[pos] += val; }

    void set(int64_t pos, T val) { add(pos, val - sum(pos, pos + 1)); }

    explicit FenwickTree(int64_t n) : tree(n + 1, 0) {}

    explicit FenwickTree(const vector<T> &vec) : tree(vec.size() + 1, 0) {
        for (int64_t i = 0; i < vec.size(); ++i) add(i, vec[i]);
    }
};


int main() {
    int64_t n, k;
    cin >> n >> k;
    vector<int64_t> nums(n);
    for (auto &num: nums) {
        cin >> num;
        --num;
    }
    vector<FenwickTree<int64_t>> fts(k + 2, FenwickTree<int64_t>(n));
    for (int64_t i = 0; i < n; ++i) {
        fts[1].add(nums[i], 1);
        for (int64_t l = 2; l <= k + 1; ++l) fts[l].add(nums[i], fts[l - 1].sum(nums[i]));
    }
    cout << fts[k + 1].sum(n);
    return 0;
}