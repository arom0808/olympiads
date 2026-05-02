#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdint>

using namespace std;

const int32_t inf = 1e9;

namespace st {
    struct Node {
        int32_t min_val = 0;
        Node *l = nullptr, *r = nullptr;
    };

    const int32_t max_st_size = 1e7;

    Node tree[max_st_size];
    int32_t used_cnt = 0;
    int32_t size;

    inline int32_t node_min_val(Node *v) { return v ? v->min_val : inf; }

    void init(Node *&v, int32_t l, int32_t r) {
        if (l >= r) return;
        if (!v) v = &tree[used_cnt++];
        v->l = v->r = nullptr;
        if (r - l == 1) {
            v->min_val = inf;
        } else {
            init(v->l, l, (l + r) / 2);
            init(v->r, (l + r) / 2, r);
            v->min_val = std::min(node_min_val(v->l), node_min_val(v->r));
        }
    }

    Node *assign(int32_t n) {
        size = n;
        Node *root = nullptr;
        init(root, 0, size);
        return root;
    }


    Node *_set(Node *v, int32_t l, int32_t r, int32_t pos, int32_t val) {
        if (l >= r || r <= pos || pos < l) return v;
        Node *nv = &(tree[used_cnt++] = *v);
        if (r - l == 1) {
            nv->min_val = val;
        } else {
            nv->l = _set(v->l, l, (l + r) / 2, pos, val);
            nv->r = _set(v->r, (l + r) / 2, r, pos, val);
            nv->min_val = std::min(node_min_val(nv->l), node_min_val(nv->r));
        }
        return nv;
    }

    Node *set(Node *root, int32_t pos, int32_t val) {
        return _set(root, 0, size, pos, val);
    }

    int32_t _min_val(Node *v, int32_t l, int32_t r, int32_t a, int32_t b) {
        if (l >= r || r <= a || b <= l) return inf;
        if (a <= l && r <= b) return v->min_val;
        return std::min(_min_val(v->l, l, (l + r) / 2, a, b), _min_val(v->r, (l + r) / 2, r, a, b));
    }

    int32_t min_val(Node *root, int32_t a, int32_t b) {
        return _min_val(root, 0, size, a, b);
    }
}

struct Ticket {
    int32_t c = 0, a = 0, b = 0;
};

vector<Ticket> tickets;

struct Act {
    int32_t ticket_id = 0;
    bool type = false; // true - start of way, false - finish of way

    Act(int32_t ticket_id, bool type) : ticket_id(ticket_id), type(type) {}

    int32_t time() const {
        return type ? tickets[ticket_id].a : tickets[ticket_id].b;
    }

    bool operator<(const Act &other) const {
        if (time() != other.time()) return time() < other.time();
        return type < other.type;
    }
};

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int32_t n, s, m;
    cin >> n >> s >> m;
    vector<int32_t> cls;
    cls.reserve(m * 2);
    tickets.resize(m);
    for (auto &[c, a, b]: tickets) {
        cin >> c >> a >> b, --c, --a, --b;
        cls.push_back(a), cls.push_back(b);
    }
    sort(cls.begin(), cls.end());
    for (auto &[c, a, b]: tickets) {
        a = distance(cls.begin(), lower_bound(cls.begin(), cls.end(), a));
        b = distance(cls.begin(), lower_bound(cls.begin(), cls.end(), b));
    }
    vector<Act> acts;
    acts.reserve(m * 2);
    for (int32_t i = 0; i < m; ++i) acts.emplace_back(i, false), acts.emplace_back(i, true);
    sort(acts.begin(), acts.end());
    vector<int32_t> last_free_pos(s, 0);
    vector<set<int32_t>> free_ids(m * 2);
    if (m > 0) for (int32_t i = 0; i < s; ++i) free_ids[0].insert(i);
    vector<st::Node *> vers(m * 2);
    if (m > 0) vers[0] = st::assign(m * 2);
    for (int32_t t = 0, a_id = 0; t < m * 2; ++t) {
        if (t != 0) vers[t] = vers[t - 1];
        for (; a_id < m * 2 && acts[a_id].time() <= t; ++a_id) {
            auto act = acts[a_id];
            if (act.type) {
                int32_t &lfp = last_free_pos[tickets[act.ticket_id].c];
                free_ids[lfp].erase(tickets[act.ticket_id].c);
                vers[t] = st::set(vers[t], lfp, free_ids[lfp].empty() ? inf : *free_ids[lfp].begin());
                lfp = inf;
            } else {
                int32_t &lfp = last_free_pos[tickets[act.ticket_id].c];
                lfp = tickets[act.ticket_id].b;
                int32_t pv = free_ids[lfp].empty() ? inf : *free_ids[lfp].begin();
                free_ids[lfp].insert(tickets[act.ticket_id].c);
                if (tickets[act.ticket_id].c < pv)
                    vers[t] = st::set(vers[t], lfp, tickets[act.ticket_id].c);
            }
        }
    }
    int32_t q;
    cin >> q;
    int32_t p = 0;
    for (int32_t i = 0, x, y, a, b; i < q; ++i) {
        cin >> x >> y;
        a = x + p - 1, b = y + p - 1;
        int32_t pl = distance(cls.begin(), lower_bound(cls.begin(), cls.end(), b));
        if (pl == 0) {
            cout << (p = 1) << "\n";
            continue;
        }
        int32_t l_pos = distance(cls.begin(), upper_bound(cls.begin(), cls.end(), a)) - 1;
        if (l_pos < 0) l_pos = 0;
        p = st::min_val(vers[pl - 1], 0, l_pos + 1);
        if (p == inf) p = 0;
        else ++p;
        cout << p << "\n";
    }
    return 0;
}
