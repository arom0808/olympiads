#include <iostream>
#include <map>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    map<string, uint32_t> alls;
    set<string> res;
    uint32_t n;
    cin >> n;
    string temp;
    for (uint32_t i = 0; i < n; ++i) {
        cin >> temp;
        auto it = alls.find(temp);
        if (it != alls.end()) {
            auto pp = temp.find('.');
            if (pp == string::npos) {
                temp.append("(");
                temp.append(to_string(it->second));
                temp.append(")");
                res.emplace(std::move(temp));
            } else {
                string toad = temp.substr(0, pp);
                toad.append("(");
                toad.append(to_string(it->second));
                toad.append(")");
                toad.append(temp.substr(pp));
                res.emplace(std::move(toad));
            }
            ++it->second;
        } else {
            alls.emplace(temp, 1);
            res.emplace(std::move(temp));
        }
    }
    for (const auto &s: res) cout << s << "\n";
    return 0;
}
