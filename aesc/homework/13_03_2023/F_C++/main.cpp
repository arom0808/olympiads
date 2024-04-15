#include <iostream>
#include <deque>

using namespace std;

inline int32_t next_el(int32_t a, int32_t b, int32_t c, int32_t i, int32_t k, deque<int> &full_deq) {
    int32_t el;
    if (i < k) cin >> el;
    else el = a * full_deq[full_deq.size() - 2] + b * full_deq[full_deq.size() - 1] + c;
    return el;
}

int main() {
    freopen("minima.in", "r", stdin);
    freopen("minima.out", "w", stdout);
    int32_t n, m, k;
    int32_t a, b, c;
    cin >> n >> m >> k >> a >> b >> c;
    deque<int32_t> min_deq, full_deq;
    for (int32_t i = 0; i < m; ++i) {
        auto el = next_el(a, b, c, i, k, full_deq);
        while (!min_deq.empty() && min_deq.back() > el) min_deq.pop_back();
        min_deq.push_back(el);
        full_deq.push_back(el);
    }
    int32_t sum = min_deq.front();
    for (int32_t i = m; i < n; ++i) {
        auto el = next_el(a, b, c, i, k, full_deq);
        if (min_deq.front() == full_deq.front()) min_deq.pop_front();
        full_deq.push_back(el);
        full_deq.pop_front();
        while (!min_deq.empty() && min_deq.back() > el) min_deq.pop_back();
        min_deq.push_back(el);
        sum += min_deq.front();
    }
    cout << sum;
    return 0;
}