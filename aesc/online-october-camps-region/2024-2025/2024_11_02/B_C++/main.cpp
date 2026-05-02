#include <algorithm>
#include <iostream>
#include <vector>


using ll = int64_t;
using namespace std;

constexpr int maxn = 1e5;

pair<int, int> fld(int x) {
    int last_d = x % 10, first_d = last_d;
    while (x) {
        first_d = x % 10;
        x /= 10;
    }
    return make_pair(first_d, last_d);
}

int swc[3][10];
int fwc[3][10];
int sfwc[3][10][10];
int arrs[3][maxn];
int cnts[3];
int temp_cnts[3];
int el_cnts[3][maxn];


int main() {
    freopen("input.txt", "r",stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> cnts[0] >> cnts[1] >> cnts[2];
    vector<int> fzn;
    fzn.reserve(cnts[0] + cnts[1] + cnts[2]);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < cnts[i]; ++j) {
            cin >> arrs[i][j];
            fzn.push_back(arrs[i][j]);
            auto fff = fld(arrs[i][j]);
            auto fd = fff.first, ld = fff.second;
            ++swc[i][fd];
            ++fwc[i][ld];
            ++sfwc[i][fd][ld];
        }
    }
    sort(fzn.begin(), fzn.end());
    fzn.erase(unique(fzn.begin(), fzn.end()), fzn.end());
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < cnts[i]; ++j)
            arrs[i][j] = static_cast<int>(lower_bound(fzn.begin(), fzn.end(), arrs[i][j]) - fzn.begin());
    for (int i = 0; i < 3; ++i) sort(begin(arrs[i]), next(begin(arrs[i]), cnts[i]));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < cnts[i]; ++j) {
            if (j != 0 && arrs[i][j - 1] == arrs[i][j]) ++el_cnts[i][temp_cnts[i] - 1];
            else el_cnts[i][temp_cnts[i]++] = 1;
        }
    }
    for (int i = 0; i < 3; ++i)
        cnts[i] = distance(begin(arrs[i]), unique(begin(arrs[i]), next(begin(arrs[i]), cnts[i])));
    ll ans = 0;
    for (int fd = 0; fd < 10; ++fd)
        for (int sd = 0; sd < 10; ++sd)
            ans += 1ll * fwc[0][fd] * sfwc[1][fd][sd] * swc[2][sd];
    for (int i = 0; i < 2; ++i) {
        for (int j = (i ? 2 : 1); j < 3; ++j) {
            int k = 3 - i - j;
            for (int nid = 0; nid < cnts[i]; ++nid) {
                int jid = distance(begin(arrs[j]),
                                   lower_bound(begin(arrs[j]), next(begin(arrs[j]), cnts[j]), arrs[i][nid]));
                if (jid == cnts[j] || arrs[j][jid] != arrs[i][nid]) continue;
                auto fff = fld(fzn[arrs[i][nid]]);
                auto swd = fff.first, fwd = fff.second;
                if (j - i == 1 && swd != fwd) continue;
                if (k == 0) ans -= 1ll * el_cnts[i][nid] * el_cnts[j][jid] * fwc[0][swd];
                else if (k == 1) ans -= 1ll * el_cnts[i][nid] * el_cnts[j][jid] * sfwc[1][fwd][swd];
                else ans -= 1ll * el_cnts[i][nid] * el_cnts[j][jid] * swc[2][fwd];
            }
        }
    }
    for (int nid = 0; nid < cnts[0]; ++nid) {
        auto fff = fld(fzn[arrs[0][nid]]);
        auto swd = fff.first, fwd = fff.second;
        if (swd != fwd) continue;
        int jid = distance(begin(arrs[1]),
                           lower_bound(begin(arrs[1]), next(begin(arrs[1]), cnts[1]), arrs[0][nid]));
        int kid = distance(begin(arrs[2]),
                           lower_bound(begin(arrs[2]), next(begin(arrs[2]), cnts[2]), arrs[0][nid]));
        if (jid == cnts[1] || kid == cnts[2] || arrs[1][jid] != arrs[0][nid] || arrs[2][kid] != arrs[0][nid]) continue;
        ans += 1ll * 2 * el_cnts[0][nid] * el_cnts[1][jid] * el_cnts[2][kid];
    }
    cout << ans;
    return 0;
}
