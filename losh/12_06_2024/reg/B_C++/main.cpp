#include <iostream>
#include <vector>

using namespace std;

int main() {
    int32_t n;
    cin >> n;
    vector<int32_t> orig_counts;
    vector<char> orig_letters;
    char c;
    for (int32_t i = 0; i < n; ++i) {
        cin >> c;
        if (i == 0 || c != orig_letters.back()) {
            orig_letters.push_back(c);
            orig_counts.push_back(1);
        } else ++orig_counts.back();
    }
    auto counts = orig_counts;
    auto now_best_size = 0, best_l_cnt = 0;
    int32_t n_cnt = 0;
    for (int32_t i = 0; i < static_cast<int32_t>(counts.size()); ++i) {
        n_cnt += counts[i];
        if (n_cnt > now_best_size) now_best_size = n_cnt, best_l_cnt = i + 1;
        n_cnt -= counts[i];
        counts[i] -= counts[i] % 3;
        n_cnt += counts[i];
    }
    counts = orig_counts;
    for (int32_t i = 0; i + 1 < best_l_cnt; ++i) counts[i] -= counts[i] % 3;
    cout << now_best_size << "\n";
    for (int32_t i = 0, k = 0; i < best_l_cnt; ++i) {
        for (int32_t j = 0; j < counts[i]; ++j, ++k) {
            cout << orig_letters[i];
            if (k % 3 == 2) cout << "\n";
        }
    }
    if (now_best_size % 3 != 0) cout << "\n";
    return 0;
}
