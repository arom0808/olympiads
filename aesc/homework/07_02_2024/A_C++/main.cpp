#include <iostream>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    int32_t arr[n];
    for (auto &el: arr) cin >> el;
    uint32_t min_id = 0, max_id = 0;
    for (uint32_t i = 0; i < n; ++i) {
        if (arr[i] < arr[min_id]) min_id = i;
        if (arr[i] > arr[max_id]) max_id = i;
    }
    swap(arr[min_id], arr[max_id]);
    for (auto v: arr) cout << v << " ";
    return 0;
}
