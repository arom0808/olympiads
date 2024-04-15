#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    string str, temp_str;
    std::getline(cin, str);
    int32_t dict_size;
    std::getline(cin, temp_str);
    dict_size = stoi(temp_str);
    vector<string> dict(dict_size);
    for (auto &s: dict) std::getline(cin, s);
    vector<int32_t> dp(str.size() + 1, -1);
    dp[0] = 0;
    for (int32_t i = 0; i < str.size(); ++i)
        if (dp[i] != -1)
            for (int32_t j = 0; j < dict.size(); ++j)
                if (dict[j].size() + i <= str.size() && equal(dict[j].begin(), dict[j].end(), next(str.begin(), i)))
                    dp[i + dict[j].size()] = j;
    vector<int32_t> ids;
    ids.reserve(str.size());
    for (int32_t i = str.size(); i > 0; i -= dict[dp[i]].size()) ids.push_back(dp[i]);
    for (auto it = ids.rbegin(); it != ids.rend(); ++it) cout << dict[*it] << " ";
    cout << "\n";
    return 0;
}
