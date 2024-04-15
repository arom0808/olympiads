#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

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

    explicit FenwickTree(int32_t n, const function<T(int32_t)> &f) : tree(n + 1, 0) {
        for (int32_t i = 0; i < n; ++i) add(i, f(i));
    }

    explicit FenwickTree(const vector<T> &vec) : tree(vec.size() + 1, 0) {
        for (int32_t i = 0; i < vec.size(); ++i) add(i, vec[i]);
    }
};

int main() {
    int32_t n;
    cin >> n;
    vector<int32_t> nums(n), temp_sorted;
    for (auto &num: nums) {
        cin >> num;
        --num;
    }
    temp_sorted = nums;
    sort(temp_sorted.begin(), temp_sorted.end());
    for (auto &num: nums) num = distance(temp_sorted.begin(), lower_bound(temp_sorted.begin(), temp_sorted.end(), num));
    FenwickTree<int32_t> left(n, [&nums](int32_t i) { return nums[0] == i ? 1 : 0; }),
            right(n, [&nums](int32_t i) { return nums[0] != i && nums[1] != i ? 1 : 0; });
    int64_t res = 0;
    for (int32_t i = 1; i + 1 < n; ++i) {
        res += static_cast<int64_t>(left.sum(nums[i] + 1, n)) * right.sum(0, nums[i]);
        left.add(nums[i], 1);
        right.add(nums[i + 1], -1);
    }
    cout << res;
    return 0;
}
