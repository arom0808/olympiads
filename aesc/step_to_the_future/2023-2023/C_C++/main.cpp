#include <iostream>
#include <vector>
#include <set>

using namespace std;

const uint64_t max_re = 1e5;

bool is_prime(const vector<uint64_t> &re, const vector<uint64_t> &pr, uint64_t num) {
    if (num <= max_re) return re[num] == num;
    for (uint64_t i = 0; i < pr.size() && pr[i] * pr[i] <= num; ++i) if (num % pr[i] == 0) return false;
    return true;
}

struct Point {
    int64_t x, y, z;

    Point(int64_t x, int64_t y, int64_t z) : x(x), y(y), z(z) {}

    bool operator<(const Point &other) const {
        if (x != other.x) return x < other.x;
        else if (y != other.y) return y < other.y;
        return z < other.z;
    }
};

int main() {
    vector<uint64_t> re(max_re + 1, 0), pr;
    re[0] = 1;
    pr.reserve(1e4);
    for (uint64_t i = 2; i <= max_re; ++i) {
        if (re[i] == 0) {
            re[i] = i;
            pr.push_back(i);
        }
        for (uint64_t j = 0; j < pr.size() && pr[j] <= re[i] && i * pr[j] <= max_re; ++j) re[i * pr[j]] = pr[j];
    }
    set<Point> res;
    int64_t x, y, z;
    cin >> x >> y >> z;
    if (is_prime(re, pr, std::abs(x) + std::abs(y) + std::abs(z))) res.emplace(x, y, z);
    uint64_t n;
    cin >> n;
    int64_t change;
    char tc;
    for (uint64_t i = 0; i < n; ++i) {
        cin >> tc >> change;
        if (tc == 'x') x += change;
        else if (tc == 'y') y += change;
        else z += change;
        if (is_prime(re, pr, std::abs(x) + std::abs(y) + std::abs(z))) res.emplace(x, y, z);
    }
    cout << res.size();
    return 0;
}
