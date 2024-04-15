#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
    vector<int32_t> ft;
public:
    void add(int32_t pos, int32_t val) { // pos by 0-indexation
        for (++pos; pos < ft.size(); pos += pos & -pos) ft[pos] += val;
    }

    int32_t sum(int32_t r) { // [0, r)
        int32_t res = 0;
        for (; r; r -= r & -r) res += ft[r];
        return res;
    }

    explicit FenwickTree(const vector<int32_t> &nums) : ft(nums.size() + 1, 0) {
        for (int32_t i = 0; i < nums.size(); ++i) add(i, nums[i]);
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
