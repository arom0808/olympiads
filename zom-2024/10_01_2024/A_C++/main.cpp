#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string str;
    cin >> str;
    for (uint32_t i = 1; i + 1 < str.size(); ++i) {
        if ((str[i] <= str[0] && str[i] <= str[i + 1]) ||
            ((str[i] > str[0] || (str[i] == str[0] && i == 1)) &&
             (str[i] > str[i + 1] || (str[i] == str[i + 1] && i + 2 == str.size())))) {
            cout << str.substr(0, i) << " " << str.substr(i, 1) << " " << str.substr(i + 1);
            return 0;
        }
    }
    cout << ":(";
    return 0;
}


//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//pair<uint32_t, uint32_t> sol(const string &str) {
//    vector<vector<uint32_t>> positions(26);
//    for (auto &v: positions) v.reserve(str.size());
//    for (uint32_t i = 0; i < str.size(); ++i) positions[str[i]].push_back(i);
//    for (char s_c = 0; s_c <= str.front(); ++s_c) {
//        for (auto sec_start: positions[s_c]) {
//            if (sec_start == 0) continue;
//            uint32_t max_end = str.size() - 1;
//            if (s_c == str.front()) {
//                bool eq = true;
//                for (uint32_t i = 0; i < sec_start && sec_start + i < str.size(); ++i) {
//                    if (str[i] == str[sec_start + i]) continue;
//                    if (str[i] < str[sec_start + i]) max_end = min(sec_start + i, max_end), eq = false;
//                    else if (str[i] > str[sec_start + i]) eq = false;
//                    break;
//                }
//                if (eq) max_end = min(sec_start * 2, max_end);
//            }
//            if (sec_start + 1 > max_end) continue;
//            for (char t_c = s_c; t_c < 26; ++t_c) {
//                uint32_t t_s_i = distance(positions[t_c].begin(),
//                                          upper_bound(positions[t_c].begin(), positions[t_c].end(), sec_start));
//                for (; t_s_i < positions[t_c].size() && positions[t_c][t_s_i] <= max_end; ++t_s_i) {
//                    uint32_t third_start = positions[t_c][t_s_i];
//                    if (str[sec_start] == str[third_start]) {
//                        bool eq = true, lower = false;
//                        for (uint32_t i = 0; sec_start + i < third_start && third_start + i < str.size(); ++i) {
//                            if (str[sec_start + i] == str[third_start + i]) continue;
//                            if (str[sec_start + i] < str[third_start + i]) lower = true, eq = false;
//                            else if (str[sec_start + i] > str[third_start + i]) eq = false;
//                            break;
//                        }
//                        if ((eq && third_start - sec_start <= str.size() - third_start) || lower) {
//                            return {sec_start, third_start};
//                        }
//                    } else {
//                        return {sec_start, third_start};
//                    }
//                }
//            }
//        }
//    }
//    for (char s_c = str.front(); s_c < 26; ++s_c) {
//        for (auto sec_start: positions[s_c]) {
//            if (sec_start == 0) continue;
//            uint32_t min_end = sec_start + 1, max_end = str.size() - 1;
//            if (s_c == str.front()) {
//                bool eq = true;
//                for (uint32_t i = 0; i < sec_start && sec_start + i < str.size(); ++i) {
//                    if (str[i] == str[sec_start + i]) continue;
//                    if (str[i] > str[sec_start + i]) max_end = min(sec_start + i, max_end), eq = false;
//                    else if (str[i] < str[sec_start + i]) min_end = max(sec_start + i + 1, min_end), eq = false;
//                    break;
//                }
//                if (eq) min_end = max(sec_start * 2, min_end);
//            }
//            if (min_end > max_end || min_end >= str.size()) continue;
//            for (char t_c = 0; t_c <= s_c; ++t_c) {
//                uint32_t t_s_i = distance(positions[t_c].begin(),
//                                          lower_bound(positions[t_c].begin(), positions[t_c].end(), min_end));
//                for (; t_s_i < positions[t_c].size() && positions[t_c][t_s_i] <= max_end; ++t_s_i) {
//                    uint32_t third_start = positions[t_c][t_s_i];
//                    if (str[sec_start] == str[third_start]) {
//                        bool eq = true, bigger = false;
//                        for (uint32_t i = 0; sec_start + i < third_start && third_start + i < str.size(); ++i) {
//                            if (str[sec_start + i] == str[third_start + i]) continue;
//                            if (str[sec_start + i] > str[third_start + i]) bigger = true, eq = false;
//                            else if (str[sec_start + i] < str[third_start + i]) eq = false;
//                            break;
//                        }
//                        if ((eq && third_start - sec_start >= str.size() - third_start) || bigger) {
//                            return {sec_start, third_start};
//                        }
//                    } else {
//                        return {sec_start, third_start};
//                    }
//                }
//            }
//        }
//    }
//    return {str.size(), str.size()};
//}
//
//int main() {
//    string str;
//    cin >> str;
//    for (auto &c: str) c -= 'a';
//    auto [sec_start, third_start] = sol(str);
//    if (sec_start == str.size() || third_start == str.size()) cout << ":(";
//    else {
//        for (auto &c: str) c += 'a';
//        cout << str.substr(0, sec_start) << " " << str.substr(sec_start, third_start - sec_start) << " "
//             << str.substr(third_start);
//    }
//    return 0;
//}
