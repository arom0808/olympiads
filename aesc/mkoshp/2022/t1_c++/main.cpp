#include <iostream>

using namespace std;
using ld = long double;

constexpr int MOD = 998244353, MAXN = 3E5, sq = 548, INF = 1E9 + 1;


template<typename T>
bool rmin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

template<typename T>
bool rmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}


int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    std::uint32_t a;
    std::cin >> a;
    return 0;
}
