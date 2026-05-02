#include <iostream>
#include <vector>

using namespace std;

int n, q;

int question(int a, int b, int c) {
    cout << "? " << a + 1 << " " << b + 1 << " " << c + 1 << "\n";
    cout.flush();
    int res;
    cin >> res;
    if (res == -1) exit(0);
    if (res == a + 1) return 0;
    if (res == b + 1) return 1;
    return 2;
}

struct Node {
    int out_left = -1, out_right = -1;
    int left = -1, right = -1;
    Node *left_child = nullptr, *center_child = nullptr, *right_child = nullptr;

    explicit Node(int out_left = -1, int out_right = -1): out_left(out_left), out_right(out_right) {
    }

    void add_val(int val) {
        if (left == -1) {
            left = val;
            return;
        }
        if (right == -1) {
            if (out_left != -1) {
                auto rr = question(out_left, left, val);
                if (rr == 1) right = val;
                else right = left, left = val;
            } else {
                auto rr = question(left, out_right, val);
                if (rr == 0) right = left, left = val;
                else right = val;
            }
            return;
        }
        auto rr = question(left, right, val);
        if (rr == 0) {
            if (left_child == nullptr) left_child = new Node(-1, left);
            left_child->add_val(val);
        } else if (rr == 1) {
            if (right_child == nullptr) right_child = new Node(right, -1);
            right_child->add_val(val);
        } else {
            if (center_child == nullptr) center_child = new Node(left, right);
            center_child->add_val(val);
        }
    }

    void append_to_vec(vector<int> &vec) {
        if (left_child != nullptr) left_child->append_to_vec(vec);
        if (left != -1) vec.push_back(left);
        if (center_child != nullptr) center_child->append_to_vec(vec);
        if (right != -1) vec.push_back(right);
        if (right_child != nullptr) right_child->append_to_vec(vec);
    }
};

Node *build_from_vec(const vector<int> &vec, int from, int to, int out_left, int out_right) {
    if (from == to) return nullptr;
    Node *res = new Node(out_left, out_right);
    if (from + 1 == to) {
        res->left = vec[from];
        return res;
    }
    if (from + 2 == to) {
        res->left = vec[from], res->right = vec[from + 1];
        return res;
    }
    int l_id = (to - from) / 3, r_id = l_id * 2;
    res->left = vec[l_id], res->right = vec[r_id];
    res->left_child = build_from_vec(vec, from, l_id, -1, vec[l_id]);
    res->center_child = build_from_vec(vec, l_id + 1, r_id, vec[l_id], vec[r_id]);
    res->right_child = build_from_vec(vec, r_id + 1, to, vec[r_id], -1);
    return res;
}

int main() {
    cin >> n >> q;
    if (n == 0) {
        cout << "! \n";
        return 0;
    }
    if (n == 1) {
        cout << "! 1\n";
        return 0;
    }
    if (n <= 2) {
        cout << "! 1 2\n";
        return 0;
    }
    vector<int> vec{0, 1};
    Node *root = build_from_vec(vec, 0, vec.size(), -1, -1);
    for (int i = 2; i < n; ++i) {
        root->add_val(i);
    }
    vec.clear();
    root->append_to_vec(vec);
    cout << "! ";
    for (auto el: vec) cout << el + 1 << " ";
    cout << "\n";
    return 0;
}
