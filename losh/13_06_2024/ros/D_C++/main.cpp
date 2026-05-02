#include <iostream>
#include <vector>

using namespace std;


const int64_t mod = 2999;
int64_t n, k;
vector<int64_t> cs;
int64_t res[800000];
int64_t cnts[7];
int64_t facts[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40640, 362880};

void rec_sol(int64_t level, int64_t w, int64_t ost_cnt) {
    if (level >= n) {
        if (ost_cnt != 0) return;
        int64_t r = facts[k];
        for (auto cnt: cnts) r /= facts[cnt];
        res[w] = (res[w] + r) % mod;
        return;
    }
    for (cnts[level] = 0; cnts[level] <= ost_cnt; ++cnts[level])
        rec_sol(level + 1, w + cs[level] * cnts[level], ost_cnt - cnts[level]);
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    if (n <= 7 && k <= 7) {
        cs.resize(n);
        for (auto &c: cs) cin >> c;
        rec_sol(0, 0, k);
        int64_t q;
        cin >> q;
        for (int64_t i = 0, w; i < q; ++i) {
            cin >> w;
            if (w < 800000) cout << res[w] << "\n";
            else cout << "0\n";
        }
    }
    return 0;
}
