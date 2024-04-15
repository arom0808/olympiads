#include <iostream>
#include <random>
#include <vector>

using namespace std;

const uint64_t k = 31, mod = 1e9 + 7;
vector<uint64_t> p;

uint64_t hash_substr(int32_t l, int32_t r, const vector<uint64_t> &h) {
    return (mod + h[r + 1] - h[l]) % mod * p[h.size() - l - 1] % mod;
}

struct Req {
    int32_t a, b, c, d;
};

void my_sol(const string &s, const vector<Req> &reqs, vector<bool> &ans) {
    ans.resize(reqs.size(), false);
    vector<uint64_t> h(s.size() + 1, 0);
    for (int32_t i = 0; i < s.size(); ++i) h[i + 1] = (h[i] + p[i] * (s[i] - 'a' + 1)) % mod;
    for (int32_t i = 0; i < reqs.size(); ++i) {
        auto [a, b, c, d] = reqs[i];
        ans[i] = b - a == d - c && hash_substr(a - 1, b - 1, h) == hash_substr(c - 1, d - 1, h);
    }
}

void good_sol(const string &s, const vector<Req> &reqs, vector<bool> &ans) {
    ans.resize(reqs.size(), false);
    for (int32_t _ = 0; _ < reqs.size(); ++_) {
        auto [a, b, c, d] = reqs[_];
        bool good = b - a == d - c;
        for (int32_t i = 0; good && i <= b - a; ++i) if (s[a + i - 1] != s[c + i - 1]) good = false;
        ans[_] = good;
    }
}

namespace Test {
    random_device dev;
    mt19937 rng(dev());

    int32_t randint(int32_t a, int32_t b) { return uniform_int_distribution(a, b)(rng); }

    pair<string, vector<Req>> gen() {
        int32_t n = randint(1, 10), m = randint(1, 1);
        string s(n, 'a');
        for (auto &c: s) c += randint(0, 25);
        vector<Req> reqs(m);
        for (auto &[a, b, c, d]: reqs)
            a = randint(1, n), b = randint(a, n), c = randint(1, n), d = randint(c, n);
        return {s, reqs};
    }

    void Test() {
        while (true) {
            auto [s, reqs] = gen();
            vector<bool> my_ans, good_ans;
            my_sol(s, reqs, my_ans);
            good_sol(s, reqs, good_ans);
            if (my_ans != good_ans) {
                cout << s << "\n" << reqs.size() << "\n";
                for (auto [a, b, c, d]: reqs) cout << a << " " << b << " " << c << " " << d << "\n";
                cout << "\nmy\n";
                for (auto a: my_ans) cout << (a ? "Yes\n" : "No\n");
                cout << "\ngood:\n";
                for (auto a: good_ans) cout << (a ? "Yes\n" : "No\n");
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    p.assign(1e5 + 1, 1);
    for (int32_t i = 1; i < p.size(); ++i) p[i] = p[i - 1] * k % mod;
//    Test::Test();

    string s;
    int32_t m;
    cin >> s >> m;
    vector<Req> reqs(m);
    for (auto &[a, b, c, d]: reqs) cin >> a >> b >> c >> d;
    vector<bool> ans;
    my_sol(s, reqs, ans);
    for (auto a: ans) cout << (a ? "Yes\n" : "No\n");
    return 0;
}