#include <cstdio>

using uint32_t = unsigned int;
using int32_t = int;
// int32_t max_gr_seq_size = 0;
//
// uint64_t stupid(int32_t n, uint32_t a0) {
//     vector<uint32_t> a(n);
//     a[0] = a0;
//     for (int32_t i = 1; i < n; ++i) a[i] = a[i - 1] * 214013u + 2531011u;
//     vector<int32_t> left_lower(n), gr_seq;
//     gr_seq.push_back(-1);
//     for (int32_t i = 0; i < n; ++i) {
//         while (gr_seq.size() > 1 && a[gr_seq.back()] >= a[i]) gr_seq.pop_back();
//         left_lower[i] = gr_seq.back();
//         gr_seq.push_back(i);
//         if (gr_seq.size() > max_gr_seq_size)max_gr_seq_size = gr_seq.size();
//     }
//     vector<int32_t> right_lower(n), l_seq;
//     l_seq.push_back(n);
//     for (int32_t i = n - 1; i >= 0; --i) {
//         while (l_seq.size() > 1 && a[l_seq.back()] >= a[i]) l_seq.pop_back();
//         right_lower[i] = l_seq.back();
//         l_seq.push_back(i);
//     }
//     uint64_t res = 0;
//     for (int32_t i = 0; i < n; ++i) res += right_lower[i] - left_lower[i] - 1;
//     return res;
// }

struct Poss {
    int32_t pos = -1, left_pos = -2, right_pos = -2;
};

unsigned long long ans = 0;
uint32_t gr_seq[100], gre_seq[100];
int32_t gr_poss[100], gre_poss[100];
Poss res_poss[200];
int32_t gr_size = 0, gre_size = 0, res_poss_size = 0;

void erase_pos(int32_t i) {
    for (int32_t j = i; j + 1 < res_poss_size; ++j) res_poss[j] = res_poss[j + 1];
    --res_poss_size;
}

void add_left_pos(int32_t pos, int32_t left_pos) {
    for (int32_t i = 0; i < res_poss_size; ++i) {
        if (res_poss[i].pos == pos) {
            ans += res_poss[i].right_pos - left_pos - 1;
            erase_pos(i);
            return;
        }
    }
    res_poss[res_poss_size++] = Poss{pos, left_pos, -2};
}

void add_right_pos(int32_t pos, int32_t right_pos) {
    for (int32_t i = 0; i < res_poss_size; ++i) {
        if (res_poss[i].pos == pos) {
            ans += right_pos - res_poss[i].left_pos - 1;
            erase_pos(i);
            return;
        }
    }
    res_poss[res_poss_size++] = Poss{pos, -2, right_pos};
}

void push_back(uint32_t *seq, int32_t *poss, int32_t &size, uint32_t val, int32_t pos) {
    seq[size] = val;
    poss[size] = pos;
    ++size;
}

void pop_back(int32_t &size) {
    --size;
}

template<typename T>
T back(T *arr, int32_t size) {
    return arr[size - 1];
}

int main() {
    int32_t n;
    uint32_t a0;
    scanf("%d %u", &n, &a0);
    push_back(gr_seq, gr_poss, gr_size, 0u - 1u, -1);
    uint32_t a = a0;
    for (int32_t i = 0; i < n; ++i) {
        while (gr_size > 1 && back(gr_seq, gr_size) <= a) pop_back(gr_size);
        while (gre_size > 0 && back(gre_seq, gre_size) < a) {
            add_right_pos(back(gre_poss, gre_size), i);
            pop_back(gre_size);
        }
        add_left_pos(i, back(gr_poss, gr_size));
        push_back(gr_seq, gr_poss, gr_size, a, i);
        push_back(gre_seq, gre_poss, gre_size, a, i);
        a = a * 214013u + 2531011u;
    }
    while (gre_size > 0) {
        add_right_pos(back(gre_poss, gre_size), n);
        pop_back(gre_size);
    }
    printf("%lld", ans);
    return 0;
}
