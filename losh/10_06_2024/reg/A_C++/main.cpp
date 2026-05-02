#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    uint64_t sa, sb, n;
    cin >> sa >> sb >> n;
    vector<uint64_t> gors(n);
    string temp;
    for (auto &val: gors) {
        cin >> temp;
        auto ps = temp.find('.');
        val = stoi(temp.substr(0, ps));
        val *= 100;
        val += stoi(temp.substr(ps + 1, 2));
    }
    sort(gors.begin(), gors.end());
    uint64_t a = sa, b = sb;
    for (auto g: gors) {
        if (a + b == 0 || a * 10000 / (a + b) >= g) ++a;
        else ++b;
    }
    uint64_t max_res = a;
    a = sa, b = sb;
    reverse(gors.begin(), gors.end());
    for (auto g: gors) {
        if (a + b == 0 || a * 10000 / (a + b) >= g) ++a;
        else ++b;
    }
    cout << a << " " << max_res;
    return 0;
}
