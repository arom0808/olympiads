#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")

#include <iostream>
#include <unordered_set>
#include <deque>
#include <algorithm>

using namespace std;

uint64_t transform_arr(const string &str) {
    uint64_t res = 0;
    for (auto c: str) {
        if (c != 'X') res <<= 1;
        if (c == 'P') res |= 1ull;
    }
    res <<= 5;
    res |= str.find('X');
    return res;
}

uint64_t sorted_trans_arr(const string &str) {
    uint64_t c_cnt = count(str.begin(), str.end(), 'C'), p_cnt = count(str.begin(), str.end(), 'P');
    return (((1ull << p_cnt) - 1) << 5) | c_cnt;
}

uint32_t n;

inline uint64_t first_left_trans(uint64_t val) {
    if ((val & ((1ull << 5) - 1)) > 0) return val - 1;
    else return 0;
}

inline uint64_t first_right_trans(uint64_t val) {
    if ((val & ((1ull << 5) - 1)) < n) return val + 1;
    else return 0;
}

inline uint64_t second_left_trans(uint64_t val) {
    uint64_t x_pos = (val & ((1ull << 5) - 1));
    if (x_pos < 2) return 0;
    if ((((val >> 5) >> (n - x_pos)) ^ ((val >> 5) >> (n - x_pos + 1))) & 1ull)
        return (val ^ (3ull << (5 + n - x_pos))) - 2;
    else return 0;
}

inline uint64_t second_right_trans(uint64_t val) {
    uint64_t x_pos = (val & ((1ull << 5) - 1));
    if (x_pos + 2 > n) return 0;
    if ((((val >> 5) >> (n - x_pos - 2)) ^ ((val >> 5) >> (n - x_pos - 1))) & 1ull)
        return (val ^ (3ull << (5 + n - x_pos - 2))) + 2;
    else return 0;
}

bool used[1ull << 26];

int main() {
//    unordered_set<uint64_t> used;
    string str;
    cin >> n >> str;
    deque<uint64_t> deq, next_deq;
    uint64_t start_pos = transform_arr(str), finish_pos = sorted_trans_arr(str);
    used[start_pos] = true;
    deq.push_back(start_pos);
    uint32_t res = 0;
    uint64_t temp[4];
    while (!used[finish_pos]) {
        while (!deq.empty()) {
            auto val = deq.front();
            deq.pop_front();
            temp[0] = first_left_trans(val), temp[1] = first_right_trans(val),
            temp[2] = second_left_trans(val), temp[3] = second_right_trans(val);
            for (auto el: temp)
                if (el != 0 && !used[el])
                    used[el] = true, next_deq.push_back(el);
        }
        next_deq.swap(deq);
        ++res;
    }
    cout << res;
}