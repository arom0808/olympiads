#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void insert_sort(vector<T> &arr) {
    for (uint32_t i = 1; i < arr.size(); ++i) {
        uint32_t l = 0, r = i;
        while (l != r) {
            uint32_t m = (l + r) / 2;
            if (arr[m] < arr[i]) l = m + 1;
            else if (arr[m] > arr[i]) r = m;
            else l = r = m;
        }
        for (uint32_t j = i; j > l; --j) swap(arr[j], arr[j - 1]);
    }
}

int main() {
    vector<uint32_t> vec{1, 56, 2, 5, 3, 3, 5, 67, 8, 9};
    insert_sort(vec);
    for (auto &el: vec) cout << el << " ";
    return 0;
}
