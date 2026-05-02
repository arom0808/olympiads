
#include <iostream>
#include <array>
#include <set>

using namespace std;

array<uint32_t, 6> arr;
set<set<uint32_t>> arrs;

void rec_sol(uint32_t val, uint32_t prev_min, uint32_t level) {
    if (level >= 5) {
        arr[level] = val;
        set<uint32_t> temp(arr.begin(), arr.end());
        if (temp.size() == arr.size()) arrs.emplace(std::move(temp));
        return;
    }
    for (uint32_t i = min(val, prev_min); i > 0; --i)
        if (val % i == 0) {
            arr[level] = i;
            rec_sol(val / i, min(prev_min, i), level + 1);
        }
}

int main() {
    rec_sol(1000000000, 1000000000, 0);
    cout << arrs.size() << "\n";
    for (auto &a: arrs) {
        for (auto el: a) cout << el << " ";
        cout << "\n";
    }
}



////#include <iostream>
////
////using namespace std;
//
////int main() {
////    uint32_t n = 1000000000, res = 0;
////    for (uint32_t i = 1; i * i <= n; ++i) {
////        if (n % i != 0) continue;
////        if (i * i == n) ++res;
////        else res += 2;
////        cout << i << " " << n / i << "\n";
////    }
////    cout << res;
////}
//
////
//#include <iostream>
//#include <array>
//#include <set>
//
//using namespace std;
//
//array<uint32_t, 6> arr;
//set<set<uint32_t>> arrs;
//
//void rec_sol(uint32_t val, uint32_t prev_min, uint32_t level) {
//    if (level >= 5) {
//        arr[level] = val;
//        if (set(arr.begin(), arr.end()).size() == arr.size()) arrs.emplace(arr.begin(), arr.end());
//        return;
//    }
//    for (uint32_t i = min(val, prev_min); i > 0; --i)
//        if (val % i == 0) {
//            arr[level] = i;
//            rec_sol(val / i, min(prev_min, i), level + 1);
//        }
//}
//
//int main() {
//    rec_sol(1000000, 1000000, 0);
//    cout << arrs.size();
//}
////    for (auto &a: arrs) {
////        for (auto el: a) cout << el << " ";
////        cout << "\n";
////    }
//
////#include <iostream>
////
////using namespace std;
////
////int main() {
////    uint32_t n = 1000000, res = 0;
////    for (uint32_t i = 1; i * i <= n; ++i) {
////        if (n % i != 0) continue;
////        if (i * i == n) ++res;
////        else res += 2;
////        cout << i << " " << n / i << "\n";
////    }
////    cout << res;
////}
//
//
//
////#include <iostream>
////#include <cmath>
////#include <iomanip>
////
////using namespace std;
////
////long double calculate_for_k(unsigned int k) {
////    long double result = 0;
////    for (; k > 0; --k) result = sqrt(result + 2 * k - 1);
////    return result;
////}
////
////long double calculate() {
////    unsigned int k = 1;
////    long double eps = 1e-20, old_val, new_val = calculate_for_k(k);
////    do {
////        swap(old_val, new_val);
////        new_val = calculate_for_k(k *= 2);
////    } while (abs(new_val - old_val) > eps);
////    return new_val;
////}
////
////int main() {
////    cout << fixed << setprecision(15) << calculate();
////    return 0;
////}
