#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100000, maxsqn = 320;
int n, k;
int nums[maxn];

struct Block {
    vector<int> vals, rems;
    int size = 0;
};

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> nums[i];
    vector<Block> blocks(n / maxsqn + (n % maxsqn != 0));
    for (int block_id = 0; block_id < blocks.size(); ++block_id) {
        auto &[vals, rems, size] = blocks[block_id];
        if (block_id * maxsqn + maxsqn <= n) size = maxsqn;
        else size = n - block_id * maxsqn;
        vals.resize(size);
        rems.resize(min(size, k), -1);
        for (int i = 0; i < size; ++i) {
            vals[i] = nums[block_id * maxsqn + i];
            if (rems[i % k] == -1 || vals[rems[i % k]] < vals[i]) rems[i % k] = i;
        }
    }
    for (int _ = 0; _ < n; ++_) {
        int best_res = -1, best_fi = -1, best_block = -1, pre_cnt = 0;
        for (int block_id = 0; block_id < blocks.size(); ++block_id) {
            auto &[vals, rems, size] = blocks[block_id];
            int fi = ((0 - pre_cnt) % k + k) % k;
            if (fi < size && (best_res == -1 || vals[rems[fi]] > best_res))
                best_res = vals[rems[fi]], best_block = block_id, best_fi = fi;
            pre_cnt += size;
        }
        cout << best_res << "\n";
        auto &[vals, rems, size] = blocks[best_block];
        vals.erase(next(vals.begin(), rems[best_fi]));
        --size;
        rems.resize(min(size, k));
        fill(rems.begin(), rems.end(), -1);
        for (int i = 0; i < size; ++i)
            if (rems[i % k] == -1 || vals[rems[i % k]] < vals[i])
                rems[i % k] = i;
    }
    return 0;
}
