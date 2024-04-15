#include <iostream>
#include <deque>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
    int32_t id = 0, parent = -1, mod = 0;
    deque<int32_t> childs;
    unordered_map<int32_t, int32_t> childs_pos;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int32_t n, m;
    cin >> n >> m;
    vector<Node> nodes(n);
    for (int32_t i = 0; i < n; ++i) nodes[i].id = i;
    string temp;
    for (int32_t _ = 0, d, d1, d2; _ < m; ++_) {
        cin >> temp;
        if (temp == "push_back") {
            cin >> d1 >> d2;
            --d1, --d2;
            nodes[d2].childs.push_back(d1);
            nodes[d1].parent = d2;
            nodes[d2].childs_pos.emplace(d1, static_cast<int32_t>(nodes[d2].childs.size()) - 1 - nodes[d2].mod);
        } else if (temp == "push_front") {
            cin >> d1 >> d2;
            --d1, --d2;
            nodes[d2].childs.push_front(d1);
            nodes[d1].parent = d2;
            ++nodes[d2].mod;
            nodes[d2].childs_pos.emplace(d1, -nodes[d2].mod);
        } else if (temp == "pop_back") {
            cin >> d;
            --d;
            int32_t td = nodes[d].childs.back();
            nodes[d].childs.pop_back();
            nodes[td].parent = -1;
            nodes[d].childs_pos.erase(td);
        } else if (temp == "pop_front") {
            cin >> d;
            --d;
            int32_t td = nodes[d].childs.front();
            nodes[d].childs.pop_front();
            nodes[td].parent = -1;
            nodes[d].childs_pos.erase(td);
            --nodes[d].mod;
        } else {
            cin >> d;
            int32_t res = 0;
            --d;
            while (nodes[d].parent != -1) {
                int32_t pos = nodes[nodes[d].parent].childs_pos[d] + nodes[nodes[d].parent].mod;
                res += min(pos + 1, static_cast<int32_t>(nodes[nodes[d].parent].childs.size()) - pos);
                d = nodes[d].parent;
            }
            cout << res << "\n";
        }
    }
    return 0;
}
