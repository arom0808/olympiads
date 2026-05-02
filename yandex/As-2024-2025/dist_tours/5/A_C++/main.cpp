#include <iostream>
#include <list>

using namespace std;
using ll = int64_t;

list<int> deq;
list<int>::iterator sec_start = deq.end(), median = deq.end();
int med_cnt_left = 0, med_cnt_right = 0;
bool med_beq_sec_start = true;
int next_user_id = 1;

void shift_median_left() {
    if (median == sec_start) med_beq_sec_start = false;
    --med_cnt_left, ++med_cnt_right;
    --median;
}

void shift_median_right() {
    ++med_cnt_left, --med_cnt_right;
    ++median;
    if (median == sec_start) med_beq_sec_start = true;
}

void correct_median_pos() {
    if (med_cnt_left > med_cnt_right) shift_median_left();
    else if (med_cnt_right - med_cnt_left >= 2) shift_median_right();
}

void proc_a() {
    deq.insert(sec_start, next_user_id++);
    if (med_beq_sec_start) ++med_cnt_left;
    else ++med_cnt_right;
    correct_median_pos();
}

void proc_b() {
    deq.insert(sec_start, next_user_id++);
    if (med_beq_sec_start) ++med_cnt_left;
    else ++med_cnt_right;
    correct_median_pos();
    --sec_start;
    if (median == sec_start) med_beq_sec_start = true;
}

void proc_A() {
    if (deq.size() % 2 != 0) shift_median_right();
    cout << deq.front() % 10;
    deq.pop_front();
    --med_cnt_left;
}

void proc_B() {
    if (deq.size() == 1) shift_median_right(), --med_cnt_left;
    else if (deq.size() % 2 == 0) shift_median_left(), --med_cnt_right;
    else --med_cnt_right;
    if (next(sec_start) == deq.end()) {
        if (median == sec_start) med_beq_sec_start = false;
        ++sec_start;
    }
    cout << deq.back() % 10;
    deq.pop_back();
}

void proc_fc() {
    sec_start = deq.begin();
    med_beq_sec_start = true;
}

void proc_sc() {
    sec_start = deq.end();
    med_beq_sec_start = median == sec_start;
}

void proc_fo() {
    sec_start = median;
    med_beq_sec_start = true;
}

void proc_so() {
    if (deq.size() % 2 == 0) {
        sec_start = median;
        med_beq_sec_start = true;
    } else {
        sec_start = next(median);
        med_beq_sec_start = false;
    }
}

void solve() {
    int n;
    cin >> n;
    char c;
    for (int i = 0; i < n; ++i) {
        cin >> c;
        if (c == 'a') proc_a();
        else if (c == 'b') proc_b();
        else if (c == 'A') proc_A();
        else if (c == 'B') proc_B();
        else if (c == '>') proc_fc();
        else if (c == ']') proc_sc();
        else if (c == '<') proc_fo();
        else if (c == '[') proc_so();
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r",stdin);
    freopen("output.txt", "w",stdout);
#endif
    solve();
    return 0;
}
