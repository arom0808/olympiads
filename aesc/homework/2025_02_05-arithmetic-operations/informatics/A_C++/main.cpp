#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int type = 0, value = 0;

    Node() = default;

    Node(int type, int value): type(type), value(value) {
    }
};

// type:
//       -1 - end of input
//       0 - value
//       1 - operation:
//          value:
//              0: +
//              1: -
//              2: *


Node read_node() {
    char pc, c;
    cin.get(pc);
    if (cin.eof()) return {-1, 0};
    cin.get(c);
    if (pc == '+') return {1, 0};
    if (pc == '-') return {1, 1};
    if (pc == '*') return {1, 2};
    int res = pc - '0';
    while (c != ' ' && !cin.eof()) {
        pc = c, cin.get(c);
        res = res * 10 + pc - '0';
    }
    return {0, res};
}

void solve() {
    vector<int> st;
    for (auto node = read_node(); node.type != -1; node = read_node()) {
        if (node.type == 0) {
            st.push_back(node.value);
            continue;
        }
        int val;
        if (node.value == 0) val = st[st.size() - 2] + st.back();
        else if (node.value == 1) val = st[st.size() - 2] - st.back();
        else val = st[st.size() - 2] * st.back();
        st.pop_back(), st.pop_back();
        st.push_back(val);
    }
    cout << st.front();
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
