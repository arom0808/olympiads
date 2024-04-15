#include <iostream>
#include <vector>

using namespace std;

class SparseTable {
    vector <vector<uint32_t>> tree;
public:
    uint32_t min(uint32_t l, uint32_t r) {
        uint32_t k = __lg(r - l);
        return std::min(tree[k][l], tree[k][r - (1 << k)]);
    }

    SparseTable(const vector <uint32_t> &nums) : tree(__lg(nums.size()) + 1, vector<uint32_t>(nums.size())) {
        tree[0] = nums;
        for (uint32_t k = 1; k < tree.size(); ++k)
            for (uint32_t i = 0; i + (1 << (k - 1)) < nums.size(); ++i)
                tree[k][i] = std::min(tree[k - 1][i], tree[k - 1][i + (1 << (k - 1))]);
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
