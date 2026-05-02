#include <iostream>

using namespace std;

namespace MT {
    struct Node {
        int val = 0;
        Node *l = nullptr, *r = nullptr;
    };

    Node *root = nullptr;

    bool _insert(Node *&v, int val) {
        if (!v) {
            v = new Node(val);
            return true;
        }
        if (v->val == val) return false;
        if (val < v->val) return _insert(v->l, val);
        return _insert(v->r, val);
    }

    bool insert(int val) {
        return _insert(root, val);
    }

    Node *&_max_val(Node *&v) {
        if (v->r) return _max_val(v->r);
        return v;
    }

    bool _erase(Node *&v, int val) {
        if (!v) return false;
        if (v->val == val) {
            Node *tp = v;
            if (!v->l) v = v->r;
            else if (!v->r) v = v->l;
            else {
                Node *&tss = _max_val(v->l);
                tp = tss;
                tss = nullptr;
                swap(v->val, tp->val);
            }
            delete tp;
            return true;
        }
        if (val < v->val) return _erase(v->l, val);
        return _erase(v->r, val);
    }

    bool erase(int val) {
        return _erase(root, val);
    }

    bool _contains(Node *v, int val) {
        if (!v) return false;
        if (v->val == val) return true;
        if (val < v->val) return _contains(v->l, val);
        return _contains(v->r, val);
    }

    bool contains(int val) {
        return _contains(root, val);
    }

    void _print(Node *v, int level) {
        if (!v) return;
        _print(v->l, level + 1);
        for (int i = 0; i < level; ++i) cout << ".";
        cout << v->val << "\n";
        _print(v->r, level + 1);
    }

    void print() {
        _print(root, 0);
    }
}

void solve() {
    string ts;
    int tv;
    while (true) {
        cin >> ts;
        if (cin.fail()) break;
        if (ts == "ADD") {
            cin >> tv;
            if (MT::insert(tv)) cout << "DONE\n";
            else cout << "ALREADY\n";
        } else if (ts == "DELETE") {
            cin >> tv;
            if (MT::erase(tv)) cout << "DONE\n";
            else cout << "CANNOT\n";
        } else if (ts == "SEARCH") {
            cin >> tv;
            if (MT::contains(tv)) cout << "YES\n";
            else cout << "NO\n";
        } else {
            MT::print();
        }
    }
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
