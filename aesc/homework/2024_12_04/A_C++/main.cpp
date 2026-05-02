#include <iostream>

using namespace std;

class List {
public:
    struct Node {
        int value;
        Node *prev = nullptr, *next = nullptr;

        explicit Node(int val = 0, Node *prev = nullptr, Node *next = nullptr): value(val), prev(prev), next(next) {
        }
    };

    Node *head = nullptr, *end = nullptr;

    void assign(int size) {
        Node *nodes = new Node[size];
        head = &nodes[0], end = &nodes[size - 1];
        for (int i = 0; i < size; ++i) {
            if (i + 1 < size) nodes[i].next = &nodes[i + 1];
            if (i > 0) nodes[i].prev = &nodes[i - 1];
        }
    }

    // [start, finish]
    void splice_to_end(List &from_list, Node *start, Node *finish) {
        if (start == nullptr || finish == nullptr) return;
        if (start->prev != nullptr) start->prev->next = finish->next;
        if (finish->next != nullptr) finish->next->prev = start->prev;
        if (from_list.head == start) from_list.head = finish->next;
        if (from_list.end == finish) from_list.end = start->prev;
        start->prev = end, finish->next = nullptr;
        if (end != nullptr) end->next = start;
        end = finish;
        if (head == nullptr) head = start;
    }
};

int n;

// [start, finish]
void my_quick_sort(List &cur_list) {
    if (cur_list.head == cur_list.end) return;
    List less_list, equal_list, greater_list;
    int val = cur_list.head->value;
    for (List::Node *node = cur_list.head, *next_node = cur_list.head->next;;) {
        if (node->value > val) greater_list.splice_to_end(cur_list, node, node);
        else if (node->value < val) less_list.splice_to_end(cur_list, node, node);
        else equal_list.splice_to_end(cur_list, node, node);
        if (cur_list.head == nullptr) break;
        node = next_node, next_node = node->next;
    }
    my_quick_sort(less_list);
    my_quick_sort(greater_list);
    cur_list.splice_to_end(less_list, less_list.head, less_list.end);
    cur_list.splice_to_end(equal_list, equal_list.head, equal_list.end);
    cur_list.splice_to_end(greater_list, greater_list.head, greater_list.end);
}

void solve() {
    cin >> n;
    List my_list;
    my_list.assign(n);
    for (List::Node *node = my_list.head; node != nullptr; node = node->next) cin >> node->value;
    my_quick_sort(my_list);
    for (List::Node *node = my_list.head; node != nullptr; node = node->next) cout << node->value << " ";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
