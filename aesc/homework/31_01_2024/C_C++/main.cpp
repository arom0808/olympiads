#include <iostream>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    switch (n % 100) {
        case 10 ... 20:
            cout << "��� " << n << " ���";
            break;
        default:
            switch (n % 10) {
                case 1:
                    cout << "��� " << n << " ���";
                    break;
                case 2 ... 4:
                    cout << "��� " << n << " ����";
                    break;
                default:
                    cout << "��� " << n << " ���";
            }
    }
    return 0;
}
