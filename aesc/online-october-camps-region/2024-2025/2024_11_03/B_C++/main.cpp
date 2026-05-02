#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

using ll = int64_t;

constexpr int maxn = 5e5;

int n, m;

struct Player {
    int p, d, id;

    bool operator<(const Player &rhs) const {
        if (p != rhs.p) return p > rhs.p;
        if (d != rhs.d) return d < rhs.d;
        return id < rhs.id;
    }
};

struct Change {
    int x, y, z;
};

Player players[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> m >> n;
    for (int i = 0; i < n; ++i) cin >> players[i].p >> players[i].d, players[i].id = i;
    sort(begin(players), next(begin(players), n));
    ll z = 0;
    vector<int> start_players;
    vector<Change> changes;
    int npid = 0, gt = 0, gtpid = -1, ppid = -1;
    for (int i = 0; i < 6; ++i) {
        int near_time = 0;
        ppid = -1;
        if (gt) {
            start_players.push_back(gtpid);
            near_time = gt;
            ppid = gtpid;
            gt = 0;
        }
        while (near_time < m) {
            if (near_time + players[npid].d <= m || i == 5) {
                int pt = std::min(m - near_time, players[npid].d);
                z += 1ll * pt * players[npid].p;
                if (ppid != -1) changes.emplace_back(near_time, ppid, npid);
                else start_players.push_back(npid);
                near_time += pt;
                ppid = npid;
                ++npid;
            } else {
                int pt = m - near_time;
                z += 1ll * players[npid].p * players[npid].d;
                if (ppid != -1) changes.emplace_back(near_time, ppid, npid);
                else start_players.push_back(npid);
                gtpid = npid;
                gt = players[npid].d - pt;
                near_time = m;
                ++npid;
            }
        }
    }
    cout << z << "\n";
    for (auto el: start_players) cout << players[el].id + 1 << " ";
    cout << "\n" << changes.size() << "\n";
    for (auto ch: changes) cout << ch.x << " " << players[ch.y].id + 1 << " " << players[ch.z].id + 1 << "\n";
    return 0;
}
