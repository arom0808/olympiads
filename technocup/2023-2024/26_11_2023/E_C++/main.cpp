#include <iostream>
#include <vector>
#include <map>

using namespace std;

const uint64_t inf = 1e18;

struct NeedMark {
    uint64_t three = 0, four = 0, five = 0;
};

uint64_t get_mark(uint64_t solved, const NeedMark &nm) {
    if (solved >= nm.five) return 5;
    if (solved >= nm.four) return 4;
    if (solved >= nm.three) return 3;
    return 2;
}

uint64_t my_stoi(const string &str, uint64_t from, uint64_t end) {
    uint64_t res = 0;
    for (uint64_t i = from; i < end && i < str.size(); ++i) {
        res *= 10;
        res += str[i] - '0';
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    uint64_t n, g, d;
    cin >> n >> g >> d;
    vector<uint64_t> solved_by_student(n, 0);
    vector<NeedMark> need_marks(n);
    vector<string> names(n);
    vector<vector<uint64_t>> group_of_student_by_day(n, vector<uint64_t>(d, 0));
    vector<vector<NeedMark>> otsechka_for_group_by_day(g, vector<NeedMark>(d));
    for (uint64_t i = 0, id; i < n; ++i) {
        cin >> id >> names[i];
        for (auto &ff: group_of_student_by_day[i]) {
            cin >> ff;
            --ff;
        }
    }
    string temp_tasks;
    vector<pair<uint64_t, uint64_t>> temp_day_and_task_id;
    for (uint64_t i = 0; i < g; ++i) {
        for (auto &[three, four, five]: otsechka_for_group_by_day[i]) cin >> three >> four >> five;
        getline(cin, temp_tasks);
        getline(cin, temp_tasks);
        temp_day_and_task_id.clear();
        temp_day_and_task_id.reserve(14 * d);
        for (uint64_t start = 0;;) {
            auto end = temp_tasks.find(' ', start);
            uint64_t task_id = temp_tasks[start] - 'A';
            uint64_t day_id = my_stoi(temp_tasks, start + 1, end) - 1;
            temp_day_and_task_id.emplace_back(day_id, task_id);
            if (end == string::npos) break;
            else start = end + 1;
        }
        for (uint64_t j = 0, id; j < n; ++j) {
            cin >> id;
            char c;
            for (auto [day_id, task_id]: temp_day_and_task_id) {
                cin >> c;
                if (c == '+' && group_of_student_by_day[j][day_id] == i) ++solved_by_student[j];
            }
        }
    }
    for (uint64_t i = 0; i < n; ++i) {
        for (uint64_t day = 0; day < d; ++day) {
            need_marks[i].three += otsechka_for_group_by_day[group_of_student_by_day[i][day]][day].three;
            need_marks[i].four += otsechka_for_group_by_day[group_of_student_by_day[i][day]][day].four;
            need_marks[i].five += otsechka_for_group_by_day[group_of_student_by_day[i][day]][day].five;
        }
    }
    uint64_t q;
    cin >> q;
    string temp_req_str;
    for (uint64_t _ = 0; _ < q; ++_) {
        cin >> temp_req_str;
        uint64_t student_id = inf;
        if ('0' <= temp_req_str[0] && temp_req_str[0] <= '9') {
            student_id = std::stoi(temp_req_str) - 1;
        } else {
            for (uint64_t i = 0; i < n; ++i) {
                if (names[i].size() != temp_req_str.size()) continue;
                uint64_t changes_cnt = 0;
                for (uint64_t j = 0; j < temp_req_str.size() && changes_cnt < 3; ++j) {
                    if (j + 2 < temp_req_str.size()) {
                        
                    }
                    if (names[i][j] == temp_req_str[j]) continue;
                    else {
                        if (j + 1 >= temp_req_str.size()) changes_cnt += 3;
                        else if (names[i][j] == temp_req_str[j + 1] && names[i][j + 1] == temp_req_str[j]) {
                            ++changes_cnt;
                            ++j;
                        } else {
                            if (j + 2 < temp_req_str.size() &&
                                ((names[i][j] == temp_req_str[j + 2] && names[i][j + 1] == temp_req_str[j] &&
                                  names[i][j + 2] == temp_req_str[j + 1]) ||
                                 (names[i][j] == temp_req_str[j + 1] && names[i][j + 1] == temp_req_str[j + 2] &&
                                  names[i][j + 2] == temp_req_str[j]))) {
                                changes_cnt += 2;
                                j += 2;
                            } else changes_cnt += 3;
                        }
                    }
                }
                if (changes_cnt <= 2) {
                    student_id = i;
                    break;
                }
            }
        }
        if (student_id == inf) cout << "Not Found\n";
        else cout << get_mark(solved_by_student[student_id], need_marks[student_id]) << "\n";
    }
    return 0;
}
