#include <iostream>
#include <vector>
#include <list>
#include <set>

class Student {
public:
    std::set<std::uint32_t> friends;
};

using Students = std::vector<Student>;

inline std::uint32_t DecrementStudentId(const std::uint32_t &student_id, const std::uint32_t &friendship_size) {
    if (student_id > 0) return student_id - 1;
    return friendship_size - 1;
}

inline std::uint32_t IncrementStudentId(const std::uint32_t &student_id, const std::uint32_t &friendship_size) {
    if (student_id < friendship_size - 1) return student_id + 1;
    return 0;
}

void EnableNeighbors(Students &students, std::uint32_t m) {
    auto DoFunction = [&students](std::uint32_t student_id, std::uint32_t cur_student_id) {
        students[student_id].friends.insert(cur_student_id);
        students[cur_student_id].friends.insert(student_id);
    };
    for (std::uint32_t student_id = 0; student_id < students.size(); ++student_id) {
        for (std::uint32_t i = 0, cur_student_id = DecrementStudentId(student_id, students.size());
             i < m; ++i, cur_student_id = DecrementStudentId(cur_student_id, students.size())) {
            DoFunction(student_id, cur_student_id);
        }
        for (std::uint32_t i = 0, cur_student_id = IncrementStudentId(student_id, students.size());
             i < m; ++i, cur_student_id = IncrementStudentId(cur_student_id, students.size())) {
            DoFunction(student_id, cur_student_id);
        }
    }
}

std::uint32_t
GetMinimalDistanceBetweenTwoStudents(const Students &students, std::uint32_t first_id, std::uint32_t second_id) {
    std::list<std::uint32_t> leafs{first_id}, temp_new_leafs;
    std::vector<bool> is_visited(students.size(), false);
    is_visited[first_id] = true;
    bool has_been_sol_found = false;
    std::uint32_t result = 0;
    while (!leafs.empty()) {
        ++result;
        for (const auto &leaf: leafs) {
            for (const auto &cur_second_id: students[leaf].friends) {
                if (is_visited[cur_second_id]) continue;
                is_visited[cur_second_id] = true;
                if (cur_second_id == second_id) {
                    has_been_sol_found = true;
                    break;
                }
                temp_new_leafs.push_back(cur_second_id);
            }
            if (has_been_sol_found) break;
        }
        if (has_been_sol_found) break;
        else {
            leafs.clear();
            leafs.merge(temp_new_leafs);
        }
    }
    if (has_been_sol_found) return result - 1;
    return students.size();
}

std::uint32_t GetGlobalMinimalDistance(const Students &students) {
    std::uint32_t result = 0, temp_res;
    for (std::uint32_t i = 0; i < students.size() - 1; ++i) {
        for (std::uint32_t j = i + 1; j < students.size(); ++j) {
            temp_res = GetMinimalDistanceBetweenTwoStudents(students, i, j);
            if (temp_res > result) result = temp_res;
        }
    }
    return result;
}

int main() {
    std::uint32_t n, m, K;
    std::cin >> n >> m >> K;
    Students students(n);
    EnableNeighbors(students, m);
    std::vector<std::uint32_t> results(K + 1);
    results[0] = GetGlobalMinimalDistance(students);
    bool temp_b;
    std::uint32_t temp_x, temp_y;
    for (std::uint32_t i = 0; i < K; ++i) {
        std::cin >> temp_b >> temp_x >> temp_y;
        if (temp_b) {
            students[temp_x - 1].friends.insert(temp_y - 1);
            students[temp_y - 1].friends.insert(temp_x - 1);
        } else {
            students[temp_x - 1].friends.erase(temp_y - 1);
            students[temp_y - 1].friends.erase(temp_x - 1);
        }
        results[i + 1] = GetGlobalMinimalDistance(students);
    }
    for (const auto &r: results) {
        std::cout << r << "\n";
    }
    return 0;
}




//class PathsNode {
//public:
//    std::uint32_t student_id = 0;
//    PathsNode *parent = nullptr;
//    std::list<PathsNode *> childs;
//
//    explicit PathsNode() = default;
//
//    explicit PathsNode(std::uint32_t student_id) : student_id(student_id) {}
//
//    explicit PathsNode(PathsNode *parent) : parent(parent) {}
//
//    explicit PathsNode(std::uint32_t student_id, PathsNode *parent) : student_id(student_id), parent(parent) {}
//
//    ~PathsNode() {
//        for (auto &&child_ptr: childs) delete child_ptr;
//    }
//};
//
//template<typename T>
//class Arr2d : public std::vector<std::vector<T>> {
//public:
//    T &Get(std::uint32_t x, std::uint32_t y) {
//        return (*this)[std::max(x, y)][std::min(x, y)];
//    }
//
//    [[nodiscard]] const T &Get(std::uint32_t x, std::uint32_t y) const {
//        return (*this)[std::max(x, y)][std::min(x, y)];
//    }
//
//    void Set(std::uint32_t x, std::uint32_t y, const T &value) {
//        (*this)[std::max(x, y)][std::min(x, y)] = value;
//    }
//
//    explicit Arr2d(std::uint32_t n) : std::vector<std::vector<T>>(n) {
//        for (std::uint32_t i = 0; i < n; ++i) (*this)[i].resize(i + 1);
//    }
//
//    explicit Arr2d(std::uint32_t n, const T &default_value) : std::vector<std::vector<T>>(n) {
//        for (std::uint32_t i = 0; i < n; ++i) (*this)[i].resize(i + 1, default_value);
//    }
//};