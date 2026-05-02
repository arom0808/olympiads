#include <iostream>
#include <set>

using namespace std;

int main() {
    int n;
    cin >> n;
    multiset<int, greater<> > mst;
    for (int i = 0, t; i < n; ++i) cin >> t, mst.insert(t);
    while (mst.size() > 1) {
        auto v1 = *mst.begin(), v2 = *next(mst.begin());
        mst.erase(mst.begin()), mst.erase(mst.begin());
        if (v1 != v2) mst.insert(std::max(v1, v2) - std::min(v1, v2));
    }
    cout << (*mst.begin()) / 2 << "\n";
    return 0;
}
