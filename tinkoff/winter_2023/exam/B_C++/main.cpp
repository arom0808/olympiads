#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

struct Task {
    std::uint32_t id, a, b;

    bool operator<(const Task &other) const {
        return this->a < other.a;
    }

    explicit Task(std::uint32_t id = 0, std::uint32_t a = 0, std::uint32_t b = 0) : id(id), a(a), b(b) {}
};

void
ExactlyTasksCountMaxResult(std::uint32_t exactly_tasks_count, std::uint32_t T, std::list<Task> &tasks_list,
                           std::uint32_t &for_max_exactly_tasks_count, std::uint32_t &max_result) {
    std::uint32_t current_tasks_count = 0, current_time = 0;
    for (auto it = tasks_list.begin(); it != tasks_list.end();) {
        if (exactly_tasks_count > it->b) {
            ++it;
            tasks_list.erase(std::prev(it));
            if (it == tasks_list.end()) break;
        } else {
            if (current_tasks_count >= exactly_tasks_count) break;
            if (current_time + it->a <= T) {
                ++current_tasks_count;
                current_time += it->a;
            } else { break; }
            ++it;
        }
    }
    if (current_tasks_count > max_result) {
        max_result = current_tasks_count;
        for_max_exactly_tasks_count = exactly_tasks_count;
    }
}

void
GetTasksIds(std::uint32_t exactly_tasks_count, std::uint32_t T, const std::list<Task> &tasks_list,
            std::list<std::uint32_t> &result_tasks_ids) {
    result_tasks_ids.clear();
    std::uint32_t current_tasks_count = 0, current_time = 0;
    for (const auto &it: tasks_list) {
        if (exactly_tasks_count > it.b) continue;
        if (current_tasks_count >= exactly_tasks_count) break;
        if (current_time + it.a <= T) {
            ++current_tasks_count;
            current_time += it.a;
            result_tasks_ids.push_back(it.id);
        } else { break; }
    }
}

std::uint32_t
MaxResult(std::uint32_t T, const std::list<Task> &start_tasks_list, std::list<std::uint32_t> &result_tasks_ids) {
    std::list<Task> tasks_list = start_tasks_list;
    std::uint32_t max_result = 0, for_max_exactly_tasks_count = 1;
    for (std::uint32_t cur_tasks_count = 1; cur_tasks_count <= tasks_list.size(); ++cur_tasks_count)
        ExactlyTasksCountMaxResult(cur_tasks_count, T, tasks_list, for_max_exactly_tasks_count, max_result);
    GetTasksIds(for_max_exactly_tasks_count, T, start_tasks_list, result_tasks_ids);
    return max_result;
}

int main() {
    std::uint32_t k, T;
    std::cin >> k >> T;
    std::vector<Task> tasks(k);
    for (std::uint32_t i = 0; i < k; ++i) {
        tasks[i].id = i;
        std::cin >> tasks[i].b >> tasks[i].a;
    }
    std::sort(tasks.begin(), tasks.end());
    std::list<Task> tasks_list(tasks.begin(), tasks.end());

    std::list<std::uint32_t> result_tasks_ids;
    std::uint32_t max_result = MaxResult(T, tasks_list, result_tasks_ids);
    std::cout << max_result << std::endl;
    std::cout << result_tasks_ids.size() << std::endl;
    for (const auto &t_id: result_tasks_ids) std::cout << t_id + 1 << " ";
    return 0;
}
