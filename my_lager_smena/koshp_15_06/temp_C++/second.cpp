

#include <iostream>
#include <vector>

using namespace std;

int main(){
    long long n, m , t;
    cin >> n >> m >> t;
    vector<long long> A(n), copy(n), new_copy(n);
    for (long long i =0; i < n; i++){
        cin >> A[i];
        copy[i] = A[i];
        new_copy[i] = A[i];
    }
    vector<long long> B(n);
    for (long long i = 0; i < n; i++){
        cin >> B[i];
    }
    long long summa = 0;
    for (long long i = 0; i < m; i++){
        long long temp;
        cin >> temp;
        summa += temp;
    }
    vector<vector<int>> dp(n, vector<int>(2000));

    if (){
        cout << "SUPER";
    }else{
        for (long long j = 0; j < n; j++){
            for (long long i = 0; i < n; i++){
                if (copy[i] <= t){
                    if (B[i] >= copy[i]){
                        t += B[i] - copy[i];
                        B[i] = 999999999;
                        copy[i] = 999999999;
                    }
                }
            }
        }if (t >= summa){
            cout << "SCHOOL";
        }else{
            cout << "EPIC FAIL";
        }
    }
}

//
//
//#include <iostream>
//
//using namespace std;
//int main(){
//    int n;
//    cin >> n;
//    if (n == 1){
//        cout << "YES" << '\n';
//        cout << 0 << ' '<< 0 <<' '<< 1;
//    } else if (n == 2 or n == 3 or n==5){
//        cout << "NO";
//    } else if (n % 2 == 0){
//        cout << "YES" << '\n';
//        int x = n / 2;
//        cout << 0 << ' ' << 0 << ' ' << x - 1 << '\n';
//        for (int i = 0; i < x; i++){
//            cout << i << ' ' << x - 1 << ' ' << 1 << '\n';
//        }for (int i = 0; i < x - 1; i++){
//            cout << x - 1 << ' ' << i << ' ' << 1 << '\n';
//        }
//    } else if (n % 4 == 3){
//        cout << "YES" << '\n';
//        int x = (n + 9) / 4;
//        cout << 0 << ' ' << 0 << ' ' << x - 2 << '\n';
//        cout << x - 2 << ' ' << 0 << ' ' << 2 << '\n';
//        cout << 0 << ' ' << x - 2 << ' ' << 2 << '\n';
//        for (int i = 0; i < x - 2; i++){
//            cout << i + 2 << ' ' << x - 2 << ' ' << 1 << '\n';
//            cout << i + 2 << ' ' << x - 1 << ' ' << 1 << '\n';
//        }for (int i = 0; i < x - 4; i++) {
//            cout << x - 2 << ' ' << i + 2 << ' ' << 1 << '\n';
//            cout << x - 1 << ' ' << i + 2 << ' ' << 1 << '\n';
//        }
//    }else if (n % 4 == 1){
//        cout << "YES" << '\n';
//        int x = (n + 3) / 4;
//        cout << 0 << ' ' << 0 << ' ' << x - 2 << '\n';
//        for (int i = 0; i < x; i++){
//            cout << i << ' ' << x - 2 << ' ' << 1 << '\n';
//            cout << i << ' ' << x - 1 << ' ' << 1 << '\n';
//        }
//        for (int i = 0; i < x - 2; i++){
//            cout << x - 2 << ' ' << i << ' ' << 1 << '\n';
//            cout << x - 1 << ' ' << i << ' ' << 1 << '\n';
//        }
//    }
//}
////
////int main() {
////    std::uint32_t x, n;
////    std::cin >> x >> n;
////    std::uint64_t sum = 0;
////    std::uint32_t i = 0;
////    for (; i < n && x != 1 && x != 2 && x != 5; ++i) {
////        sum += x % 10;
////        x = (x * 3) % 10;
////    }
////    if (x == 1 || x == 2) {
////        sum += ((n - i) / 4 * 20);
////        i += (n - i) / 4 * 4;
////    } else if (x == 5) {
////        sum += (n - i) * 5;
////        i += (n - i);
////    }
////    for (; i < n; ++i) {
////        sum += x % 10;
////        x = (x * 3) % 10;
////    }
////    std::cout << (sum % 3 == 0 ? "YES" : "NO");
////}
////
//////int main() {
//////    int h1, m1, t1, h2, m2, t2;
//////    cin >> h1 >> m1 >> t1 >> h2 >> m2 >> t2;
//////    int temp2 = h2 * 60 + m2, temp1 = h1 * 60 + m1;
//////    if (temp2 - temp1 > t1 + t2){
//////        cout << "OK";
//////    }else{
//////        cout << "CHANGE TICKET";
//////    }
//////    return 0;
//////}
