#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    freopen("test.txt", "r", stdin);
    int32_t n, q;
    cin >> n >> q;
    vector<int32_t> raw_nums(n), nums(n);
    for (auto &num: raw_nums) cin >> num;
    for (int32_t i = 0, x, v; i < q; ++i) {
        cin >> x >> v;
        raw_nums[x - 1] = v;
        copy(raw_nums.begin(), raw_nums.end(), nums.begin());
        int32_t r = 0;
        while (true) {
            bool sorted = true;
            for (int32_t j = 0; j + 1 < n; ++j)
                if (nums[j] > nums[j + 1])
                    swap(nums[j], nums[j + 1]), sorted = false;
            if (sorted) break;
            else ++r;
        }
        cout << r << "\n";
    }
    return 0;
}