#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

random_device dev;
mt19937 rng(dev());

inline uint64_t d_to_u64(double num) {
    return *(reinterpret_cast<uint64_t *>(&num));
}

inline uint64_t abs_d_to_u64(double num) {
    uint64_t u64 = d_to_u64(num);
    if (u64 >> 63) return ~u64;
    return u64;
}

inline uint64_t get_radix(double num, uint32_t rad) {
    if (rad < 3) return (abs_d_to_u64(num) >> (16 * rad)) & ((1 << 16) - 1);
    else if (rad == 3) return (abs_d_to_u64(num) >> (16 * rad)) & ((1 << 15) - 1);
    else if (rad == 4) return 1 - (d_to_u64(num) >> 63);
//    if (rad <= 4) return (abs_d_to_u64(num) >> (10 * rad)) & ((1ull << 10) - 1);
//    if (rad == 5) return (abs_d_to_u64(num) >> (10 * rad)) & ((1ull << 13) - 1);
//    if (rad == 7) return 1 - (d_to_u64(num) >> 63);
}

vector<uint32_t> ps(1ull << 16);

int64_t radix_sort(vector<double> &arr1) {
    auto start = chrono::system_clock::now();
    vector<double> arr2(arr1.size());
    for (uint32_t rad = 0; rad < 5; ++rad) {
        for (uint32_t i = 0; i < ps.size(); ++i) ps[i] = 0;
//        for (auto &el: ps) el = 0;
        for (auto el: arr1) ++ps[get_radix(el, rad)];
        for (uint32_t i = 1; i < ps.size(); ++i) ps[i] += ps[i - 1];
        for (int32_t i = arr1.size() - 1; i >= 0; --i) arr2[--ps[get_radix(arr1[i], rad)]] = arr1[i];
        arr1.swap(arr2);
    }
    auto end = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

int64_t std_sort(vector<double> &arr) {
    auto start = chrono::system_clock::now();
    sort(arr.begin(), arr.end());
    auto end = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

enum class ArrType {
    to_top, to_down, rand
};

void generate_array(vector<double> &arr, uint32_t n, ArrType arr_type = ArrType::rand) {
    auto dist1 = uniform_real_distribution(-1e300, 1e300);
    auto dist2 = uniform_int_distribution(0u, n - 1);
    arr.resize(n);
    for (auto &el: arr) el = dist1(rng);
    if (arr_type == ArrType::to_top) {
        sort(arr.begin(), arr.end());
        for (uint32_t i = 0; 2 * i * i < n; ++i) arr[dist2(rng)] = dist1(rng);
    } else if (arr_type == ArrType::to_down) {
        sort(arr.rbegin(), arr.rend());
        for (uint32_t i = 0; 2 * i * i < n; ++i) arr[dist2(rng)] = dist1(rng);
    }
}

int main() {
    vector<int32_t> ns = {100, 1000, static_cast<int>(1e4), static_cast<int>(15000), static_cast<int>(2e5),
                          static_cast<int>(7.5e5), static_cast<int>(25e5), static_cast<int>(4e6),
                          static_cast<int>(1e7), static_cast<int>(1.5e7), static_cast<int>(1.75e7),
                          static_cast<int>(2.2e7)};
    vector<double> temp1, temp2;
    vector<vector<double>> arrs(5);
    for (auto n: ns) {
        cout << n << "\n";
        for (auto &arr: arrs) generate_array(arr, n);
        uint64_t sum1 = 0;
        for (auto &arr: arrs) {
            temp1 = arr;
            uint64_t ee = radix_sort(temp1);
            sum1 += ee;
            cout << ee << " ";
        }
        cout << sum1 / 5 << "\n";
        uint64_t sum2 = 0;
        for (auto &arr: arrs) {
            temp1 = arr;
            uint64_t ee = std_sort(temp1);
            sum2 += ee;
            cout << ee << " ";
        }
        cout << sum2 / 5 << "\n";
    }
    return 0;
}
