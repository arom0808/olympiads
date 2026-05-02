#include <iostream>
#include <set>

using namespace std;

const int32_t maxroom = 2e5 + 1;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n;
    cin >> n;
    set<int32_t> free_rooms;
    for (int32_t i = 1; i <= maxroom; ++i) free_rooms.insert(i);
    for (int32_t i = 0, a; i < n; ++i) {
        cin >> a;
        if (a > 0) {
            auto it = free_rooms.lower_bound(a);
            cout << *it << "\n";
            free_rooms.erase(it);
        } else {
            free_rooms.insert(-a);
        }
    }
    return 0;
}
