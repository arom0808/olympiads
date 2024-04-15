#include <iostream>

using namespace std;

const int32_t end_val = -2000000000;

int main() {
    int32_t pre, now, n = 1;
    cin >> pre;
    bool a = true, wa = true, d = true, wd = true, c = true;
    while (true) {
        cin >> now;
        if (now == end_val) break;
        ++n;
        if (now != pre) c = false;
        if (now < pre) wa = false;
        if (now <= pre) a = false;
        if (now > pre) wd = false;
        if (now >= pre) d = false;
        pre = now;
    }
    cout << n << "\n";
    if (c) cout << "CONSTANT";
    else if (a) cout << "ASCENDING";
    else if (d) cout << "DESCENDING";
    else if (wa) cout << "WEAKLY ASCENDING";
    else if (wd) cout << "WEAKLY DESCENDING";
    else cout << "RANDOM";
    return 0;
}
