#include <iostream>
#include <list>
#include <set>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

int main() {
    std::int64_t n;
    std::cin >> n;
    std::list<std::int64_t> nums(n);
    for (auto &&num: nums) std::cin >> num;
    std::int64_t count = 0;
    tree<int64_t, null_type, std::less<>, rb_tree_tag, tree_order_statistics_node_update> last_els;
    last_els.insert(nums.back());
    for (auto it = std::next(nums.rbegin()); it != nums.rend(); ++it) {
        count += static_cast<std::int64_t>(last_els.order_of_key(*it));
        last_els.insert(*it);
    }
    for (std::int64_t i = 0; i < n; ++i) {
        std::cout << count << "\n";
        count -= nums.front();
        count += n - nums.front() - 1;
        nums.splice(nums.end(), nums, nums.begin());
    }
    return 0;
}
