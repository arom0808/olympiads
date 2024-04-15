#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize(3)
#pragma GCC optimize("O3")
#pragma GCC optimize("inline")

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Vertex {
    Vertex *parent;
    Vertex *to[2] = {nullptr, nullptr};
    bool is_terminal = false;
    int full_terminal_cnt = 0;

    explicit Vertex(Vertex *parent) : parent(parent) {}

    ~Vertex() {
        for (auto &t: to) delete t;
    }
};

Vertex *root = nullptr;

vector<int> num_str;
string coded;
vector<string> codes;

bool rec_sol(int i, int coded_i) {
    if (i == num_str.size() && coded_i == coded.size()) return true;
    if (i >= num_str.size() || coded_i >= coded.size()) return false;
    if (coded_i + codes[num_str[i]].size() > coded.size()) return false;
    if (codes[num_str[i]].empty()) {
        Vertex *v = root;
        for (int ci = 0; coded_i + ci < coded.size(); ++ci) {
            if (v->to[coded[coded_i + ci]] == nullptr) v->to[coded[coded_i + ci]] = new Vertex(v);
            ++v->full_terminal_cnt;
            v = v->to[coded[coded_i + ci]];
            if (v->is_terminal) break;
            if (v->full_terminal_cnt == 0) {
                ++v->full_terminal_cnt;
                v->is_terminal = true;
                codes[num_str[i]] = coded.substr(coded_i, ci + 1);
                if (rec_sol(i + 1, coded_i + ci + 1)) return true;
                codes[num_str[i]] = "";
                v->is_terminal = false;
                --v->full_terminal_cnt;
            }
        }
        for (v = v->parent; v != nullptr; v = v->parent) --v->full_terminal_cnt;
    } else {
        auto &code = codes[num_str[i]];
        for (int ci = 0; ci < code.size(); ++ci) if (coded[coded_i + ci] != code[ci]) return false;
        return rec_sol(i + 1, coded_i + code.size());
    }
    return false;
}

map<char, string> make_test(int test_id, const string &str, const string &tcoded) {
    map<char, int> temp_ids;
    num_str.assign(str.size(), 0);
    for (uint32_t i = 0; i < str.size(); ++i) {
        auto it = temp_ids.find(str[i]);
        if (it == temp_ids.end()) it = temp_ids.emplace(str[i], temp_ids.size()).first;
        num_str[i] = it->second;
    }
    codes.assign(temp_ids.size(), "");
    coded = tcoded;
    for (auto &c: coded) c = c - '0';
    delete root;
    root = new Vertex(nullptr);
    rec_sol(0, 0);
    map<char, string> res;
    for (auto [c, id]: temp_ids) {
        string tmp_str = codes[id];
        for (auto &cc: tmp_str) cc = '0' + cc;
        res.emplace(c, tmp_str);
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    string str, tcoded;
    for (uint32_t i = 0; i < t; ++i) {
        cin >> str >> tcoded;
        auto res = make_test(i, str, tcoded);
        for (auto [c, code]: res) cout << c << " " << code << "\n";
        cout << "\n";
        cout.flush();
    }
    return 0;
}
