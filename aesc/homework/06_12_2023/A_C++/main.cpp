#include <iostream>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    int32_t m1 = 30001, m2 = 30001;
    for (int32_t i = 0, num; i < n; ++i) {
        cin >> num;
        if (num < m1) {
            m2 = m1;
            m1 = num;
        } else if (num < m2) m2 = num;
    }
    cout << m1 << " " << m2;
    return 0;
}
