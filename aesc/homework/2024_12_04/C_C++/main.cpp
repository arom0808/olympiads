#include <iostream>

using namespace std;

using ll = long long;

template<typename T>
class List {
public:
    struct Node {
        T *value = nullptr;
        Node *prev = nullptr, *next = nullptr;

        explicit Node(T *val = nullptr, Node *prev = nullptr, Node *next = nullptr)
            : value(val), prev(prev), next(next) {
        }

        ~Node() {
            delete value;
        }
    };

    Node head_el, end_el;
    Node *head_ptr = &head_el, *end_ptr = &end_el;

    List() {
        head_ptr->next = end_ptr;
        end_ptr->prev = head_ptr;
    }

    ~List() {
        if (head_ptr->next == end_ptr) return;
        for (auto it = head_ptr->next->next; it != nullptr; ++it) delete it->prev;
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
        delete pos;
    }

    void insert(Node *pos, T el) {
        Node *new_node = new Node(el, pos->prev, pos);
        pos->prev->next = new_node;
        pos->prev = new_node;
    }
};

struct Monomial {
    ll k, p;

    explicit Monomial(ll k = 0, ll p = 0): k(k), p(p) {
    }
};

class Polynomial : List<Monomial> {
public:

};

void REM() {
    string nothing_str;
    std::getline(cin, nothing_str);
}

void READ() {
}

void PRINT() {
}

void DEL() {
}

void EQ() {
}

void DIFF() {
}

void VAL() {
}

void SUM() {
}

void MUL() {
}

void EXIT() {
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    string cmd;
    while (true) {
        cin >> cmd;
        if (cmd == "REM") REM();
        else if (cmd == "READ") READ();
        else if (cmd == "PRINT") PRINT();
        else if (cmd == "DEL") DEL();
        else if (cmd == "EQ") EQ();
        else if (cmd == "DIFF") DIFF();
        else if (cmd == "VAL") VAL();
        else if (cmd == "SUM") SUM();
        else if (cmd == "MUL") MUL();
        else {
            EXIT();
            break;
        }
    }
    return 0;
}
