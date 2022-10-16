#include <iostream>
#include <vector>

bool VisitPair(std::uint32_t pair_id, const std::vector<std::pair<std::uint32_t, std::uint32_t>> &student_pairs,
               std::vector<bool> &is_pair_visited, std::vector<std::uint32_t> &students) {
    is_pair_visited[pair_id] = true;
    if (students[student_pairs[pair_id].first] == 0) {
        students[student_pairs[pair_id].first] = 1;
        students[student_pairs[pair_id].second] = 2;
    }
    for (std::uint32_t i = 0; i < student_pairs.size(); ++i) {
        if (student_pairs[i].first == student_pairs[pair_id].first) {
            if (students[student_pairs[i].first] == students[student_pairs[pair_id].second])
                return false;
            students[student_pairs[i].first] = students[student_pairs[pair_id].first];
            students[student_pairs[i].second] = students[student_pairs[pair_id].second];
        }
        if (student_pairs[i].first == student_pairs[pair_id].second) {
            if (students[student_pairs[i].first] == students[student_pairs[pair_id].first])
                return false;
            students[student_pairs[i].first] = students[student_pairs[pair_id].second];
            students[student_pairs[i].second] = students[student_pairs[pair_id].first];
        }
        if (student_pairs[i].second == student_pairs[pair_id].first) {
            if (students[student_pairs[i].second] == students[student_pairs[pair_id].second])
                return false;
            students[student_pairs[i].first] = students[student_pairs[pair_id].second];
            students[student_pairs[i].second] = students[student_pairs[pair_id].first];
        }
        if (student_pairs[i].second == student_pairs[pair_id].second) {
            if (students[student_pairs[i].second] == students[student_pairs[pair_id].first])
                return false;
            students[student_pairs[i].first] = students[student_pairs[pair_id].first];
            students[student_pairs[i].second] = students[student_pairs[pair_id].second];
        }
        if (is_pair_visited[i]) continue;
        bool tmp_res = VisitPair(i, student_pairs, is_pair_visited, students);
        if (!tmp_res) return false;
    }
    return true;
}

int main() {
    std::uint32_t N, M;
    std::cin >> N >> M;
    std::vector<std::uint32_t> students(N, 0);
    std::vector<std::pair<std::uint32_t, std::uint32_t>> student_pairs(M);
    for (auto &&student_pair: student_pairs) {
        std::cin >> student_pair.first >> student_pair.second;
        --student_pair.first;
        --student_pair.second;
    }
    std::vector<bool> is_pair_visited(M, false);
    for (std::uint32_t i = 0; i < M; ++i) {
        if (is_pair_visited[i]) continue;
        bool tmp_res = VisitPair(i, student_pairs, is_pair_visited, students);
        if (!tmp_res) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}
