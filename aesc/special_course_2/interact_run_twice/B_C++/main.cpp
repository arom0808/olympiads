#include <iostream>
#include <vector>
#include <set>
#include <cstdint>

using namespace std;

struct AskAns {
    int64_t a, l, r;
};

AskAns ask(int64_t l, int64_t r) {
    cout << "? " << l + 1 << " " << r << endl;
    int64_t a;
    cin >> a >> l >> r;
    if (a == -1 && l == -1 && r == -1) exit(0);
    return {a, l - 1, r};
}

set<pair<int64_t, int64_t>> baned;

int main() {
    int64_t n;
    cin >> n;
    vector<int64_t> nums(n);
    auto aans = ask(0, 1);
    nums[0] = aans.a;
    baned.emplace(aans.l, aans.r);
    for (int64_t i = 1; i < n; ++i) {
        int64_t l = i, r = i + 1;
        while (baned.find({l, r}) != baned.end()) --l;
        aans = ask(l, r);
        int64_t pre_sum = 0;
        for (int64_t j = l; j < r; ++j) pre_sum += nums[j];
        nums[i] = aans.a - pre_sum;
        baned.emplace(aans.l, aans.r);
    }
    cout << "!\n";
    for (auto v: nums) cout << v << " ";
    cout << endl;
    return 0;
}
