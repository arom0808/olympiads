#include <iostream>

using namespace std;

int main() {
    int64_t n;
    cin >> n;
    int64_t candidate, count = 0, el;
    for (int64_t i = 0; i < n; ++i) {
        cin >> el;
        if (count == 0) candidate = el, ++count;
        else if (el == candidate) ++count;
        else --count;
    }
    cout << candidate;
    return 0;
}
