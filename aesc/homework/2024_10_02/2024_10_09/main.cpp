#include <iostream>

using namespace std;

void rec_sol(int32_t level) {
    if (level == 0) {
        cout << "go(5)\n";
        return;
    }
    rec_sol(level - 1);
    cout << "turn(60)\n";
    rec_sol(level - 1);
    cout << "turn(-120)\n";
    rec_sol(level - 1);
    cout << "turn(60)\n";
    rec_sol(level - 1);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int32_t n;
    cin >> n;
    rec_sol(n);
    return 0;
}
