#include <iostream>
#include <cstdint>

using namespace std;

const int64_t maxn = 1e5, sqrt_c = 500;

struct Change {
    int64_t l, r, x, y;
};

int64_t versions[maxn / sqrt_c + 2][maxn]; // after 0, sqrt_c, 2*sqrt_c ops
int64_t queries[maxn];
int64_t n, m;
int64_t first_derivative[maxn], second_derivative[maxn];
Change changes[maxn];


template<typename T1, typename T2>
void get_derivative(const T1 orig[maxn], T2 derivative[maxn]) {
    derivative[0] = orig[0];
    for (int64_t i = 1; i < n; ++i) derivative[i] = orig[i] - orig[i - 1];
}

template<typename T1, typename T2>
void get_integral(const T1 derivative[maxn], T2 orig[maxn]) {
    orig[0] = derivative[0];
    for (int64_t i = 1; i < n; ++i) orig[i] = orig[i - 1] + derivative[i];
}

void add(int64_t l, int64_t r, int64_t x, int64_t y) {
    second_derivative[l] += x;
    if (l < r) {
        if (l + 1 < n) second_derivative[l + 1] += y - x;
        if (r + 1 < n) second_derivative[r + 1] += -x - y * (r - l + 1);
        if (r + 2 < n) second_derivative[r + 2] += x + y * (r - l);
    } else {
        if (l + 1 < n) second_derivative[l + 1] -= x * 2;
        if (l + 2 < n) second_derivative[l + 2] += x;
    }
}

int64_t get_i_after_k_changes(int64_t i, int64_t k) {
    int64_t val = versions[k / sqrt_c][i];
    for (int64_t c_id = k / sqrt_c * sqrt_c; c_id < k; ++c_id) {
        auto [l, r, x, y] = changes[c_id];
        if (l <= i && i <= r) val += x + (i - l) * y;
    }
    return val;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int64_t i = 0; i < n; ++i) cin >> versions[0][i];
    for (int64_t i = 0; i < n; ++i) cin >> queries[i];
    cin >> m;
    get_derivative(versions[0], first_derivative);
    get_derivative(first_derivative, second_derivative);
    for (int64_t i = 0; i < m; ++i) {
        auto &[l, r, x, y] = changes[i];
        cin >> l >> r >> x >> y, --l, --r;
        add(l, r, x, y);
        if ((i + 1) % sqrt_c == 0) {
            get_integral(second_derivative, first_derivative);
            get_integral(first_derivative, versions[(i + 1) / sqrt_c]);
        }
    }
    for (int64_t i = 0; i < n; ++i) {
        int64_t l = 0, r = m;
        while (l < r) {
            auto mid = (l + r) / 2;
            auto val = get_i_after_k_changes(i, mid);
            if (val < queries[i]) l = mid + 1;
            else r = mid;
        }
        if (get_i_after_k_changes(i, l) < queries[i]) cout << "-1 ";
        else cout << l << " ";
    }
    return 0;
}



//void add(int64_t l, int64_t r, int64_t x, int64_t y) {
//    second_derivative[l] += x;
//    if (l < r) {
//        second_derivative[l + 1] += y - x;
//        second_derivative[r + 1] += -x - y * (r - l + 1);
//        second_derivative[r + 2] += x + y * (r - l);
//    } else {
//        second_derivative[l + 1] -= x * 2;
//        second_derivative[l + 2] += x;
//    }
//}
//
//void get_derivative(const vector<int64_t> &orig, vector<int64_t> &d) {
//    d.resize(orig.size());
//    d[0] = orig[0];
//    for (int64_t i = 1; i < orig.size(); ++i) d[i] = orig[i] - orig[i - 1];
//}
//
//void get_integral(const vector<int64_t> &d, vector<int64_t> &orig) {
//    orig.resize(d.size());
//    orig[0] = d[0];
//    for (int64_t i = 1; i < d.size(); ++i) orig[i] = orig[i - 1] + d[i];
//}