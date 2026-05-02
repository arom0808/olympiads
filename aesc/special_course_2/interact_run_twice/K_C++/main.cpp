#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

void Alice() {
    string num;
    cin >> num;
//    for (int32_t i = 0; i < num.size(); ++i) cout << '0';
    for (int32_t i = 0; i < num.size(); ++i)
        for (int32_t j = 0; j <= num[i] - '0'; ++j)
            cout << static_cast<char>('0' + i);
    cout << endl;
}

void Bob() {
    string rrr;
    cin >> rrr;
    vector<int32_t> cnts(10);
    for (auto c: rrr) ++cnts[c - '0'];
    uint64_t num = 0;
    for (int32_t i = 0; i < 10; ++i) {
        if (cnts[i] == 0) break;
        num *= 10;
        num += cnts[i] - 1;
    }
    cout << num << endl;
//    string num(cnts[0], '0');
//    for (int32_t i = 0; i < num.size(); ++i) num[i] = '0' + cnts[i + 1];
//    cout << num << endl;
}

int main() {
    string st;
    cin >> st;
    if (st == "Alice") {
        Alice();
    } else {
        Bob();
    }
    return 0;
}
