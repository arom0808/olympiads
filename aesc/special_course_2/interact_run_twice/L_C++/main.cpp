//#include <iostream>
#include <cstdint>

using namespace std;

int64_t encode(double val) {
    return *reinterpret_cast<int64_t *>(&val);
}

double decode(int64_t val) {
    return *reinterpret_cast<double *>(&val);
}

//int main() {
//    double aa = 0.124124322e55;
//    double bb = decode(encode(aa));
//    std::cout << (aa == bb);
//    return 0;
//}
