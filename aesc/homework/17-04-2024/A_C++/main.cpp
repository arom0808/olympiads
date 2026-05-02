#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    uint32_t n;
    cin >> n;
    vector<uint32_t> counts(65536);
    int32_t temp_num;
    for (uint32_t i = 0; i < n; ++i) cin >> temp_num, ++counts[temp_num + 32768];
    for (int32_t i = 0; i < counts.size(); ++i) for (uint32_t j = 0; j < counts[i]; ++j) cout << i - 32768 << " ";
    return 0;
}
