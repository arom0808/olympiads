#include <iostream>
#include <vector>

using namespace std;

struct Node {
    bool flag = false, type = false; // false - or, true - and
    Node *parent = nullptr;
    int32_t child_true_cnt = 0;
};

int32_t n, m, s;

bool one_child_true(Node *node) {
    if (node == nullptr) return true;
    ++node->child_true_cnt;
    if (node->flag || (node->type && node->child_true_cnt < 2)) return false;
    node->flag = true;
    return one_child_true(node->parent);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m >> s;
    vector g(m, vector<Node>(2 * n - 1));
    for (int i = 0; i < m; ++i) {
        for (int32_t p = 0, a, b, op; p + 1 < n; ++p) {
            cin >> a >> b >> op;
            g[i][n + p].type = op == 1;
            g[i][a - 1].parent = g[i][b - 1].parent = &g[i][n + p];
        }
    }
    vector table_nodes(n, vector<Node *>(m, nullptr));
    for (int i = 0; i < m; ++i) {
        for (int32_t j = 0, x; j < n; ++j) {
            cin >> x;
            table_nodes[j][x] = &g[i][j];
        }
    }
    int32_t true_cnt = 0;
    int32_t i = 0, j = 0;
    for (; i < n; ++i) {
        for (j = 0; j < m && true_cnt < s; ++j) true_cnt += one_child_true(table_nodes[i][j]->parent);
        if (true_cnt == s) break;
    }
    for (int32_t k = 0; k < i; ++k) cout << m << " ";
    if (i < n) cout << j << " ";
    for (int32_t k = i + 1; k < n; ++k) cout << "0 ";
    return 0;
}
