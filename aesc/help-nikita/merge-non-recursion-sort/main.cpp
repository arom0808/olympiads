#include <iostream>
#include <vector>
#include <random>

using namespace std;

//template<typename T>
//void merge_sort(vector<T> &vec) {
//    for (uint32_t s = 1; s < vec.size(); s *= 2) {
//        for (uint32_t i = 0; i < vec.size(); i += s * 2) {
//            if (i + s >= vec.size()) continue;
//            uint32_t p1 = i, p2 = i + s;
//            while (p1 < vec.size() && p2 < vec.size()) {
//                if (vec[p1] > vec[p2])
//            }
//        }
//    }
//}

namespace Rand {
    random_device dev;
    uint32_t seed = dev();
    mt19937 rng(seed);

    template<typename T>
    T randint(T a, T b) {
        return uniform_int_distribution(a, b)(rng);
    }
}

template<typename T>
T kth_element(vector<T> &vec, uint32_t k) {
    uint32_t l = 0, r = vec.size() - 1;
    do {
        auto t = Rand::randint<uint32_t>(l, r);
        uint32_t i = l, j = r;
        while (i <= j) {
            while (vec[i] < vec[t] && i < vec.size()) ++i;
            while (vec[j] > vec[t] && j > 0) --j;
            if (i <= j) {
                if (t == i) t = j;
                if (t == j) t = i;
                swap(vec[i], vec[j]);
                ++i, --j;
            }
        }
        if (t < k) l = t + 1;
        else if (t > k) r = t - 1;
        else l = r = k;
    } while (l != r);
    return vec[k];
}

int main() {
    vector<uint32_t> arr{5, 4, 3, 2, 1, 1, 0, 0};
    cout << kth_element(arr, 4);
    return 0;
}