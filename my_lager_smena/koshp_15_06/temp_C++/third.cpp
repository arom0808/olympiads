

//#include <iostream>
//#include <vector>
//#include <queue>
//#include <algorithm>
//
//#define int long long
//using namespace std;
//
//signed main() {
//    int x, n;
//    cin >> x >> n;
//    vector<int> b;
//    int i = 0;
//    while (i < n) {
//        b.push_back(x);
//        x = (x * 3) % 10;
//        if (find(b.begin(), b.end(), x) != b.end()) {
//            break;
//        }
//        ++i;
//    }
//    if (i == n) {
//        int ans = 0;
//        for (int j = 0; j < n; j++) {
//            ans += b[j];
//        }
//        if (ans%3==0) {
//            cout << "YES\n";
//        } else {
//            cout << "NO\n";
//        }
//        return 0;
//    }
//    int k = -1;
//    for (int j = 0; j < b.size(); j++) {
//        if (b[j] == x) k = j;
//    }
//    int s1 = 0;
//    for (int j = k; j < b.size(); j++) {
//        s1 += b[j];
//    }
//    int s2 = 0;
//    for (int j = 0; j < k; j++) s2 += b[j];
//    int ans = s2 + s1 * (n / (b.size() - k));
//    for (int j = 0; j < (n - i - 1) % (b.size() - k); j++) ans += b[j + k];
//    if (ans%3==0) {
//        cout << "YES\n";
//    } else {
//        cout << "NO\n";
//    }
//}