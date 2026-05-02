#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class List {
public:
    struct Node {
        T *value = nullptr;
        Node *prev = nullptr, *next = nullptr;

        explicit Node(T *val = nullptr, Node *prev = nullptr, Node *next = nullptr)
            : value(val), prev(prev), next(next) {
        }
    };

    Node head_el, end_el;
    Node *head_ptr = &head_el, *end_ptr = &end_el;

    List() {
        head_ptr->next = end_ptr;
        end_ptr->prev = head_ptr;
    }

    void push_back(T el) {
        Node *new_node = new Node(new T(el), end_ptr->prev, end_ptr);
        end_ptr->prev->next = new_node;
        end_ptr->prev = new_node;
    }

    Node *begin() {
        return head_ptr->next;
    }

    Node *end() {
        return end_ptr;
    }

    void splice(Node *pos, Node *start, Node *finish) {
        if (start == finish) return;
        finish = finish->prev;
        start->prev->next = finish->next;
        finish->next->prev = start->prev;
        start->prev = pos->prev;
        finish->next = pos;
        start->prev->next = start;
        finish->next->prev = finish;
    }

    void erase(Node *pos) {
        if (pos == end()) return;
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        delete pos->value;
        delete pos;
    }

    void insert(Node *pos, T el) {
        Node *new_node = new Node(el, pos->prev, pos);
        pos->prev->next = new_node;
        pos->prev = new_node;
    }
};

struct Chip {
    int type, pos, size;

    explicit Chip(int type, int pos, int size): type(type), pos(pos), size(size) {
    }
};

using LCit = List<Chip>::Node *;

int n, k;
List<Chip> chip_list;

void condensate(int first_cnt = 1e9) {
    int cnt = 0;
    for (LCit it = chip_list.begin(); it->next != chip_list.end() && cnt < first_cnt; ++cnt) {
        if (it->value->type == it->next->value->type) {
            it->value->size += it->next->value->size;
            chip_list.erase(it->next);
        } else it = it->next;
    }
}

void swap_to_nearby_els(List<Chip>::Node *it) {
    swap(it->value, it->next->value);
    swap(it->value->pos, it->next->value->pos);
    it->next->value->pos = it->value->pos + it->value->size;
}

void solve() {
    cin >> n >> k;
    for (int i = 0, t; i < n; ++i) {
        cin >> t;
        chip_list.push_back(Chip(t, i, 1));
    }
    condensate();
    vector<int> ops;
    while (chip_list.begin()->next != chip_list.end() && chip_list.begin()->next->next != chip_list.end()) {
        bool first_type = chip_list.begin()->value->type;
        auto it = chip_list.begin();
        ops.clear();
        while (it != chip_list.end() && it->next != chip_list.end() && ops.size() < k) {
            if (first_type != it->value->type) {
                ops.push_back(it->value->pos);
                swap_to_nearby_els(it);
            } else if (it->next->next != chip_list.end()) {
                ops.push_back(it->next->value->pos);
                swap_to_nearby_els(it->next);
            }
            first_type = !first_type;
            for (int i = 0; i < 3; ++i) if (it != chip_list.end()) it = it->next;
        }
        condensate((ops.size() + 1) * 3);
        cout << ops.size() << " ";
        for (auto el: ops) cout << el + 1 << " ";
        cout << "\n";
    }
    cout << "0\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    freopen("fishes.in", "r", stdin);
    freopen("fishes.out", "w", stdout);
#endif
    solve();
    return 0;
}
