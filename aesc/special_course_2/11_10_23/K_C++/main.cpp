#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

const uint32_t max_n = 1e6;
vector<uint32_t> divs(max_n + 1, 0);
vector<uint32_t> prime;

void init_divs() {
    for (uint32_t k = 2; k <= max_n; ++k) {
        if (!divs[k]) prime.push_back(divs[k] = k);
        for (auto p: prime) {
            if (p > divs[k] || p * divs[k] > max_n) break;
            divs[p * divs[k]] = p;
        }
    }
}

int main() {
    init_divs();
    cout << prime.size();
    return 0;
}
