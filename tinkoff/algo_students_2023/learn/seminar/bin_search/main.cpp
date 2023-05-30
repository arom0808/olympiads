#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

class Solution {
public:
    std::pair<std::uint32_t, std::uint32_t>
    MinAndMaxOfUsingFirstArr(const std::vector<std::int32_t> &nums, const std::int32_t find_num,
                             std::int32_t not_use_num) {
        std::uint32_t first_id = std::distance(nums.begin(), std::lower_bound(nums.begin(), nums.end(), find_num));
        std::uint32_t last_id = std::distance(nums.begin(), std::lower_bound(nums.begin(), nums.end(), not_use_num));
        return {first_id, last_id};
    }

    std::pair<std::uint32_t, std::uint32_t>
    CountOfElementsToUseInArrays(const std::vector<int> &_nums1, const std::vector<int> &_nums2) {
        bool is_reversed = (_nums1.empty() ? true : (_nums2.empty() ? false : _nums1.back() >= _nums2.back()));
        const std::vector<int> &nums1 = (is_reversed ? _nums2 : _nums1), nums2 = (is_reversed ? _nums1 : _nums2);
        std::uint32_t l = 0, r = nums2.size();
        std::uint32_t req_using_cnt = (nums1.size() + nums2.size()) / 2 + 1;
        while (l != r) {
            std::uint32_t m = (l + r) / 2 + (l + r) % 2;
            auto min_max_of_using_first_arr =
                    MinAndMaxOfUsingFirstArr(nums1, nums2[m - 1],
                                             (m == nums2.size() ? std::numeric_limits<std::int32_t>::max() : nums2[m]));
            if (min_max_of_using_first_arr.second + m < req_using_cnt) l = m + 1;
            else if (min_max_of_using_first_arr.first + m > req_using_cnt) r = m - 1;
            else {
                l = m;
                r = m;
            }
        }
        if (is_reversed) return {l, req_using_cnt - l};
        else return {req_using_cnt - l, l};
    }

    double findMedianSortedArrays(const std::vector<int> &nums1, const std::vector<int> &nums2) {
        auto count_of_els_using_in_arrays = CountOfElementsToUseInArrays(nums1, nums2);
        std::vector<std::int32_t> elements(4, std::numeric_limits<std::int32_t>::min());
        if (count_of_els_using_in_arrays.first > 0) elements[0] = nums1[count_of_els_using_in_arrays.first - 1];
        if (count_of_els_using_in_arrays.second > 0) elements[1] = nums2[count_of_els_using_in_arrays.second - 1];
        if ((nums1.size() + nums2.size()) % 2 == 0) {
            if (count_of_els_using_in_arrays.first > 1)
                elements[2] = nums1[count_of_els_using_in_arrays.first - 2];
            if (count_of_els_using_in_arrays.second > 1)
                elements[3] = nums2[count_of_els_using_in_arrays.second - 2];
        }
        std::sort(elements.begin(), elements.end());
        if ((nums1.size() + nums2.size()) % 2 == 0) return static_cast<double>(elements[2] + elements[3]) / 2;
        else return elements[3];
    }
};

int main() {
    Solution solution;
    std::cout << solution.findMedianSortedArrays({}, {2, 3});
    return 0;
}
