#include <iostream>
#include <vector>

using namespace std;

struct Node {
    char type = 0;
    int value = 0;

    Node() = default;

    Node(char type, int value): type(type), value(value) {
    }
};

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_op(char c) {
    return c == '+' || c == '-' || c == '*';
}

bool is_type_op(char c) {
    return c == '+' || c == '-' || c == '*' || c == '_';
}

string s;
int priors[256];

pair<int, int> read_number(int pos) {
    int res = 0;
    for (; is_digit(s[pos]); ++pos) res = res * 10 + s[pos] - '0';
    return {res, pos};
}

int skip_spaces(int pos) {
    while (s[pos] == ' ') ++pos;
    return pos;
}

bool check() {
    for (int i = 0; i + 1 < s.size(); ++i) if (s[i] == '#') return false;
    int state = 0, balance = 0;
    for (int i = 0; i <= s.size(); ++i) {
        if (state == 0) {
            if (s[i] == '(') ++balance;
            else if (is_digit(s[i])) i = read_number(i).second - 1, state = 1;
            else if (s[i] != ' ') return false;
        } else if (state == 1) {
            if (is_op(s[i])) state = 0;
            else if (s[i] == ')') {
                if (--balance < 0) return false;
            } else if (s[i] == '#') state = 2;
            else if (s[i] != ' ') return false;
        } else {
            if (balance || i != s.size()) return false;
        }
    }
    return true;
}

vector<Node> convert_to_postfix() {
    vector<Node> res;
    vector<Node> st;
    for (int i = 0; i < s.size(); ++i) {
        if (is_digit(s[i])) {
            auto [num, ni] = read_number(i);
            i = ni - 1;
            res.emplace_back('d', num);
        } else if (s[i] == '(') st.emplace_back('(', 0);
        else if (is_op(s[i])) {
            int cur_prior = priors[s[i]];
            while (!st.empty() && is_type_op(st.back().type) && priors[st.back().type] >= cur_prior) {
                res.push_back(st.back());
                st.pop_back();
            }
            st.emplace_back(s[i], 0);
        } else if (s[i] == ')') {
            while (st.back().type != '(') {
                res.push_back(st.back());
                st.pop_back();
            }
            st.pop_back();
        } else if (s[i] == '#') {
            while (!st.empty()) {
                res.push_back(st.back());
                st.pop_back();
            }
        }
    }
    return res;
}

int calc_postfix(const vector<Node> &ex) {
    vector<int> st;
    for (auto [type,value]: ex) {
        if (type == 'd') st.push_back(value);
        else {
            int v2 = st.back();
            st.pop_back();
            int v1 = st.back();
            st.pop_back();
            if (type == '+') st.push_back(v1 + v2);
            else if (type == '-') st.push_back(v1 - v2);
            else if (type == '*') st.push_back(v1 * v2);
        }
    }
    return st.back();
}

void solve() {
    priors['-'] = priors['+'] = 0;
    priors['*'] = 1;
    priors['_'] = 2;
    std::getline(cin, s);
    s.push_back('#');
    if (!check()) {
        cout << "WRONG\n";
        return;
    }
    erase(s, ' ');
    cout << calc_postfix(convert_to_postfix()) << "\n";
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
