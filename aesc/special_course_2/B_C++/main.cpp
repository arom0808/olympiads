#include <iostream>
#include <vector>
#include <algorithm>

struct Request {
    std::uint32_t id = 0, l = 0, r = 0, ans = 0;
};

class MyMultiset {
    std::vector<std::uint32_t> counts;
    std::uint32_t non_zero_cnt = 0;

public:
    explicit MyMultiset(std::uint32_t n) : counts(n, 0) {}

    void add(std::uint32_t value) {
        if ((counts[value]++) == 0) ++non_zero_cnt;
    }

    void del(std::uint32_t value) {
        if ((--counts[value]) == 0) --non_zero_cnt;
    }

    [[nodiscard]] std::uint32_t unique_cnt() const { return non_zero_cnt; }
};


void zip_coords(std::vector<std::uint32_t> &nums) {
    std::vector<std::uint32_t> sorted_nums = nums;
    std::sort(sorted_nums.begin(), sorted_nums.end());
    for (auto &num: nums)
        num = std::distance(sorted_nums.begin(), std::lower_bound(sorted_nums.begin(), sorted_nums.end(), num));
}

const std::uint32_t k = 550;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::uint32_t n, q;
    std::cin >> n;
    std::vector<std::uint32_t> nums(n);
    for (auto &num: nums) std::cin >> num;
    zip_coords(nums);
    std::cin >> q;
    std::vector<Request> requests(q);
    for (std::uint32_t i = 0; i < q; ++i) {
        auto &req = requests[i];
        req.id = i;
        std::cin >> req.l >> req.r;
        --req.l;
    }
    std::sort(requests.begin(), requests.end(), [](const Request &a, const Request &b) {
        if (a.l / k < b.l / k) return true;
        if (a.l / k > b.l / k) return false;
        return a.r < b.r;
    });
    MyMultiset counts(n);
    std::uint32_t g_l = 0, g_r = 0;
    for (auto &req: requests) {
        while (g_r < req.r) counts.add(nums[g_r++]);
        while (req.l < g_l) counts.add(nums[--g_l]);
        while (g_r > req.r) counts.del(nums[--g_r]);
        while (req.l > g_l) counts.del(nums[g_l++]);
        req.ans = counts.unique_cnt();
    }
    std::vector<std::uint32_t> answers(q);
    for (const auto &req: requests) answers[req.id] = req.ans;
    for (const auto &ans: answers) std::cout << ans << "\n";
    return 0;
}

//    std::freopen("out.txt", "r", stdin);
//    std::freopen("mpout.txt", "w", stdout);