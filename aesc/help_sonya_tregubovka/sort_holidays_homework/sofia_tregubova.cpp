#include <iostream>
#include <vector>
#include <random>

using namespace std;
using ll = long long;

uint32_t seed = random_device()();

mt19937 rng(seed);
uniform_int_distribution num_dist(-1000000, 1000000);

pair<ll, ll> insertion_sort(vector<int> &arr) {
    ll comparisons_cnt = 0, assignments_cnt = 0;
    for (int i = 1; i < arr.size(); ++i) {
        int val = arr[i], j = i - 1;
        ++assignments_cnt;
        while (j >= 0 && arr[j] > val) arr[j + 1] = arr[j], --j, ++assignments_cnt, ++comparisons_cnt;
        arr[j + 1] = val;
        ++assignments_cnt, ++comparisons_cnt;
    }
    return {comparisons_cnt, assignments_cnt};
}

vector<int> temp;

pair<ll, ll> merge_sort(vector<int> &arr) {
    ll comparisons_cnt = 0, assignments_cnt = 0;
    for (int l = 1; l < arr.size(); l <<= 1) {
        for (int i = 0; i + l < arr.size(); i += l << 1) {
            temp.clear();
            int j = i, k = i + l;
            while (j < i + l && k < i + (l << 1) && k < arr.size()) {
                if (arr[j] < arr[k]) temp.push_back(arr[j++]);
                else temp.push_back(arr[k++]);
                ++comparisons_cnt, ++assignments_cnt;
            }
            while (j < i + l) temp.push_back(arr[j++]), ++assignments_cnt;
            while (k < i + (l << 1) && k < arr.size()) temp.push_back(arr[k++]), ++assignments_cnt;
            for (j = 0; j < temp.size(); ++j) arr[i + j] = temp[j], ++assignments_cnt;
        }
    }
    return {comparisons_cnt, assignments_cnt};
}

vector<int> sizes{
    5, 94, 266, 890, 1784, 2457, 3354, 3828, 4475, 5259, 6585, 7427, 7719, 8351, 8997, 9965, 10242, 10981, 11422, 12245,
    12730, 13422, 13832, 14493, 15770, 16497, 17618, 18393, 19007, 19674, 20479, 21188, 21941, 22416, 23597, 24325,
    25153, 26097, 27020, 27597, 28063, 28643
};

int main() {
    vector<int> arr, temp_arr;
    for (auto sz: sizes) {
        arr.clear();
        arr.resize(sz, 0);
        ll insert_comp_cnt = 0, insert_assign_cnt = 0, merge_comp_cnt = 0, merge_assign_cnt = 0;
        auto [icc1, iac1] = insertion_sort(arr);
        insert_comp_cnt += icc1, insert_assign_cnt += iac1;
        auto [mcc1,mac1] = merge_sort(arr);
        merge_comp_cnt += mcc1, merge_assign_cnt += mac1;
        for (int i = 0; i < sz; ++i) arr[i] = i;
        auto [icc2, iac2] = insertion_sort(arr);
        insert_comp_cnt += icc2, insert_assign_cnt += iac2;
        auto [mcc2,mac2] = merge_sort(arr);
        merge_comp_cnt += mcc2, merge_assign_cnt += mac2;
        for (int i = 0; i < sz; ++i) arr[i] = sz - i;
        auto [icc3, iac3] = insertion_sort(arr);
        insert_comp_cnt += icc3, insert_assign_cnt += iac3;
        for (int i = 0; i < sz; ++i) arr[i] = sz - i;
        auto [mcc3,mac3] = merge_sort(arr);
        merge_comp_cnt += mcc3, merge_assign_cnt += mac3;
        for (int _ = 0; _ < 3; ++_) {
            for (auto &val: arr) val = num_dist(rng);
            temp_arr = arr;
            auto [icc4, iac4] = insertion_sort(temp_arr);
            insert_comp_cnt += icc4, insert_assign_cnt += iac4;
            temp_arr = arr;
            auto [mcc4,mac4] = merge_sort(temp_arr);
            merge_comp_cnt += mcc4, merge_assign_cnt += mac4;
        }
        cout << sz << " " << insert_comp_cnt / 6 << " " << insert_assign_cnt / 6 << " " << merge_comp_cnt / 6 << " " <<
                merge_assign_cnt / 6 << "\n";
    }
    return 0;
}
