#include <iostream>

using namespace std;

int main() {
    int32_t n;
    cin >> n;
    int32_t day1 = 0, day2 = 0, price1 = 0, price2 = 0, min_price = 1e9, min_day = 0;
    for (int32_t i = 1, day_price; i <= n; ++i) {
        cin >> day_price;
        if (day_price > min_price) {
            if (!day1 || day_price * price1 >= min_price * price2) {
                day1 = min_day;
                price1 = min_price;
                day2 = i;
                price2 = day_price;
            }
        } else if (day_price < min_price) {
            min_price = day_price;
            min_day = i;
        }
    }
    cout << day1 << " " << day2;
    return 0;
}
