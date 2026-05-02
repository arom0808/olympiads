#include <iostream>
#include <vector>
#include <random>

using namespace std;
using ll = long long;

uint32_t seed = random_device()();

mt19937 rng(seed);
uniform_int_distribution<int> num_dist(-1000000, 1000000);

ll insert_comp_cnt = 0, insert_assign_cnt = 0, merge_comp_cnt = 0, merge_assign_cnt = 0;

void insertion_sort(vector<int> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        int val = arr[i];
        int j = i - 1;
        insert_assign_cnt++;
        while (j >= 0 and arr[j] > val) {
            arr[j + 1] = arr[j];
            j--;
            insert_assign_cnt++;
            insert_comp_cnt++;
        }
        arr[j + 1] = val;
        insert_assign_cnt++;
        insert_comp_cnt++;
    }
}

vector<int> temp;

void merge_sort(vector<int> &arr) {
    for (int l = 1; l < arr.size(); l *= 2) {
        for (int i = 0; i + l < arr.size(); i += l * 2) {
            temp.clear();
            int j = i, k = i + l;
            while (j < i + l and k < i + l * 2 and k < arr.size()) {
                if (arr[j] < arr[k]) {
                    temp.push_back(arr[j++]);
                } else {
                    temp.push_back(arr[k++]);
                }
                merge_comp_cnt++;
                merge_assign_cnt++;
            }
            while (j < i + l) {
                temp.push_back(arr[j++]);
                merge_assign_cnt++;
            }
            while (k < i + l * 2 and k < arr.size()) {
                temp.push_back(arr[k++]);
                merge_assign_cnt++;
            }
            for (j = 0; j < temp.size(); j++) {
                arr[i + j] = temp[j];
                merge_assign_cnt++;
            }
        }
    }
}

vector<int> sizes{
    5, 94, 266, 890, 1784, 2457, 3354, 3828, 4475, 5259, 6585, 7427, 7719, 8351, 8997, 9965, 10242, 10981, 11422, 12245,
    12730, 13422, 13832, 14493, 15770, 16497, 17618, 18393, 19007, 19674, 20479, 21188, 21941, 22416, 23597, 24325,
    25153, 26097, 27020, 27597, 28063, 28643, 30008, 130000, 230439, 326401, 422164, 518244, 615291, 712086, 811759,
    910202, 1009967, 1107441, 1201956, 1304113, 1401793, 1499937, 1596166, 1695390, 1796136, 1893756, 1991247, 2089756,
    2190657, 2292545, 2390062, 2493916, 2595531, 2695965, 2797994, 2898310
};

int main() {
    vector<int> arr, temp_arr;
    for (int sz_i = 0; sz_i < sizes.size(); sz_i++) {
        insert_comp_cnt = 0, insert_assign_cnt = 0, merge_comp_cnt = 0, merge_assign_cnt = 0;
        int sz = sizes[sz_i];
        arr.clear();
        arr.resize(sz, 0);
        if (sz <= 30000) {
            insertion_sort(arr);
        }
        merge_sort(arr);
        for (int i = 0; i < sz; i++) {
            arr[i] = i;
        }
        if (sz <= 30000) {
            insertion_sort(arr);
        }
        merge_sort(arr);
        if (sz <= 30000) {
            for (int i = 0; i < sz; i++) {
                arr[i] = sz - i;
            }
            insertion_sort(arr);
        }
        for (int i = 0; i < sz; i++) {
            arr[i] = sz - i;
        }
        merge_sort(arr);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < arr.size(); ++j) {
                arr[j] = num_dist(rng);
            }
            if (sz <= 30000) {
                temp_arr = arr;
                insertion_sort(arr);
            }
            temp_arr = arr;
            merge_sort(temp_arr);
        }
        cout << sz << " " << insert_comp_cnt / 6 << " " << insert_assign_cnt / 6 << " " << merge_comp_cnt / 6 << " " <<
                merge_assign_cnt / 6 << "\n";
    }
    return 0;
}
