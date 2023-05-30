#include <iostream>
#include <list>
#include <deque>
#include <vector>

struct Task {
    std::vector<std::uint32_t>::iterator begin_it, end_it;
    bool type;

    Task(const std::vector<std::uint32_t>::iterator &begin_it,
         const std::vector<std::uint32_t>::iterator &end_it,
         bool type) : begin_it(begin_it), end_it(end_it), type(type) {}
};

int main() {
    std::uint32_t n;
    std::cin >> n;
    std::vector<std::uint32_t> nums(n);
    for (auto &&num: nums) std::cin >> num;
    std::deque<Task> tasks{{nums.begin(), nums.end(), false}};
    std::uint64_t glob_res = 0;
    while (!tasks.empty()) {
        auto &task = tasks.back();
        std::uint32_t local_n = std::distance(task.begin_it, task.end_it);
        if (!task.type) {
            if (local_n == 1) tasks.pop_back();
            else {
                auto mid = std::next(task.begin_it, local_n / 2);
                tasks.emplace_back(task.begin_it, mid, false);
                tasks.emplace_back(mid, task.end_it, false);
                task.type = true;
            }
        } else {
            auto mid = std::next(task.begin_it, local_n / 2);
            std::vector<std::uint32_t> local_result(local_n);
            for (auto it1 = task.begin_it, it2 = mid, res_it = local_result.begin();
                 it1 != mid || it2 != task.end_it; ++res_it) {
                if (it1 != mid) {
                    if (it2 != task.end_it) {
                        if (*it1 <= *it2) {
                            *res_it = *it1;
                            std::advance(it1, 1);
                        } else {
                            *res_it = *it2;
                            std::advance(it2, 1);
                            glob_res += std::distance(it1, mid);
                        }
                    } else {
                        *res_it = *it1;
                        std::advance(it1, 1);
                    }
                } else if (it2 != task.end_it) {
                    *res_it = *it2;
                    std::advance(it2, 1);
                }
            }
            std::copy(local_result.begin(), local_result.end(), task.begin_it);
            tasks.pop_back();
        }
    }
    std::cout << glob_res << std::endl;
    for (const auto &num: nums) std::cout << num << " ";
    return 0;
}