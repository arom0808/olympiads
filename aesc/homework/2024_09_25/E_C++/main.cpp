
#include <iostream>
#include <cmath>

using namespace std;

struct PV {
    int32_t x, y;

    explicit PV(int32_t x = 0, int32_t y = 0) : x(x), y(y) {}

    [[nodiscard]] long double dist(const PV &other) const {
        return std::sqrt(
                static_cast<long double>(1ll * (x - other.x) * (x - other.x) + 1ll * (y - other.y) * (y - other.y)));
    }
};

const int32_t maxn = 5000;
int32_t n;
long double g[maxn][maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for(int32_t i = 0; i)
    return 0;
}
