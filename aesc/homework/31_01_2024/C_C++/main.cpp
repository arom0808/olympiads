#include <iostream>

using namespace std;

int main() {
    uint32_t n;
    cin >> n;
    switch (n % 100) {
        case 10 ... 20:
            cout << "ћне " << n << " лет";
            break;
        default:
            switch (n % 10) {
                case 1:
                    cout << "ћне " << n << " год";
                    break;
                case 2 ... 4:
                    cout << "ћне " << n << " года";
                    break;
                default:
                    cout << "ћне " << n << " лет";
            }
    }
    return 0;
}
