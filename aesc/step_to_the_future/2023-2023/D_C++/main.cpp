#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    vector<uint32_t> cards(n);
    for (auto &c: cards) cin >> c;
    partial_sort(cards.begin(), next(cards.begin(), 4), cards.end(), [](uint32_t a, uint32_t b) { return a > b; });
    for (uint32_t i = 0; i < 4; ++i) cout << cards[i];
    return 0;
}
