#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

struct Que {
    int32_t val = 0, id = 0;

    bool operator<(const Que &other) const {
        return val < other.val;
    }
};

namespace Bor {
    struct Node {
        Node *child[2] = {nullptr, nullptr};
        int32_t min_not_full_level = 0;
    };
    const int32_t max_bor_size = 1e6;
    Node nodes[max_bor_size];

    Node *root = nullptr;
    int32_t used_nodes = 0;

    void init() {
        root = &nodes[0];
        used_nodes = 1;
    }

    void update_node(Node *node) {
        if (node->child[0] == nullptr || node->child[1] == nullptr) node->min_not_full_level = 0;
        else node->min_not_full_level = min(node->child[0]->min_not_full_level, node->child[1]->min_not_full_level) + 1;
    }

    string nr = "";

    bool _try_add(Node *node, int32_t len) {
        if (len == 0) return true;
        if (len <= node->min_not_full_level) return false;
        if (node->child[0] == nullptr && node->child[1] == nullptr) {
            node->child[0] = &nodes[used_nodes++];
            nr += "0";
            _try_add(node->child[0], len - 1);
        } else if (node->child[0] == nullptr) {
            if (len - 1 > node->child[1]->min_not_full_level) {
                nr += "1";
                _try_add(node->child[1], len - 1);
            } else {
                node->child[0] = &nodes[used_nodes++];
                nr += "0";
                _try_add(node->child[0], len - 1);
            }
        } else if (node->child[1] == nullptr) {
            if (len - 1 > node->child[0]->min_not_full_level) {
                nr += "0";
                _try_add(node->child[0], len - 1);
            } else {
                node->child[1] = &nodes[used_nodes++];
                nr += "1";
                _try_add(node->child[1], len - 1);
            }
        } else {
            if (len - 1 > node->child[0]->min_not_full_level) {
                nr += "0";
                _try_add(node->child[0], len - 1);
            } else if (len - 1 > node->child[1]->min_not_full_level) {
                nr += "1";
                _try_add(node->child[1], len - 1);
            } else return false;
        }
        update_node(node);
        return true;
    }

    bool try_add(int32_t len) {
        nr = "";
        return _try_add(root, len);
    }
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n;
    cin >> n;
    vector<Que> ques(n);
    for (int32_t i = 0; i < n; ++i) cin >> ques[i].val, ques[i].id = i;
    sort(ques.rbegin(), ques.rend());
    vector<string> rs(n);
    Bor::init();
    for (auto [val, id]: ques) {
        if (Bor::try_add(val)) rs[id] = Bor::nr;
        else {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    for (auto &r: rs) cout << r << "\n";
    return 0;
}
