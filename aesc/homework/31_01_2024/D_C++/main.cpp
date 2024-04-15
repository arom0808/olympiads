#include <iostream>

using namespace std;

int main() {
    int32_t res = 0;
    bool act = true;
    char d;
    while (d != '.') {
        cin >> d;
        switch (d) {
            case '+':
            case '-':
                act = d == '+';
                break;
            case '0' ... '9':
                res += (act ? d - '0' : '0' - d);
        }
    }
    cout << res;
    return 0;
}
