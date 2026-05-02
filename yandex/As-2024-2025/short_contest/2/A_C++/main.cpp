#include <iostream>

using namespace std;

constexpr int maxn = 1e4;
int arr[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n;
    cin >> n;
    int average = 0;
    for (int i = 0; i < n; ++i) cin >> arr[i], average += arr[i];
    average /= n;
    int ans = 0;
    for (int i = 0; i < n; ++i) if (arr[i] < average) ans += average - arr[i];
    cout << ans << "\n";
    return 0;
}
