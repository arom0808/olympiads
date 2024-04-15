#include <iostream>

using namespace std;

int main() {
    uint64_t day, month, year;
    char c1, c2;
    cin.get(c1), cin.get(c2);
    day = (c1 - '0') * 10 + c2 - '0';
    cin.get(c1), cin.get(c1), cin.get(c2);
    month = (c1 - '0') * 10 + c2 - '0';
    cin.get(c1);
    cin >> year;
    uint64_t days_in_month = 31;
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            days_in_month = 30;
            break;
        case 2:
            days_in_month = year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? 29 : 28;
    }
    if (day < 1 || month < 1 || month > 12 || day > days_in_month) {
        cout << "WRONG DATE";
        return 0;
    }
    if (day == days_in_month) {
        if (month == 12) day = 1, month = 1, ++year;
        else day = 1, ++month;
    } else ++day;
    cout << (day < 10 ? "0" : "") << day << "." << (month < 10 ? "0" : "") << month << "." << year;
    return 0;
}
