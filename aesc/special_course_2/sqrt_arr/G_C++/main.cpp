#include <iostream>
#include <vector>
#include <set>

const std::int32_t sqrt_m = 3e2, inf = 1e9;

struct Request {
    std::int32_t l, r, x, y;
};

void process_request(const Request &req, std::vector<std::int32_t> &dif_arr,
                     std::vector<std::int32_t> &sec_dif_arr) {
    dif_arr[req.l] += req.x;
    if (req.l + 1 < dif_arr.size()) sec_dif_arr[req.l + 1] += req.y;
    if (req.r < dif_arr.size()) {
        dif_arr[req.r] -= req.x + req.y * (req.r - req.l - 1);
        sec_dif_arr[req.r] -= req.y;
    }
}

void process_diffs(std::vector<std::int32_t> &nums, std::vector<std::int32_t> &dif_arr,
                   std::vector<std::int32_t> &sec_dif_arr) {
    for (std::uint32_t i = 0; i < nums.size(); ++i) dif_arr[i] += nums[i] - (i == 0 ? 0 : nums[i - 1]);
    for (std::uint32_t i = 0; i < nums.size(); ++i) {
        dif_arr[i] = (i == 0 ? 0 : dif_arr[i - 1]) + sec_dif_arr[i];
        nums[i] = (i == 0 ? 0 : nums[i - 1]) + dif_arr[i];
    }
}

int main() {
    std::int32_t n;
    std::cin >> n;
    std::vector<std::int32_t> nums(n), required_nums(n);
    for (auto &num: nums) std::cin >> num;
    for (auto &num: required_nums) std::cin >> num;
    std::int32_t m;
    std::cin >> m;
    std::vector<Request> requests(m);
    for (auto &req: requests) {
        std::cin >> req.l >> req.r >> req.x >> req.y;
        --req.l;
    }
    std::vector<std::int32_t> ans(n, inf);
    for (std::int32_t i = 0; i < n; ++i) if (nums[i] >= required_nums[i]) ans[i] = 0;
    std::vector<std::int32_t> temp_nums, dif_arr(n, 0), sec_dif_arr(n, 0);
    for (std::int32_t made_requests = 0; made_requests < m; made_requests += sqrt_m) {
        std::fill(dif_arr.begin(), dif_arr.end(), 0);
        std::fill(sec_dif_arr.begin(), sec_dif_arr.end(), 0);
        for (std::int32_t i = made_requests; i < made_requests + sqrt_m && i < m; ++i)
            process_request(requests[i], dif_arr, sec_dif_arr);
        temp_nums = nums;
        process_diffs(temp_nums, dif_arr, sec_dif_arr);
        std::set<std::uint32_t> changed;
        for (std::uint32_t i = 0; i < n; ++i)
            if (temp_nums[i] >= required_nums[i] && ans[i] == inf)
                changed.push_back(i);
        if (!changed.empty()) {

        }
    }
    return 0;
}
