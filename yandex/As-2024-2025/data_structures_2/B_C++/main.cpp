#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;;

const int maxn = 2e5;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, m;
    ordered_set<int> zeros_poses;
    cin >> n;
    for (int i = 0, el; i < n; ++i) {
        cin >> el;
        if (!el) zeros_poses.insert(i);
    }
    cin >> m;
    char c;
    for (int i = 0, f, s, t; i < m; ++i) {
        cin >> c;
        if (c == 's') {
            cin >> f >> s >> t, --f, --s, --t;
            auto fpos = zeros_poses.order_of_key(f);
            if (fpos + t >= zeros_poses.size()) {
                cout << "-1 ";
                continue;
            }
            auto spos = *zeros_poses.find_by_order(fpos + t);
            if (spos > s) cout << "-1 ";
            else cout << spos + 1 << " ";
        } else {
            cin >> f >> s, --f;
            zeros_poses.erase(f);
            if (!s) zeros_poses.insert(f);
        }
    }
    return 0;
}
