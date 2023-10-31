#include <iostream>
#include <vector>
#include <algorithm>

struct Request {
    std::uint32_t id = 0, l = 0, r = 0, ans = 0;
};

class MyMultiset {
    std::vector<std::uint32_t> counts;
    const std::vector<std::uint32_t> &sorted_nums;
    std::uint32_t x_x_cnt = 0;

public:
    explicit MyMultiset(std::uint32_t n, const std::vector<std::uint32_t> &sorted_nums)
            : counts(n, 0), sorted_nums(sorted_nums) {}

    void add(std::uint32_t value) {
        if (counts[value] == sorted_nums[value]) --x_x_cnt;
        if (++counts[value] == sorted_nums[value]) ++x_x_cnt;
    }

    void del(std::uint32_t value) {
        if (counts[value] == sorted_nums[value]) --x_x_cnt;
        if (--counts[value] == sorted_nums[value]) ++x_x_cnt;
    }

    [[nodiscard]] std::uint32_t x_cnt() const { return x_x_cnt; }
};

void zip_coords(const std::vector<std::uint32_t> &raw_nums, std::vector<std::uint32_t> &sorted_nums,
                std::vector<std::uint32_t> &nums) {
    nums = sorted_nums = raw_nums;
    std::sort(sorted_nums.begin(), sorted_nums.end());
    for (auto &num: nums)
        num = std::distance(sorted_nums.begin(), std::lower_bound(sorted_nums.begin(), sorted_nums.end(), num));
}

const std::uint32_t sqrt_n = 3e2;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::uint32_t n, m;
    std::cin >> n >> m;
    std::vector<std::uint32_t> raw_nums(n), sorted_nums, nums;
    for (auto &num: raw_nums) std::cin >> num;
    zip_coords(raw_nums, sorted_nums, nums);
    std::vector<Request> requests(m);
    for (std::uint32_t i = 0; i < m; ++i) {
        auto &req = requests[i];
        req.id = i;
        std::cin >> req.l >> req.r;
        --req.l;
    }
    std::sort(requests.begin(), requests.end(), [](const Request &a, const Request &b) {
        if (a.l / sqrt_n < b.l / sqrt_n) return true;
        if (a.l / sqrt_n > b.l / sqrt_n) return false;
        return a.r < b.r;
    });
    MyMultiset counts(n, sorted_nums);
    std::uint32_t g_l = 0, g_r = 0;
    for (auto &req: requests) {
        while (g_r < req.r) counts.add(nums[g_r++]);
        while (req.l < g_l) counts.add(nums[--g_l]);
        while (g_r > req.r) counts.del(nums[--g_r]);
        while (req.l > g_l) counts.del(nums[g_l++]);
        req.ans = counts.x_cnt();
    }
    std::vector<std::uint32_t> answers(m);
    for (const auto &req: requests) answers[req.id] = req.ans;
    for (const auto &ans: answers) std::cout << ans << "\n";
    return 0;
}
