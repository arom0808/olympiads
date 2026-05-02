#include <iostream>
#include <vector>

using namespace std;

struct Employer {
    int32_t t, z, y;

    explicit Employer(int32_t t = 0, int32_t z = 0, int32_t y = 0) : t(t), z(z), y(y) {}
};

bool check_for_t(const vector<Employer> &employers, int32_t time, int32_t target) {
    int32_t balloons_cnt = 0;
    for (auto [t, z, y]: employers) balloons_cnt += time / (t * z + y) * z + min(time % (t * z + y) / t, z);
    return balloons_cnt >= target;
}

int main() {
    int32_t m, n;
    cin >> m >> n;
    vector<Employer> employers(n);
    for (auto &[t, z, y]: employers) cin >> t >> z >> y;
    int32_t l = 0, r = 1e9;
    while (l != r) {
        int32_t mid = (l + r) / 2;
        if (check_for_t(employers, mid, m)) r = mid;
        else l = mid + 1;
    }
    cout << l << "\n";
    for (auto [t, z, y]: employers) {
        int32_t c_cnt = l / (t * z + y) * z + min(l % (t * z + y) / t, z);
        if (m > c_cnt) cout << c_cnt << " ";
        else cout << m << " ";
        m = max(m - c_cnt, 0);
    }
}



////#pragma GCC optimize("Ofast")
////#pragma GCC optimize(O3)
////#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")
////#pragma GCC optimize("unroll-loops")
////#pragma GCC optimize("unswitch-loops")
////#pragma GCC optimize("function-sections")
////#pragma GCC optimize("inline")
//
//#include <iostream>
//#include <cstdint>
//#include <vector>
//#include <set>
//#include <algorithm>
//
//#define ll long long
//using namespace std;
//
//int main() {
//    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
//    int64_t n;
//    cin >> n;
//    vector<int64_t> a(n), b(n), c(n, 0);
//    for (auto &el: a) cin >> el;
//    for (auto &el: b) cin >> el;
//    int64_t all_sum = 0;
//    for (int64_t i = 0; i < n; ++i) all_sum += b[i];
//    for (int64_t ost_cnt = 0; ost_cnt < n; ++ost_cnt) {
//        int64_t diff = a[0] - c[0];
//        bool ok_ost = true;
//        for (int64_t i = 1; i < n; ++i) {
//            if (a[i] - c[i] != diff) {
//                ok_ost = false;
//            }
//        }
//        if (ok_ost) {
//            if (diff == 0) {
//                cout << ost_cnt;
//                return 0;
//            } else if (all_sum != 0 && ((diff < 0 && all_sum < 0) || (diff > 0 && all_sum > 0)) &&
//                       diff % all_sum == 0) {
//                cout << (diff / all_sum) * n + ost_cnt;
//                return 0;
//            }
//        }
//        for (int64_t i = 0; i < n; ++i) c[i] += b[i];
//        int64_t temp = b[0];
//        for (int64_t i = 0; i + 1 < n; ++i) b[i] = b[i + 1];
//        b[n - 1] = temp;
//    }
//    cout << "-1";
//    return 0;
//}
//
//
////long long n;
////    cin >>n;
////    ll l=0;
////    ll r=n;
////    while (r-l>1){
////        ll sr=(l+r)/2;
////        while ()
////    }