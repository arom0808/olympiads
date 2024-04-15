#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <algorithm>
#include <limits>
#include <stack>

using namespace std;

int max_circle_subarray_sum(const vector<int> &arr) {
    int whole_sum = 0, max_sum = 0, max_now_ends_sum = 0, min_sum = 0, min_now_ends_sum = 0;
    for (auto el: arr) {
        whole_sum += el;
        max_now_ends_sum = max(max_now_ends_sum + el, el);
        max_sum = max(max_sum, max_now_ends_sum);
        min_now_ends_sum = min(min_now_ends_sum + el, el);
        min_sum = min(min_sum, min_now_ends_sum);
    }
    return max(max_sum, whole_sum - min_sum);
}

int min_miss_natural(const vector<int> &arr) {
    int left = 1, right = arr.size() + 1;
    while (left < right) {
        int mid = (left + right) / 2, le_mid_cnt = 0;
        for (auto el: arr) if (el <= mid) ++le_mid_cnt;
        if (le_mid_cnt < mid) right = mid;
        else left = mid + 1;
    }
    return left;
}

bool find_k_in_matrix(const vector<vector<int>> &matrix, int si, int ei, int sj, int ej, int num, int &ai, int &aj) {
    if (si >= ei || sj >= ej || matrix[si][sj] > num || matrix[ei - 1][ej - 1] < num) return false;
    auto mi = (si + ei) / 2, mj = (sj + ej) / 2;
    if (matrix[mi][mj] == num) {
        ai = mi, aj = mj;
        return true;
    } else if (num < matrix[mi][mj]) {
        if (find_k_in_matrix(matrix, si, ei, sj, mj, num, ai, aj)) return true;
        if (find_k_in_matrix(matrix, si, mi, mj, ej, num, ai, aj)) return true;
    } else {
        if (find_k_in_matrix(matrix, si, ei, mj + 1, ej, num, ai, aj)) return true;
        if (find_k_in_matrix(matrix, mi + 1, ei, sj, mj + 1, num, ai, aj)) return true;
    }
    return false;
}

template<typename T>
T find_dominant_element(const vector<T> &arr) {
    T candidate;
    int count = 0;
    for (const auto &el: arr) {
        if (count == 0) candidate = el, ++count;
        else if (el == candidate) ++count;
        else --count;
    }
    return candidate;
}

void find_neighbours_smaller_elements(const vector<int> &arr, vector<int> &res_left, vector<int> &res_right) {
    res_left.assign(arr.size(), -1), res_right.assign(arr.size(), -1);
    stack<int> stack_le, stack_l;
    for (int i = 0; i < arr.size(); ++i) {
        while (!stack_le.empty() && arr[stack_le.top()] >= arr[i]) {
            stack_le.pop();
        }
        while (!stack_l.empty() && arr[stack_l.top()] > arr[i]) {
            res_right[stack_l.top()] = i;
            stack_l.pop();
        }
        if (!stack_le.empty()) res_left[i] = stack_le.top();
        stack_l.push(i);
        stack_le.push(i);
    }
}

void find_max_submatrix(const vector<vector<int>> &matrix, int &aib, int &aie, int &ajb, int &aje) { // i: [aib, aie), j: [ajb, aje)
    aib = aie = ajb = aje = 0;
    if (matrix.empty() || matrix.front().empty()) return;
    int n = matrix.size(), m = matrix.front().size();
    int max_sum = numeric_limits<int>::min();
    vector<int> row_sums(n);
    for (int left_j = 0; left_j < m; ++left_j) {
        for (auto &el: row_sums) el = 0;
        for (int right_j = left_j; right_j < m; ++right_j) {
            int cur_max = numeric_limits<int>::min(), cur_max_now_ends = numeric_limits<int>::min(), cur_top = 0, best_top = 0, best_bottom = 0;
            for (int i = 0; i < n; ++i) {
                row_sums[i] += matrix[i][right_j];
                if (cur_max_now_ends < 0) cur_top = i, cur_max_now_ends = row_sums[i];
                else cur_max_now_ends = cur_max_now_ends + row_sums[i];
                if (cur_max_now_ends > cur_max) cur_max = cur_max_now_ends, best_top = cur_top, best_bottom = i + 1;
            }
            if (cur_max > max_sum)
                max_sum = cur_max, aib = best_top, aie = best_bottom, ajb = left_j, aje = right_j + 1;
        }
    }
}

void reverse_array(vector<int> &array, int start, int end) {
    while (start < end) {
        swap(array[start], array[end]);
        ++start, --end;
    }
}

void swap_els(vector<int> &array, int n) {
    int m = array.size() - n;
    reverse_array(array, 0, n - 1);
    reverse_array(array, n, array.size() - 1);
    reverse_array(array, 0, array.size() - 1);
}

int main() {
    vector<int> array{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    swap_els(array, 5);
    for (auto el: array) cout << el << " ";
    return 0;
}
