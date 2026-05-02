#include <iostream>
#include <vector>

using namespace std;

const int64_t maxn = 1e5, sqrtn = 320, alpha_size = 26, inf = 1e9;

namespace Bor {
    struct Node {
        int64_t k, ans;
        Node *child[alpha_size];
        vector<int64_t> pos;

        void init() {
            k = ans = inf;
            for (auto &ch: child) ch = nullptr;
        }
    };

    Node nodes[maxn * sqrtn / 100];
    int64_t nodes_used = 0;
    Node *root = nullptr;

    void init() {
        (root = &nodes[nodes_used++])->init();
    }

    void add_req_str(const string &s, int64_t k) {
        auto cn = root;
        for (auto c: s) {
            if (!cn->child[c]) (cn->child[c] = &nodes[nodes_used++])->init();
            cn = cn->child[c];
        }
        cn->k = k;
    }

    void add_s_str(const string &s, int64_t from, int64_t to) {
        auto cn = root;
        for (int64_t i = from; i < to; ++i) {
            if (!cn->child[s[i]]) return;
            cn = cn->child[s[i]];
            if (cn->k != inf) {
                cn->pos.push_back(from);
                if (cn->pos.size() >= cn->k)
                    cn->ans = std::min(cn->ans, cn->pos.back() - cn->pos[cn->pos.size() - cn->k] + i - from + 1);
            }
        }
    }

    int64_t get_ans(const string &s) {
        auto cn = root;
        for (auto c: s) cn = cn->child[c];
        return cn->ans;
    }
};

void z_function(const string &s, vector<int64_t> &z) {
    z.clear(), z.resize(s.size(), 0);
    int64_t l = 0, r = 0;
    for (int64_t i = 1; i < s.size(); ++i) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}

int main() {
    Bor::init();
    ios::sync_with_stdio(false), cin.tie(nullptr);
    string s;
    cin >> s;
    for (auto &c: s) c -= 'a';
    int64_t n;
    cin >> n;
    vector<pair<int64_t, string>> reqs(n);
    for (auto &[k, req]: reqs) {
        cin >> k >> req;
        for (auto &c: req) c -= 'a';
        if (req.size() <= sqrtn) Bor::add_req_str(req, k);
    }
    for (int64_t i = 0; i < s.size(); ++i) Bor::add_s_str(s, i, std::min<int64_t>(i + sqrtn, s.size()));
    string temp_s;
    vector<int64_t> z, pos;
    for (auto &[k, req]: reqs) {
        int64_t ans = inf;
        if (req.size() < sqrtn) ans = Bor::get_ans(req);
        else {
            temp_s.clear(), temp_s += req, temp_s += "#", temp_s += s;
            z_function(temp_s, z);
            pos.clear();
            for (int64_t i = req.size() + 1; i < z.size(); ++i) {
                if (z[i] == req.size()) pos.push_back(i);
                if (pos.size() >= k)
                    ans = std::min<int64_t>(ans, pos.back() - pos[pos.size() - k] + req.size());
            }
        }
        cout << (ans == inf ? -1 : ans) << "\n";
    }
    return 0;
}
